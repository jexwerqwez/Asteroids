---
layout: post
title: Introduction
excerpt_separator:  <!--more-->
---

The game Asteroids was developed as a project-technological practice 
on the course of object-oriented programming by a student at the 
Bauman Moscow State Technical University.

<a href="https://github.com/jexwerquez/Asteroids" target="_blank">View the project on GitHub</a>

### Process descriprion

The player controls an arrow-shaped spaceship that can move in the x0y plane and 
shoot forward at the press of a key. To the right hover asteroids move, which you 
can dodge or shoot down. Occasionally unidentified flying objects  appear, which 
the user can ignore or pick up, randomly earning a bonus or anti-bonus. 

The game ends when a spaceship collides with an asteroids.

### Demonstration

<img src='https://github.com/jexwerquez/asteroids/blob/develop/dem.gif?raw=true'/>

### Installation

```
git clone https://github.com/jexwerquez/practice.git
cd asteroids
make all
./asteroids
```

### Features

* The choice of difficulty, which determines the speed of 
  the game and the ratio of bonuses to anti-bonuses.

* Ability to change the size of the field.

* Set your initial settings in an optional input file.

### Requirements

* C++ 17
* Linux
* Ncurses
* Git
