# gazebo_energy_tutorial
An elastic collision simulation with bouncing ball in gazebo
See the mechanical energy preservation with calculating kinetic and potential energy.

##
Compile with cakin_make after adding this package in your catkin workspace
```
>> catkin_make
```
Before making a new gazebo simulation,
Make gazebo knows we are using custom world file and models and their location.
```
>> source /usr/share/gazebo/setup.sh
>> export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:/home/{your_home_directory}/catkin_ws/src/gazebo_energy_tutorial/world
>> export GAZEBO_RESOURCE_PATH=$GAZEBO_RESOURCE_PATH:/home/{your_home_directory}/catkin_ws/src/gazebo_energy_tutorial/world
```

1. Bouncy ball simulation

In another shell,
```
>> roslaunch gazebo_energy_tutorial empty_world_elastic.launch
```
In another shell,
```
>> rosrun gazebo_ros spawn_model -file `rospack find gazebo_energy_tutorial`/sdf/oneBouncyBall.sdf -sdf -z 5 -model ball
```
to simulate the elastic ground world and spawn the bouncy ball.

##
2. Energy publisher

In another shell,
```
>> rosrun gazebo_energy_tutorial energy_publisher ball
```
In another shell,
```
>> rqt
```
to see the published energy related topics

You can check 3 topics
```
/gazebo_energy_tutorial/kinetic,
/gazebo_energy_tutorial/mechanical,
/gazebo_energy_tutorial/potential

```
