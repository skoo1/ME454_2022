#include "ros/ros.h"
#include "gazebo_msgs/ModelStates.h"
#include "std_msgs/Float32.h"
#include <string>

class EnergySP
{
public:
  EnergySP(std::string const &inputmodelName)
  {
    pub_potential_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/potential", 1);
    pub_kinetic_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/kinetic", 1);
    pub_mechanical_ = n_.advertise<std_msgs::Float32>("/gazebo_energy_tutorial/mechanical", 1);
    sub_ = n_.subscribe("/gazebo/model_states", 1, &EnergySP::callback, this);
    knowIndexOfModels = false;
    ModelIndex = 0;
    modelName = inputmodelName;
  }

  void callback(const gazebo_msgs::ModelStates::ConstPtr& msg)
  {

    if(!knowIndexOfModels){
        for(ModelIndex = 0;ModelIndex < (msg->name).size(); ModelIndex++){
            // ROS_INFO("ModelIndex : %d",ModelIndex);
            // ROS_INFO("(msg->name).size() : %lu",(msg->name).size());

            // ROS_INFO("%d",strcmp(msg->name[ModelIndex].c_str(), modelName.c_str()));
            if(strcmp(msg->name[ModelIndex].c_str(), modelName.c_str()) == 0){
                knowIndexOfModels = true;
                // ROS_INFO("right index : %d",ModelIndex);
                return;
            }
        }               
        ROS_INFO("could not find %s",modelName.c_str());
        return;
    }

    std_msgs::Float32 output_kinetic, output_potential, output_mechanical;
    output_potential.data = 9.81 * msg->pose[ModelIndex].position.z;
    pub_potential_.publish(output_potential);
    output_kinetic.data = 0.5 * msg->twist[ModelIndex].linear.z * msg->twist[ModelIndex].linear.z;
    pub_kinetic_.publish(output_kinetic);
    output_mechanical.data = 9.81 * msg->pose[ModelIndex].position.z + 0.5 * msg->twist[ModelIndex].linear.z * msg->twist[ModelIndex].linear.z;
    pub_mechanical_.publish(output_mechanical);
  }

private: 
  ros::NodeHandle n_; 
  ros::Publisher pub_potential_;
  ros::Publisher pub_kinetic_;
  ros::Publisher pub_mechanical_;
  ros::Subscriber sub_;
  bool knowIndexOfModels;
  int ModelIndex;
  std::string modelName;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gazebo_energy_tutorial");
  std::string modelName(argv[1]);
  ROS_INFO("%s",modelName.c_str());

  EnergySP EnergySPObject(modelName); // We know the model name in gazebo is ball
  ros::spin();
  return 0;
}
