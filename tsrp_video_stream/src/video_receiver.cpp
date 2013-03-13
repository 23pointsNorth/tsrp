#include <ros/ros.h>
#include <sensor_msgs/Image.h>

void imageReceivedCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // display the image
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "motor_control");
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

		img_refresh.sleep();
	}

	ros::shutdown();
	return 0;
}
