🎮 Tank Battle Game
📝 Description
A thrilling two-player terminal-based artillery game where two tanks battle each other on a 2D battlefield. Players take turns adjusting their tank's position, firing angle, and shot power to hit the opponent's tank. The game simulates projectile physics with gravity, providing a realistic and engaging experience.

🎯 Features
Turn-based gameplay – Players alternate turns to move and shoot

Realistic projectile physics – Simulated trajectory with gravity

Dynamic tank positioning – Tanks can move left or right within designated zones

Health system – Each tank starts with 100% health; hits reduce health by 20%

Interactive command system – Move, skip turn, quit, or start a new game

Status bar – Displays real-time health of both players at the top

Smooth projectile animation – Visual bullet trajectory with frame delays

Bonus feature – "Back" command allows one undo per game

🗺️ Game Map Specifications
Dimensions: 120 columns × 22 rows

Terrain elements:

Space ( ): Empty area – bullets can move freely

Ground (Ø): Tanks move on ground; bullets are destroyed on impact

Rocks (Ø): Impassable obstacles; bullets are destroyed on impact

The map is rendered inside a border frame to separate the game area from the terminal background.

🎨 Tank Design
Each tank is a 9×3 character structure:

Player 1 (Left Tank):
   __    
 _|__|_//
|_______|

Player 2 (Right Tank):
    __  
\\_|__|_ 
|_______|
Tanks start with 100% health

Each successful hit reduces health by 20%

Tanks spawn randomly within designated zones

Tank positions are dynamic and rendered each frame

Movement Boundaries
Player 1 (Left): 0 ≤ Px ≤ 24

Player 2 (Right): 85 ≤ Px ≤ 111

Py is always 19 (ground level)

💥 Projectile System
Launch Point Calculation
Player 1: (Px + 9, 17)

Player 2: (Px - 1, 17)

Physics Formulas
Quantity	Formula
Horizontal Velocity	vx = power × cos(θ)
Vertical Velocity	vy = power × sin(θ)
Horizontal Position	x(t) = vx × t + x₀
Vertical Position	y(t) = -½gt² + vy × t + y₀
Constants:

Gravity (g) = 0.4

Time step (Δt) = 0.1

Power formula: power = 2 + 7 × (power_input / 100)^1.5

π = 3.14159265358

🎮 Controls
Command Input (First Prompt)
Command	Description
R [number]	Move tank right by [number] spaces
L [number]	Move tank left by [number] spaces
S	Skip turn
Q	Quit game
N	New game (random positions, full health)
B	Undo last enemy shot (bonus feature, once per game)
Firing Angle (Second Prompt)
Range: 0° to 180° (decimal values allowed)

Converts to radians: rad = θ × π/180

Shot Power (Third Prompt)
Range: 1 to 100 (integer)

Power is transformed using the formula above

Game Messages
Event	Message
Invalid command	Invalid Command - Your Turn Is Lost!
Illegal move	Illegal Move - Your Turn Is Lost!
Angle out of range	Angle Out Of Range - Your Turn Is Lost!
Power out of range	Power Out Of Range - Your Turn Is Lost!
Back ability already used	Ability Is Already Used - Your Turn Is Lost!
Hit enemy	BOOM!!! Clean Hit On The Enemy
Hit own tank	BOOM!!! Friendly Fire
Hit obstacle/ground	Shot Terminated!
Game over (Player 1 wins)	---PLAYER 1 WINS---
Game over (Player 2 wins)	---PLAYER 2 WINS---
🔧 Installation & Setup
Prerequisites
GCC compiler

Windows OS (for system("cls") compatibility)

Compilation
gcc game.c -o tank_battle -lm

Execution
./tank_battle

Note: Increase terminal size for proper game display.

🚀 How to Play
Game starts with Player 1's turn

Enter command: Move tank (R/L + distance), skip (S), quit (Q), new game (N), or back (B)

Enter angle: Choose firing angle between 0° and 180°

Enter power: Choose shot power between 1 and 100

Watch the bullet travel across the screen

Result displayed – Hit, miss, or terminated shot

Turn switches to the other player

Game ends when one player's health reaches 0%

🎯 Winning Condition
A player wins when the opponent's health drops to 0%

Victory message displays the winner

Game terminates automatically

💡 Development Notes
Libraries Used
stdio.h – Input/output operations

stdlib.h – Random number generation, system commands

math.h – Mathematical functions (sin, cos, pow, round)

time.h – Time-based random seed

windows.h – Sleep function for delays

Important Functions
srand(time(NULL)) – Initialize random seed

rand() – Generate random positions

system("cls") – Clear terminal screen

Sleep(ms) – Pause execution for specified milliseconds

sin(), cos(), pow(), round() – Physics calculations

Key Implementation Details
Use \\ for backslash character in tank design

Bullet position: col = round(x(t)), row = round(y(t))

Update display only when bullet moves 6 cells

Frame delay: 750ms between projectile positions

Error delay: 3 seconds before next turn

📊 User Interface
Status Bar (Top)
Displays player information:
Player 1: [██████████] 100%    Player 2: [██████████] 100%

Game Area (Middle)
120×22 grid with border frame

Terrain elements (ground, rocks)

Dynamic tank positions

Projectile trajectory (*)

Input Prompts (Bottom)
(Player [1 or 2]) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game, B=Back:
(Player [1 or 2]) Enter Firing Angle [0-180]:
(Player [1 or 2]) Enter Shot Power [1-100]:
🏆 Bonus Feature
Back Command (B) – Each player can use this ability once per game:

Reverts game state to before the opponent's last shot

Restores previous tank positions and health status

Player can then take their turn normally

⚠️ Important Notes
Global variables are strictly prohibited

Only use libraries and concepts taught in class

All input validation must be handled as specified

Screen clearing is mandatory between turns

Follow exact message formats

Individual project – plagiarism results in zero points
