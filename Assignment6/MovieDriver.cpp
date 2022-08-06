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
  cout << "1. Find a movie" << endl ;
  cout << "2. Query movies" << endl ;
  cout << "3. Print the inventory" << endl ;
  cout << "4. Average Rating of movies" << endl ;
  cout << "5. Quit" << endl ;
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
        movieDB.addMovieNode(rank,tit,ye,rat);
      }
    }
  }else { cout << "help" << endl;}
  fsInput.close();

  string choice;

  while(choice != "5"){
    displayMenu();
    getline(cin,choice);
    int intChoice = stoi(choice);
    switch (intChoice) {

      case 1:
        cout << "Enter title:" << endl ;
        getline(cin,tit);
        movieDB.findMovie(tit);
        break;

      case 2:
        cout << "Enter minimum rating:" << endl;
        getline(cin,holder);
        rat = stof(holder);
        cout << "Enter minimum year:" << endl;
        getline(cin,holder);
        ye = stoi(holder);
        movieDB.queryMovies(rat,ye);
        break;

      case 3:
        movieDB.printMovieInventory();
        break;

      case 4:
        movieDB.averageRating();
        break;

      case 5:
        cout << "Goodbye!" << endl ;
        break;
      }
    }
}
