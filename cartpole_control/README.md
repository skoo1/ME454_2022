# cartpole control
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
>> roslaunch cartpole_control cartpole.launch
```
In another shell,
```
>> python ~/catkin_ws/src/cartpole_control/src/dqn_train.py
```

## Acknowledgements
### urdf model is brought from "https://github.com/nav74neet/ppo_gazebo_tf" and modified
### The pytorch-based DQN RL routine is brought from "https://github.com/seungeunrho/minimalRL"
