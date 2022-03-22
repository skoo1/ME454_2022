# oneball_urdf  
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
>> roslaunch gazebo_ros empty_world.launch
```
In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
# Spawn a ball in gazebo
>> rosrun gazebo_ros spawn_model -file `rospack find oneball_urdf`/urdf/oneball.urdf -urdf -z 1 -model oneball
# See model state in gazebo
>> rosservice call /gazebo/get_model_state '{model_name: oneball}'
# See model properties in gazebo
>> rosservice call /gazebo/get_model_properties '{model_name: oneball}'
# Throw the ball in gazebo
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: oneball, pose: {position: {x: 0, y: 0, z: 0.1}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: 0, y: 10, z: 10}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
```
