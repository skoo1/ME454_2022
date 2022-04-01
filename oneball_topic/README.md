# oneball topic listener Tutorial   
A package for ROS  

##
In a shell,
```
>> catkin_make
>> roscore
```
In another shell,
```
>> roslaunch gazebo_ros empty_world.launch
```
>> source ~/catkin_ws/devel/setup.bash
# Spawn a ball in gazebo
>> rosrun gazebo_ros spawn_model -file `rospack find oneball_urdf`/urdf/oneball.urdf -urdf -z 1 -model oneball

# Throw the ball in gazebo
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: oneball, pose: {position: {x: 0, y: 0, z: 0.1}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: 0, y: 10, z: 10}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'  
  
In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun oneball_topic listener
```
In another shell,
```
  
we can check its z position like this.  
```
>> rostopic echo /gazebo/model_states/pose[1]/position/z

```


