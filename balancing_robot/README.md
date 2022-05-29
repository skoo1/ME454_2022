# balancing_robot
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
>> roslaunch balancing_robot launch_two_wheel_robot_effort.launch
```
In another shell,
```
>> python ~/catkin_ws/src/balancing_robot/src/dqn_train_effort.py
```

I could NOT train the Deep RL controller with effort controller successfully. There was a bit of training effects but it was not satisfactory.  
When I tried to switch the effort controller to a jointvelocitycontroller (PID to effort), the urdf model behaved strangely in gazebo.  


## Acknowledgements
### The pytorch-based DQN RL routine is brought from "https://github.com/seungeunrho/minimalRL"
