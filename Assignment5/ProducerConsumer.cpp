/****************************************************************/
/*                Producer Consumer File                        */
/****************************************************************/
/* TODO: Implement functions as described in the writeup        */
/****************************************************************/

#include "ProducerConsumer.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

ProducerConsumer::ProducerConsumer(){
  queueEnd = 0;
  queueFront = 0;
}

bool ProducerConsumer::isEmpty(){
  return (queueFront == queueEnd && counter == 0);
}

bool ProducerConsumer::isFull(){
  return (counter == SIZE);
}

void ProducerConsumer::enqueue(string item){
  if(!isFull()){
    if(isEmpty()){
      queueEnd++;
      queue[queueFront] = item;
      counter++;
    }else {
      if(queueEnd == SIZE){
        queueEnd = 0;
      }
      queue[queueEnd] = item;
      queueEnd++;
      counter++;
    }
  }else {cout << "Queue full, cannot add new item" << endl;}
}

void ProducerConsumer::dequeue(){
  if(queueFront == SIZE){
    queueFront = 0;
  }
  if(!isEmpty()){
  queue[queueFront] = "";
  queueFront++;
  counter--;
  }else{cout << "Queue empty, cannot dequeue an item" << endl;}
}

string ProducerConsumer::peek(){
  if(isEmpty()){
    cout << "Queue empty, cannot peek";
    return "";
  }else{
    return queue[queueFront];
  }
}

int ProducerConsumer::queueSize(){//changed
  return counter;
}
