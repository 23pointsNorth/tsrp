#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int32.h>

bool img_received = false;
cv::Mat img;

void imageReceivedCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // display the image
	img = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8)->image;
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
