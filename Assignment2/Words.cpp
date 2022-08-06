//CS1300 Fall 2019
//Author: Mark Davis
//Recitation:203 Divya
//Homework #2

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

using namespace std;

struct wordItem {
  string word = "";
  int count = 0;
};

void getStopWords (const char *ignoreFile, string ignoreWords[]){
  ifstream fsignore; //create ifstream(reading) variable
  fsignore.open(ignoreFile); //open file using variable and passed name
  string line = ""; //create empty string for file
  int i=0;

  if (fsignore.is_open()){ //check if file opened
    while (!(fsignore.eof())){
     if(getline(fsignore, line)){
       istringstream ss(line);
       getline(ss,ignoreWords[i]);
         // len++;
         i++;
      }
    }
  }
  else {cout << "Failed to open " << ignoreFile << endl;}
  fsignore.close();
}

bool isStopWord (string word, string ignoreWords[]){
  bool flip=false;
  for (int i=0; i<50; i++){
    if(word == ignoreWords[i]){
      flip = true;
    }
  }
  return flip;
}

int getTotalNumberNonStopWords (wordItem uniqueWords[], int length){
   int hold = 0;
   for(int i=0; i<length; i++){
       hold += uniqueWords[i].count;
       // cout << uniqueWords[i].word << endl;
   }
   return hold;
}

void arraySort(wordItem uniqueWords[], int length)
{
    int k = 0;
    int temp1 = 0;
    string temp = "";
    while(k<length){
        for (int j = 0; j<length-1; j++){
            if (uniqueWords[j].count < uniqueWords[j+1].count){
                temp = uniqueWords[j+1].word;
                uniqueWords[j+1].word = uniqueWords[j].word;
                uniqueWords[j].word = temp;
                temp1 = uniqueWords[j+1].count;
                uniqueWords[j+1].count = uniqueWords[j].count;
                uniqueWords[j].count = temp1;
            }
        }
        k++;
    }
}

void printNext10 (wordItem uniqueWords[], int printIndex, int totalNumWords){
  cout << "Probability of next 10 words from rank " << printIndex << "\n---------------------------------------" << endl;
  for(int i=printIndex; i<printIndex+10; i++){
    cout.precision(4);
    cout << fixed << (float) uniqueWords[i].count / totalNumWords <<  " - " << uniqueWords[i].word << endl;
  }
}

int main (int argc, char *argv[]){

  string inputFile = "";
  char* ignoreFile;
  int p = 100;
  int *maxEntries = &p;
  wordItem *uniqueWords = new wordItem[*maxEntries];
  string ignoreWords[50];
  int doubled = 0;
  string saveWord = "";
  int printIndex = 0;

  if (argc != 4){
    std::cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << std::endl;
    return 0;
  }
  else {
    printIndex = stoi(argv[1]);
    inputFile = argv[2];
    ignoreFile = argv[3];
  }
// cout << ignoreFile << endl;
// return 0;
  getStopWords (ignoreFile, ignoreWords);

  ifstream fsInput; //create ifstream(reading) variable

  fsInput.open(inputFile); //open file using variable and passed name
  string line = ""; //create empty string for file
  int current = 0;
  bool flag = false;

  if (fsInput.is_open()){ //check if file opened
    while (!(fsInput.eof())){
     if(getline(fsInput, line)){
       istringstream ss(line);
       while (getline(ss,saveWord, ' ')){
         // cout << saveWord << endl;
         // cout << isStopWord(saveWord,ignoreWords) << endl;
         if (isStopWord(saveWord,ignoreWords) == 0){
           // cout << "checked" << endl;
           for(int i = 0; i<current; i++){
             // cout << "checked 2" << endl;
             if (uniqueWords[i].word == saveWord){
               // cout << "checked 3" << endl;
               uniqueWords[i].count += 1;
               // cout << uniqueWords[i].count << endl;
               flag=true;
             }
           }
           if (flag == false){
             // cout << "checked 4" << endl;
             uniqueWords[current].word = saveWord;
             // cout << uniqueWords[current].word << endl;
             uniqueWords[current].count += 1;
             // cout << uniqueWords[current].count << endl;

             if (*maxEntries-1 == current){
               // cout << "before: "<< *maxEntries << endl;
               *maxEntries = 2*(current+1);
               // cout << "after: " << *maxEntries << endl;
               doubled++;
               wordItem *newArray = new wordItem[*maxEntries];
               for(int k=0; k<current+1; k++){
                 // cout << "k's" << k << endl;
                 newArray[k] = uniqueWords[k];
                 // cout << uniqueWords[k].word << endl;
               }
               //current = *maxEntries;
               // cout << "address before: " << &uniqueWords[0] << endl;
               uniqueWords = newArray;
               // cout << "address after: " << &uniqueWords[0] << endl;
             }
             current++;
            }
         }

         flag = false;
         // cout << uniqueWords[2].count << endl;
         // cout << current << endl;
         }
        }
      }
    }
  else {cout << "Failed to open the file." << endl;}

  arraySort(uniqueWords, current);
  cout << "Array doubled: " << doubled << "\n#\n";
  cout << "Unique non-common words: " << current << "\n#\n";
  cout << "Total non-common words: " << getTotalNumberNonStopWords (uniqueWords, current) << "\n#\n";

  printNext10 (uniqueWords, printIndex, getTotalNumberNonStopWords (uniqueWords, current));
  delete [] uniqueWords;
  fsInput.close();

}
