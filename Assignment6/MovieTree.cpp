#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

void deleteTree(MovieNode *node){
  if (node == NULL)
    return;

  deleteTree(node->left);
  deleteTree(node->right);
  node = NULL;
}

void printTree(MovieNode *node){
  if(node != NULL){
    printTree(node->left);
    cout << "Movie: " << node->title << " " << node->rating << endl;
    printTree(node->right);
    }
}

MovieNode* findMovieHelp(string title, MovieNode* n) {
  if(n == NULL)
    return NULL;

  if(n->title == title)
    return n;

  if(n->title > title)
    return findMovieHelp(title, n->left);

  return findMovieHelp (title, n->right);
}

void findRatingHelp(float r, int y, MovieNode* n) {
  bool found = 0;
  if(n == NULL)
    return;

  if(n){
    if(n->rating > r && n->year > y){
      cout << n->title << "(" << n->year << ") " << n->rating << endl;
      found = 1;
    }
    findRatingHelp(r,y, n->left);
    findRatingHelp(r,y, n->right);
  }

  if(n == NULL and found == 0)
    cout << "Tree is Empty. Cannot query Movies" << endl;
}

void averageRatingHelp(float &xy, float &count, MovieNode* n) {
  if(n == NULL){
    return;
    }

  if(n){
    //cout << count << endl;
    xy = xy + n->rating;
    count++;
    averageRatingHelp(xy,count,n->left);
    averageRatingHelp(xy,count,n->right);
  }
}

// MovieNode: node struct that will be stored in the MovieTree BST

MovieTree::MovieTree() {
  //write your code
  root = NULL;
}

MovieTree::~MovieTree() {
  //write your code
  if(root)
    deleteTree(root);
    root = NULL;
}

void MovieTree::printMovieInventory(){
    // Your code here
    if (root == NULL){
    cout << "Tree is Empty. Cannot print" << endl ;
    return;
    }else{printTree(root);}
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //write your code
  MovieNode *newNode = new MovieNode(ranking,title,year,rating);
  if(!root){
    root = newNode;
  }else{
    MovieNode *pres = root;
    while(newNode){
      if(pres->title <= title){
        if(pres->right == NULL){
          pres->right = newNode;
          newNode = NULL;
        }else{pres = pres->right;}
      }
      if(pres->title > title){
        if(pres->left == NULL){
          pres->left = newNode;
          newNode = NULL;
        }else{pres = pres->left;}
      }
    }
  }
}


void MovieTree::findMovie(string title) {
  //write your code
  MovieNode *node = findMovieHelp(title,root);
  if(node != NULL){
      cout << "Movie Info:" << endl;
      cout << "==================" << endl;
      cout << "Ranking:" << node->ranking << endl;
      cout << "Title :" << node->title << endl;
      cout << "Year :" << node->year << endl;
      cout << "rating :" << node->rating << endl;
  }else{
      cout << "Movie not found." << endl ;
    }
}

void MovieTree::queryMovies(float rating, int year) {
  //write your code
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  findRatingHelp(rating,year,root);
}

void MovieTree::averageRating() {
  //write your code
  float x = 0;
  float c = 0;
  averageRatingHelp(x,c,root);
  if(x != 0)
    cout << "Average rating:" << x/c << endl ;
  else
    cout << "Average rating:0.0" << endl ;
}
