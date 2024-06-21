#include <iostream>
using namespace std;

int place(bool** board, int n, int row, int startCol) {
  int placedPos = -1;
  for (int i = startCol; i < n; i++) {
    if (board[row][i] == 1) continue;

    placedPos = i;

    // Mark horizontally
    for (int j = 0; j < n; j++) {
      board[row][j] = 1;
    }

    // Mark vertically
    for (int j = 0; j < n; j++) {
      board[j][i] = 1;
    }

    // Mark diagonally
    for (int j = 1; j < n; j++) {
      if (row + j < n) {
        if (i - j >= 0) board[row + j][i - j] = 1;
        if (i + j < n) board[row + j][i + j] = 1;
      }
      if (row - j >= 0) {
        if (i - j >= 0) board[row - j][i - j] = 1;
        if (i + j < n) board[row - j][i + j] = 1;
      }
    }

    break;
  }

  return placedPos;
}

void queens(int n) {
  bool** board = new bool*[n];

  for (int i = 0; i < n; i++) {
    board[i] = new bool[n]{0};
  }

  // Save previous queens
  int* pos = new int[n]{0};
  
  int row = 0;
  int startCol = 0;
  bool possible = true;

  int result;
  while (pos[0] < n) {
    if(startCol == n)
      break;

    while (row < n) {
      result = place(board, n, row, startCol);
      if (result != -1) {
        // Save the queen's position
        pos[row] = result;
        // Move to the next row
        row++;
        // Start from the beginning of the board
        startCol = 0;
      } else {
        // Go back a row
        row--;
        
        // Start placing the queen in the previous row one column further
        startCol = pos[row] + 1;

        if (startCol == n || row < 0) {
          possible = false;
          break;
        }

        // Reset the board
        for (int x = 0; x < n; x++) {
          for (int y = 0; y < n; y++) {
            board[x][y] = 0;
          }
        }

        // Place back previous queens
        for (int x = 0; x < row; x++) {
          place(board, n, x, pos[x]);
        }
      }
    }

    // Reset the board
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        board[x][y] = 0;
      }
    }

    // Print the results
    if(possible){
      for(int x = 0; x < n; x++){
          for(int y  = 0; y < n; y++){
            if(pos[x] == y)
              cout << "X";
            else
              cout << "O";
            cout << "\t";
          }
          cout << endl;
      }
      cout << endl << endl;
    }

    // Reset and start one field further
    possible = true;
    row = 0;
    startCol = pos[0] + 1;
  }
}

int main() {
  cout << "Program do rozwiazywania problemu n-hetmanow" << endl;
  cout << "Lukasz Konieczny | LK4 | LAB 9" << endl << endl;
  cout << "Podaj liczbe n: ";
  
  int n;
  cin >> n;

  if(n < 1){
    cout << "Niepoprane n!";
    exit(-1);
  }

  cout << endl;
  queens(n);
  return 0;
}