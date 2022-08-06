/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork(){
   head = NULL;
   string name = "";
   string message = "";
   //int numberMessages = 0;
 }


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty(){
  if(head == nullptr){
    return true;
  }
  else{return false;}
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 void CountryNetwork::insertCountry(Country* previous, string countryName){

   if(head == nullptr){
     Country *temp = new Country;
     temp->name = countryName;
     temp->next = NULL;
     head = temp;
     // If you are adding at the beginning use:
     cout << "adding: " << countryName << " (HEAD)" << endl;
   }
   // if list is not empty, adding a new head
   else if(previous == NULL){
     Country *temp = new Country;
     temp->name = countryName;
     temp->next = head;
     head = temp;
     // If you are adding at the beginning use:
     cout << "adding: " << countryName << " (HEAD)" << endl;
      }
      else{
         Country *temp = new Country;
         temp->name = countryName;
         temp->next = previous->next;
         previous->next = temp;
         // Otherwise use this:
         cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
           }
 }


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
  Country* previous = nullptr;
  Country* temp = head;
  if(head == NULL){ //if list is empty
   cout << "list is empty" << endl;
  }
  // if list is not empty, search
  else if(head != nullptr){
    temp = searchNetwork(countryName);\
    if(temp == head){
      head = head->next;
      delete temp;
      return;
    }
    if(temp != nullptr){
      previous = head;
      while (previous->next->name != countryName && previous->next != nullptr){
          previous = previous->next;
        }
      previous->next = previous->next->next;
      delete temp;
      }
      else {cout << "Country does not exist." << endl;}
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
 void CountryNetwork::loadDefaultSetup(){
   Country *temp = new Country;
   int size = 6;
   char const* load[]= {"United States", "Canada", "Brazil", "India", "China", "Australia"};
   for (int i=0; i< size; i++){
     if(i==0){
         insertCountry(NULL,load[i]);
     }
     else {
         temp = searchNetwork(load[i-1]);
         insertCountry(temp,load[i]);
     }
   }
 }

/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
 Country* CountryNetwork::searchNetwork(string countryName){
   Country* ptr = head;
   while (ptr != NULL && ptr->name != countryName)
   {
       ptr = ptr->next;
   }
   return ptr;
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
  if(!isEmpty()){
    while (head != nullptr){
      Country * temp = head;
      cout << "deleting: " << head->name << endl;
      head = head->next;
      delete temp;
    }
    if(head == nullptr){
      cout << "Deleted network" << endl;
      return;
    }
  }else{return;}
}

/*
 * Purpose: Rotate the linked list i.e. move 'n' elements from
 * the back of the the linked to the front in the same order.
 * @param number elements to be moved from the end of the list to the beginning
 * @return none
 */
 void CountryNetwork :: rotateNetwork(int n) {
   Country* temp = head;
   Country* oldHead = head;
   //Country* prev;
   Country* nptr;
   int count = 2;
   if(!isEmpty()){
     while(temp->next != nullptr){
       temp = temp->next;
       if(count == n){
         nptr = temp;
       }
       count++;
     }
     if(count > 0 && n < count){
       head = nptr->next;
       temp->next = oldHead;
       while(oldHead->next != head){
           oldHead = oldHead->next;
       }
       oldHead->next = nullptr;
       cout << "Rotate Complete" << endl;
       return;
     }
     else {cout << "Rotate not possible" << endl; return;}
   }
   else{cout << "Linked List is Empty" << endl;}
 }

/*
 * Purpose: reverse the entire network
 * @param ptr head of list
 */
 void CountryNetwork::reverseEntireNetwork(){ //reverse the pointers while traversing
  Country *previous = nullptr; //initialize previous node as NULL
  Country *temp; //save current node
  Country *future; //save next node
  if(!isEmpty()){ //check if list is empty, then setup the rest of the variables
    temp = head; //copy current head as current node
    future = head->next; //copy next node as future
    while (future != nullptr){ //checking if the next node is null (end)
      temp->next = previous; //set temps' next pointer to point to previous node
      previous = temp; //update previous to temp
      temp = future; //update current to the future (previously saved) node
      future = temp->next; //update future node to the next to recheck condition
      if(future == nullptr){ //checking if future has reached end
          temp->next = previous; //if has loop stops fix temps' next to previous
      }
    }
    head = temp; //set the head to temp which all should be pointing backwards now
    return;
  }
 }

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
 void CountryNetwork::printPath()
 {
   Country* print = head;
   if(print == NULL){
     cout << "== CURRENT PATH ==" << endl;
     cout << "nothing in path" << endl;
     cout << "===" << endl;
     return;
   }
   if(print != NULL){
     cout << "== CURRENT PATH ==" << endl;
     while(print != NULL){
       cout<< print->name << " -> ";
       print = print->next;
     }
     cout << "NULL" << endl;
     cout << "===" << endl;
   }
 }
