#include <iostream>
#include <vector>
#include "graphics.h"  // Assuming you have a graphics.cpp file
#include "input.h"     // Assuming you have an input.cpp file

using namespace std;

// Structure to represent a game in the platform
struct Game {
  string name;
  bool (*startGame)();  // Function pointer to start the game logic
  void (*drawGame)(sf::RenderWindow& window);  // Function pointer for drawing the game (if using graphics)
};

// Function prototypes for specific game modules (replace with your game implementations)
bool startTicTacToe();
void drawTicTacToe(sf::RenderWindow& window);

bool startHangman();
void drawHangman(sf::RenderWindow& window);

// ... (add similar functions for other games)

// Vector to store available games in the platform
vector<Game> availableGames;

int main() {
  // Initialize available games
  availableGames.push_back({"Tic-Tac-Toe", startTicTacToe, drawTicTacToe});
  availableGames.push_back({"Hangman", startHangman, drawHangman});

  // ... (add other games to the vector)

  // Main game loop
  while (true) {
    // Display a menu of available games
    cout << "Welcome to The Game Cave!" << endl;
    for (int i = 0; i < availableGames.size(); i++) {
      cout << (i + 1) << ". " << availableGames[i].name << endl;
    }
    cout << "0. Exit" << endl;

    // Get user input for game selection
    int choice = getIntegerInput("Enter your choice (0-Exit): ", 0, availableGames.size());

    if (choice == 0) {
      break; // Exit the game loop
    }

    // Start the chosen game
    if (choice > 0 && choice <= availableGames.size()) {
      Game chosenGame = availableGames[choice - 1];
      if (!chosenGame.startGame()) {
        cout << "An error occurred while starting the game." << endl;
      }
    } else {
      cout << "Invalid choice. Please try again." << endl;
    }
  }

  cout << "Thank you for playing The Game Cave!" << endl;
  return 0;
}

// Implementations for specific game logic and drawing functions (in separate cpp files)
bool startTicTacToe() {
  // ... (Tic-Tac-Toe game logic)
}

void drawTicTacToe(sf::RenderWindow& window) {
  // ... (Draw Tic-Tac-Toe game using graphics library)
}

// ... (Implement similar functions for other games)

