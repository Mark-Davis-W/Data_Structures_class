#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

TreeNode* getMaxValueNode(TreeNode* currNode){
    if(currNode->rightChild == NULL){
        return currNode;
    }
    return getMaxValueNode(currNode->rightChild);
}

TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

void deleteMovieNodeLL(TreeNode *n, string t){
  LLMovieNode* hold = n->head;
  LLMovieNode* prev = NULL;

  while(hold != NULL && hold->title != t){
      prev = hold;
      hold = hold->next;
  }

  if(hold == NULL){
    cout << "Movie: " << t << " not found, cannot delete." << endl;
    return;
  }
  if(prev == NULL && n->head->next != NULL){
    n->head = n->head->next;
    delete hold;
    return;
  }
  if (prev != NULL && hold != NULL){
    prev->next = hold->next;
    delete hold;
    return;
  }
  if(hold->title == t){
      n->head = n->head->next;
      delete hold;
      return;
  }
}

TreeNode* deleteMovieNodehelper(TreeNode *r, char t){
  TreeNode* temp = r;

  if(!r){
      return r;
    }
    else if(temp->titleChar < t){
      temp->rightChild = deleteMovieNodehelper(temp->rightChild,t);
    }
    else if(temp->titleChar > t){
      temp->leftChild = deleteMovieNodehelper(temp->leftChild, t);
    }
    else{
      TreeNode* temp2 = temp;
      if(temp->leftChild == NULL && temp->rightChild == NULL){
      delete temp;
      temp = NULL;
      }
      //Only right child
      else if(temp->leftChild == NULL){
        temp2 = temp;
        temp->rightChild->parent = temp->parent;
        temp = temp->rightChild;
        delete temp2;
        //return temp;
      }
      //Only left child
      else if(temp->rightChild == NULL){
        temp2 = temp;
        temp->leftChild->parent = temp->parent;
        temp = temp->leftChild;
        delete temp2;
        //return temp;
      }else{
        ///Replace with Minimum from right subtree
        TreeNode* Rmin = getMinValueNode(temp->rightChild);
        temp->head = Rmin->head;
        temp->titleChar = Rmin->titleChar;
        temp->rightChild = deleteMovieNodehelper(temp->rightChild,Rmin->titleChar);

        //cout << "Rmin parent: " << Rmin->parent->titleChar << ", Rmin char " << Rmin->titleChar << endl;
        //return temp;
        }
    }
  return temp;
}

TreeNode* deleteMovieNode(TreeNode *rNode, string tit){
    TreeNode* temp = rNode;

    if(!temp){
      cout << "Movie: " << tit << " not found, cannot delete." << endl;
      return temp;
    }

    if(temp->titleChar < tit[0]){
      temp->rightChild = deleteMovieNode(temp->rightChild,tit);
    }
    else if(temp->titleChar > tit[0]){
      temp->leftChild = deleteMovieNode(temp->leftChild, tit);
    }
    else{
      deleteMovieNodeLL(temp,tit);
      if(!temp->head){
          temp = deleteMovieNodehelper(temp,tit[0]);
      }
    }
    //cout << "Movie: " << tit << " not found, cannot delete." << endl;
    return temp;
}

void MovieTree::deleteMovie(string tit){
    root = deleteMovieNode(root,tit);
}

void deleteTreeLL(LLMovieNode *node){
  if (node == NULL)
    return;

  deleteTreeLL(node->next);
  delete node;
  return;
}

void deleteTree(TreeNode *node){
  if (node == NULL)
    return;

  deleteTree(node->leftChild);
  deleteTreeLL(node->head);
  deleteTree(node->rightChild);
  delete node;
}

void printTreeLL(LLMovieNode *node, char x){
  cout << "Movies starting with letter: " << x << endl;
  if(node != NULL){
    while(node){
      cout << " >> " << node->title << " " << node->rating << endl;
      node = node->next;
    }
  }
}

void printTree(TreeNode *node){
  if(node != NULL){
    printTree(node->leftChild);
    printTreeLL(node->head,node->titleChar);
    printTree(node->rightChild);
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
    delete root;
    root = NULL;
}

void MovieTree::printMovieInventory(){
    if (root == NULL){
    return;
    }else{printTree(root);}
}

void addMovieNodeLL(TreeNode *node, LLMovieNode* newN){
  LLMovieNode *hold = node->head;

  if(hold->title > newN->title){
    newN->next = hold;
    node->head = newN;
  }else{
    while(hold){
     if(hold->next == NULL){
        hold->next = newN;
        newN->next = NULL;
        return;
        }else if(hold->title < newN->title && hold->next->title < newN->title){
        hold = hold->next;
            }else{
            newN->next = hold->next;
            hold->next = newN;
            return;
            }
        }
    }
}

TreeNode* addMovieNode(TreeNode* r, LLMovieNode* n) {
  //write your code
    if(r->titleChar < n->title[0]){
      if(r->rightChild == NULL){
        TreeNode *temp = new TreeNode;
        temp->titleChar = n->title[0];
        temp->head = n;
        r->rightChild = temp;
        r->rightChild->parent = r;
        //cout << "parent of " << r->rightChild->titleChar << " is: " << r->titleChar << endl;
        return r;
      }else{r = addMovieNode(r->rightChild, n);}
    }else if(r->titleChar > n->title[0]){
      if(r->leftChild == NULL){
        TreeNode *temp = new TreeNode;
        temp->titleChar = n->title[0];
        temp->head = n;
        r->leftChild = temp;
        r->leftChild->parent = r;
        //cout << "parent of " << r->leftChild->titleChar << " is: " << r->titleChar << endl;
        return r;
      }else{r = addMovieNode(r->leftChild, n);}
    }else{addMovieNodeLL(r,n);}
}

void MovieTree::addMovie(int ranking, string title, int year, float rating) {
  LLMovieNode* newNode = new LLMovieNode(ranking,title,year,rating);

  if(!root){
      TreeNode *temp = new TreeNode;
      temp->titleChar = title[0];
      temp->head = newNode;
      root = temp;
      //addMovieNode(root,newNode);
    }else{
      addMovieNode(root,newNode);
    }
}
