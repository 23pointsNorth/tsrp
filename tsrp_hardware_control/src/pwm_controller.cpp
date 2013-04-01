#include "pwm_controller.h"

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt32.h>

PWMController::PWMController(int argc, char *argv[], std::string _name, GPIOpin* _dir, GPIOpin* _pwm, long _update_freq, double _duty_cycle)
{
	std::string node_name = "pwm_controller_";
	node_name += _name;
	ros::init(argc, argv, node_name);
	if (!ros::master::check())
	{
		std::string error_msg = "[";
		error_msg += node_name; error_msg += "] Cannot detect ROS master";
		ROS_ERROR(error_msg.c_str());
	}

	node = new ros::NodeHandle();	

	std::string duty_cycle_subname = "pwm_duty_cycle_"; duty_cycle_subname += _name;
	ros::Subscriber duty_cycle_sub = node->subscribe(duty_cycle_subname.c_str(), 10, &PWMController::new_duty_cycle_callback, this);

	std::string freq_subname = "pwm_freq_"; freq_subname += _name;
	ros::Subscriber freq_sub = node->subscribe(freq_subname.c_str(), 10, &PWMController::new_freq_callback, this);

	name = _name;
	dir = _dir;
	pwm = _pwm;
	period_s = ((1.0) / _update_freq);
	duty_cycle = _duty_cycle;
}

void PWMController::new_duty_cycle_callback(const std_msgs::Float32& msg)
{
	duty_cycle = msg.data;
}

void PWMController::new_freq_callback(const std_msgs::UInt32& msg)
{
	period_s = ((1.0) / msg.data);
}

PWMController::~PWMController() 
{
	ros::shutdown();
}

void PWMController::Start()
{
	stop = false;
	//Start a new thread with PWMCycle
}

void PWMController::Stop()
{
	stop = true;
}

void PWMController::PWMCycle()
{
	ros::Rate period((1)/period_s); 

	while(ros::ok() && (!stop))
	{
		ros::spinOnce();
		
		pwm->SetOutput(HIGH);
		ros::Duration(period_s * duty_cycle).sleep();
		
		pwm->SetOutput(LOW);
		ros::Duration(period_s * (1 - duty_cycle)).sleep();
		
		period.sleep();
	}

}