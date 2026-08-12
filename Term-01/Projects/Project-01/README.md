# Tarzan Rescue

## Description
A simple simulation game where Tarzan must navigate through a jungle path to rescue his friend. The path contains obstacles and hazards, and each move consumes Tarzan's energy. The program receives movement commands from the user, reports Tarzan's status step by step, and displays the final result.

## Features
- Simulates Tarzan's movement through a jungle path using character mapping
- Manages energy and lives
- Detects hazards (holes and traps)
- Supports single and double-step moves
- Displays status after each move
- Handles game-over conditions

## Path Map
| Character | Description |
|-----------|-------------|
| S | Tarzan's starting position |
| F | Friend's position |
| H | Hole |
| T | Hunter's trap |
| G | Normal ground |

## Available Moves
| Character | Description | Energy Cost |
|-----------|-------------|-------------|
| R | Move one step right | 1 |
| L | Move one step left | 1 |
| T | Jump two steps right | 2 |
| K | Jump two steps left | 2 |
| Q | Quit the game | - |

## Installation & Execution
1. Save `q1.c` in a folder.
2. Compile using: `gcc q1.c -o tarzan`
3. Run: `./tarzan`

## Usage
The program receives inputs in this order:
1. Path string (max 100 characters)
2. Initial lives (integer)
3. Initial energy (integer)
4. Movement commands (one character at a time)

### Sample Input:
SGGTHGF
5
6
R
R
T
L
R

### Sample Output:
Moved to position 2, Energy left: 5, Lives left: 5
Moved to position 3, Energy left: 4, Lives left: 5
TARZAN STEPPED INTO A HOLE, LOSE 1 LIFE
Moved to position 5, Energy left: 2, Lives left: 4
TARZAN STEPPED ON A TRAP, LOSE 1 LIFE
Moved to position 4, Energy left: 1, Lives left: 3
TARZAN STEPPED INTO A HOLE, LOSE 1 LIFE
Moved to position 5, Energy left: 0, Lives left: 2
TARZAN RAN OUT OF ENERGY!

## Game Over Conditions
| Condition | Message |
|-----------|---------|
| Reached friend | TARZAN REACHED HIS FRIEND! |
| No lives left | TARZAN HAS NO LIFE LEFT! |
| Moved out of bounds | TARZAN GOT LOST IN THE JUNGLE! |
| No energy left | TARZAN RAN OUT OF ENERGY! |

## Suggested Functions
- `int getLength(char arr[])` – Calculate path length
- `int getEnergyCost(char move)` – Calculate energy cost per move
- `int getNewPosition(int pos, char move)` – Calculate new position
- `int getNewLivesValue(int lives, char cell)` – Update lives after hazards

## Important Notes
- Maximum path length: 100 characters
- If multiple end conditions occur, the first one in the listed order takes priority
- For double-step moves, if energy runs out mid-move, the move is partially executed
