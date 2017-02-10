#ifndef PHIDGETS_IK_IK_ROS_I_H
#define PHIDGETS_IK_IK_ROS_I_H

#include <ros/ros.h>
#include <phidgets_api/ik.h>

namespace phidgets {

class IKRosI : public IK 
{

  public:

    IKRosI(ros::NodeHandle nh, ros::NodeHandle nh_private);

  private:

    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    void initDevice();
    void sensorHandler(int index, int sensorValue);
};

} //namespace phidgets

#endif // PHIDGETS_IK_IK_ROS_I_H
