# 🎬 Cinema Management System

A simple cinema management system for scheduling movie shows and managing seat reservations.

---

## Description

This system allows users to add movie showtimes to cinema halls, reserve seats for specific shows, list all movies playing in a hall, and generate reports of reserved seats for any showtime.

---

## Hall Specifications

| Hall Number | Seat Capacity |
|-------------|---------------|
| 1 | 10 |
| 2 | 20 |
| 3 | 30 |

- Seat numbers in each hall start from 1
- Each movie has a duration of 1 hour
- Show times range from 1 to 24 (24-hour format)

---

## Commands

### 1. Add Show

Creates a new show for a movie in a specific hall at a specific time.

**Format:**
add_show <movie_name> <time> <hall_number>

**Output:**
- `OK` – Show added successfully
- `A movie is already scheduled in this hall at this time` – Hall is occupied at that time

**Sample Input:**
add_show SpongeBob 10 3

**Sample Output:**
OK

---

### 2. Reserve Seat

Reserves a specific seat for a movie in a specific hall at a specific time.

**Format:**
reserve <hall_number> <time> <seat_number> <name>

**Output:**
- `OK` – Seat reserved successfully
- `No show is scheduled in this hall at the specified time` – No movie playing at that time
- `This seat is already reserved` – Seat already taken

**Sample Input:**
reserve 3 10 21 Parisa

**Sample Output:**
OK

---

### 3. List Movies

Displays all movies playing in a specific hall with available seats.

**Format:**
list_movies <hall_number>

**Output:**
- Movies listed as: `<movie_name> at <time>:00: <available_seats> seats available`
- `No movie found` – No shows scheduled in this hall

**Sample Input:**
list_movies 3

**Sample Output:**
SpongeBob at 10:00: 29 seats available
PinkPanter at 14:00: 10 seats available

---

### 4. Report Reserved Seats

Shows all reserved seats for a specific showtime in a hall.

**Format:**
report_seats <hall_number> <time>

**Output:**
- `Seat <seat_number> is reserved by <name>` – For each reserved seat
- `All seats are available` – No seats reserved

**Sample Input:**
report_seats 2 24

**Sample Output:**
Seat 19 is reserved by Parisa
Seat 20 is reserved by Kourosh

---

## Installation & Execution

1. Save `A1-StudentID.cpp` in a folder.
2. Compile: `g++ A1-StudentID.cpp -o cinema`
3. Run: `./cinema`

---

## Important Notes

- Movie names contain no spaces
- Times are integers from 1 to 24
- Seat numbers are guaranteed to be within hall capacity
- Output messages must match exactly (case-sensitive, no extra spaces)
- Commands are case-sensitive
- Only use C++ standard libraries

