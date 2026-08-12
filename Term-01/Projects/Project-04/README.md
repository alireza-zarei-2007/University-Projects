# 🎮 Tank Battle Game

A thrilling two-player terminal-based artillery game with realistic projectile physics.

---

## Description

Two players take turns controlling tanks on a 2D battlefield. Each player adjusts their tank's position, firing angle, and shot power to hit the opponent's tank. The game simulates projectile physics with gravity for realistic trajectory.

---

## Game Map

- **Dimensions:** 120 columns × 22 rows
- **Terrain Elements:**
  - Space (` `) – Bullets move freely
  - Ground (`Ø`) – Tanks move here; bullets stop on impact
  - Rocks (`Ø`) – Impassable obstacles; bullets stop on impact

The map is rendered inside a border frame.

---

## Tank Specifications

- **Width:** 9 characters
- **Height:** 3 lines
- **Starting Health:** 100%
- **Damage per Hit:** 20%

### Movement Boundaries
- **Player 1 (Left):** 0 ≤ Px ≤ 24
- **Player 2 (Right):** 85 ≤ Px ≤ 111
- **Py:** Always 19 (ground level)

---

## Projectile Physics

### Launch Points
- **Player 1:** (Px + 9, 17)
- **Player 2:** (Px - 1, 17)

### Formulas
| Quantity | Formula |
|----------|---------|
| Horizontal Velocity | `vx = power × cos(θ)` |
| Vertical Velocity | `vy = power × sin(θ)` |
| Horizontal Position | `x(t) = vx × t + x₀` |
| Vertical Position | `y(t) = -½gt² + vy × t + y₀` |

### Constants
- **Gravity (g):** 0.4
- **Time Step (Δt):** 0.1
- **π:** 3.14159265358
- **Power Formula:** `power = 2 + 7 × (power_input / 100)^1.5`

---

## Controls

### Command Input (First Prompt)
| Command | Description |
|---------|-------------|
| `R [n]` | Move tank Right by `n` spaces |
| `L [n]` | Move tank Left by `n` spaces |
| `S` | Skip turn |
| `Q` | Quit game |
| `N` | New game (random positions, full health) |
| `B` | Back (undo last enemy shot – once per game) |

### Firing Angle (Second Prompt)
- **Range:** 0° to 180° (decimal values allowed)
- **Conversion:** `rad = θ × π/180`

### Shot Power (Third Prompt)
- **Range:** 1 to 100 (integer)
- **Transformation:** `power = 2 + 7 × (power_input / 100)^1.5`

---

## Game Messages

### Error Messages
| Situation | Message |
|-----------|---------|
| Invalid command | `Invalid Command - Your Turn Is Lost!` |
| Illegal move | `Illegal Move - Your Turn Is Lost!` |
| Angle out of range | `Angle Out Of Range - Your Turn Is Lost!` |
| Power out of range | `Power Out Of Range - Your Turn Is Lost!` |
| Back already used | `Ability Is Already Used - Your Turn Is Lost!` |

### Shot Results
| Result | Message |
|--------|---------|
| Hit enemy tank | `BOOM!!! Clean Hit On The Enemy` |
| Hit own tank | `BOOM!!! Friendly Fire` |
| Hit obstacle/ground | `Shot Terminated!` |

### Victory Messages
| Winner | Message |
|--------|---------|
| Player 1 | `---PLAYER 1 WINS---` |
| Player 2 | `---PLAYER 2 WINS---` |

---

## Installation & Execution

1. Save `game.c` in a folder.
2. Compile: `gcc game.c -o tank_battle -lm`
3. Run: `./tank_battle`

> **Note:** Increase terminal size for proper game display.

---

## How to Play

1. Game starts with Player 1's turn
2. Enter command: Move (R/L + distance), Skip (S), Quit (Q), New Game (N), or Back (B)
3. Enter angle: 0° to 180°
4. Enter power: 1 to 100
5. Watch bullet trajectory across the screen
6. See result (Hit / Miss / Terminated)
7. Turn switches to the other player
8. Game ends when a player's health reaches 0%

---

## Winning Condition

A player wins when the opponent's health drops to 0%. Victory message is displayed and game terminates.

---

## Bonus Feature: Back Command

Each player can use the **Back (B)** command once per game:
- Reverts game state to before the opponent's last shot
- Restores previous tank positions and health
- Player can then take their turn normally

If already used, the turn is lost.

---

## User Interface

### Status Bar (Top)
Player 1: [██████████] 100% Player 2: [██████████] 100%

### Input Prompts (Bottom)
(Player [1 or 2]) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back:
(Player [1 or 2]) Enter Firing Angle [0-180]:
(Player [1 or 2]) Enter Shot Power [1-100]:

---

## Libraries Used
- `<stdio.h>` – Input/output operations
- `<stdlib.h>` – Random generation, system commands
- `<math.h>` – Mathematical functions (sin, cos, pow, round)
- `<time.h>` – Time-based random seed
- `<windows.h>` – Sleep function for delays

---

## Important Notes
- **Global variables are strictly prohibited**
- Only use libraries and concepts taught in class
- All input validation must be handled as specified
- Screen clearing is mandatory between turns (`system("cls")`)
- Follow exact message formats
- Individual project – plagiarism results in zero points
