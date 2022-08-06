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

LLMovieNode* deleteMovieNodeLL(LLMovieNode* n, string t){
  LLMovieNode* del = n;
  if(n == NULL){
      return NULL;
  }
  else if(t != n->title){
      deleteMovieNodeLL(n,t);
  }else if(t == n->title){
      del = n;
      n = n->next;
      delete del;
      return n;
  }else if(t == n->next->title){
      del = n;
      n->next = n->next->next;
      delete del;
      return n;
    }
    if(!del){
    cout << "Movie: " << t << " not found, cannot delete." << endl;
    }
}

TreeNode* deleteMovieNodehelper(TreeNode* r, string tit){
  if(r == NULL){
    return r;
  }
  else if(tit[0] < r->titleChar){
    r->leftChild = deleteMovieNodehelper(r->leftChild, tit);
  }
  else if(tit[0] > r->titleChar){
    r->rightChild = deleteMovieNodehelper(r->rightChild, tit);
  }
  else{
    //No child
    if(r->leftChild == NULL && r->rightChild == NULL){
      delete r;
      r = NULL;
    }
    //Only right child
    else if(r->leftChild == NULL){
      TreeNode *temp = r;
      r = r->rightChild;
      delete temp;
    }
    //Only left child
    else if(r->rightChild == NULL){
      TreeNode *temp = r;
      r = r->leftChild;
      delete temp;
    }
    //Both left and right child
    else{
      if(r->rightChild){
          ///Replace with Minimum from right subtree
          TreeNode *temp = getMinValueNode(r->rightChild);
          r->titleChar = temp->titleChar;
          r->rightChild = deleteMovieNodehelper(r->rightChild,tit);
        }else if(r->leftChild){
          ///Replace with Maximum from left subtree
          TreeNode *temp = getMaxValueNode(r->leftChild);
          r->titleChar = temp->titleChar;
          r->rightChild = deleteMovieNodehelper(r->leftChild,tit);
        }
    }
  }
return r;
}

void deleteMovieNode(TreeNode* r, string tit){
  if(r == NULL){
      return;
  }
  if(r){
    if(r->titleChar == tit[0]){
      r->head = deleteMovieNodeLL(r->head,tit);
      if(r->head == NULL){
          r = deleteMovieNodehelper(r,tit);
      }
      return;
    }else if(r->titleChar < tit[0] && r->leftChild != NULL){
      deleteMovieNode(r->leftChild,tit);
    }else if(r->titleChar > tit[0] && r->rightChild != NULL){
      deleteMovieNode(r->rightChild, tit);
    }else {cout << "Movie: " << tit << " not found, cannot delete." << endl;}
  }
}

void MovieTree::deleteMovie(string tit){
  if(root){
    deleteMovieNode(root,tit);
  }
}


**************SAVED 2************************************************************


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

LLMovieNode* deleteMovieNodeLL(LLMovieNode* n, string t){
  LLMovieNode* del = n;
  if(n == NULL){
      return NULL;
  }
  else if(t == n->title){
      //cout << "tried to delete" << endl;
      del = n;
      n = n->next;
      delete del;
      //cout << "n: " << n << endl;
      return n;
  }else if(t != n->title){
      n = deleteMovieNodeLL(n->next,t);
  }
    cout << "Movie: " << t << " not found, cannot delete." << endl;
}

TreeNode* deleteMovieNodehelper(TreeNode* r, char t){
  if(r == NULL){
    return NULL;
  }
  else if(t < r->titleChar){
    r->leftChild = deleteMovieNodehelper(r->leftChild, t);
  }
  else if(t > r->titleChar){
    r->rightChild = deleteMovieNodehelper(r->rightChild, t);
  }else{
    if(r->leftChild == NULL && r->rightChild == NULL){
    delete r;
    r = NULL;
    }
    //Only right child
    else if(r->leftChild == NULL){
      TreeNode *temp = r;
      r = r->rightChild;
      //r->titleChar = r->rightChild->titleChar;
      //r->head = r->rightChild->head;
      delete temp;
    }
    //Only left child
    else if(r->rightChild == NULL){
      TreeNode *temp = r;
      r = r->leftChild;
      //r->titleChar = r->leftChild->titleChar;
      //r->head = r->leftChild->head;
      cout << "r char: " << r->titleChar << endl;
      delete temp;
    }else{
      if(r->rightChild != NULL){
      ///Replace with Minimum from right subtree
      TreeNode *temp = getMinValueNode(r->rightChild);
      //r->titleChar = temp->titleChar;
      //r->head = temp->head;
      cout << "r char: " << r->titleChar << endl;
      deleteMovieNodehelper(r->rightChild,temp->titleChar);
      r = temp;
      delete temp;
    }else if(r->leftChild != NULL){
      ///Replace with Maximum from left subtree
      TreeNode *temp = getMaxValueNode(r->leftChild);
      //r->titleChar = temp->titleChar;
      //r->head = temp->head;
      cout << "r char: " << r->titleChar << endl;
      deleteMovieNodehelper(r->leftChild,temp->titleChar);
      r = temp;
      delete temp;
      }
    }
  }
return r;
}

void deleteMovieNode(TreeNode* r, string tit){
    if(r->head == NULL){
        cout << "Movie: " << tit << " not found, cannot delete." << endl;
        return;
    }

    if(r == NULL){
      return;
    }
    else if(r->titleChar < tit[0] && r->leftChild != NULL){
      deleteMovieNode(r->rightChild,tit);
    }
    else if(r->titleChar > tit[0] && r->rightChild != NULL){
      deleteMovieNode(r->leftChild, tit);
    }else{
      r->head = deleteMovieNodeLL(r->head,tit);
      if(r->head == NULL){
          deleteMovieNodehelper(r,tit[0]);
      }
      return;
    }
    //cout << "Movie: " << tit << " not found, cannot delete." << endl;
}

void MovieTree::deleteMovie(string tit){
  if(root){
    deleteMovieNode(root,tit);
  }else{cout << "Movie: " << tit << " not found, cannot delete." << endl;}

}

*********************************SAVE3**********************************

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

LLMovieNode* deleteMovieNodeLL(LLMovieNode* n, string t){
  LLMovieNode* del = n;
  if(n == NULL){
      return NULL;
  }
  else if(t == n->title){
      //cout << "tried to delete" << endl;
      del = n;
      n = n->next;
      delete del;
      //cout << "n: " << n << endl;
      return n;
  }else if(t != n->title){
      n = deleteMovieNodeLL(n->next,t);
  }
    cout << "Movie: " << t << " not found, cannot delete." << endl;
}

TreeNode* deleteMovieNodehelper(TreeNode* r, char t){

  if(!r){
    return r;
  }
  else if(t > r->titleChar){
    r->leftChild = deleteMovieNodehelper(r->leftChild, t);
  }
  else if(t < r->titleChar){
    r->rightChild = deleteMovieNodehelper(r->rightChild, t);
  }else{
    TreeNode *temp = r;
    if(r->leftChild == r->rightChild){
    delete r;
    r = NULL;
    }
    //Only right child
    else if(r->leftChild == NULL){
      r = r->rightChild;
      delete temp;
      // r = NULL;
      return r;
    }
    //Only left child
    else if(r->rightChild == NULL){
      r = r->leftChild;
      delete temp;
      // r = NULL;
      return r;
    }else{
      // if(r->rightChild){
          ///Replace with Minimum from right subtree
          TreeNode *Rmin = getMinValueNode(r->rightChild);
          //char c = Rmin->titleChar;
          // Rmin->titleChar = r->titleChar;
          Rmin->leftChild = r->leftChild;
          Rmin->rightChild = r->rightChild;
          Rmin->parent = r->parent;
          temp->rightChild = deleteMovieNodehelper(r->rightChild,Rmin->titleChar);


          delete temp;
          // r = NULL;
          return r;
        // }
        // }else if(r->leftChild){
        //   ///Replace with Maximum from left subtree
        //   TreeNode* Lmax = getMaxValueNode(r->leftChild);
        //   char c = Lmax->titleChar;
        //   deleteMovieNodehelper(r,Lmax->titleChar);
        //
        //   Lmax->titleChar = Lmax->titleChar;
        //   Lmax->leftChild = r->leftChild;
        //   Lmax->rightChild = r->rightChild;
        //   Lmax->parent = r->parent;
        //   delete r;
        //   r = NULL;
        //   return Lmax;
        // }
    }
  }
  return r;
}

TreeNode* deleteMovieNode(TreeNode* r, string tit){
    if(r->head == NULL){
        cout << "Movie: " << tit << " not found, cannot delete." << endl;
        return NULL;
    }
    TreeNode* hold = r;
    TreeNode *temp = r;
    if(r == NULL){
      return r;
    }

    if(temp->titleChar < tit[0]){
      temp->leftChild = deleteMovieNode(temp->leftChild,tit);
    }
    else if(temp->titleChar > tit[0]){
      temp->rightChild = deleteMovieNode(temp->rightChild, tit);
    }else{
      temp = r;
      if(r->leftChild == r->rightChild){
      delete r;
      r = NULL;
      }
      //Only right child
      else if(r->leftChild == NULL){
        r = r->rightChild;
        delete temp;
        // r = NULL;
        return r;
      }
      //Only left child
      else if(r->rightChild == NULL){
        r = r->leftChild;
        delete temp;
        // r = NULL;
        return r;
      }else{

        if(!(temp->head = deleteMovieNodeLL(temp->head,tit))){
            cout << "calling delete" << endl;
            temp = deleteMovieNode(hold,tit[0]);
            cout << "out of delete" << endl;
            }
        if(r->rightChild){
            ///Replace with Minimum from right subtree
            TreeNode *Rmin = getMinValueNode(r->rightChild);
            char c = Rmin->titleChar;

            deleteMovieNode(hold,Rmin->titleChar);

            Rmin->titleChar = c;
            Rmin->leftChild = temp->leftChild;
            Rmin->rightChild = temp->rightChild;
            Rmin->parent = temp->parent;
            delete temp;
            // r = NULL;
            return Rmin;
          }
          else if(r->leftChild){
            ///Replace with Maximum from left subtree
            TreeNode* Lmax = getMaxValueNode(r->leftChild);
            char c = Lmax->titleChar;
            deleteMovieNode(hold,Lmax->titleChar);

            Lmax->titleChar = c;
            Lmax->leftChild = temp->leftChild;
            Lmax->rightChild = temp->rightChild;
            Lmax->parent = temp->parent;
            delete temp;
            // r = NULL;
            return Lmax;
          }
        }
    }
    return r;
    //cout << "Movie: " << tit << " not found, cannot delete." << endl;
}

void MovieTree::deleteMovie(string tit){
  root = deleteMovieNode(root,tit);
  if(!root)
    cout << "Movie: " << tit << " not found, cannot delete." << endl;

}



********************************SAVE4*************************************

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

LLMovieNode* deleteMovieNodeLL(LLMovieNode* n, string t){
  LLMovieNode* del = n;
  if(n == NULL){
      return NULL;
  }
  else if(t == n->title){
      //cout << "tried to delete" << endl;
      del = n;
      n = n->next;
      delete del;
      //cout << "n: " << n << endl;
      return n;
  }else if(t != n->title){
      n = deleteMovieNodeLL(n->next,t);
  }
    cout << "Movie: " << t << " not found, cannot delete." << endl;
}


TreeNode* deleteMovieNode(TreeNode* r, string tit){

    TreeNode* hold = r;
    TreeNode* temp = r;
    if(!r){
      return r;
    }
    else if(r->titleChar < tit[0]){
      r->rightChild = deleteMovieNode(r->rightChild,tit);
    }
    else if(r->titleChar > tit[0]){
      r->leftChild = deleteMovieNode(r->leftChild, tit);
    }else{
      temp = r;
      if(r->leftChild == r->rightChild){
      delete r;
      r = NULL;
      }
      //Only right child
      else if(r->leftChild == NULL){
        temp = r->rightChild;
        delete r;
        // r = NULL;
        return temp;
      }
      //Only left child
      else if(r->rightChild == NULL){
        temp = r->leftChild;
        delete r;
        // r = NULL;
        return temp;
      }else{
        r->head = deleteMovieNodeLL(r->head,tit);
        if(r->head == NULL){
            deleteMovieNodehelper(r,tit[0]);
        }
       //if(r->rightChild){
          ///Replace with Minimum from right subtree
          temp = getMinValueNode(r->rightChild);
          char c = temp->titleChar;
          //string s = (temp->titleChar) + s;
          deleteMovieNode(r->rightChild,temp->head->title);

          temp->titleChar = c;
          temp->leftChild = r->leftChild;
          temp->rightChild = r->rightChild;
          temp->parent = r->parent;
          delete r;
          // r = NULL;
          return temp;
        //}
        //else if(r->leftChild){
          ///Replace with Maximum from left subtree
          //temp = getMaxValueNode(r->leftChild);
          //char c = temp->titleChar;
          //string s = (temp->titleChar) + s;
          //deleteMovieNode(hold,s);

          //temp->titleChar = c;
          //temp->leftChild = r->leftChild;
          //temp->rightChild = r->rightChild;
          //temp->parent = r->parent;
          //delete r;
          // r = NULL;
          //return temp;
        //}
      }
    }

    return r;
    //cout << "Movie: " << tit << " not found, cannot delete." << endl;
}
void MovieTree::deleteMovie(string tit){
  root = deleteMovieNode(root,tit);
  if(!root)
    cout << "Movie: " << tit << " not found, cannot delete." << endl;

}


**********************Another Save*****************************************


TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

void deleteMovieNodeLL(TreeNode *n, string t){
  LLMovieNode* hold = n->head;
  if(hold->title == t){
    n->head = hold->next;
    delete hold;
  }
  else if(hold->title != t && hold->next->title != t){
    hold = hold->next;
    }else if(hold->next->title == t){
        LLMovieNode* todel = hold;
        hold->next = hold->next->next;
        delete todel;
    }else {cout << "Movie: " << t << " not found, cannot delete." << endl;}

}

TreeNode* deleteMovieNodehelper(TreeNode *r, char t){
  TreeNode* temp = r;

  if(!temp){
      return temp;
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
        temp2 = temp->rightChild;
        delete temp;
        return temp2;
      }
      //Only left child
      else if(temp->rightChild == NULL){
        temp2 = temp->leftChild;
        delete temp;
        return temp2;
      }else{
        //cout << "inside helper r: " << r->titleChar << endl;
        ///Replace with Minimum from right subtree
        TreeNode* Rmin = getMinValueNode(temp->rightChild);
        //cout << "Rmin: " << Rmin->titleChar << " Rmin right: " << Rmin->rightChild->titleChar << endl;
        char c = Rmin->titleChar;
        deleteMovieNodehelper(r,c);

        Rmin->titleChar = c;
        Rmin->leftChild = temp->leftChild;
        Rmin->rightChild = temp->rightChild;

        //cout << "Rmin parent: " << Rmin->parent->titleChar << ", Rmin char " << Rmin->titleChar << endl;
        delete temp;
        return Rmin;
        }
    }
    //cout << "end helper r: " << r->titleChar << endl;
return temp;
}

TreeNode* deleteMovieNode(TreeNode *rNode, string tit){
    TreeNode* temp = rNode;

    if(!temp){
      return temp;
    }
    else if(temp->titleChar < tit[0]){
      temp->rightChild = deleteMovieNode(temp->rightChild,tit);
    }
    else if(temp->titleChar > tit[0]){
      temp->leftChild = deleteMovieNode(temp->leftChild, tit);
    }else{
      deleteMovieNodeLL(temp,tit);
      if(!temp->head){
          cout << "rNode is : " << rNode->titleChar << endl;
          temp = deleteMovieNodehelper(rNode,tit[0]);
          cout << "NULL VALUE  " << "rNode: " << rNode->titleChar << " temp: " << temp->titleChar << endl;
          return temp;
      }
      return temp;
    }
    //cout << "Movie: " << tit << " not found, cannot delete." << endl;
    return temp;
}

void MovieTree::deleteMovie(string tit){
  if(root){
    root = deleteMovieNode(root,tit);
    }
  else
    cout << "Movie: " << tit << " not found, cannot delete." << endl;
}
