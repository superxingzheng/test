/*
 * Updated on: Aug.28,2017
 * Updated by: Zheng Xing <zxing@robohome.org>
 *
 * Tested with ROS Kinetic, Gazebo 7.0.0 and Catkin Tools 0.4.4
 * 
 * Reference:
 * 1. http://docs.ros.org/jade/api/gazebo_msgs/html/index-msg.html
 * 2. http://wiki.ros.org/roscpp/Overview/Services
 * 3. http://gazebosim.org/tutorials/?tut=ros_comm
 * 
 */
#include <iostream>
#include <ros/ros.h>

#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>

int main(int argc, char** argv) {
	using namespace std;
	ros::init(argc, argv, "learning_simulation_node");
	ros::NodeHandle nh;
	
	ros::ServiceClient setter_client = nh.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");
	ros::ServiceClient getter_client = nh.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
	
	gazebo_msgs::GetModelState getter;
	getter.request.model_name = "mybot1";

	if (getter_client.call(getter)) {
		ROS_INFO("Model state got successfully.");
		double x = getter.response.pose.position.x;
		double y = getter.response.pose.position.y;
		double z = getter.response.pose.position.z;
		cout << "x = " << x << endl;
		cout << "y = " << y << endl;
		cout << "z = " << z << endl;
	} else {
		ROS_ERROR("Failed to get model state: %s",
				getter.response.status_message.c_str());
	}
	
	geometry_msgs::Point position;
	position.x = 0.0;
	position.y = 0.0;
	position.z = 0.0;
	
	geometry_msgs::Quaternion orientation;
	orientation.x = 0.0;
	orientation.y = 0.0;
	orientation.z = 0.0;
	orientation.w = 1.0;
	
	geometry_msgs::Pose pose;
	pose.position = position;
	pose.orientation = orientation;
	
	gazebo_msgs::ModelState model_state;
	model_state.model_name = "mybot1";
	model_state.pose = pose;
	
	gazebo_msgs::SetModelState setter;
	setter.request.model_state = model_state;
	
	if (setter_client.call(setter)) {
		ROS_INFO("Model state set successfully.");
	} else {
		ROS_ERROR("Failed to set model state: %s", setter.response.status_message.c_str());
	}
	
	return 0;
}
