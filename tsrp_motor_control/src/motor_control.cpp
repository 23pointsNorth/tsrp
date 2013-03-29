#include <ros/ros.h>
#include <GPIOpin.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "motor_control");
	if (!ros::master::check())
	{
		ROS_ERROR("[MOTOR_CONTROL] Cannot detect ROS master!");
		return 1;
	}
	ROS_INFO("[MOTOR_CONTROL] Subscribing and Advertising.");
	ros::NodeHandle* node = new ros::NodeHandle();	

	ros::Rate motor_refresh(200); //200Hz

	GPIOpin dir(1, "direction");
	GPIOpin speed(1, "speed", OUTPUT, LOW);

	while(ros::ok())
	{
		ros::spinOnce();
		
		speed.ToggleOutput(); // Create a square wave 50% filled.

		motor_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}
