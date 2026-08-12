# Athlete Performance Analysis

## Description
A program that analyzes an athlete's performance trend over time. By receiving training data including week number, day, intensity, and duration, the system classifies the athlete's overall status into three categories: Improving, Declining, or Stable.

## Features
- Accepts training data in groups of 4 numbers (week, day, intensity, duration)
- Analyzes the trend of successful sessions
- Calculates average training intensity
- Determines overall status: Improving, Declining, or Stable
- Displays final status in specified format

## Input Format
Input is a sequence of numbers, where every 4 numbers represent one training session:
- First number: Week number
- Second number: Day number
- Third number: Training intensity (1–10)
- Fourth number: Training duration (minutes)

### Sample Input:
4 6 5 30 5 6 32 6 7 33 7 8 35
This represents 3 training sessions.

### Sample Output:
Athlete Status: Improving


## Installation & Execution
1. Save `q3.c` in a folder.
2. Compile: `gcc q3.c -o athlete`
3. Run: `./athlete`

## Analysis Logic
- Successful sessions: Intensity exceeds overall average
- Success trend: Whether successful sessions increase, decrease, or remain constant across weeks
- Average intensity: Average of all sessions

### Classification Rules:
- Improving: Number of successful sessions increases over time
- Declining: Number of successful sessions decreases over time
- Stable: Otherwise

## Suggested Function
```c
void printStatus(int improvingSuccess, double avgDifficulty);
Important Notes
Input is a continuous sequence of integers

Number of sessions is not fixed and continues until EOF

Intensity ranges from 1 to 10

Output must be exactly one of the three specified statuses
