# Friction Test on Gazebo   
A package for ROS  
##
In a terminal,
```
>> catkin_make
```
To build the package, then
```
>> roslaunch gazebo_ros empty_world.launch
```
To starts gazebo simulator with empty world.

In another shell,
```
>> rosrun gazebo_ros spawn_model -file `rospack find gazebo_friction_test`/urdf/friction_cube.urdf -urdf -z 0.125 -model cube1
>> rosrun gazebo_ros spawn_model -file `rospack find gazebo_friction_test`/urdf/friction_cube_fdirchanged.urdf -urdf -y 1 -z 0.125 -model cube2

```
To spawn the model

```
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: cube1, pose: {position: {x: 0, y: 0, z: 0.125}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: 5, y: 0, z: 0}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
>> rostopic pub -1 /gazebo/set_model_state gazebo_msgs/ModelState '{model_name: cube2, pose: {position: {x: 0, y: 1, z: 0.125}, orientation: {x: 0, y: 0, z: 0, w: 1}}, twist: {linear: {x: 5, y: 0, z: 0}, angular: { x: 0, y: 0, z: 0}}, reference_frame: world}'
```
to see the models slide on the ground.
Those 2 model has same surface parameters except 'fdir'. However the distance passed was different and it is result of different fdir which determines the orientation of coulumb friction pyramid.