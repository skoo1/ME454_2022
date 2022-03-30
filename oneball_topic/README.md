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
In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun oneball_topic listener
```
In another shell,
```
>> rosservice call /gazebo/apply_joint_effort "{joint_name: 'pendulum_horizon::pendulum_joint', effort: 30, start_time: {secs: 0, nsecs: 0}, duration: {secs: 1, nsecs: 0}}"

```
to apply joint torque,
  
we can check its z position like this.  
```
>> rostopic echo /gazebo/model_states/pose[1]/position/z

```


