# vibration
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
0. translate urdf into sdf
>> go to urdf directory. 
   
>> gz sdf -p ./[].urdf > ./[].sdf

>> and please give your own property to your sdf file.

1. spawn spring damper system

In another shell,
```
>> source ~/catkin_ws/devel/setup.bash
>> rosrun gazebo_ros spawn_model -file `rospack find vibration`/urdf/vibration.sdf -sdf -model vibration 

```
>> you can give some initial condition with '-J joint_name joint_position'

##

