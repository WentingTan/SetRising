SetRising
=========
CSci680/420 Course Project
---
Group 1:

* Gilbert Colón 
* Jinri Hong
* Matthew Stephens 
* Wenting Tan


Design Document (Simple Version)
===============

Logo:

> ![Simple Space Ship State Graph](https://github.com/WentingTan/SetRising/blob/master/Photos/logo.png)


Introduction
-------

Set Rising is a single-player, side-scrolling action platformer set within the context of a galactic civilization far in the future.  The player controls Set, an infamous war criminal who is offered his freedom in exchange for waging war against an invading alien species known as the Myrmidons.  Each level is set on a different planet, features a unique ammunition type or upgrade for Set’s main weapon (i.e. the player can switch to using a flamethrower on the volcanic planet), consists of killing enemies and overcoming platforming challenges, and ends with a boss battle.  Upon completion of each level, the player is rewarded with a piece of equipment that confers a new ability that can be useful in combat or in solving new platforming challenges.  The new equipment includes a device that allows the player to walk through certain types of walls, a device that slows the passage of time for objects and enemies in the environment but not for the player, a jetpack that allows vertical boosts and slows the rate of falling, and a black-hole grenade which upon detonation draws enemies within a certain radius towards its center.  After completing a linear series of four main levels, the player is given the choice of two options for the final level.  The ending of the game is different depending on the choice of final level.


Story
----

The basic story is: A powerful and ruthless alien civilization known only as the Myrmidons has descended upon the galaxy, laying waste to planet after planet. Entire populations are massacred, and the remnants of the broken Fleet are scattered, leaving the empire utterly defenseless. As the invading force nears closer to the core worlds, the Council makes a desperate and perilous gambit in an attempt to stop the slaughter. Set, infamous war criminal and the only man in the galaxy whose cruelty and malice matches that of the Myrmidons, has been offered his freedom and a full pardon in exchange for routing and exterminating the invaders. Eager to have a weapon in his hands again and get back to doing what he does best with it, Set accepts the offer, suits up, and ships out to the nearest planet under siege…

Levels
-----

> ![Simple Space Ship State Graph](https://github.com/WentingTan/SetRising/blob/master/Photos/LevelType.png)


Each level is set on a different planet. Each planet has a different theme, end boss, and new ability or weapon earned upon completion. Two planets add a new ammunition types to Set’s arsenal.

###Level 1: Vanaheim

Theme: War-torn city

Background: Planet under siege by the Myrmidons (aliens).  Destroyed buildings. 

Weapon granted: Black-hole grenades

Boss: Myrmidon General

- Bigger, more powerful version of the Myrmidon foot soldier
- Armed with a shield and spear
- Shield makes him invulnerable to frontal attacks
- Will charge across the screen with his spear.  Platforms (maybe stationary, maybe moving, maybe disappearing) will - allow Set to jump over him while he charges.
- If Set successfully dodges the charge, the boss will be momentarily stunned, and then Set may damage him by shooting him in the back


###Level 2: Niflheim

Theme: Ice planet

Ammo type added: Freeze ray 

Ability granted: Time manipulation

Boss: Tank

- Main idea: use freeze ray to cause the boss to damage himself
- Potential candidate: Tank that releases minions and fires missiles.  Missiles can impact frozen minions, and will damage the boss if this occurs close enough to the boss
- Potential candidate: Rocket launcher pops up from the tank.  Set must shoot it with the freeze ray before it fires, thereby blocking the rocket’s exit, causing it to blow up inside the launcher and damaging the boss

###Level 3: Muspelheim

Theme: Volcanic/fire planet

Ammo type added: Flamethrower

Ability granted: Jetpack

Boss: Super Grenadier

- On a platform (possibly stationary, or a moving platform, or the boss may jump between platforms)
- Throws grenades at Set
- The black-hole grenade can suck up and dispose of these grenades as well
- Boss takes little damage from Set’s weapons, but hitting a grenade with the flamethrower while the boss is still holding it will cause the grenade to blow up and do more damage to the boss. 

###Myrmidon Home (choosable)

Theme: Underground caverns/ant colony.

Ability granted: No new ability

Boss: “Ant Queen”

- Very large.  Only a specific body part visible on screen at a time
- Generates foot soldiers

###Human Capital (choosable)

Theme: Civilized, futuristic society.

Ability granted: No new ability

Boss: Human defender or champion, rival to Set

- Similar weapons and abilities as Set

###Timeline

Week of 10/11 - 10/17:
Create custom map editor

Work on concept art for Set and enemies
Begin working on Set spritesheet
Search for free tile sets

Week of 10/18 - 10/24:
Finalize the Set spritesheet
Complete spritesheet for one enemy
Design HUD and menus
Game prototype showing key gameplay elements such as platforming and interacting with enemies

Week of 10/25 - 10/31:
Implement all special abilities and level-sspecific weapons
Spritesheets for other enemies
Complete the first level and its boss

Week of 11/1 - 11/7:
Complete next two levels and their bosses.

Week of 11/8 - 11/14:
Complete last two levels and their bosses.

Week (and a half) of 11/15 - 11/24:
Testing & balancing
If time allows, polish the game and create extra content such as an introduction animation

