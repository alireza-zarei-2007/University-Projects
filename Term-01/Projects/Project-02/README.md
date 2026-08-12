# Sleep Monitoring System

## Description
An intelligent system for monitoring students' sleep patterns in university dormitories. Each student records their sleep and wake times, and the system calculates useful statistics including total sleep, daily average, number of low-sleep nights, and irregular nights.

## Features
- Accepts sleep data for n nights (max 365 nights)
- Calculates total sleep time in minutes
- Computes average daily sleep time
- Detects low-sleep nights (less than 6 hours)
- Detects irregular nights (waking after 10:00 AM)
- Standard input/output format

## Input Format
Each time interval is entered as `HHMM-HHMM`:
- HHMM: Time as a 4-digit number
- Sleep time: Between 8:00 PM and 5:00 AM
- Wake time: Between 5:00 AM and 8:00 PM

### Sample Input:
5
2310-0710
0100-0630
0215-0545
0030-1130
2345-0615

### Sample Output:
Total Sleep: 2070 minutes
Average Sleep: 414.00 minutes
Low Sleep Nights: 2
Irregular Nights: 3

## Installation & Execution
1. Save `q2.c` in a folder.
2. Compile: `gcc q2.c -o sleep_monitor -lm`
3. Run: `./sleep_monitor`

## Helper Functions
- `int calculate_sleep_minutes(int sleep_time, int wake_time)` – Calculates sleep duration in minutes
- `int is_irregular(int sleep_time, int wake_time)` – Checks if sleep is irregular

## Calculated Statistics
| Statistic | Description |
|-----------|-------------|
| Total Sleep | Sum of all sleep minutes across all nights |
| Average Sleep | Average sleep minutes per night |
| Low Sleep Nights | Nights with less than 6 hours (360 minutes) of sleep |
| Irregular Nights | Nights where waking is after 10:00 AM |

## Important Notes
- Maximum number of nights: 365
- Sleep time is guaranteed between 8:00 PM and 5:00 AM
- Wake time is guaranteed between 5:00 AM and 8:00 PM
- Times are read as 4-digit integers using `%4d`
- Average is displayed with 2 decimal places
