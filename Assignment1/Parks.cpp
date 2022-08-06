//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #1 Problem #2

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

struct Park {
string parkname;
string state;
int area;
};



void addPark(Park parks[], string parkname, string state, int area, int length){

  parks[length].parkname = parkname;
  parks[length].state = state;
  parks[length].area = area;

}

void printList(const Park parks[], int length){
  for (int i=0; i<length; i++){
    cout << parks[i].parkname << " [" << parks[i].state << "] area: " << parks[i].area << endl;
  }
}

int main(int argc, char *argv[]){
  string inputFile = "";
  string outFile = "";
  double minArea = 10000000000;

  if (argc > 4){
    cout << "Too many Arguments entered." << endl;
    return 0;
  }
  else if (argc < 4) {
    cout << "Too few arguments, did you forget the filename or something else?" << endl;
    return 0;
  }
  else {
    inputFile = argv[1];
    outFile = argv[2];
    minArea = stod(argv[3]);
  }

  Park parks[100];

  for (int i = 0; i<100; i++){
    parks[i].parkname = "";
    parks[i].state = "";
    parks[i].area = 0;
  }

  ifstream fs; //create ifstream(reading) variable
  fs.open(inputFile); //open file using variable and passed name
  int i = 0;

  string line = ""; //create empty string for file
  string name, st, sarea;
  int area, len = 0;

  if (fs.is_open()){ //check if file opened
    while (!(fs.eof())/* & (len < 101)*/){
     if(getline(fs, line)){
       istringstream ss(line);
       while (getline(ss,name,',')){
         getline(ss,st,',');
         getline(ss,sarea);
         area = stoi(sarea);
         addPark(parks,name,st,area,len);
         len++;
       }
      }
    }
  }
  else {cout << "Failed to open the file." << endl;}
  printList(parks,len);

 fs.close();
 ofstream fsOut;
 fsOut.open(outFile);

 for (int i=0; i<len; i++){
  if (parks[i].area > minArea){
      fsOut << parks[i].parkname << "," << parks[i].state << "," << parks[i].area << endl;
  }
}
 fsOut.close();
 return 0;
}
