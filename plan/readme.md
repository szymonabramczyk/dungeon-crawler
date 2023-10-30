"Dungeon crawler"
-----------------



Scope of the work: what features and functionalities will be implemented, how is the program used, and how does it work
--------------

Basic features:
---------------
Simple 2D graphics (using the library SFML for implementation this feature). We have a text space at the bottom of a screen with a output and input.
-------
Moving through corridors and rooms. (Simple moves up,down,left, right).
-------
Combat between the player and different types of monsters (Basic attacks (some buttons), super attacks(some buttons), have special abilities. If you can heat emenies - deal damage and deplete their HP,the same for the enemy,it can hit you and deplete your hp. Enemy have percents of health (healt points). Types of monsters: mini(spider), mini-bosses(goblin), bosses (orc).  Armour system: armour decreases chances to be heat.
--------
Collectibles which can be used later on (weapons, potions, etc.)
Basic weapons:
Advanced weapons ( need to earn or find it,has more damage), 
slots for armour and weapon
potionts can be seen as an icon in a bootom of screen with an int nier them.

Inventory - need to see itoms belonging: bombs, weapon, bow, knife, magic potion - advanced option with a visual interface, basic one with the text(if you type inventory - you will be outputed with a list of items you have) 
--------
Some sort of progression (winning & losing conditions) 
To win you need to defeat the boos after sever rooms with minions, if you die - you start again.
------

The game:
- Turn based
- a medival setting 


Additional features:
---------------------

Randomly generated dungeons
Seems hard to implement - dont know yet

Randomly generated monsters and items
We have some pool of name and stats and we combine them making a random monster/ weapon.

Character leveling
 (skills & abilities) killing monsters gives you expirience points, when you reach needed amount - you level up. level up grants you higher hp and new abilities.

Ability to craft / modify items 
You find materials in the dungeon like a silver bar. You can find the anvil too, when you go past the anvil the output will sugest to interact with it. If you type yes, it will show what you can craft/upgrade and choose it with numbers(1 - uupgrade sword, 2 - craft something)


Quests or other events
you can have a charcter quest giver at the dungeon level, he teels you to kill 5 goblins for example. When you've done it, you can meet the charecter again and get a random revard.

Other kinds of non-player characters (shopkeepers, allied combat, etc.)
you find the non hostile nps like a shop keeper. Like the quest giver he will interact with you vai the text interface.

Additional UI elements (dungeon map, interactive inventory, etc.) The visual map will be implemented, the ui inventory probably will not be implemented.

Sound effects
If we have extra time, we will try to implement it.


------------
The high-level structure of the software: main modules, main classes (according to current understanding)
------------
Class game :
methods -run, -events, - render

Class visuals - stores textures
methods like: pop up text

Class entity: 
parameters: health, location etc. Inhereting classes Player and Enemy. Enemy will have a sub - class ai

Class combat:
methods: attack, defend, ability. Class palyer will use this this 

Class movement:
methods go [direction]. Also used by a player class.

Class Item:
atributes: amount
methods: use item
inheriting from item classes: weapon, armour potions etc

class npc:
methods: interact
inheriting from npc classes: blacksmith, trader, quest giver.

class text:
methods print, recieve input 

------------
External lb 
------------
 SFML
 -----------
 division of the roles
 -----------
 Viktor - Visuals ?sounds? and textures, text and npc 
 Szymon - class game and entity 
 Anastasiia - Class item
 Ripe - class combat n movement
------------
10th of november friday - milestone one
17th of november - milestone two
24 of november - milestone three
30th of november - fianl version
4th december report
