# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Meeting 08.11.2023 18:30

**Participants**: 
1. Szymon Abramczyk
2. Viktor Dementev
3. Anastasiia Semenova
4. Risto-pekka Siponen

## Summary of works
1. Szymon Abramczyk 
   
   Reading about SFML and CMake and improving the understanding of the project.

2. Viktor Dementev

   Made a CMake file and installed SFML.

3. Anastasiia Semenova

   Reading about implementation regarding items. What sub item classes can be done. 

4. Risto-pekka Siponen

   Studied the project plan after returning from absence and reading about the basics of SFML and possible combat & movement classes.

## Challenges

1. Implementing the Game class to handle events.
2. Implementing menu for the game.
3. Improving CMake to make it work for multiple files.
4. Implementing basic features so that further work can be done.

## Actions
1. All members are going to continue to read about SMFL.
2. All members are going to read and find out how to implement their part of the project.

## Project status 
The project has one basic class that displays the game window. There is a CMake file that enables to automatically build the project.

### TODOs
1. Szymon will change CMake so that it works automatically for newly added .cpp files.
2. Members will meet in person to push the project forward and figure out next steps.


# Meeting 09.11.2023 15:30

**Participants**: 
1. Szymon Abramczyk
2. Viktor Dementev
3. Risto-pekka Siponen

## Summary of works
1. Szymon Abramczyk 
   
   Made a game class with ability to pop up a charecter, which is vector for now. Added basic controls to the charecter is player class, so he can move on the screen.

2. Viktor Dementev

   Made a asset class and sprite class. Enabled to load custom textures to convert them to the sprites with a size and texture. They tried to combined their work to have a charecter sprite to move on a screen instead of vector.

3. Risto-pekka Siponen

Was solwing issues with a SFML library. It didnt allow to run code on his local envierment.

## Challenges

1. Enebeling SFML on all machines.
2. Implementing menu for the game.
3. Combining sprites and player.


## Actions
1. All members are going to continue to read about SMFL.
2. All members are going to read and find out how to implement their part of the project.

## Project status 
The project can handle a charecter movement on a screen and loading textures to make them sprites. Game can refresh via the main game loop and handle events.

### TODOs
1. Add content folder to a build folder, so sprites can actually appear on the screen.
2. Members will work on their own untill the next week.
