#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <sensor_msgs/JointState.h>
#include <stdlib.h>


class SubPubMoveIt
{
public:
  SubPubMoveIt()
  {
    // Topic to be published
    pub = nh.advertise<trajectory_msgs::JointTrajectory>("/joint_controller_1/command", 1000);  

    // Subscribe to this topic
    sub = nh.subscribe("/move_group/fake_controller_joint_states", 1000, &SubPubMoveIt::callback, this);
  }

  void callback(const sensor_msgs::JointState msg)
  {
  	trajectory_msgs::JointTrajectory output;
    output.joint_names.resize(6);     
    output.joint_names[0] = "base_pan";
  	output.joint_names[1] = "shoulder_tilt";
  	output.joint_names[2] = "elbow_tilt";
  	output.joint_names[3] = "wrist_tilt";
  	output.joint_names[4] = "wrist_rotate";     
    output.joint_names[5] = "gripper";   

  	output.points.resize(1);
  	output.points[0].positions.resize(6);

  	// Base_pan... GOOD
  	output.points[0].positions[0] = -1 * (msg.position[0] - 1.57);

    // Shoulder_tilt
    output.points[0].positions[1] = -1 * (msg.position[2] - 1.57);

    // Setting Elbow_tilt
  	output.points[0].positions[2] =  1 * (msg.position[1] - 1.57); // -0.52

    // Wrist Tilt, which is 5th element in msg
    output.points[0].positions[3] = -1 * (msg.position[4] - 1.57);  	

    // Wrist_rotate
    output.points[0].positions[4] = -1 * (msg.position[3] - 1.57);  	
  	
  	//Gripper, Not currently used in moveit
  	output.points[0].positions[5] = 0;


  	ROS_INFO("After setting output");
     
  	output.points[0].velocities.resize(6);
  	output.points[0].velocities[0] = 0.5;
  	output.points[0].velocities[1] = 0.5;
  	output.points[0].velocities[2] = 0.5;
  	output.points[0].velocities[3] = 0.5;
  	output.points[0].velocities[4] = 0.5;
    output.points[0].velocities[5] = 0.5;

  	pub.publish(output);
  }


private:
  ros::NodeHandle nh;	
  ros::Publisher pub;
  ros::Subscriber sub;
}; // end of class

int main(int argc, char **argv) 
{

  ros::init(argc, argv, "publish_joint_states");

  SubPubMoveIt spmObj;

  ros::spin();

  return 0;
}