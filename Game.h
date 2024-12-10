// Name: charanjit singh
// Student Number: 100334202

#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game {
   public:
      // create an empty game
      Game();

      // return true if there are no numbers (that have been read)
      // false otherwise
      // if an attempt is made to read values but this fails, isEmpty is true
      bool isEmpty() const;

      

      // solve the game
      // precondition: data has been read having used the input operator >>
      //               and an open input stream
      // output ALL the solution
      // each solution is printed using 
      // the operator << and the passed output stream out
      void solve(std::ostream& out);

      // after calling solve, numberOfSolutions returns how many solutions
      // were computed (and printed) during the last call to solve
      // return the number of solutions
      int numberOfSolutions() const;

      // after calling solve, workAssigns returns how many assignments 
      // to the board were made during the last call to solve
      // return the number of work assignments
      long workAssigns() const;

      // return the side of the board 
      // return the number of rows which is the number of columns
      // possible value of a board is 1, 2, ..., dimension
      // the dimension is set on input
      // typical values returned are 4 or 9 or 16
      int dimension() const;

      // read the number of rows and number of columns
      // expected first are two integers corresponding to the rows and columns
      //   if rows is not equal to columns, DO NOTHING
      //   the rows should be equal to the columns and
      //   this number becomes the dimension of the board
      // afterwards, until the end of file 
      // read all the positions in the format
      //    i  j  num
      // where 
      //    1 <= i <= dimension()
      //    1 <= j <= dimension()
      //    1 <= num <= dimension()
      // assume that all the other spots not given in the stream are empty
      // set the dimension inside of the operator >> 
      friend std::istream& operator >> (std::istream& in, Game&);

      // a pretty printed board
      friend std::ostream& operator << (std::ostream& out, const Game&);
      
      // copy constructor
      Game(const Game&);  
   
      // overloaded assignment operator
      Game& operator = (const Game&);
   
      // destructor
      ~Game();
       
   private:
       

      // CPSC 2150 add here
      int** array ;    // 2d array for storing
      int dim  ;            // dimensions
      int nSol  ;         // no of solution , it is increasing in the base case of solve function for evry 1 solution
      int nWork ;         // no of assignments , increaing in solve finction , whenever an assignment happens

     static void solve(int x , int  y , std::ostream& out,Game& g );    // Backtrack recursive function 
     static bool check(int** arr , int x  , int y,int n);               // simple function to check conditon for arr[x][y] element

     
     
      // represent a empty spot in the board
      static const int EMPTY;

      // for pretty printing
      // width of a cell for up to 2 digits
      static const int OUT_WIDTH;
      // roof of a cell
      static const std::string OUT_ROOF; 
      // vertical wall around a cell
      static const char OUT_WALL;
      // show that the board is empty
      static const char OUT_BLANK;
      // corner of a cell
      static const char OUT_CORNER;

      static void printHorizontalLine(int n, std::ostream& out);

      // pretty print the nxn board to standard output
      // note that it is printed with the highest row first down to the 0th row
      void printBoard(std::ostream& out) const;

};
#endif

// copyright 2022 Gladys Monagan
