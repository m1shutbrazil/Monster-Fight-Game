# Monster Fighting Game

This is a terminal-based monster fighting game implemented in C++. The player must fight a series of monsters, level up, and survive until reaching level 20 to win the game.

## Features

- Fight against various types of monsters (orc, dragon, slime)
- Level up by defeating monsters and improve your damage
- Random encounters with monsters, with a chance to flee
- Win by reaching level 20, or lose if your health drops to zero
- Random gold rewards for defeating monsters

## How to Play

1. Objective: The goal is to survive encounters with monsters, level up your character, and reach level 20.
2. Encounters: During each round, you will face a random monster.
3. Choices: 
   - You can choose to:
     - (R)un: Attempt to flee from the monster (50% chance of success).
     - (F)ight: Engage in combat with the monster. You and the monster will exchange blows until one of you is defeated.
4. Combat:
   - When you attack a monster, it loses health equal to your damage.
   - When the monster attacks you, you lose health equal to the monster's damage.
   - If you defeat the monster, you level up, increasing your damage and finding gold.
5. Winning and Losing:
   - Winning: Reach level 20 to win the game.
   - Losing: The game ends if your health drops to zero.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Monster-Fight-Game-cpp.git
   cd moster-fight-game-cpp
2. Compile the programm
   ```bash
   g++ -o game game.cpp
3. Run the game
   ```bash
    ./game

  ## Example Gameplay
  ```console
  Enter your name: Hero
  Welcome, Hero.
  You have 10 health and are carrying 0 gold.
  You have encountered a slime (s)
  (R)un or (F)ight: F
  You hit the slime for 1 damage.
  The slime hit you for 1 damage.
  You hit the slime for 1 damage.
  You killed the slime!
  You are now level 2.
  You found 10 gold.
