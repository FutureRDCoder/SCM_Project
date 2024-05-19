#include <iostream>
#include <limits> // for numeric input validation

using namespace std;

// Function to get user input as a string
string getStringInput(const string& prompt) {
  cout << prompt << ": ";
  string input;
  getline(cin, input);
  return input;
}

// Function to get user input as an integer within a specified range
int getIntegerInput(const string& prompt, int min, int max) {
  int input;
  while (true) {
    cout << prompt << " (" << min << "-" << max << "): ";
    if (cin >> input) {
      // Clear the input stream buffer (handle potential newline character)
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      if (input >= min && input <= max) {
        return input;
      } else {
        cout << "Invalid input. Please enter a number between " << min << " and " << max << endl;
      }
    } else {
      // Handle non-numeric input
      cout << "Invalid input. Please enter a number." << endl;
      cin.clear(); // Clear the error state from the input stream
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
}

// Function to get user input as a character (single character)
char getCharInput(const string& prompt) {
  char input;
  cout << prompt << ": ";
  cin >> input;
  // Clear the input stream buffer (handle potential newline character)
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return input;
}

int main() {
  // Example usage of the input functions
  string name = getStringInput("Enter your name");
  int age = getIntegerInput("Enter your age", 18, 120);
  char initial = getCharInput("Enter your initial");

  cout << "Hello " << name << ", you are " << age << " years old and your initial is " << initial << endl;

  return 0;
}

