#include <stdio.h>
//functions prototypes
void choiceOfPosition();
int legalMove(int grid[81], int location);
int correctMove (int grid[81], int num , int location);
void readgame (int grid[81]);
void displayBoard(int grid[81]);
void getInputs (int grid[81], int *mistakes);
int puzzleSolved (int grid[81]);
void writeGame(int grid[81], int *mistakes);
int exitGame(int grid[81], int *mistakes);
void red();
void blue();
void green();
void reset();

int main(void) {
  int grid[81] ={0};
  int mistakes = 0; 
  int stop;
  choiceOfPosition();
  readgame(grid);
  displayBoard(grid);
  getInputs(grid, &mistakes); //get inputs from user and display current board if input is valid

  if (puzzleSolved(grid)) {
        printf("Puzzle Solved!\n");
    } else {
        printf("Puzzle Not Solved.\n");
    }

    writeGame(grid, &mistakes);
    return exitGame(grid, &mistakes);

  
}


//function to readgame from a file and initializing variables
void readgame (int grid[81]) {
  FILE *originalGridFile;
  int i;
  int done = 0;
  int message = 0;
  originalGridFile = fopen ("Sudoku.txt", "r");
  
  if (originalGridFile == NULL) printf ("Invalid file!");
  
  while (!done) {
    //writing file elements to array
    message = fscanf(originalGridFile, "%d", &grid[i]);
    if (message == EOF) done = 1;
    else i++;
    
    }

  fclose (originalGridFile);
  }

//function to give user a grid for locations in the grid
void choiceOfPosition()
{ 
  int row, column, dash;
  int position = 0;
  printf("\n\nYour possible inputs for locations are:\n\n");
  
  //printing 9 numbers per row with a total of 9 rows
  for (row = 1; row <=9; row++) {
      //constructing the grid layout
      for (dash = 0; dash < 45; dash++) {
        printf("-");
        }
        printf("\n");
      //printing positions 0-80
      for(column = position; column< row*9; column++){
        printf(" %2d |", column);
        position = column+1; 
      }
    printf("\n");
  }
  //constructing the grid layout
  for (dash = 0; dash < 45; dash++) {
        printf("-");
        }
printf ("\n");
}


//function to display the sudoku grid for player to keep track of the game
void displayBoard(int grid[81]){
  int location, row, dash;
  
  printf("\n\n Your current Sudoku game grid is: \n\n ");
  //getting all 80 elements form array "grid"
  for(row = 1; row<=81; row++){
      if(row%9 == 0){
        if(grid[row-1] == 0){
          printf("\n");
          //constructing the grid layout with a space between each row
          if (row % 27 != 0) {
          printf("%13s | %9s |\n", "", "");
          }
        }
        else{
          //print number when the number is not 0
          printf("\t%d\n", grid[row-1]);
          if (row % 27 != 0) {
          printf("%13s | %9s | \n", "", "");}
         }
       }
      
      else if(row%3==0){
        printf("");
        // is number is zero print space 
        if(grid[row-1]==0){
          printf("\t  |");
        } 
        else{
          //number is not zero then print the element from the grid
          printf("\t%d |", grid[row-1]);
        }
      }
        
      // constructing the grid layout with the plus
      else if(row == 28 || row == 55){
        for(dash = 0; dash < 40; dash++){
          if (dash == 14 || dash == 26) {
            blue();
            printf("+");}
          else {
            blue();
            printf("-");
            reset();
            }
        }
        printf("\n");
        if(grid[row-1] == 0){
          printf("\t");
        } else{
          printf("\t%d", grid[row-1]);
        } 
      }
       
      else{
        //if element from grid is 0 print space
        if (grid[row-1] == 0){
        printf("\t ");
      } 
        else{
          //if element from grid is not  0 print element
          printf("\t%d", grid[row-1]);
        }
      }
    }
}


//function to check if the number is not already existing in a row, column and box
int correctMove (int grid[81], int num , int location)
{ 
  
  //check row
  int i;
  
  for (i = (location/9)*9 ; i < ((location/9)+1)*9 ; i++)
  { //checking if the user input number already exists in row, it does return 0 if not return 1
    if (grid[i]==num) {
      return 0;
      }
  }

  //check column
  for (i = 0 ; i < 9 ; i++)
  {  //checking if the user input number already exists in column, it does return 0 if not return 1
    int newlocation = (location%9) +(9*i);
    if (grid[newlocation]==num) {
      return 0;
      }
  }

  //check square
  int squarelocation =0;
  int newsquarelocation = (location/27)*3 +( (location%27)%9)/3;
  for (i=0; i<9; i++)
    {
      squarelocation = (27 * (newsquarelocation/3)) + ((newsquarelocation%3)*3) + ((i/3)*6) +i;
      //checking if the user input number already exists in 3x3 block, it does return 0 if not return 1
      if (grid[squarelocation] == num){
        return 0;
      }
    }
  
return 1;
  
}


//function to check if the location chosen by the user is not already occupied by another number
int legalMove(int grid[81], int location){
      // if user input location is occupied by a number return 0 if not return 1
     if(grid[location] != 0){
       return 0;
       }
  return 1;
}


//function that gets inputs, check if they are valid and display if input is valid 
void getInputs (int grid[81], int *mistakes){
  
  int usernum, userlocation;
  printf ("\n\nValid positions are 0-80\n");
  printf("\nWhat position do you want to play at: \n");
  green();
  scanf("%d", &userlocation);
  reset();//reset to default color
    
  printf ("Valid numbers are 1-9\n");
  printf("What number do you want to add at that position: \n");
  red();
  scanf("%d", &usernum);
  reset();//reset to default color
  
//check if input are in the range of possible inputs   
if ((usernum > 0 && usernum <= 9) && (userlocation >= 0 && userlocation < 81))  {
  if ((correctMove(grid, usernum, userlocation)) && legalMove(grid, userlocation) ){ //valid move
    grid [userlocation] = usernum;
    green();
    displayBoard(grid);
    reset();
    
    puzzleSolved(grid);
    //checking if puzzle is solved then tell the user that they've won
    if (puzzleSolved(grid)) {
      red();
      printf("\nCongratz!! You've solved the Puzzle\n\n");
      reset();
    }
    //giving the user an option of not saving the file and puzzle is not solved; then the game should continue
    if ((!exitGame(grid, mistakes)) && (!puzzleSolved(grid))){
        getInputs(grid, mistakes);
      }
  }
    
  //run only if the move is invalid and counting mistakes
  else{
    *mistakes += 1;
    if ( *mistakes < 4){
    printf ("\nNumber already exists in column or line or grid. Try again!\n");
      if (!exitGame(grid, mistakes)){
        getInputs(grid, mistakes);
      }
      }
    
    else {
      printf("\nYou've reached a total of three mistakes! That's the limit!\n You cannot continue game is next move is invalid\n");
      red();
      printf ("\nPUZZLE NOT SOLVED! GAME OVER\n");
      reset();
      //giving user an option to save the game even though they've made mistakes
      exitGame(grid, mistakes);
      }
    }
  }

//computing for the mistakes if inputs are out of valid range
else{
    *mistakes += 1;
    if ( *mistakes < 3){
    printf("Invalid inputs. Try again!\n\n");
    //giving the user an option of saving game before continuing
    if (!exitGame(grid, mistakes)){
      getInputs(grid, mistakes);
      }
    }
    else {
      printf("\nYou've reached a total of three mistakes! That's the limit!\n");
      red();
      printf ("\nPUZZLE NOT SOLVED! GAME OVER");
      reset();
      //give the user the option of saving the game when 3 mistakes have been made and exit game
      exitGame(grid, mistakes);
      }
  }
}


//check if the last move of user has solved the puzzle
int puzzleSolved (int grid[81])
{
  int i;
  int count=0;
  //checking if all indexes in the array are occupied by non zero numbers
  for (i= 0; i<81; i++){
    if (grid[i] != 0)
      //counting the elements that are not zero or occupied indexes
      count++;}
  //returning 1 if all are occupied and 0 if not all are occupied
  if (count == 81){
    return 1;}
  else {
    return 0;}
}


//write current game into a newfile
void writeGame(int grid[81], int *mistakes){
  FILE *updatedgridfile;
  int i = 0;
  //opening file for writing
  updatedgridfile = fopen("SudokuSave.txt", "w");
  //writing all elements of the array into the grid
  while(i<81){
    fprintf(updatedgridfile,"%d ", grid[i]);
    i++;
  }
  //closing file
  fclose(updatedgridfile);

  //openig file for appending an element at the end
  updatedgridfile = fopen("SudokuSave.txt", "a");
  fprintf(updatedgridfile, "%d ", *mistakes);
  fclose(updatedgridfile);
}


//exit and save game or continue and do not save game function
int exitGame(int grid [81], int *mistakes) {
  int stop;
  printf("\n\nWould you like to save the game: \n(1) enter any number to continue and to not save the game \n(2) enter -1 to exit and save: \n\n");
  scanf ("%d", &stop);
  if (stop == -1){
    //save game if user choose to exist and return 1/true
    writeGame(grid, mistakes);
    blue();//color
    printf("Your game file has been saved to SudokuSavedFile.txt file\n");
    reset();
    return 1;
    }
blue();
printf("File not saved.\n");
reset();//reset to default color
return 0;
}

//THE COLORS FUNCTIONS WERE FECTCHED FROM https://www.theurbanpenguin.com/4184-2/

//colors functions
void red () {
  printf("\033[1;31m");
}

void blue () {
  printf("\033[0;34m");
}

void green (){
  printf("\033[0;32m");
  }

//function to reset to default coor
void reset () {
  printf("\033[0m");
}

