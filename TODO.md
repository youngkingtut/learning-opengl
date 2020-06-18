## Renderer
* ~~Camera bound to player~~
* Camera stationary when player reaches edges
    * ~~Implemented a sudden stop when player gets near edge, the effect is a bit jarring. Should instead
    slow to a stop.~~
* ~~Colors for player~~
* Draw instanced 
    * Pack direction and position information in separate buffer.
* Render background star field

### Animation
* Event queue
    * Spawning enemies
    * Despawning particles and enemies

## Models
* ~~Enemy~~
* ~~Enemy 2~~
* Enemy 3 (Dodger)
* ~~Bullet~~
* Bullet 2 (Spray)
* ~~World~~

## Mechanics
* ~~Rate of acceleration and max speed dependent on tilt of joystick.~~
* Shield.
* Shield on spawn.
* Mark enemy that killed player.

### Enemy types
* Random movement enemy.

### Enemy Spawn
* Spawn system with scaling options.
    * Enemy type and weighting
    * Scaling enemy cooldown
    * Can have multiple systems going at once
    * Time based progression? Score based progression? All enemies are dead?

## Interface
* ~~Pause during game~~
* Dynamic resolution
* Menu
* Option to restart on death

## Bugs
* Some buttons are not registering with movement and bullets when using the keyboard. 
Specifically, holding down on movement does not allow for diagonal down right shooting.
    * This bug seems to only effect on s key on my keyboard. Think I'll add key bindings
    to absolve this issue. 
