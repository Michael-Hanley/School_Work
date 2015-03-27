
/*********************************************
Filename: golf.cpp
name: M Hanley
Company: Sacramento City College
Date: Feb 3rd, 2015
This program writes "Hello World" on screen
History
Date      Initials       Action
=================================================
02/03/2015  MPH          Wrote program/compiled
03/25/2015  MPH          Added sort
*********************************************** */

#include <iomanip>
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;
double CalcAvg(int, int, int, int, int &);
void ClearLines(int);
void TellUser();
void swap(string &, string &);
void swap(int &, int &);
void swap(double &, double &);
const int SIZE = 20;
int main()
{
bool swapflag = false;          //no swaps when false
int i=0; 		         	// counter
int numgolf;                    // total number of golfers
int lowscore = 400;             // lowest score
int round1[SIZE], round2[SIZE],
    round3[SIZE], round4[SIZE]; //scores on 4 rounds of golf
ifstream input_file;            //input file name 
ofstream output_file;           //output file name
int lastpos, numpeep;           //last position to compare and number of golfers
string  firstname[SIZE], lastname[SIZE];  // First and last name of the golfer.
string  wfirstn, wlastn;        // First and last name of the winner.
int total[SIZE];                // four rounds of golf scores.
double average[SIZE];           // Average of the scores.
bool outOpen = false;           //only write output to screen when true 
ClearLines(35);
TellUser();                     // tells the user what the program does
input_file.open("golfers.txt");
if(input_file.fail())
{
	cout << "Error opening file golfers.txt \n\n";
	cout << "end of program \n\n";
	return 1;                          //error end of the program
}

  while(i < SIZE && input_file >> round1[i]) //there is a line of data to read
  {		input_file >> round2[i];   //read golf score
		input_file >> round3[i];   //read golf score
		input_file >> round4[i];   //read golf score
		input_file >> firstname[i];//read first name
		input_file >> lastname[i]; //read last name
		i++;
  }                                        //end while loop
  cout << "There were " << i << " golfers\n\n";
  numgolf = i;                             //number of golfers
  input_file.close(); //close the file after reading it
  cout << "inout file read and closed \n";
// **********************Close input File**********************
// loop to calculate total and average for each golfer and finds winner
  for(i=0; i<numgolf; i++)
  {
    average[i] = CalcAvg(round1[i], round2[i], round3[i], round4[i], total[i]);
    if(total[i] <lowscore)
	{
	wfirstn =firstname[i];  // store first name of the winner
	wlastn = lastname[i];   // store last name of new winner
	lowscore = total[i];   // lowest score now
        } // end if
   } // end loop

	
   // open report file and write output data ************************
  output_file.open("golfreport.txt"); // output file
  if (output_file.fail())
  {
	cout << "output file did NOT open\n";
	cout << "output will only be sent to the screen\n";
  }
  outOpen=true;
  ClearLines(5);
  cout << "\n\nGolfers'   Names       rnd1 rnd2 rnd3 rnd4 total average\n";
  cout << "========================================================\n";
  if(outOpen)
  output_file << "\n\nGolfers'   Names      rnd1 rnd2 rnd3 rnd4 total average\n";
  output_file << "=======================================================\n";

	//Start sort
	numpeep = numgolf;
	lastpos = numpeep;
	do
	{
	  lastpos--;     //number of comparisons
	  swapflag = false;  //no swaps yet this pass
	  for(i=0; i < lastpos; i++)
	  {
	    if(total[i]>total[i+1])    //out of order
	    {
		swap(firstname[i], firstname[i+1]); //first name swap
		swap(lastname[i], lastname[i+1]);   //last name swap
		swap(round1[i], round1[i+1]);       //round 1 swap
		swap(round2[i], round2[i+1]);       //round 2 swap
		swap(round3[i], round3[i+1]);       //round 3 swap
		swap(round4[i], round4[i+1]);       //round 4 swap
		swap(total[i], total[i+1]);         //total swap
		swap(average[i], average[i+1]);     //average swap
		swapflag = true;
	    }   // end of if
         } // end of for loop
	}while(swapflag);  // end of do while



	//loop to print report of golfers	
  for(i=0; i < numgolf; i++)
  {
    cout << left <<  setw(10) << firstname[i] << " "; 
    cout << setw(10) << lastname[i] << " " << right;
    cout << setw(4) << round1[i] << " " << setw(4) << round2[i] << "  ";
    cout << setw(4) << round3[i] << " " << setw(4) <<  round4[i] << "  ";
    cout << setw(4) << total[i] << " " << setprecision(2); 
    cout << setw(6) << average[i] << "\n";
	if(outOpen)
	{
	  output_file << left << setw(10) << firstname[i]<< " ";
  	  output_file << setw(10) << lastname[i] << " " << right;
	  output_file << setw(4) << round1[i] << " ";
          output_file << setw(4) << round2[i] << " ";
	  output_file << setw(4) << round3[i] << " ";
 	  output_file << setw(4) << round4[i] << " ";
	  output_file << setw(4) << total[i]  << " ";
	  output_file << setprecision(2) << setw(6) <<  average[i] << "\n";
	}
  }  // end of forloop
  cout << "\nThe Winner is " << wfirstn << " " << wlastn << endl;
  if (outOpen)
  {
	output_file << "\nThe winner is " << wfirstn << " " << wlastn << endl;
	output_file.close();
	cout << "\nOutput file close \n\n";
  }
return 0;
} //end of main ******************************************
/*********************************************************************
*function TellUser
*it tells the user what the program does
*it prints output to the screen
* output: writes output to the screen
*****************************************************************/
void TellUser()
{
	cout << "This program reads a file called Golfers.txt\n";
	cout << " and it calculate the total and average for each golfer\n";
	cout << " output is written to the screen. and to an output fil\n\n";
}
/*********************************************************************
function ClearLines - clears lines on the screen
inout parameter: numl - number of lines to clear
output: prints new lines to the screen
return: none
******************************************************************** */
void ClearLines(int numl)
{
  int k;
  for  ( k= 0; k < numl; k++)
    cout << "\n";
}
/*********************************************************************
*function Calc Avg: Reveives the 4 scores ad address of total
*calculates the average and returns it.
*intput parameters: r1, r2, r3, r4 - four rounds of golf scores
*output paramter: tot - total of those scores
*return: avg- the average of those 4 scores 
*********************************************************************/
double CalcAvg(int r1, int r2, int r3, int r4, int &tot)
{
  double avg;   //calculates average
  tot = r1 + r2 + r3 +r4;
  avg = 1.0 * tot / 4.0;
  return avg;
}
/*******************************************************************
Function swap = will swap two strings
input parameters: name[i], name[i+1]
output paramters: &name1, &name2
*******************************************************************/
void swap(string &name1, string &name2)
{
  string temp;
  temp = name1;
  name1 = name2;
  name2 = temp;
}
/*******************************************************************
Function swap = will swap two strings
input parameters: round1-4[i] and round1-4[i+1], total[i] and total [i+1]
output paramters: &name1, &name2
*******************************************************************/
void swap(int &num1, int &num2)
{
int temp;
temp = num1;
num1 = num2;
num2 = temp;
}
/*******************************************************************
Function swap = will swap two strings
input parameters: average[i] and average[i+1]
output paramters: &name1, &name2
*******************************************************************/
void swap(double &num1, double &num2)
{
double temp;
temp = num1;
num1 = num2;
num2 = temp;
}
