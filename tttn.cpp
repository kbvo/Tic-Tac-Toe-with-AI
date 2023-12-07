// NxN tic-tac-toes
#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);


/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    return grid[(r * dim) + c];
}

int idxToRow(int idx, int dim)
{
    return idx / dim;
}

int idxToCol(int idx, int dim)
{
    return idx % dim;
}

void printTTT(char grid[], int dim)
{ 
  // prints entries at row i, column j
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      cout << " " << getEntryAtRC(grid, dim, i, j) << " ";
      // prints vertical seperators between columns if its not the last column
      if (j < dim - 1) {
        cout << "|";
      }
    }
    cout << endl;
    // prints horizontal seprators bewteen rows if it is not the last row
    if (i < dim - 1) {
      for (int j = 0; j < dim - 1; j++) {
        cout << "----"; // prints 4 dashes for every column except the last one
      }
      cout << "---"; // print 3 dashes for the last column
      cout << endl;
    }
  }
}

int checkForWinner(char grid[], int dim)
{
  // checks rows
  for (int i = 0; i < dim; i++) {
    bool isWinner = true;
    // assigns leftmost entry of the row to leftEntry
    char leftEntry = getEntryAtRC(grid, dim, i, 0);
    // compares leftmost entry to the entries to its right
    for (int j = 1; j < dim; j++) {
      // stops comparison if those entries do not match leftEntry (no winner)
      if (leftEntry != getEntryAtRC(grid, dim, i , j)) {
        isWinner = false;
        break;
      }
    }
    // if there is a winner that is either X or O
    if (isWinner && leftEntry != '?') {
      // X wins
      if (leftEntry == 'X') {
        return 1;
      }
      // O wins
      else if (leftEntry == 'O') {
        return 2;
      }
    }
  }
  
  // checks columns
  for (int j = 0; j < dim; j++) {
    bool isWinner = true;
    // assigns topmost entry of the column to topEntry
    char topEntry = getEntryAtRC(grid, dim, 0, j);
    // compares topmost entry to the entries beneath it
    for (int i = 1; i < dim; i++) {
      // stops comparison if those entries do not match topEntry (no winner)
      if (topEntry != getEntryAtRC(grid, dim, i, j)) {
        isWinner = false;
        break;
      }
    }
    // if there is a winner that is either X or O
    if (isWinner && topEntry != '?') {
      // X wins
      if (topEntry == 'X') {
        return 1;
      }
      // O wins
      else if (topEntry == 'O') {
        return 2;
      }
    }
  }
  
  // check diagonal (top left to bottom right)
  char topLeftEntry = getEntryAtRC(grid, dim, 0, 0);
  // declare boolean that is in scope of entire checkForWinner function
  bool isWinner = true;
  // compares top left entry to the entries in its diagonal
  for (int i = 1; i < dim; i++) {
    // stops comparison if those entries do not match topLeftEntry (no winner)
    if (topLeftEntry != getEntryAtRC(grid, dim, i, i)) {
      isWinner = false;
      break;
    }
  }
  // if there is a winner that is either X or O
  if (isWinner && topLeftEntry != '?') {
    // X wins
    if (topLeftEntry == 'X') {
      return 1;
    }
    // O wins
    else if (topLeftEntry == 'O') {
      return 2;
    }
  }
  
  // check diagonal (top right to bottom left)
  char topRightEntry = getEntryAtRC(grid, dim, 0, dim - 1);
  // Resets isWinner value from previous diagonal check since it's in scope
  isWinner = true;
  // compares top right entry to the entries in its diagonal
  for (int i = 1; i < dim; i++) {
    // stops comparison if those entries do not match topRightEntry (no winner)
    if (topRightEntry != getEntryAtRC(grid, dim, i, dim - 1 - i)) {
      isWinner = false;
      break;
    }
  }
  // if there is a winner that is either X or O
  if (isWinner && topRightEntry != '?') {
    // X wins
    if (topRightEntry == 'X') {
      return 1;
    }
    // O wins
    else if (topRightEntry == 'O') {
      return 2;
    }
  }
  return 0; // no winner found yet
}

bool checkForDraw(char grid[], int dim)
{
  // check rows for X and O
  for (int i = 0; i < dim; i++) {
    bool hasX = false, hasO = false;
    for (int j = 0; j < dim; j++) {
      char entry = getEntryAtRC(grid, dim, i, j);
      if (entry == 'X') {
        hasX = true;
      }
      if (entry == 'O') {
        hasO = true;
      }
    }
    // there is not at least 1 X or O in the row (no draw)
    if (!hasX || !hasO) {
      return false;
    }
  }

  // check columns for X and O
  for (int j = 0; j < dim; j++) {
    bool hasX = false, hasO = false;
    for (int i = 0; i < dim; i++) {
      char entry = getEntryAtRC(grid, dim, i, j);
      if (entry == 'X') {
      hasX = true;
      }
      if (entry == 'O') {
      hasO = true;
      }
    }
    // there is not at least 1 X or O in the column (no draw)
    if (!hasX || !hasO) {
      return false;
    }
  }

  // declare booleans that are in scope of entire checkForDraw function
  bool hasX = false, hasO = false;
  // check diagonal for X and O (top left to bottom right)
  for (int i = 0; i < dim; i++) {
    char entry = getEntryAtRC(grid, dim, i, i);
    if (entry == 'X') {
      hasX = true;
    }
    if (entry == 'O') {
      hasO = true;
    }
  }
  // there is not at least 1 X or O in the diagonal (no draw)
  if (!hasX || !hasO) {
    return false;
  }
  
  // Reset booleans values from previous diagonal since they
  // are still in scope of the entire checkForDraw function
  hasX = false, hasO = false;
  // check diagonal for X and O (top right to bottom left)
  for (int i = 0; i < dim; i++) {
    char entry = getEntryAtRC(grid, dim, i, dim - i - 1);
    if (entry == 'X') {
      hasX = true;
    }
    if (entry == 'O') {
      hasO = true;
    }
  }
  // there is not at least 1 X or O in the diagonal (no draw)
  if (!hasX || !hasO) {
    return false;
  }
  else {
    // there is a draw (X and O present in every row, column, and diagonal)
    return true;
  }
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  // if the AI is playing with O
  if (player == 'O') {
  // check if AI can win on current move
  for (int i = 0; i < dim * dim; i++) { // iterate through grid[]
    if (grid[i] == '?') { // if AI can place O on grid[i]
      grid[i] = 'O'; // Place O on grid[i]
      // if that is winning move for AI
      if (checkForWinner(grid, dim) == 2) {
        return false; // it is a winning move for AI (play sucessful)
      }
      // If not a winning move then undo O placement on 
      // grid[i] to check next grid[i] for winning move
      grid[i] = '?';
    }
  }
  // check if AI has to block player's potential winning move
  for (int i = 0; i < dim * dim; i++) { // iterate through grid[]
    if (grid[i] == '?') { // if player can place X on grid[i]
      grid[i] = 'X'; // place X on grid[i]
       // if that is winning move for player X
      if (checkForWinner(grid, dim) == 1) {
        grid[i] = 'O'; // block player move
        return false; // play sucessful
      }
      // If not a blocking move then undo X placement on
      // grid[i] to check next grid[i] for blocking move
      grid[i] = '?';
    }
  }
  // if AI can't win or block, it makes a random move
  return getRandChoiceAndUpdateGrid(grid, dim, player);
  }

  // if the AI is playing with X
  if (player == 'X') {
  // check if AI can win on current move
  for (int i = 0; i < dim * dim; i++) { // iterate through grid[]
    if (grid[i] == '?') { // if AI can place X on grid[i]
      grid[i] = 'X'; // Place X on grid[i]
      // if that is winning move for AI
      if (checkForWinner(grid, dim) == 1) {
        return false; // it is a winning move for AI (play sucessful)
      }
      // If not a winning move then undo O placement on 
      // grid[i] to check next grid[i] for winning move
      grid[i] = '?';
    }
  }
  // check if AI has to block player's potential winning move
  // iterate through grid[]
  for (int i = 0; i < dim * dim; i++) {
    if (grid[i] == '?') { // if player can place O on grid[i]
      grid[i] = 'O'; // place O on grid[i]
       // if that is winning move for the player
      if (checkForWinner(grid, dim) == 2) {
        grid[i] = 'X'; // block player move
        return false; // play sucessful
      }
      // If not a blocking move then undo X placement on
      // grid[i] to check next grid[i] for blocking move
      grid[i] = '?';
    }
  }
  // if AI can't win or block, it makes a random move
  return getRandChoiceAndUpdateGrid(grid, dim, player);
  }
}


// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player)
{
    int start = rand()%(dim*dim);
    // look for an open location to play based on random starting location.
    // If that location is occupied, move on sequentially until wrapping and
    // trying all locations
    for(int i=0; i < dim*dim; i++) {
        int loc = (start + i) % (dim*dim);
        if(grid[ loc ] == '?') {
            grid[ loc ] = player;
            return false;
        }
    }
    // No viable location
    return true;
}


/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main()
{
    // This array holds the actual board/grid of X and Os. It is sized
    // for the biggest possible case (11x11), but you should only
    // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
    char tttdata[121];

    // dim stands for dimension and is the side length of the
    // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
    int dim;
    int seed;
    // Get the dimension from the user
    cin >> dim >> seed;
    srand(seed);

    int dim_sq = dim*dim;

    for(int i=0; i < dim_sq; i++) {
        tttdata[i] = '?';
    }

    // Print one of these messages when the game is over
    // and before you quit
    const char xwins_msg[] = "X player wins!";
    const char owins_msg[] = "O player wins!";
    const char draw_msg[] =  "Draw...game over!";

    bool done = false;
    char player = 'X';
    // Show the initial starting board
    printTTT(tttdata, dim);

    while(!done) {

        //**********************************************************
        // Get the current player's input (i.e. the location they want to
        // choose to place their mark [X or O]) or choice of AI or Random
        // location and update the tttdata array.
        // Be sure to follow the requirements defined in the guide/writeup
        // for quitting immediately if the user input is out-of-bounds
        // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
        // continuing to prompt for an input if the user chooses locations
        // that have already been chosen (already marked with an X or O).
        //**********************************************************

        // the square the player chooses to play on (can also be AI or random)
        int squareChoice;
        
        bool isOccupied = true; // allows prompt to be printed initially
        
        // Keeps printing prompt if player chooses 
        // a square that is occupied by X or O
        while (isOccupied) {
          cout << "Player " << player << " enter your square choice [0-24], -1 (AI), or -2 (Random):\n";
          cin >> squareChoice;
          // ifSquare choice is not occupied by X or O, or is out of bounds
          if (tttdata[squareChoice] == '?' || squareChoice < 0 || squareChoice >= dim_sq) {
            isOccupied = false; // break loop
          }
        }
        
        // if player uses the AI
        if (squareChoice == -1) {
          getAiChoiceAndUpdateGrid(tttdata, dim, player);
        }
        // if player wants a random square
        else if (squareChoice == -2) {
          getRandChoiceAndUpdateGrid(tttdata, dim , player);
        }
        // if player's input is out of bounds of the grid
        else if (squareChoice < 0 || squareChoice >= dim_sq) {
          return 0;
        }
        // else player's choice is valid and places entry on squareChoice
        else {
          tttdata[squareChoice] = player;
        }
        
        // Show the updated board if the user eventually chose a valid location
        // (i.e. you should have quit the loop and program by now without any
        //  other output message if the user chosen an out-of-bounds input).
        printTTT(tttdata, dim);

        //**********************************************************
        // Complete the body of the while loop to process the input that was just
        //  received to check for a winner or draw and update other status, as
        //  needed.
        //
        // To match our automated checkers' expected output, you must output
        // one of the messages defined above using *one* of the cout commands
        // (under the appropriate condition) below:
        //   cout << xwins_msg << endl;  OR
        //   cout << owins_msg << endl;  OR
        //   cout << draw_msg << endl;
        //
        // Note: Our automated checkers will examine a specific number of lines
        //  at the end of the program's output and expect to see the updated board
        //  and game status message.  You may certainly add some debug print
        //  statements during development but they will need to be removed to
        //  pass the automated checks.
        //**********************************************************
        
        // check win and draw conditions
        if (checkForWinner(tttdata, dim) == 1) { // X wins
          cout << xwins_msg << endl;
          done = true; // game ends
        }
        else if (checkForWinner(tttdata, dim) == 2) { // O wins
          cout << owins_msg << endl;
          done = true; // game ends
        }
        else if (checkForDraw(tttdata, dim)) { // there is a draw
          cout << draw_msg << endl;
          done = true; // game ends
        }

        // switch to other player's turn if game is not over
        if (player == 'X') { // if player X was playing switch to player O
          player = 'O';
        }
        else if (player == 'O') { // if player O was playing switch to player X
          player = 'X';
        }
    } // end while
    return 0;
}