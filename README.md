# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

[//]: # (Image References)
[image1]: ./report/pic.png "PID"
[image2]: ./report/block-diagram.png "PID Diagram"
[image3]: ./report/formula.png "PID Formula"
[image4]: ./report/graph.png "PID Graph"


This project is about implementing PID and discussing what is a PID.
![alt text][image1]
PID means three things : 
* Proportional
* Derivative
* Integral

The PID block diagram can help to figure out.

![alt text][image3]

In the self-driving car we are trying to implement, we put a PID regulator to output the steering angle.
A PID simply means that we look at an error and are trying to minimize it. I refer you to [a project](https://github.com/Jeremy26/behavioral-cloning) where we also want to predict a steering angle with Deep Learning. 

Predicting the angle is this time done with robotics. The behavioral cloning project above had a PID to drive the car (move forward) but not to predict the angle.

Looking at the formula and the following graph, we can comment a few things.

![alt text][image3]
![alt text][image4]

We have a reference line in red we want to follow, and we have robotics and math formulas to follow it. The goal for a self-driving car is to stay in the center of the line. Now suppose we know where the center of the line is, maybe we used Deep Learning or Computer Vision to find out. I can send you to [this project](https://github.com/Jeremy26/advanced-lane-lines) where we output the distance to the center of the road.
The distance is this time called Cross Track Error. Our goal is to minimize it.

The formula above has a sum of all three components.
* The Proportional component is how we oscillates. This component steers the car proporionally to the CTE to get back to the center of the road. Unfortunately and as observed in the graph above, this controller alone will make the car oscillate around the center without ever going straight. We can see that this looks at the derivative of the CTE over time elapsed.
* The Derivative component is here to compensate these oscillations. A PD Controller is a good implementation but has a bias due to real life conditions. This bias can prevent the robot to go back to the center.
* The Integral component is here to make a sum of the errors and go back to the center, to compensate the bias.

Now that we know what a PID is, let's look at the error parameters, the three Tau.
* Tp is small because we don't want the car to oscillate too much : *0.17*
* Ti is even smaller because we don't have a huge bias. *0.004*
* Td is huge because we want a big compensation to Tp. *3*
I chose Sebastian Thrun's initial component 0.2,0.004 and 3 and tweaked them all, this is a fine combination.
I did not implement Twiddle to find the parameters, having a parameter optimization algorithm would make the solution better.

Concerning the speed, I chose a small value of 35 mph that manages to keep the car on the road. If we get that speed higher, we would need a PID controller to adjust the throttle parameters. When we go at high speed, we don't need as much steering as when we drive slowly. This would need to be taken into account.

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

