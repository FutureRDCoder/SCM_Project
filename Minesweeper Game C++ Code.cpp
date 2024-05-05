#include <iostream>
#include <vector>
#include <ctime>
#include <thread>

using namespace std;

const int ROWS = 9;
const int COLS = 9;
const int NUM_MINES = 10;

char board[ROWS][COLS];
bool revealed[ROWS][COLS];
int flags[ROWS][COLS];

bool gameOver = false;
int timeLeft = 600; // 10 minutes in seconds

void initializeBoard() {
  // Fill with empty cells
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = ' ';
      revealed[i][j] = false;
      flags[i][j] = 0;
    }
  }

  // Place mines randomly
  srand(time(0));
  for (int i = 0; i < NUM_MINES; i++) {
    int row = rand() % ROWS;
    int col = rand() % COLS;
    if (board[row][col] == ' ') {
      board[row][col] = 'M';
    } else {
      i--; // Place again if there's already a mine
    }
  }

  // Calculate surrounding mines for each cell (except mines)
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] != 'M') {
        int count = 0;
        for (int di = -1; di <= 1; di++) {
          for (int dj = -1; dj <= 1; dj++) {
            int ni = i + di;
            int nj = j + dj;
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS && board[ni][nj] == 'M') {
              count++;
            }
          }
        }
        board[i][j] = count + '0';
      }
    }
  }
}

void displayBoard() {
  system("clear"); // Clear the screen
  cout << "  ";
  for (int i = 0; i < COLS; i++) {
    cout << i << " ";
  }
  cout << endl;

  for (int i = 0; i < ROWS; i++) {
    cout << i << " ";
    for (int j = 0; j < COLS; j++) {
      if (revealed[i][j]) {
        if (flags[i][j]) {
          cout << "F ";
        } else {
          cout << board[i][j] << " ";
        }
      } else {
        cout << "* ";
      }
    }
    cout << endl;
  }

  cout << "Time Left: " << timeLeft / 60 << ":" << timeLeft % 60 << endl;
}

bool isValidMove(int row, int col) {
  return row >= 0 && row < ROWS && col >= 0 && col < COLS && !revealed[row][col];
}

void revealCell(int row, int col) {
  if (!isValidMove(row, col)) {
    return;
  }
  revealed[row][col] = true;

  if (board[row][col] == 'M') {
    gameOver = true;
    return;
  }

  if (board[row][col] == '0') {
    // Flood fill to reveal all empty cells connected
    for (int di = -1; di <= 1; di++) {
      for (int dj = -1; dj <= 1; dj++) {
        revealCell(row + di, col + dj);
      }
    }
  }
}

void toggleFlag(int row, int col) {
  if (!isValidMove(row, col)) {
    return;
  }
  flags[row][col] = !flags[row][col];
}

void handleInput() {
  int row, col, action;
  char input;

  cout << "Enter row, column (e.g., 3 2) and action (R: reveal, F: flag): ";
  cin >> row >> col >> input;

  action = (input == 'R') ? 1 : 0; // 1 for reveal, 0 for flag

  if (action == 1) {
    revealCell(row, col);
  } else {
    toggleFlag(row, col);
  }
}

// Timer thread function
void timerThread() {
  while (timeLeft > 0 && !gameOver) {
    this_thread::sleep_for(chrono::seconds(1));
    timeLeft--;
  }

  if (gameOver) {
    cout << "You Lose!" << endl;
  } else {
    cout << "You Win!" << endl;
  }
}

int main() {
  initializeBoard();

  // Start timer thread
  thread timer(timerThread);

  while (!gameOver && timeLeft > 0) {
    displayBoard();
    handleInput();
  }

  timer.join(); // Wait for timer thread to finish

  return 0;
}

