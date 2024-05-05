#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

const int BOARD_SIZE = 3;

char board[BOARD_SIZE][BOARD_SIZE]; // Tic-Tac-Toe board represented as a 2D character array

// Function to initialize the game board with empty spaces
void initializeBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = ' '; // Empty space
    }
  }
}

// Function to display the current game board state
void displayBoard() {
  cout << "  |  |  " << endl;
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      cout << board[i][j] << " | ";
    }
    cout << endl;
    if (i != BOARD_SIZE - 1) {
      cout << "--+---+--" << endl;
    }
  }
  cout << "  |  |  " << endl;
}

// Function to check if a position on the board is empty
bool isEmpty(int row, int col) {
  return board[row][col] == ' ';
}

// Function to get player input for the next move
int getPlayerMove(char player) {
  int row, col;
  while (true) {
    cout << player << "'s turn, enter row (1-3): ";
    cin >> row;
    cout << player << "'s turn, enter column (1-3): ";
    cin >> col;

    // Validate input within board boundaries and check for empty space
    if (row > 0 && row <= BOARD_SIZE && col > 0 && col <= BOARD_SIZE && isEmpty(row - 1, col - 1)) {
      return (row - 1) * BOARD_SIZE + col - 1; // Convert row, col to single index
    } else {
      cout << "Invalid input. Please enter a valid empty position." << endl;
    }
  }
}

// Function to place a player's mark (X or O) on the board
void placeMark(int position, char player) {
  int row = position / BOARD_SIZE;
  int col = position % BOARD_SIZE;
  board[row][col] = player;
}

// Function to check if a player has won
bool checkWin(char player) {
  // Check rows
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
      return true;
    }
  }

  // Check columns
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
      return true;
    }
  }

  // Check diagonals
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
    return true;
  }
  if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
    return true;
  }

  return false;
}

// Function to check if the board is full (no empty spaces)
bool isBoardFull() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isEmpty(i, j)) {
        return false;
      }
    }
  }
  return true;
}

// Function for the computer to make a move
int computerMove(char computerMark) {
  // Prioritize winning moves for the computer
    // 1. Check for winning moves for the computer
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isEmpty(i, j)) {
        // Simulate placing the computer's mark at this position
        board[i][j] = computerMark;
        if (checkWin(computerMark)) {
          // Found a winning move for the computer, return this position
          board[i][j] = ' '; // Undo the simulated move
          return i * BOARD_SIZE + j;
        }
        board[i][j] = ' '; // Undo the simulated move
      }
    }
  }

  // 2. Check for blocking winning moves for the player (if no winning move for computer)
  char playerMark = (computerMark == 'X') ? 'O' : 'X'; // Determine player's mark
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isEmpty(i, j)) {
        // Simulate placing the player's mark at this position
        board[i][j] = playerMark;
        if (checkWin(playerMark)) {
          // Found a potential winning move for the player, block it!
          board[i][j] = computerMark; // Place computer's mark to block
          return i * BOARD_SIZE + j;
        }
        board[i][j] = ' '; // Undo the simulated move
      }
    }
  }

  // 3. Choose a center position if available (strategic placement)
  if (isEmpty(1, 1)) {
    return 1 * BOARD_SIZE + 1;
  }

  // 4. Choose a corner position if available (strategic placement)
  for (int i = 0; i < BOARD_SIZE; i = i == 1 ? 2 : 0) {
    for (int j = 0; j < BOARD_SIZE; j = j == 1 ? 2 : 0) {
      if (isEmpty(i, j)) {
        return i * BOARD_SIZE + j;
      }
    }
  }

  // 5. Choose any remaining empty position (fallback)
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isEmpty(i, j)) {
        return i * BOARD_SIZE + j;
      }
    }
  }

  return -1; // Should never reach here (indicates an issue with the game logic)
}

int main() {
  char playerMark;
  char computerMark;

  // Ask player to choose X or O
  cout << "Do you want to be X or O? (X goes first): ";
  cin >> playerMark;

  // Determine computer's mark based on player's choice
  computerMark = (playerMark == 'X') ? 'O' : 'X';

  cout << "Playing Tic-Tac-Toe!" << endl;
  cout << (playerMark == 'X' ? "You go first!" : "Computer goes first!") << endl;

  // Game loop
  while (true) {
    // Display board
    displayBoard();

    // Get player's move
    int playerMove = getPlayerMove(playerMark);
    placeMark(playerMove, playerMark);

    // Check for player win
    if (checkWin(playerMark)) {
        displayBoard();
        cout << playerMark << " wins!" << endl;
        break;
    }

    // Check for a draw
    if(isBoardFull()) {
        displayBoard();
        cout << "It's a draw!" << endl;
        break;
    }

    // Computer's turn
    int computerMoveIndex = computerMove(computerMark);
    placeMark(computerMoveIndex, computerMark);

    // Check for computer win
    if (checkWin(computerMark)) {
        displayBoard();
        cout << computerMark << " wins!" << endl;
        break;
    }
  }

  return 0;
}

