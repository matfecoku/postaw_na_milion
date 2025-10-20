# Postaw na milion - Game Show Simulator

A **C++ console application** that simulates the popular Polish game show "Postaw na milion".

> The code, comments and the game itself are written in **Polish**.
> This README is provided in English for accessability.

## Features

- **8 rounds** of trivia questions
- **Multiple categories**: General knowledge, Culture, History, Nature, Sports, Science, Technology, Entertainment
- **Lifeline system** with help options
- **Save/Load functionality** to continue game later
- **Leaderboard system** to track high scores
- **Clean console interface** with organized question display

## Requirements
- **Visual Studio 2019** (or another C++ compiler)
- **C++14**

## Usage
1. Clone the repository and navigate to the project folder
2. Go into the "Source" folder
3. Open the solution file (`postaw_na_milion.sln`) or the project file (`postaw_na_milion.vcxproj`) in Visual Studio
4. Build and run the project (F5 or Ctrl+F5)
5. Follow the on-screen menu to start a new game or load a saved one

## How it works
- **Question System**: Loads questions from `questions.txt` with categories, questions, and answers
- **Player Management**: Tracks player name, current winnings, and game progress
- **Round Progression**: 8 rounds with increasing difficulty and prize amounts
- **Save System**: Saves game state to `savefile.txt` for later continuation
- **Leaderboard**: Records high scores in `leaderboard.txt` with timestamps
- **File Management**: Handles reading/writing of game data and configuration files

## Game Structure
- **Questions**: Stored in `questions.txt`
- **Save Files**: Game state saved to `savefile.txt` for resuming games
- **Leaderboard**: High scores tracked in `leaderboard.txt` with player names and amounts

## Notes
- Ensure **questions.txt** contains properly formatted questions before running
- Leaderboard entries include timestamps for tracking when scores were achieved
