# Strategy
A pixel-art turn-based strategy game set in Berlin, April 1945. You are General Helmuth Weidling, defending the ruins of the city against the Red Army. This battle is not meant to be won, only to be held for as long as possible.
 
![Strategy](https://cdn.hackclub.com/01a205fd-e698-7607-8e61-670a2067cf20/captura_de_pantalla_2026-11-22_201905.png)

![Strategy](https://cdn.hackclub.com/01a205fe-1e1d-7aba-a793-6f0ee0dd5e0f/captura_de_pantalla_2026-11-22_201918.png)
 
## How to run it
1. Go to the Releases section of this repository.
2. Download `Strategy_Nivel3.zip`.
3. Right-click it and choose **Extract All...** (don't run the .exe from inside the zip).
4. Open the extracted folder and run `Strategy.exe`.
 
## Features
- **Story intro:** two illustrated pixel-art scenes set the stage, with a narration screen and General Weidling giving his orders.
- **Grid battlefield:** a pixel-art map of Berlin split by a river that can only be crossed at the bridges.
- **Turn-based combat:** one action per unit each turn, move or attack.
- **Enemy turns:** Soviet units advance on your closest soldier and attack when they get close.
- **Animated units:** walking animations in all four directions, health bars and visible turn state.
- **Turn counter and HUD:** turn number and remaining units for both sides.

## How to play
- **Click** one of your German soldiers (blue ring) to select it.
- **Blue cells** show where it can move. Click one to move there.
- **Red cells** mark enemies in reach. Click an adjacent Soviet soldier to attack it.
- Each unit can only move **or** attack once per turn. When every soldier has acted, the turn ends on its own.
- Press **Space** to end your turn early.
- The level is lost when you have no units left. Your score is how long you resisted and how many enemies you took down.

P.S: Soldiers attack like a rook in chess, but only one square away: up, down, left or right (no diagonals). 

![Strategy](https://cdn.hackclub.com/01a20600-f47f-7bdb-a7e8-4008bdbaf378/captura_de_pantalla_2026-11-22_201927.png)

## Built With
C++/CLI, Windows Forms and GDI+. Pixel art made with Aseprite.

This game is still under construction; more updates will be coming soon :D
 
*A project made for YSWS Terra by Hack Club.*
