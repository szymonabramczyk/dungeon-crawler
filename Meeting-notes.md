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
4. Risto-Pekka Siponen

## Summary of works
1. Szymon Abramczyk 
   
   Reading about SFML and CMake and improving the understanding of the project.

2. Viktor Dementev

   Made a CMake file and installed SFML.

3. Anastasiia Semenova

   Reading about implementation regarding items. What sub item classes can be done. 

4. Risto-Pekka Siponen

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
3. Risto-Pekka Siponen

## Summary of works
1. Szymon Abramczyk 
   
   Made a game class with ability to pop up a charecter, which is vector for now. Added basic controls to the charecter is player class, so he can move on the screen.

2. Viktor Dementev

   Made a asset class and sprite class. Enabled to load custom textures to convert them to the sprites with a size and texture. They tried to combined their work to have a charecter sprite to move on a screen instead of vector.

3. Risto-Pekka Siponen

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


# Meeting 15.11.2023 16:30

**Participants**: 
1. Szymon Abramczyk
2. Viktor Dementev
3. Anastasiia Semenova
4. Risto-Pekka Siponen

## Summary of works
1. Anastasiia Semenova

   Prepared plan for class structure item with inheriting classes and methods. Sfml guide

2. Risto-Pekka Siponen

   Fixed issue with Visual Studio Code, more research on combat & movement

## Challenges

1. Making choices regarding the gameplay
2. Planning for the future of the project
3. Combining everyones works in the project

## Actions
1. All members are going to read and find out how to implement their part of the project.

## Project status 
No changes in status

### TODOs
1. Have another meeting on campus tomorrow with Viktor, Szymon and Risto-Pekka to work on the project code.
2. Fix issue with Sprite class
3. Work on game visuals & dungeon generation
4. Implement early iteration of combat
5. All members will continue to do more research on their respective areas.


# Meeting 16.11.2023 16:15

**Participants**: 
1. Szymon Abramczyk
2. Viktor Dementev
3. Risto-Pekka Siponen

## Summary of works
1. Szymon Abramczyk
   
   Solved the problem of sprites not loading and changed the movement of the player to tile-based.

2. Viktor Dementev

   Made improvements to the cmake file and made a skeleton for a world class that will handle every separate render and event at once. Also studied a bit about level creation.  

3. Risto-Pekka Siponen

   Started working on the entity/player class and researching the implementation for combat.

## Challenges

1. Changing from the current player implementation to a seperate player/entity class
2. Implementaton of level generation
3. Making gameplay choices

## Actions
1. Viktor and Szymon will work on implementing the level creation together.
2. Risto-Pekka will finish implementing player class and do research on combat.
3. All members are going to read and find out how to implement their part of the project.

## Project status 
The game can display a window and draw the player on it. The game supports loading textures and tile-based charecter movement. Game can refresh via the main game loop and handle player events.

### TODOs
1. Implement entity/player class
2. Work on level generation
3. Work on game visuals 
4. Implement early iteration of combat
5. All members will continue to do more research on their respective areas.

# Meeting 29.11.2023 16:00

**Participants**: 
1. Szymon Abramczyk
2. Viktor Dementev
3. Risto-Pekka Siponen
4. Anastasiia Semenova

## Summary of works
1. Szymon Abramczyk
   
   Created the Tile-based map and changed the movement and rendering of the player to be tile-based only. Implemented basic Inventory class and collecting basic items.

2. Viktor Dementev

   Made a several level system to implement traveling through them in the next build.Drawn new charecter and enemy and items model 

3. Risto-Pekka Siponen

   Implemented Entity, Monster and Player classes, as well as monster pathfinding and basic combat features (normal & ranged attack).

4. Anastasiia Semenova

   Implemented items system - armour health potions and weapons.

## Challenges

1. Adapting methods to new level structure.
2. Implementaton of random level genetation. Doors must be always on the same place.
3. Outputing equiping items to the screen.
4. Game designing different enemies.

## Actions
1. Viktor and Szymon will work on level traveling together 
2. Viktor and Szymon will try to make doors staic, while other objects will be randomly generated.
3. Anastasiia will change the item methods.
4. Risto-Pekka will implement different enemies.

## Project status 
The game can display a window and draw the player on it. The game can draw several levels, traveling via them is not implemented yet. The game supports picking up items. The game has basic combat and one enemy type.  The game supports loading textures and tile-based charecter movement. Game can refresh via the main game loop and handle player events.

### TODOs
1. Implement random level generation.
2. Work on level traveling.
3. Add more visuals.
4. Make level up progression.
5. Fix minor issues. 
6. Add more enemies. 
