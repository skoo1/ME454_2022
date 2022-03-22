# Pendulum Tutorial   
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
>> rosrun gazebo_ros spawn_model -file `rospack find pendulum_tutorial`/urdf/pendulum.urdf -urdf -model pendulum
>> rosrun gazebo_ros spawn_model -file `rospack find pendulum_tutorial`/urdf/pendulum_horizon.urdf -urdf -model pendulum_ horizon

```
In another shell,
```
>> rosservice call /gazebo/apply_joint_effort "{joint_name: 'pendulum_horizon::pendulum_joint', effort: 30, start_time: {secs: 0, nsecs: 0}, duration: {secs: 1, nsecs: 0}}"

```
to apply joint torque,
