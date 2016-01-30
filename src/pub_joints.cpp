// This program will publish joint states

#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  double max_angle = 1.57, min_angle= -1.57;
  ros::init(argc, argv, "publish_joint_states");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<trajectory_msgs::JointTrajectory>("/joint_controller_1/command", 1000);

  ros::Rate rate(0.5);
  while(ros::ok())
  {
  	 trajectory_msgs::JointTrajectory msg;

  	 msg.joint_names.resize(1);  	 
  	 msg.joint_names[0] = "joint_2";

  	 double a_random_double = (double)rand() / RAND_MAX;
  	 a_random_double = min_angle + a_random_double * (max_angle - min_angle);

	   msg.points.resize(1);
  	 msg.points[0].positions.resize(1);
  	 msg.points[0].positions[0] = a_random_double;

  	 msg.points[0].velocities.resize(1);
     msg.points[0].velocities[0] = 0.5;

	   msg.points[0].accelerations.resize(1);
  	 msg.points[0].accelerations[0] = 0.0;

	   msg.points[0].effort.resize(1);
  	 msg.points[0].effort[0] = 0.0;
  	 //msg.points[0].time_from_start->secs = 0;
  	 //msg.points[0].time_from_start->nsecs = 0;
  	 //ROS_INFO_STREAM("Sending... position 3");
  	 pub.publish(msg);

  	 ROS_INFO_STREAM("Sending... position"<<  msg.joint_names[0]);

  	 rate.sleep();
  	}


return 0;

}