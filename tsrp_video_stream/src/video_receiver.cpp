#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/image_encodings.h>

bool img_received = false;
cv::Mat img;

void imageReceivedCallback(const sensor_msgs::Image& msg)
{
  	ROS_INFO("[VIDEO_RECEIVER] Image received. Converting...");
	//Create an empty image
	img = cv::Mat(msg.height, msg.width, CV_8UC3);
	//Load data to image
	int msg_idx, buf_idx;
	for(unsigned int i = 0; i < msg.height; i++)
	{
		for(unsigned int j = 0; j < msg.step; j++)
		{
			msg_idx = (msg.height - i - 1) * msg.step + j;
			buf_idx = i * msg.step + j;
			img.data[buf_idx] = msg.data[msg_idx];
		}
	}

	img_received = true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "video_receiver");
	if (!ros::master::check())
	{
		ROS_ERROR("[VIDEO_RECEIVER] Cannot detect ROS master!");
		return 1;
	}
	ROS_INFO("[VIDEO_RECEIVER] Subscribing and Advertising.");
	ros::NodeHandle* node = new ros::NodeHandle();	
	ros::Subscriber img_sub = node->subscribe("webcam_stream", 1, imageReceivedCallback);

	ros::Rate img_refresh(30); //30Hz

	while(ros::ok())
	{
		ros::spinOnce();
		if (img_received)
		{
			cv::imshow("Image", img);
	
			img_received = false;
			cv::waitKey(5);
		}

		img_refresh.sleep();
	}

	ros::shutdown();
	return 0;
}
