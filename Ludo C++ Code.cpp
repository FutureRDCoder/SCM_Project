#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX_PLAYERS = 4;
const int BOARD_SIZE = 56; // Ludo board has 56 squares

// Structure to represent a player's token
struct Token {
  int position;
  bool isOut; // Flag to indicate if token is out of starting base
};

// Structure to represent a player
struct Player {
  string name;
  vector<Token> tokens; // Each player has 4 tokens
};

// Function to roll a dice (returns a random number between 1 and 6)
int rollDice() {
  srand(time(0)); // Seed random number generator
  return (rand() % 6) + 1;
}

// Function to check if a player can move a token (needs a 6 to get out)
bool canMoveToken(Player player) {
  if (player.tokens[0].isOut) {
    return true;
  }
  return false; // Can only move out if token is not out yet
}

// Function to move a player's token (handles moving out, capturing, etc.)
void moveToken(Player& player, int diceRoll) {
  if (!canMoveToken(player)) {
    cout << "You need to roll a 6 to get your token out." << endl;
    return;
  }

  int tokenIndex;

  do {
    cout << "Select token to move (1-4): ";
    cin >> tokenIndex;
  } while (tokenIndex < 1 || tokenIndex > 4 || player.tokens[tokenIndex - 1].isOut);

  tokenIndex--; // Adjust for 0-based indexing

  int newPosition = player.tokens[tokenIndex].position + diceRoll;

  // Handle moving out of starting base
  if (!player.tokens[tokenIndex].isOut) {
    if (diceRoll == 6) {
      player.tokens[tokenIndex].isOut = true;
      newPosition = 0; // Move to starting square
    } else {
      return; // Can't move token if not a 6
    }
  }

  // Handle going beyond the board
  newPosition = newPosition % BOARD_SIZE;

  // Check for capturing opponent's token
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (i != player.tokens[tokenIndex].position && !player.tokens[tokenIndex].isOut) {
      for (int j = 0; j < MAX_PLAYERS; j++) {
        if (j != i && player.tokens[tokenIndex].position == player.tokens[j].position) {
          player.tokens[j].isOut = false; // Send opponent's token back to starting base
          player.tokens[j].position = 0;
          cout << "Captured opponent's token!" << endl;
          break;
        }
      }
    }
  }

  player.tokens[tokenIndex].position = newPosition;

  cout << "Moved token " << tokenIndex + 1 << " to " << newPosition << endl;
}

// Check if a player has all 4 tokens in the finish area (positions 49-52)

bool isWinner(Player player) {
    for (const Token& token : player.tokens) { // Use const Token& for read-only access
        if (token.position < 49 || !token.isOut) {
            return false;
        }
    }
    return true;
}

int main() {
  int numPlayers;

  cout << "Welcome to Ludo!" << endl;

  // Get number of players
  do {
    cout << "Enter number of players (1-4): ";
    cin >> numPlayers;
  } 
  while (numPlayers < 1 || numPlayers > MAX_PLAYERS);

  vector<Player> players(numPlayers);

  // Get player names and initialize tokens
  for (int i = 0; i < numPlayers; i++) {
    cout << "Enter player " << i + 1 << " name: ";
    cin >> players[i].name;

    for (int j = 0; j < 4; j++) {
        players[i].tokens.push_back({0, false}); // All tokens start at position 0 (not out)
    }
  }

  int currentPlayer = 0;
  
  bool winnerFound = false;

  while (true) {
    string currentName = players[currentPlayer].name;

    cout << currentName << "'s turn." << endl;

    int diceRoll = rollDice();
    cout << "Dice rolled: " << diceRoll << endl;

    if (diceRoll != 6) {
        cout << "You can't move this turn. Pass to next player." << endl;
    } 
    else {
  // Offer choice to move a token or roll again for another chance at 6
        int choice;
        do {
            cout << "(1) Move a token or (2) Roll again: ";
            cin >> choice;
        } 
        while (choice < 1 || choice > 2);

        if (choice == 1) {
        moveToken(players[currentPlayer], diceRoll);
        } 
        else {
    // Roll again if player chooses to
        diceRoll = rollDice();
        cout << "Dice rolled again: " << diceRoll << endl;
        moveToken(players[currentPlayer], diceRoll);
        }
    }
    
    currentPlayer = (currentPlayer + 1) % numPlayers;

    if (isWinner(players[currentPlayer - 1])) {
        cout << players[currentPlayer - 1].name << " wins!" << endl;
        winnerFound = true;
        break;
    }
    
    if (winnerFound) {
        break; 
    }
  }
  
  return 0;
}