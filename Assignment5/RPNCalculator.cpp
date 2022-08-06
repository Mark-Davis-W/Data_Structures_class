/****************************************************************/
/*                  RPN Calculator function File                */
/****************************************************************/
/*      TODO: Implement functions as described in the writeup   */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

RPNCalculator::RPNCalculator(){
  stackHead = NULL;
}
RPNCalculator::~RPNCalculator(){
  while(!isEmpty())
    pop();
  stackHead = NULL;
}
bool RPNCalculator::isEmpty(){
  if(stackHead)
    return false;

  return true;
}
void RPNCalculator::push(float num){
  Operand *newOperand = new Operand;
  newOperand->number = num;
  newOperand->next = stackHead;
  stackHead = newOperand;
}
void RPNCalculator::pop(){
  if(!stackHead){
    cout << "Stack empty, cannot pop an item." << endl;
    return;}

  Operand *node = stackHead;
  stackHead = stackHead->next;
  delete node;
}

Operand* RPNCalculator::peek(){
  if(!isEmpty())
      return stackHead;
  else{
      cout<<"Stack empty, cannot peek."<<endl;
      return NULL;
  }
}

bool RPNCalculator::compute(string symbol){
  if(symbol == "+" || symbol == "*"){
    float node;
    float node2;
    if(stackHead == NULL){
      cout << "err: not enough Operands" << endl;return 0;
    }else{node = stackHead->number;pop();}

    if(stackHead == NULL){
      cout << "err: not enough Operands" << endl; push(node);return 0;
    }else{
      node2 = stackHead->number;
      pop();
      }
    if(symbol == "+"){
    //cout << "adding " << node << "+ " << node2 << endl;
      node = node + node2;
      push(node);
    }
    if(symbol == "*"){
      node = node * node2;
      push(node);
    }
    return 1;
  }else{cout << "err: invalid operation" << endl;return 0;}
}
