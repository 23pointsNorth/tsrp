#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

namespace enc = sensor_msgs::image_encodings;

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
		cv_bridge::CvImage cv_brdg_img;
		ros::Time time = ros::Time::now();
		cv_brdg_img.header.stamp = time;
		cv_brdg_img.header.frame_id = "frame_id";//frame_id;
		cv_brdg_img.encoding = sensor_msgs::image_encodings::BGR8;
		cv_brdg_img.image = frame;
		
		cv_brdg_img.toImageMsg(img);
		img.height = frame.rows;
		img.width  = frame.cols;
		img.is_bigendian = 0;

		//Publish image
		img_pub.publish(img);

		img_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}

