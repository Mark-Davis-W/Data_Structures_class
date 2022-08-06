//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #1 Problem #1

#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <locale>
#include <vector>

using namespace std;

int insertIntoSortedArray (int myArray[], int numEntries, int newValue)
{
  numEntries++;
  myArray[numEntries-1] = newValue;
  int temp = 0;

  for (int j = 0; j<numEntries; j++){
    for (int k = j+1;k<numEntries; k++){
      if (myArray[j] > myArray[k]){
          temp = myArray[j];
          myArray[j] = myArray[k];
          myArray[k] = temp;
      }
    }
  }
  return numEntries;
}


int main(int argc, char *argv[]){
  string filename = "";
  if (argc > 2){
    cout << "Too many Arguments entered." << endl;
    return 0;
  }
  else if (argc < 2) {
    cout << "Too few arguments, did you forget the filename?" << endl;
    return 0;
  }
  else {filename = argv[1];}

  int myArray[100];
  int numEntries = 0;

  for (int i = 0; i<100; i++){
    myArray[i]=0;
  }

  ifstream fs; //create ifstream(reading) variable

  fs.open(filename); //open file using variable and passed name
  string line = ""; //create empty string for file
  int j = 0;

  if (fs.is_open()){ //check if file opened
    while (!(fs.eof()) & (numEntries < 101)){
     if(getline(fs, line)){
  //      istringstream(line) >> j;
        j = stoi(line);
          // cout << j << endl;
        numEntries = insertIntoSortedArray(myArray,numEntries,j);
        for (int i =0;i<numEntries; i++){
          if(i<numEntries-1){
           cout << myArray[i] << ",";
          }
          else{
            cout << myArray[i];
          }
        }
      }
      cout << endl;
    }
  }
  else {cout << "Failed to open the file." << endl;}
  fs.close();
  return 0;
}
