#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/image_encodings.h>

unsigned long long frame_id = 0;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "video_streamer");
	if (!ros::master::check())
	{
		ROS_ERROR("[VIDEO_STREAMER] Cannot detect ROS master!");
		return 1;
	}
	ROS_INFO("[VIDEO_STREAMER] Subscribing and Advertising.");
	ros::NodeHandle* node = new ros::NodeHandle();	
	ros::Publisher img_pub = node->advertise<sensor_msgs::Image>("webcam_stream", 1);
	ros::Rate img_refresh(30); //30Hz
	sensor_msgs::Image img;
	
	cv::VideoCapture webcam_cap;

	webcam_cap.open(0);
	cv::Mat frame;

	while(ros::ok())
	{
		ros::spinOnce();
		webcam_cap >> frame;
		frame_id++;
		if (!frame.data) ROS_ERROR("[VIDEO_STREAMER] Wrong frame.");

		//Generate image
		img.encoding = sensor_msgs::image_encodings::RGB8;
		img.height = frame.rows;
		img.width  = frame.cols;
		img.step   = img.width * 3; //image stride in bytes

		int data_len = img.step * img.height;
		img.data.resize(data_len);
		img.is_bigendian = 0;

		//Load data into msg
		int msg_idx, buf_idx;
		for(unsigned int i = 0; i < img.height; i++)
		{
			for(unsigned int j = 0; j < img.step; j++)
			{
				msg_idx = (img.height - i - 1) * img.step + j;
				buf_idx = i * img.step + j;
				img.data[msg_idx] = (unsigned char)(frame.data[buf_idx]);
			}
		}

		//Publish image
		img_pub.publish(img);

		img_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}

