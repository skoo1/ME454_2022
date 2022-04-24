# crankshaft
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
1. spawn crankshaft system

In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun gazebo_ros spawn_model -file `rospack find crankshaft`/urdf/crankshaft.urdf -urdf -model crankshaft -J first_joint 0.5 -J second_joint 1.5 -J third_joint 0.4

```

2. Apply torque for operating crankshaft system  

```
>> rosservice call /gazebo/apply_joint_effort "{joint_name: 'crankshaft::first_joint', effort: 10000, start_time: {secs: 0, nsecs: 0}, duration: {secs: 20, nsecs: 0}}"
```

##

