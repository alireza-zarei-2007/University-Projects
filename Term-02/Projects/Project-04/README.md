# ♟️ Board Game Solver

A recursive backtracking solver for a 7×7 board game where players jump over each other to remove pieces, aiming to leave exactly one piece in the center.

---

## Description

The game is played on a 7×7 board with holes (X) that cannot be occupied. Players jump over adjacent pieces into empty spaces, removing the jumped piece. The goal is to find a sequence of moves that leaves exactly one piece in the center (D4).

---

## Board Layout

### Grid Coordinates
|----|----|----|----|----|----|----|
| A1 | A2 | A3 | A4 | A5 | A6 | A7 |
| B1 | B2 | B3 | B4 | B5 | B6 | B7 |
| C1 | C2 | C3 | C4 | C5 | C6 | C7 |
| D1 | D2 | D3 | D4 | D5 | D6 | D7 |
| E1 | E2 | E3 | E4 | E5 | E6 | E7 |
| F1 | F2 | F3 | F4 | F5 | F6 | F7 |
| G1 | G2 | G3 | G4 | G5 | G6 | G7 |

### Hole Positions (Fixed)
|---|---|---|---|---|---|---|
| X | X | 0 | 0 | 0 | X | X |
| X | X | 0 | 0 | 0 | X | X |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| X | X | 0 | 0 | 0 | X | X |
| X | X | 0 | 0 | 0 | X | X |

- `X` = Hole (cannot be occupied)
- `0` = Empty space (cells with `0` in the hole pattern)

---

## Input Format

- 7 lines, each containing 7 characters
- **Characters:**
  - `X` – Hole (fixed, cannot change)
  - `N` – Player piece present
  - `O` – Empty cell

**Note:** No spaces between characters in each line.

---

## Sample Input 1
XXOOOXX
XXOOOXX
0000000
OONOONO
0000NNO
XXONOXX
XXOOOXX

## Sample Output 1
E6 LEFT F4 UP D3 RIGHT D6 LEFT

---

## Sample Input 2
XXOOOXX
XXOOOXX
OOOOOOO
OONOOOO
OOOOOOO
XXONOXX
XXOOOXX

## Sample Output 2
Loser

---

## Rules

1. **Valid moves:** A piece jumps over an adjacent piece into an empty cell
2. **Direction:** UP, DOWN, LEFT, RIGHT (2 cells away)
3. **Jumped piece removed** – The piece being jumped over is eliminated
4. **Winning condition:** Exactly one piece remains in the center (D4)
5. **Losing condition:** No valid moves available or cannot reach winning state

---

## Move Notation

Format: `<start_cell> <DIRECTION>`

Example: `A3 DOWN`
- Means: Piece at A3 jumps DOWN over B3 into C3

---

## Output Format

- Sequence of moves separated by spaces
- `Loser` – If no solution exists

---

## Installation & Execution

1. Save `Q3.cpp` in a folder.
2. Compile: `g++ Q3.cpp -o board_game`
3. Run: `./board_game`

---

## Game Logic

1. Find all possible jumps on the board
2. Try each jump recursively (backtracking)
3. After each jump, remove the jumped piece
4. If board state is winning (one piece at D4), print moves and exit
5. If no moves available, backtrack and try different paths
6. If all paths exhausted, print "Loser"

---

## Important Notes

- **Recursive backtracking required** – The solution must use recursion
- Board is 7×7 with fixed hole positions (XX000XX pattern)
- Center cell is D4
- Only one piece should remain in center to win
- The solution should find the first valid sequence of moves

---

## Move Validation

| Condition | Requirement |
|-----------|-------------|
| Start cell | Must contain a piece |
| Jump direction | Must be within board bounds |
| Middle cell | Must contain a piece (being jumped over) |
| Target cell | Must be empty (`O`) |
| Target cell | Must be within bounds |

---

## Sample Output Format

Moves are printed as:
E6 LEFT F4 UP D3 RIGHT D6 LEFT


This means:
1. Piece at E6 moves LEFT
2. Piece at F4 moves UP
3. Piece at D3 moves RIGHT
4. Piece at D6 moves LEFT

---
