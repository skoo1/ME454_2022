# bowling   
A package for ROS  

##
In a shell,
```
>> cd ~/catkin_ws
>> catkin_make
>> source ~/catkin_ws/devel/setup.bash
>> roscore
```
In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> roslaunch bowling makeBowling.launch
```
In another shell,
```
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: bowl, pose: {position: {x: 7, y: -1, z: 0.991}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: -10, y: 0, z: 0}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
```
