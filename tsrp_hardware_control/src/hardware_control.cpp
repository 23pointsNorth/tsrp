#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "hardware_control");
	if (!ros::master::check())
	{
		ROS_ERROR("[HARDWARE_CONTROL] Cannot detect ROS master!");
		return 1;
	}
	ROS_INFO("Subscribing and Advertising.");
	ros::NodeHandle* node = new ros::NodeHandle();	

	ros::Rate refresh(20); //20Hz

	while(ros::ok())
	{
		ros::spinOnce();

		motor_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}
