/**********************************************************************
golfstruct.cpp
Michael Hanley
April 7, 2015
This program reads golfers from a file and stores them in a structure.
**********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
struct GolfStruct
{
  string firstn,	// first name
  	 lastn,         // last name
  	 fullname,
	 newname;      // full name of golfer
  int score1,           // score on round 1
      score2,           // score on round 2
      score3,           // score on round 3
      score4,           // score on round 4
      total;            // total of score
  double average; 	// average of the scores
};
const int MAX =20;        //max number of golfers
void DoMath(GolfStruct [],int);
void BubbleSort(GolfStruct [], int);
void Swap(GolfStruct &, GolfStruct &);
void Search(GolfStruct [], int);
int main()
{
  GolfStruct golfer[MAX];    //one golfer
  int k;                //counter
  int numgolf;          //number of golfers
  char yesno;		//do-while test variable
  ifstream inputFile;    //read from file
  ofstream outputFile;   // read to file
  bool flag = true;      // able to write report when true
  inputFile.open("golfers.txt"); //open file of data
  if (inputFile.fail())
  {
     cout << "unable to open golfers.txt\n";
     cout << "program ending \n\n";
     return 1;
  }
  k=0;           //ready to read the first golfer
  while(k < MAX && inputFile >> golfer[k].score1)
  {
    inputFile >> golfer[k].score2;
    inputFile >> golfer[k].score3;
    inputFile >> golfer[k].score4;
    inputFile >> golfer[k].firstn;
    inputFile >> golfer[k].lastn;
    golfer[k].fullname = golfer[k].firstn + " " + golfer[k].lastn;
    golfer[k].newname = golfer[k].lastn + ", " + golfer[k].firstn; 
    k++;
  }
  inputFile.close();
  numgolf = k;
  cout << "There were " << numgolf << " golfers \n"<< endl;
  DoMath(golfer, numgolf);
  BubbleSort(golfer, numgolf);
  outputFile.open("report.txt");
    if ( outputFile.fail())
	flag = false;
  cout << "Firstname Lastname   Score1 Score2 score3 score4 total average" << endl;
  for( k =0; k<numgolf; k++)
  { 
    cout << setprecision(2) << fixed << left << setw(20);
    cout << golfer[k].fullname << " " << right << setw(6) << golfer[k].score1;
    cout << setw(7) << golfer[k].score2 << " " << setw(6) << golfer[k].score3;
    cout << " " << setw(6) << golfer[k].score4;
    cout << setw(6) << golfer[k].total << " ";
    cout << setw(6) <<  golfer[k].average << endl;
  if(flag)
    {
    outputFile << setprecision(2) << fixed << left << setw(20);
    outputFile << golfer[k].fullname << " " << right << setw(6) << golfer[k].score1;
    outputFile << setw(7) << golfer[k].score2 << " " << setw(6) << golfer[k].score3;
    outputFile << " " << setw(6) << golfer[k].score4;
    outputFile << setw(6) << golfer[k].total << " ";
    outputFile << setw(6) <<  golfer[k].average << endl;
    }
  } 
  if(flag) outputFile.close();
    do
  {
     cout << "\nWould you like to search for another golfer? y/n ";
     cin >> yesno;
     cin.ignore(20,'\n');
     yesno = toupper(yesno);
     if(yesno == 'Y') 
	Search(golfer,numgolf);
  }while(yesno=='Y');
  return 0;
}
/************************************************************
Function: DoMath
finds the total and average of each golfer
Input Parameters: gol[] - array of golfers with 4 scores each
      numgolf- number of golfers int hat array'
output parameters: gol[] - now has a total and average for each golfer
********************************************************/
void DoMath(GolfStruct gol[],int numgolf)
{
 int i;  //counter
 for(i=0; i < numgolf; i++)
 {
    gol[i].total = gol[i].score1+ gol[i].score2 +
   		   gol[i].score3 + gol[i].score4;
    gol[i].average = gol[i].total/4.0;
 }

}
/*******************************************************************
function swap - swaps two golfer data structures 
input parameters: a- golfer 1
                  b- golfer 2
output parameters: a and b have been swapped
*******************************************************************/
void Swap(GolfStruct &a, GolfStruct &b)
{
  GolfStruct temp;
  temp = a;
  a = b;
  b = temp;
}

/**********************************************************************
Function: bubble sort uses the bubble sort to put the golfer with the
lowest score at the top of the list - because that is the winner
input parameters: golf[] - an array of golfer and their data
		number - the number of golfers and teir data
output parameters: golf[] - has been sorted with the lowest score first
**********************************************************************/
void  BubbleSort(GolfStruct golf[], int number)
{
  int lastpos = number;	//last position to look at this pass
  bool swapmade = false;  //when true a swap has been made
  int k; 			// counter
  do
  {
    lastpos--;
    swapmade=false;
    for (k=0; k<lastpos; k++)
    {
	if (golf[k].newname > golf[k+1].newname)
	{
	  swapmade = true;
	  Swap(golf[k], golf[k+1]);
	}
    }
  }while(swapmade);
}
/************************************************************************
Function Bi search - uses a binary search to find a golfer by last name
input parameters: golf[] - an array of golf structures
                  number - the number of golfers in that array
input 
**********************************************************************/
void Search(GolfStruct golf[], int number)
{
  int firstpos, midpos, lastpos, // first, middle, and last search position
      position;         // found person in this position
  string findlast;	// last name to search for
  int j; 		//counter
  bool flag =false;     // flag true when golfer is found

   cout << "Who are you searching for, enter their last name? ";
   getline(cin, findlast);
   firstpos = 0;
   lastpos = number;
   position = -1;	// we have not found the golfer yeT
   while (position == -1 && firstpos <= lastpos)
   {
      midpos = (firstpos + lastpos)/2;
      j=midpos;
      if(findlast == golf[j].lastn)
     {  //this is the person we are looking for
	flag = true;
	cout <<"found " << findlast << " with information as follows\n";
        cout << "Firstname Lastname   Score1 Score2 score3 score4 total average" << endl;
        cout << setprecision(2) << fixed << left << setw(20);
        cout << golf[j].fullname << " " << right << setw(6) << golf[j].score1;
        cout << setw(7) << golf[j].score2 << " " << setw(6) << golf[j].score3;
        cout << " " << setw(6) << golf[j].score4;
        cout << setw(6) << golf[j].total << " ";
        cout << setw(6) <<  golf[j].average << endl;
	position = j;
     }
     else if(findlast > golf[j].lastn)
     {
       firstpos = midpos + 1;
     }
     else
     {
       lastpos = midpos - 1;
     }
   } // end of while loop
  if(!flag)
    cout << "Unable to find golfer " << findlast << endl << endl;
}
