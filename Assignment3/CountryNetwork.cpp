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
  int numberMessages = 0;
}


/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
 void CountryNetwork::insertCountry(Country* previous, string countryName){

   if(head == NULL){
     Country *temp = new Country;
     head = temp;
     head->name = countryName;
     head->next = NULL;
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
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
 void CountryNetwork::transmitMsg(string receiver, string message){
   bool found = false;
   if(head == NULL){ //checks if list is empty
     cout << "Empty list" << endl;
     return;
   }
   Country *temp;
   Country *ptr = NULL;
   temp = head;
   if(temp != NULL){//checking if list has the name needed
     while(found == false & temp != NULL){
       if(temp->name == receiver){
         ptr = temp; //storing when found
         found = true;
       }
       temp = temp -> next; //progressing pointer to next one
     }
   }
   if(found != true){ //checking previous search bool to see if found
     cout << "Country not found" << endl;
     return;
   }
   if(found == true){ //if found we need to reset to beginning and print
     temp = head;
     while(temp != NULL & temp != ptr->next){
       temp->numberMessages++;
       temp->message = message;
       cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
       temp = temp -> next;
     }
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
