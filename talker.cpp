#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gpm_msgs/BarcodeReaderState.h"
#include "GPM_LOG.cpp"

GPM_LOG LOG;
string topic_name;

void chatterCallback(const gpm_msgs::BarcodeReaderState& msg)
{
  ROS_INFO("BarcodeReader_State: \nstate:%d\ntagID:%d\nxValue:%f\nyValue:%f\ntheta:%f\n", msg.state,msg.tagID,msg.xValue,msg.yValue,msg.theta);

  int state = msg.state ;
  std::stringstream AllLogData;

  AllLogData  << "\nState" << " : " << state << "\ntagID" << " : " << msg.tagID << "\nxValue" << " : " 
  << msg.xValue << " \nyValue" << " : " << msg.yValue << "\nTheta" << " : " << msg.theta;

  LOG.systime(AllLogData.str()); 

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;
  ros::Rate loop_rate(1);

  LOG.CreateFolder();

  LOG.RemoveFolder();

  topic_name = "/barcodereader_state";  
  ros::Subscriber sub = n.subscribe(topic_name, 1000, chatterCallback);

  ros::spin();

  return 0;
}