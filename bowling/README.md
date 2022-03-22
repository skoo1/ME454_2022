# bowling   
A package for ROS  

##
In a shell,
```
>> cd ~/catkin_ws
>> export GAZEBO_RESOURCE_PATH=~/catkin_ws/src/bowling:$GAZEBO_RESOURCE_PATH
>> catkin_make
>> roscore
```
In another shell,
```
>> roslaunch bowling makeBowling.launch
```
In another shell,
```
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: bowl, pose: {position: {x: 7, y: -1, z: 0.991}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: -10, y: 0, z: 0}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
```