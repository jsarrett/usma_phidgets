#ifndef PHIDGETS_IK_IK_ROS_I_H
#define PHIDGETS_IK_IK_ROS_I_H

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <phidgets_api/ik.h>

namespace phidgets {

class IKRosI : public IK 
{

  public:

    IKRosI(ros::NodeHandle nh, ros::NodeHandle nh_private);

  protected:

    int n_in;
    int n_out;
    int n_sensors;
    ros::Publisher in_pubs_[16];
    ros::Publisher sensor_pubs_[16];

  private:

    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    void initDevice();
    void sensorHandler(int index, int sensorValue);
    void inputHandler(int index, int inputValue);
};

} //namespace phidgets

#endif // PHIDGETS_IK_IK_ROS_I_H
