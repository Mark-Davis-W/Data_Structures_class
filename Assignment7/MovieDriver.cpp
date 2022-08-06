//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #6

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "MovieTree.cpp"

using namespace std;

void displayMenu(){
  cout << "======Main Menu======" << endl ;
  cout << "1. Print the inventory" << endl ;
  cout << "2. Delete a movie" << endl ;
  cout << "3. Quit" << endl ;
}


int main(int argc, char *argv[]){
  MovieTree movieDB;
  string inputFile = argv[1];
  ifstream fsInput;
  fsInput.open(inputFile);
  string line = "";
  string holder = "";
  int rank = 0;
  string tit = "";
  int ye = 0;
  float rat = 0;
  if(fsInput.is_open()){
    while(!(fsInput.eof())){
      if(getline(fsInput,line)){
        istringstream ss(line);
        getline(ss,holder, ',');
        rank = stoi(holder);
        getline(ss,tit, ',');
        getline(ss,holder, ',');
        ye = stoi(holder);
        getline(ss,holder);
        rat = stof(holder);
        movieDB.addMovie(rank,tit,ye,rat);
      }
    }
  }else { cout << "help" << endl;}
  fsInput.close();

  string choice;

  while(choice != "3"){
    displayMenu();
    getline(cin,choice);
    int intChoice = stoi(choice);
    switch (intChoice) {

      case 1:
        movieDB.printMovieInventory();
        break;

      case 2:
        cout << "Enter a movie title:" << endl;
        getline(cin,tit);
        movieDB.deleteMovie(tit);
        break;

      case 3:
        cout << "Goodbye!" << endl ;
        break;
    }
  }
  return 0;
}
