# OpenGL-Engine
Fundamental Game Engine

## Main Class: 
OpenGL trial folder, all the classes should be there. The res folder contains some models and their corresponding diffuse maps.

As you can see from the GIF, I can load in multiple models. I created a function where you can change the colour of the light to red green or blue using the keys R,G or B. And multiple camera functions which can change the projection and view matrix. 

Different transformations are also possible using a function call for seperate objects instead of copy pasting lines of code for model transformations.

There are actually 2 light sources, the animated light is a point light which uses diffuse lighting. And another light which is a replica of the sun which uses directional light and creates a subtle yet strong ambient light.

[EngineDemo](https://media.giphy.com/media/BzjKrt5cggW9w1s0Tt/giphy.gif)

Currently working on implementing another model loader class for DAE objects and then focus on skeletal animation.
