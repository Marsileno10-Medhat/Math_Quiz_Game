# Math Quiz Game

A simple C++ console-based math quiz game that tests the player's arithmetic skills with different difficulty levels and operation types. It generates random math questions, accepts user input, and displays results at the end.

## Features

- Choose the number of questions (1–100).
- Select difficulty level: Easy, Medium, Hard, or Mixed.
- Select operation type: Addition, Subtraction, Multiplication, Division, or Mixed.
- Instant feedback on each answer with colored screen response (green for correct, red for wrong).
- Final results summary after all questions.

## Game Levels

- **Easy:** Numbers between 1 and 10
- **Medium:** Numbers between 10 and 50
- **Hard:** Numbers between 50 and 100
- **Mix:** Randomly selects one of the above for each question

## Operations

- **Addition (+)**
- **Subtraction (-)**
- **Multiplication (*)**
- **Division (/)** — Integer division is used
- **Mix:** Random operation for each question

## How It Works

1. The player is prompted to enter:
   - Number of questions.
   - Difficulty level.
   - Type of operation.
2. Questions are generated randomly based on the selected settings.
3. The player answers each question.
4. Immediate feedback is shown.
5. Final results are displayed after all questions.

## Requirements

- C++11 or higher
- Windows terminal (for color codes using `system("color")`)

## Compile and Run

Use a C++ compiler such as g++ or any C++ IDE like Visual Studio Code or Code::Blocks.

### Using g++ (MinGW for Windows):

```bash
g++ -o MathQuiz MathQuiz.cpp
./MathQuiz
