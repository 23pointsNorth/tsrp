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
	ROS_INFO("[MOTOR_CONTROL] Initializing GPIO pins...");
	if (!GPIOpin::InitializeGPIOpin())
	{
		ROS_ERROR("[MOTOR_CONTROL] Failed to initialize GPIO pins.");
		return 1;
	}
	GPIOpin dir(17, "direction", OUTPUT, HIGH);
	GPIOpin speed(18, "speed", OUTPUT, LOW);
	ROS_INFO("[MOTOR_CONTROL] Generating square wave.");

	while(ros::ok())
	{
		ros::spinOnce();
		
		speed.ToggleOutput(); // Create a square wave 50% filled.

		motor_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}
