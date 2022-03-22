# billiard   
A package for ROS  

##
In a shell,
```
>> cd ~/catkin_ws
>> export GAZEBO_RESOURCE_PATH=~/catkin_ws/src/billiard:$GAZEBO_RESOURCE_PATH
>> catkin_make
>> roscore
```
In another shell,
```
>> roslaunch billiard makeBilliard.launch
```
In another shell,
```
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: ball_0, pose: {position: {x: 5, y: -1, z: 0.491}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: -20, y: 0, z: 0}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
```
