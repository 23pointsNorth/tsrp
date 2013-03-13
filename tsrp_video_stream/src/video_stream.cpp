#include <ros/ros.h>
#include <sensor_msgs/Image.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "video_stream");
	if (!ros::master::check())
	{
		ROS_ERROR("[VIDEO_STREAM] Cannot detect ROS master!");
		return 1;
	}
	ROS_INFO("[VIDEO_STREAM] Subscribing and Advertising.");
	ros::NodeHandle* node = new ros::NodeHandle();	

	ros::Rate img_refresh(30); //30Hz

	while(ros::ok())
	{
		ros::spinOnce();

		img_refresh.sleep();
	}
	
	ros::shutdown();
	return 0;
}

