# Dungeon crawler
Szymon Abramczyk<br>Viktor Dementev<br>Anastasiia Semenova<br>Risto-pekka Siponen

## Scope of the work

### The game:

- Turn based.
- A medieval setting.

### Basic features:

- **Simple 2D graphics** (we will use the SFML library for implementing this feature). We have a text space at the bottom of a screen with output and input.

- **Moving through corridors and rooms.** (Simple moves up, down,left, right).

- **Combat between the player and different types of monsters**:
  - Basic attacks, 
  - Super attacks,
  - Special abilities. 
  - If you can hit emenies - deal damage and deplete their HP. The same for the enemy, it can hit you and deplete your HP. Enemy have percentage of health (healt points). 
  - Types of monsters: 
    - mini(spider), 
    - mini-bosses(goblin), 
    - bosses (orc).  
  - Armour system: armour decreases chances to be hit.

- **Collectibles** which can be used by a Player (weapons, potions, etc.)
- **Basic weapons**
- **Advanced weapons** (need to earn or find it,deal more damage),
- **Inventory** 
  - Seeing the items belonging to a Player: bombs, weapon, bow, knife, magic potion 
    - advanced option with a visual interface, 
    - basic option with the text (if you type inventory - you will be outputed with a list of items you have).
  -  Slots for armour, weapon and potions can be seen as an icon in a bottom of the screen with a number near them.

- **Some sort of progression** (winning & losing conditions)
  - To win you need to defeat the boss after several rooms with minions, if you die - you start again.




### Additional features:

We are planning to implement the following additional features:

- **Randomly generated monsters and items** <br>
  - We have some pool of names and stats and we combine them making a random monster/weapon.

- **Character leveling** (skills & abilities) 
  - killing monsters gives you experience points, when you reach the needed amount - you level up. Level-up grants you higher HP and new abilities.

- **Ability to craft / modify items**
  - The Player finds materials in the dungeon like a silver bar. You can find the anvil too, when you go past the anvil the output will sugest to interact with it. If you type yes, it will show what you can craft/upgrade and choose it with numbers(e.g. 1 - upgrade sword, 2 - craft something)


- **Quests or other events**
  - The Player can find a character Quest Giver at the dungeon level, he tells the Player to kill 5 goblins for example. When the Player does it, they can meet the charecter again and get a random reward.

- **Other kinds of non-player characters** (shopkeepers, allied combat, etc.)
  - The Player finds the non-hostile NPCs like a Shop Keeper. Similarly to the Quest giver, he will interact with the Player via the text interface.

- **Additional UI elements** (dungeon map, interactive inventory, etc.) 
  - The visual map will be implemented, the UI inventory probably will not be implemented.

- **Sound effects**
  - If we have time, we will try to implement it.
 
 ## The high-level structure of the software (according to current understanding)

**Main Classes**:

- **Game**:
  - Example methods: 
    - run(),
    - events(),
    - render().

- **Visuals** (stores textures etc.): 
  - Example methods: 
    - pop_up_text().

- **Entity**: 
  - Attributes: 
    - health, 
    - location etc.  
  - **Player** and **Enemy** classes will inherit from this class.
    - **Enemy** will have a subclass AI.

- **Combat**:
  - Example methods: 
    - attack, 
    - defend, 
    - ability. 
  - This class will be used by **Player** class.

- **Movement**:
  - Example methods:
    - go(direction).  
  - This class will be used by **Player** class.

- **Item**:
  - Atributes: 
    - amount.
  - Example methods: 
    - use_item().
  - Inheriting classes: **Weapon**, **Armour**, **Potions** etc.

- **NPC**:
  - Example methods: 
    - interact().
  - Inheriting classes: **Blacksmith**, **Trader**, **QuestGiver** etc.

- **Text**:
  - Example methods 
    - print(), 
    - recieve_input().


## External libraries

 - SFML

## Division of work

 - Viktor Dementev
   - Visuals, Sounds and Textures, Text and NPC 
 - Szymon Abramczyk 
   - Game and Entity classes
 - Anastasiia Semenova  
   - Item class 
 - Risto-pekka Siponen
   - Combat and Movement classes

## Planned schedule and milestones
- 10th of November - milestone one
- 17th of November - milestone two
- 24th of November - milestone three
- 30th of November - final version
- 4th December - report
