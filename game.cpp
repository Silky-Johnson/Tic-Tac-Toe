#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class GameBoard;

struct Vec2 {
   int x;
   int y;
};

class GameBoard {
private:
   char board[3][3] = {};
   char oppPiece[1];

   
public:
   char playerPiece[1];

   GameBoard() {
      for (int i = 0; i < 3; i++) {
         for (int k = 0; k < 3; k++) {
            board[i][k] = '.';
         }
      }
   }
   
   /**
    * Sets the players piece variable.
    */
   void setPlayerPiece(char& piece) {
      *playerPiece = piece;
   }
   
   /**
    * Sets the opponents piece. Main Setter.
    */
   void setOppPiece(char& piece) {
      *oppPiece = piece;
   }
   
   /**
    * Sets the players spot, at whichever location the player has chosen.
    */
   void setSpot(Vec2 pos, char& piece) {
      printf("Spot placed X: %d, Y: %d\n\n", pos.x, pos.y);
      board[pos.x][pos.y] = piece;  
   }

   /**
   * Checks to see if a win condition has been met. This will run at the end of
   * the final turn (Turn 4).
   *
   * @return An int, which is the value of the evaluation. If it's 1, player X
   * wins. -1, player O wins. 0 means a draw.
   */ 
   int eval() {
      // Checking rows to see if there's 3 in a row
      for (int i = 0; i < 3; i++) {
         if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == *playerPiece) {
               return +10;
            } else if (board[i][0] == *oppPiece) {
               return -10;
            }
         }
      }

      // Checking columns to see if the are 3 in one column
      for (int i = 0; i < 3; i++) {
         if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == *playerPiece) {
               return +10;
            } else if (board[0][i] == *oppPiece) {
               return -10;
            }
         }
      }

      // Next two if statements check the diagonals to see if there are
      // 3 of the same
      if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
         if (board[0][0] == *playerPiece) {
            return +10;
         } else if (board[0][0] == *oppPiece) {
            return -10;
         }
      }

      if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
         if (board[0][2] == *playerPiece) {
            return +10;
         } else if (board[0][2] == *oppPiece) {
            return -10;
         }
      } 

      // If none of them have won, then we have a draw!
      return 0;
   }

   /**
    * This is the minimax function. Considers all possible
    * ways the game can be played and returns the value of the
    * board.
    *
    * @return a value representing the value of the board.
    */
   int minimax(int depth, bool isPlayer) {
      int score = eval();


      // If X player has won the game, return their
      // evaluated score.
      if (score == 10) {
         return score;
      }

      // If O player has won the game, return their
      // evaluated score.
      if (score == -10) {
         return score;
      }

      // If there are no more moves available,
      // there is no winner and therefor a tie.
      if (isMovesRemaining() == false) {
         return 0;
      }

      // If this is Players move
      if (isPlayer) {
         int best = -1000;

         // Travel all cells
         for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
               // Check if a spot is empty
               if (board[i][k] == '.') {
                  // Make the move
                  board[i][k] = *playerPiece;

                  
                  // Call minimax recursively and choose
                  // the maximum value
                  best = max(best, minimax(depth + 1, !isPlayer));

                  board[i][k] = '.';
               }
            }
         }

         return best;
      } else {
         // This is O move.
         int best = 1000;

         // Travel all cells
         for (int i = 0; i < 3; i++) {
            for (int k = 0; k < 3; k++) {
               // Check if cell is empty
               if (board[i][k] == '.') {
                  board[i][k] = *oppPiece;
                  best = min(best, minimax(depth - 1, isPlayer));

                  board[i][k] = '.';
               }
            }
         }

         return best;
      }
   }

   /**
    * Finds the best move for the opponent
    */
   Vec2 findBestMove() {
      
      int val = -1000;

      Vec2 bestMove;
      bestMove.x = -1;
      bestMove.y = -1;

      for (int i = 0; i < 3; i++) {
         for (int k = 0; k < 3; k++) {
            if (board[i][k] == '.') {
               board[i][k] = *playerPiece;

               // compute the evaluation function for this move.
               int moreVal = minimax(1, false);

               board[i][k] = '.';

               if (moreVal > val) {
                  bestMove.x = i;
                  bestMove.y = k;
                  val = moreVal;
               }
            }
         }
      }

      return bestMove;
   }

   /**
    * Prints the board, showing all empty spaces and places
    * that both Player and Opponent have placed up to the point
    * of the function call.
    */
   void printBoard() {
      for (int i = 0; i < 3; i++) {
         for (int k = 0; k < 3; k++) {
            cout << board[i][k];
         }
         cout << endl;
         
      }
      cout << endl;
   }

   bool checkBoard(Vec2 pos) {
      if (board[pos.x][pos.y] != '.') {
         printf("There is already a spot here! Please choose another\n\n");
         return false;
      }

      return true;
   }

   /**
    * Checks if there are any moves available.
    *
    * @return True if moves spaces are empty, False if all spaces contain X or O
    */
   bool isMovesRemaining() {
      for (int i = 0; i < 3; i++) {
         for (int k = 0; k < 3; k++) {
            if (board[i][k] == '.'){
               return true;
            }
         }
      }

      return false;
   }

  
};

class Player {
private:
   char player_piece[1];

public:
   Player(char& piece) {
      *player_piece = piece;
   }
};

string runGame(GameBoard& board, char& first, char& second, bool isPlayerFirst) {
   Vec2 firstSpot;
   Vec2 secondSpot;
   int rounds = 0;

   while (rounds < 9) {

      if(isPlayerFirst) {
         cout << "Where do you want to place?" << endl;
         cin >> firstSpot.x >> firstSpot.y;

         while (!board.checkBoard(firstSpot)) {
            cin >> firstSpot.x >> firstSpot.y;
         }
         
         board.setSpot(firstSpot, first);

         printf("Now the Opponent will choose a spot\n\n");
         secondSpot = board.findBestMove();

         printf("Opponent has chosen X: %d, Y: %d as their spot.\n\n", secondSpot.x, secondSpot.y);
         board.setSpot(secondSpot, second);
      } else if (!isPlayerFirst) {
         printf("The Opponent will choose their spot first.\n\n");
         firstSpot = board.findBestMove();
         printf("The Opponent has chosen X: %d, Y: %d as their spot.\n\n", firstSpot.x, firstSpot.y);
         board.setSpot(firstSpot, first);

         board.printBoard();

         cout << "Now it is your turn." << endl;
         cout << "Where do you want to place?\n" << endl;
         cin >> secondSpot.x >> secondSpot.y;

         while (!board.checkBoard(secondSpot)) {
            cin >> secondSpot.x >> secondSpot.y;
         }

         board.setSpot(secondSpot, second);
      }
  
      board.printBoard();

      if (board.eval() == 10) {
         return "X Wins!\n";
      } else if (board.eval() == -10) {
         return "O Wins!\n";
      }

      rounds++;
   }

   return "Draw!\n";
}

int main() {
   GameBoard gb = GameBoard();
   string whoWon;
   char playerPiece[1];
   char oppPiece[1];

   cout << "Welcome to Tic Tac Toe!" << endl;
   cout << "What piece do you want? X or O?" << endl;
   cin >> playerPiece;
   cout << endl;
   
   gb.setPlayerPiece(*playerPiece);
   Player player(*playerPiece);

   if (*playerPiece == 'X') {
      *oppPiece = 'O';
      gb.setOppPiece(*oppPiece);

      cout << runGame(gb, *playerPiece, *oppPiece, true) << endl;
   } else {
      *oppPiece = 'X';
      gb.setOppPiece(*oppPiece);

      cout << runGame(gb, *oppPiece, *playerPiece, false) << endl;
   }

   return 0;
}
