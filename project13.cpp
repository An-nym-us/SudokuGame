/***********************************************************************
* Program:
*    Project 13, Sudoku          
*    Brother Foushee, CS124
* Author:
*    Jonathan Gunderson
* Summary:
*    This program is an interactive Sudoku game that a user can
* solve. THis program will also offer hints to possible values
* for different squares.
* 
*
*    Estimated:  10.0 hrs
*    Actual:     16.0 hrs
*      
* This was a difficult project for sure. For me, the hardest part was
* The check board system to make sure that the user values are valid 
* for entry. There was a lot of things to manage and make sure 
* worked together. If asked to make this program form the ground up 
* again, there would be a ton of things I would do differently. More
* Than I could list in a single paragraph. 
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>
#include <iomanip>

using namespace std;




/**********************************************************************
 * This will display possible values to the user.
 * It is also an error checker, making sure that all user entered
 * Values are valid.
 ***********************************************************************/
bool isBoardValid(char arrRead[9][9], 
   int rowTest, 
   int colTest, 
   int userValue, 
   bool displayResults)
{
  // these will be converted into coordinates values entered by the user.
  

   int testBoardRow[9] = { 0,0,0,0,0,0,0,0,0 };
   int testBoardCol[9] = { 0,0,0,0,0,0,0,0,0 };
   int testBoardSquare[9] = { 0,0,0,0,0,0,0,0,0 };
   int outPutArray[9] = { 1,2,3,4,5,6,7,8,9 };

   char swapForm[2];
   char displayRow[2];

   bool hasValidOut = false;
   bool doOnce = true;

   int displayCol = 0;
   int commaTracker = 0;
   int squareFoundRow = 0; // This value will be either 0 , 3 , or 6
   int squareFoundCol = 0; // This value will be either 0 , 3 , or 6



   // locate the correct square.
   
   if (rowTest >= 0 && rowTest <= 2)
   {
      squareFoundRow = 0;
   }
   else if (rowTest >= 3 && rowTest <= 5)
   {
      squareFoundRow = 3;
   }
   else if (rowTest >= 6 && rowTest <= 9)
   {
      squareFoundRow = 6;
   }

   if (colTest >= 0 && colTest <= 2)
   {
      squareFoundCol = 0;
   }
   else if (colTest >= 3 && colTest <= 5)
   {
      squareFoundCol = 3;
   }
   else if (colTest >= 6 && colTest <= 9)
   {
      squareFoundCol = 6;
   }



   // read values for row place them in test array.
   for (int i = 0; i < 9; i++)
   {
      if (isdigit(arrRead[i][rowTest]))
      {
         swapForm[0] = arrRead[i][rowTest];
         testBoardRow[i] = swapForm[0] - 48;
      }
   }



   // read values for col place them into test array
   for (int i = 0; i < 9; i++)
   {
      if (isdigit(arrRead[colTest][i]))
      {
         swapForm[0] =  arrRead[colTest][i];
         testBoardCol[i] = swapForm[0] - 48;
      }    
   }

   
   // read values in each square place them into a test array.

   int lineTracker = 0;

   for (int i = squareFoundRow; i < squareFoundRow + 3; i++)
   {
      for (int j = squareFoundCol; j < squareFoundCol + 3; j++)
      {         
         if (isdigit(arrRead[j][i]))
         {          
            swapForm[0] = arrRead[j][i];
            testBoardSquare[lineTracker] = swapForm[0] - 48;
            lineTracker++;
         }
      }
   }
   



   // this will burn through the Row Array
   // run through test array.
   for (int i = 0; i < 9; i++)
   {
     // run through output array.
      for (int j = 0; j < 9; j++)
      {
         if (testBoardRow[j] == outPutArray[i])
         {
            outPutArray[i] = -1;
         }
      }
   }



   // this will burn through the Col Array
   // run through test array.
   for (int i = 0; i < 9; i++)
   {
      // run through output array.
      for (int j = 0; j < 9; j++)
      {
         if (testBoardCol[j] == outPutArray[i])
         {
            outPutArray[i] = -1;
         }
      }
   }




   // this will burn through the square Array
   // run through test array.
   for (int i = 0; i < 9; i++)
   {
      // run through output array.
      for (int j = 0; j < 9; j++)
      {
         if (testBoardSquare[j] == outPutArray[i])
         {
            outPutArray[i] = -1;
         }

      }
   }

   


   if (displayResults == true)
   {
      displayCol = colTest + 1;
      displayRow[0] = rowTest + 65;

      cout << "The possible values for \'"   
         << displayRow[0]
         << displayCol
         << "\' are: ";

      for (int i = 0; i < 9; ++i)
      {
         
         if (outPutArray[i] != -1)
         {
            commaTracker++;

         }
      }

      for (int i = 0; i < 9; ++i)
      {
         if (outPutArray[i] != -1 && commaTracker > 1 )
         {
            commaTracker--;
            cout << outPutArray[i] << ", ";
         }
         else if (outPutArray[i] != -1)
         {
            cout << outPutArray[i];
         }
      }
      cout << "\n";
   }






   for (int i = 0; i < 9; i++)
   {
      if (outPutArray[i] == userValue)
      {
         hasValidOut = true;
      }
   }




   if (hasValidOut == true)
   {
      return true;

   }
   else
   {
      return false;
   }
}










/**********************************************************************
 * This will allow the user to edit the board and board points if 
 * Follows and passes the requirements.
 ***********************************************************************/
void editBoard(char arrRead[9][9], int &row, int &col, bool skipUserValAsk)
{
   

   bool check = false;
   bool skipLine = false;
   bool checkBoard = false;
   bool canEdit = false;
   bool displayResults = false;

   char rowChar;
   char userValue[3];
   char coord[5];

   int tempCoordCheck = -1;
   int value = 0;

   // Get the user coordinates and translates that to a int. format
   do 
   {
      cout << "What are the coordinates of the square: ";
      cin.clear();
      cin >> coord;

      // This takes the lower case values to uppercase and
      //Error check user input coordinates
      if (!isalpha(coord[0]) 
         || isalpha(coord[1])  
         || !(coord[1] >= '0' && coord[1] <= '9'))
      {
         cout << "ERROR: Square \'" << coord << "\' is invalid\n";
         break;
         check = false;
         skipLine = true;
      }

      else
      {
         
         // Convert from lower to upper case
         if (coord[0] >= 97 && coord[0] <= 105)
         {
            coord[0] = coord[0] - 32;
         }

         // convert char to int.
         col = coord[1] - 49;
         row = coord[0] - 65;
         tempCoordCheck = arrRead[row][col];
    
         
         // Checks if spot is open
         if (!isdigit(tempCoordCheck))
         {
            check = false;
         }
         else
         {
            check = false;
            skipLine = true;
            cout << "ERROR: Square \'" << coord << "\' is filled\n";
            break;
         }


      }

   } while (check == true);







   //get the user value to check and enter
   
   if (skipLine == false && skipUserValAsk != true)
   {

      do
      {
         cout << "What is the value at \'" << coord[0] << coord[1] << "\': ";
         cin.clear();
         cin >> userValue[1];

         // convert to int. from char
         value = userValue[1] - 48;

         displayResults = false;
         checkBoard = isBoardValid(arrRead, row, col, value, displayResults);

         if (checkBoard == false) 
         {
            
            cout << "ERROR: Value \'" << value << "\' in square \'" 
               << coord[0] << coord[1] << "\' is invalid\n";

            break;
         }



         if (!(value >= 0 || value <= 9))
         {
            cout << "ERROR:\n";
         }
         else
         {
            check = false;
            // convert char to int. and places it into the array.
            arrRead[col][row] = value + 48;
         }

      } while (check == true);

   }





}



/**********************************************************************
 * This will display the board, full modular, can be called anywhere 
 * As long as the array is provided
 ***********************************************************************/
void displayPuzzle(char arrRead[9][9])
{
   int verticalTracker = 0;
   int rowTracker = 0;
   
   cout << "   A B C D E F G H I" << endl;

   for (int i = 0; i < 9; ++i)
   {
      ++rowTracker;
      ++verticalTracker;

      // Places coordinate rows
      cout << verticalTracker << "  ";


      // display Row Values.
      int colTracker = 0;
      for (int j = 0; j < 9; ++j)
      {
         ++colTracker;
         cout << arrRead[i][j];
         // tracks the vertical line placement and spaces.
         if (colTracker == 3 && j < 8)
         {
            colTracker = 0;
            cout << "|";
         }
         else if (j < 8)
         {
            cout << " ";
         }
      }

      cout << "\n";

      // places divider every 3 lines.
      if (rowTracker == 3 && i < 8)
      {
         rowTracker = 0;
         cout << "   -----+" << "-----+-----\n";
      }

   }



}




/**********************************************************************
 * This will take user input, whether it is lower case or upper case
 * And convert it to all upper case for the program to use.
 ***********************************************************************/
int converData(char temp)
{
   bool isValid = false;

 
   do
   {
      if (temp == '?')
      {
         isValid = true;
         return 0;
      }
      else  if (temp == 'd' || temp == 'D')
      {
         isValid = true;
         return 1;
      }
      else if (temp == 'e' || temp == 'E')
      {
         isValid = true;
         return 2;
      }
      else if (temp == 's' || temp == 'S')
      {
         isValid = true;
         return 3;
      }
      else if (temp == 'q' || temp == 'Q')
      {
         isValid = true;
         return 4;
      }
      else
      {
         cout << "ERROR: Invalid command";
         return -1;
      }
   } while (isValid == false);
   
 
}




/**********************************************************************
 * This will show the user menu, as well as the board fill
 * At startup
 ***********************************************************************/
void showMenu(char arrRead[9][9], bool doOnce)
{
   // Display Options
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n";
   cout << "   D  Display the board\n";
   cout << "   E  Edit one square\n";
   cout << "   S  Show the possible values for a square\n";
   cout << "   Q  Save and Quit\n";


   if (doOnce == true)
   {
      cout << "\n";
      displayPuzzle(arrRead);
   }

   bool isValid = false;

}





/**********************************************************************
 * When call it will as the user for a file save 
 * location then display if saved.
 ***********************************************************************/
void saveAndQuit(char arrRead[9][9])
{
   char fileName[256];
   cout << "What file would you like to write your board to: ";
   cin >> fileName;
   ofstream fout(fileName);
   // Check for issues opening file.
   if (fout.fail())
   {
      cout << "Unable to open file " << fileName
         << "." << endl;
      
   }
   // First loop writes the rows
   for (int row = 0; row < 9; row++)
   {
      // For each row we go through the columns input info
      // from our array to the file.
      for (int col = 0; col < 9; col++)
      {
         
         // Places a zero in the text file were there are spaces in the array.
         if (arrRead[row][col] == ' ')
         {
            fout << '0' << ' ';
         }
         else
         {
            // Makes sure there are no spaces at the end of each line.
            if (col < 8)
            {
               fout << arrRead[row][col] << ' ';
            }
            else
            {
               fout << arrRead[row][col];
            }

         }
            
      }
      fout << endl;
   }

   cout << "Board written successfully\n";
   fout.close();

}




/**********************************************************************
 * This will read the file provided by the user
 * And convert the text file into a char array.
 ***********************************************************************/
void readFile(char fileName[], char arrRead[9][9])
{

   cout << "Where is your board located? ";

   cin >> fileName;
   ifstream fin;

   fin.open(fileName);
   

   if (fin.fail())
      cout << "Error reading file: " << fileName;

   for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
         fin >> arrRead[i][j];

   for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
         //preforms a conditional test. if doc value is zero 
         //it places a space.
         arrRead[i][j] = (arrRead[i][j] == '0') ? ' ' : arrRead[i][j];


}




/**********************************************************************
 * This is the main function, it will set
 *  base values and call all other functions.
 ***********************************************************************/
int main()
{
   char arrRead[9][9];
   char fileName[256];
   char temp[2];

   bool contin = true;
   bool boardValid = false;
   bool doOnce = true;
   bool displayResults = false;
   bool skipUserValAsk = false;

   int menu = 0;
   int row = 1;  // B2
   int col = 1;  // B2
   int userValue = 0;

   readFile(fileName, arrRead);

   // Show start up prompts
   showMenu(arrRead, doOnce);
   doOnce = false;


   do
   {
      // Get switch value
      cout << "\n> ";
      char temp;
      cin.clear();


      cin >> temp;
      menu = converData(temp);

      switch (menu)
      {
         case 0:
            showMenu(arrRead, doOnce);
            cout << "\n";
            break;

         case 1:
            displayPuzzle(arrRead);
            break;

         case 2:
            skipUserValAsk = false;
            editBoard(arrRead, row, col, skipUserValAsk);
            break;

         case 3:
            skipUserValAsk = true;
            editBoard(arrRead, row, col, skipUserValAsk);
            displayResults = true;
            boardValid = isBoardValid(arrRead, row, 
               col, userValue, displayResults);
            break;

         case 4:
            saveAndQuit(arrRead);
            contin = false;
            break;

         default:
            cout << "777 error 777";
            break;

      }
   } while (contin == true);
   
   return 0;
}