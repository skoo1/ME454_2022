# mass and inertia
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
1. mass and translation test

In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun gazebo_ros spawn_model -file `rospack find massAndInertia`/urdf/box_translation.urdf -urdf -model box_translation

```
In another shell,
```
>> rosservice call /gazebo/apply_body_wrench "{body_name: 'box_translation::link_box', wrench: { force: { x: 0, y: -1 , z: 0 } }, start_time: {secs: 0, nsecs: 0}, duration: {secs: 2, nsecs: 0}"
```
to apply Force with time duration,  

##
2. inertia and rotation test

In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun gazebo_ros spawn_model -file `rospack find massAndInertia`/urdf/box_rotation.urdf -urdf -model box_rotation

```
In another shell,
```
>> rosservice call /gazebo/apply_body_wrench "{body_name: 'box_rotation::link_box', wrench: { torque: { x: 0, y: 0 , z: 0.5 } }, start_time: {secs: 0, nsecs: 0}, duration: {secs: 10, nsecs: 0}}"

```
to apply Force with time duration
