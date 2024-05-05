#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_PLAYERS = 4;
const int BOARD_SIZE = 100;

// Structure to represent a player
struct Player {
  string name;
  int position;
};

// Function to roll a dice (returns a random number between 1 and 6)
int rollDice() {
  srand(time(0)); // Seed random number generator
  return (rand() % 6) + 1;
}

// Function to check if a player lands on a snake or ladder
int checkSnakesAndLadders(int position) {
  // Define snake and ladder positions here (modify as needed)
  int snakes[][2] = {{16, 6}, {48, 26}, {62, 19}};
  int ladders[][2] = {{1, 38}, {4, 14}, {21, 81}};

  for (int i = 0; i < sizeof(snakes) / sizeof(snakes[0]); i++) {
    if (position == snakes[i][0]) {
      return snakes[i][1]; // Landed on a snake, move down
    }
  }

  for (int i = 0; i < sizeof(ladders) / sizeof(ladders[0]); i++) {
    if (position == ladders[i][0]) {
      return ladders[i][1]; // Landed on a ladder, move up
    }
  }

  return position; // No snake or ladder
}

int main() {
  int numPlayers;

  cout << "Welcome to Snake & Ladders!" << endl;

  // Get number of players
  do {
    cout << "Enter number of players (1-4): ";
    cin >> numPlayers;
  } while (numPlayers < 1 || numPlayers > MAX_PLAYERS);

  Player players[MAX_PLAYERS];

  // Get player names and set starting position to 0
  for (int i = 0; i < numPlayers; i++) {
    cout << "Enter player " << i + 1 << " name: ";
    cin >> players[i].name;
    players[i].position = 0; // Start all players at position 0
  }

  int currentPlayer = 0;

  while (true) {
    string currentName = players[currentPlayer].name;
    int currentPos = players[currentPlayer].position;

    cout << currentName << "'s turn." << endl;

    int diceRoll = rollDice();
    cout << "Dice rolled: " << diceRoll << endl;

    int newPosition = currentPos + diceRoll;

    // Check if player goes beyond the board
    if (newPosition > BOARD_SIZE) {
      cout << "You can't go beyond the board. Stay at position " << currentPos << endl;
    } else {
      newPosition = checkSnakesAndLadders(newPosition);
      players[currentPlayer].position = newPosition;

      cout << "Landed on " << newPosition << endl;

      if (newPosition == BOARD_SIZE) {
        cout << currentName << " wins!" << endl;
        break;
      }
    }

    currentPlayer = (currentPlayer + 1) % numPlayers; // Switch to next player
  }

  return 0;
}
