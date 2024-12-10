// Name:
// Student Number:

#include <iostream>
#include <fstream>  // for file input and output
#include <iomanip>  // std::setw
#include <climits>  // INT_MIN
#include  <cmath>
#include "Game.h"

// represent an empty spot in the grid
const int Game::EMPTY = INT_MIN;

// width of a number
const int Game::OUT_WIDTH = 2;
// output that the position is empty
const char Game::OUT_BLANK = ' ';
// should be as long as WIDTH + 1
const std::string Game::OUT_ROOF = "---"; 
// output a wall around the number
const char Game::OUT_WALL = '|';
// corner of a number
const char Game::OUT_CORNER = '+';

// create an empty game 
// setting dimensions to be 0 , no of sol  0 , no of assignment operation  0
Game::Game() {
     this->array = new int*;
     
     this->dim  =  0  ;
     this->nSol =  0;
     this->nWork =  0;
     

}
// simple return dimenstion

bool Game::isEmpty() const {

    return ( this->dim ==0);
}
// check for row  col and quadrant  , i am using root of n to find quadrant position
 bool Game::check(int** arr , int x  , int y,int n){
         
         // checking in row
         
         for(int  i =0 ; i<n;i++){
               if(arr[x][i] == arr[x][y]){
                  if( i != y){
                     return false;
                  }
               }
         }
         // checking in column
         for( int i =0 ; i< n ; i++){
            if( arr[i][y] == arr[x][y]){
               if( i != x){
                  return false;
               }
            }
         }
         // checking for quadrals
         //find starting x and y using division of x and y by root 
         // then just run  double loop to traverse throgh 
         int root = sqrt(n);
         int rStarter  = ( (y/root)*root) ;
         int cStarter = ((x/root)*root) ;
         for( int  i =0 ; i<root ; i++){
            for(int j =0 ; j< root ; j++){
               if(arr[cStarter+i][rStarter+j] == arr[x][y]){
                  if((cStarter+i != x) && (rStarter  + j) != y){
                     return false;
                  }
               }
            }
         }
         return true;

}

      // Solve recursive backtrack function
      //Algo : base case  :check if we are out of arry : means we already found a solution : increase the nsol ++ and output the array 
      //                  to output file return back
      //      otherwise if there is already an elemt at  xy go to next position else try to place 1 to n ints and check if it safe go to next 
      //     positoin and then backtrack for next int , at last place MIN_INT 
 void Game::solve( int x  , int y ,std::ostream& out,Game &g ){
         int n = g.dim;
         
         if( x >= g.dim){
            g.nSol++;
            out<<g;
            

            return ;
         }
         if(g.array[x][y] != Game::EMPTY){
            if( y < n-1){
                solve(x , y+1  , out,  g);
            }else{
                solve(x+1,0,out,g);
            }
         }
          else{
         for(int  i = 1  ; i <= n ; i++){
            
              g.array[x][y] = i;
              g.nWork++;
              if(check(g.array,x,y,n)){
                   if( y  < n-1){
                     solve(x,y+1 ,out,g);
                   }else{
                     solve(x+1, 0,out , g);
                   }
              }
              g.array[x][y] = Game::EMPTY; // backtrack
                 
         }
      }
      }
// find all the possible solutions
// count the number of solutions possible
// compute the work done
// output each solution using the output stream out
// if the dimension() is zero, do nothing
// precondition: out is open
void Game::solve(std::ostream& out){
   if(this->isEmpty()){
      return;
   }
   else{
   Game::solve(0,0,out,*this);                  // calling recursive backtarck function
   }
}

int Game::numberOfSolutions() const {
     
     return this->nSol;

}


long Game::workAssigns() const {
  
     return this->nWork;
}

int Game::dimension() const {

   return this->dim;
}


// if there was a dynamically allocated array already, deallocate it
// precondition: in is open
std::istream& operator >> (std::istream& in, Game& g){
        
        if(g.dim !=0){                              // if there is dim mean there is array so delete prev array
         for(int i =0 ; i<g.dim ; i++){
            delete []g.array[i];
         }
         delete []g.array;
        }
        int rows  ;
        int cols ;
        in>>rows;
        
        in>>cols;
       
        g.dim = rows;
        g.array= new int*;                             //intialize each elemt of array or board to INT_MIN
        for(int i = 0 ;  i < rows ;i++){
            g.array[i]= new int[cols];
            for(int j =0 ; j<cols ; j++){
               g.array[i][j] = Game::EMPTY;
            }
        }
        
        int x  ;
        int y ;                                   // put given values to array or board
        int num ;
        while(in>>x){
         
            
            in>>y;
            in>>num ;
            g.array[x-1][y-1] = num ;
           
        }
        

   return in;
}

// pretty printing
void Game::printHorizontalLine(int n, std::ostream& out) {
   out << OUT_CORNER;
   for (int i = 0; i < n; i++)  {
      out << OUT_ROOF << OUT_CORNER;
   }
   out << std::endl;
}

// pretty printing
// CPSC 2150
// fix the code below so that your instance variable for the 
// dimension replaces the local variable yourInstanceVariable
// yourInstanceVariable corresponds to the number of rows (and columns) 
// fix the for loops
// output correct values
void Game::printBoard(std::ostream& out) const {
   int yourInstanceVariable = this->dim; // CPSC 2150 remove, fix
   //std::cout<<" the instance variable is "<<yourInstanceVariable<<std::endl;
   // print a top line
   printHorizontalLine(yourInstanceVariable, out);
   for (int i = 1; i <= yourInstanceVariable; i++) {
      out << OUT_WALL;
      for (int j = 1; j <= yourInstanceVariable; j++) {
         out << std::setw(Game::OUT_WIDTH);

         out << this->array[i-1][j-1]; // BOGUS VALUE !!!!!!!! CPSC 2150 fix

         out << OUT_BLANK << OUT_WALL;
      } // for j
      out << std::endl;
      printHorizontalLine(yourInstanceVariable, out);
   } // for i
   out << std::endl;
}

// precondition: out is open
std::ostream& operator << (std::ostream& out, const Game& g) {
   if (!g.isEmpty()){
     // std::cout<<" dimensions i s"<<g.dim<<std::endl;
      g.printBoard(out);
   }
   return out;

}

// delete array  and making new deep copoy of other  array and other vaiables as  well
Game::Game(const Game& other) {
         
            for(int  i =0  ; i < this->dim ; i++){
               delete []this->array[i];
            }
            delete [] this->array;
            this->dim =  other.dim;
            this->nSol= other.nSol;
            this->nWork = other.nWork;
            this->array = new int*;
            for( int i =0 ; i< this->dim  ; i++){
               this->array[i]= new int[this->dim];
               for(int j =0 ; j<this->dim ; j++){
                  this->array[i][j] = other.array[i][j];
               }
            }

        

}
//simply  deep copy array and other variable and delete current array before

Game& Game::operator = (const Game& rtSide) {
      
        
        for(int  i =0  ; i < this->dim ; i++){
               delete []this->array[i];
            }
            delete  []this->array;

      this->array = new int* ;
      this->dim = rtSide.dim;
      this->nSol = rtSide.nSol;
      this->nWork = rtSide.nWork;

      for( int  i =0 ; i <rtSide.dim ; i++ ){
         this->array[i] = new int[rtSide.dim];
         for( int  j=0 ; j<rtSide.dim ; j++){
            this->array[i][j] = rtSide.array[i][j];
         }
      }

      return *this;
}

Game::~Game() {

        for(int  i =0  ; i < this->dim ; i++){
               delete []this->array[i];
            }
            delete  []this->array;
}

