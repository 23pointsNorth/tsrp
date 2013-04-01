#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include <string>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt32.h>

#include "GPIOpin.h"

class PWMController
{
public:
	PWMController(int argc, char *argv[], std::string _name, GPIOpin* _dir, GPIOpin* _pwm, long _update_freq, double _duty_cycle);
	~PWMController();
	void Start();
	void Stop();

private:
	void PWMCycle();
	inline void new_duty_cycle_callback(const std_msgs::Float32& msg);
	inline void new_freq_callback(const std_msgs::UInt32& msg);
	
	ros::NodeHandle* node;
	bool stop;
	std::string name;
	GPIOpin* dir;
	GPIOpin* pwm;
	double period_s;
	double duty_cycle;
};

#endif /* PWM_CONTROLLER_H */