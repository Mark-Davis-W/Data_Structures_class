/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.cpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace std;
// you may include more libraries as needed

// declarations for main helper-functions
// void displayMenu();

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char* argv[]) {
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    string choice;
    CountryNetwork CountryNet;
    string userCountry;
    string prevCountry;
    string userMessage;
    Country *ptr = NULL;

    while(choice != "5"){
      displayMenu();
      getline(cin,choice);
      int intChoice = stoi(choice);
      switch (intChoice) {
        case 1:
          CountryNet.loadDefaultSetup();
          CountryNet.printPath();
          break;

        case 2:
          CountryNet.printPath();
          break;
        case 3:
          cout << "Enter name of the country to receive the message:" << endl;
          getline(cin,userCountry);
          cout << "Enter the message to send:\n" << endl;
          getline(cin,userMessage);
          CountryNet.transmitMsg(userCountry,userMessage);
          break;
        case 4:
          cout << "Enter a new country name:" << endl;
          getline(cin,userCountry);
          if(!(userCountry[0] >= 'A' && userCountry[0] <= 'Z')){
            userCountry[0] = userCountry[0]- 32;
          }
          cout << "Enter the previous country name (or First):" << endl;
          getline(cin,prevCountry);

          ptr = CountryNet.searchNetwork(prevCountry);
          while (ptr == NULL){
            // cout << "help me" << endl;
            if((prevCountry == "First") || (prevCountry == "first")){
              prevCountry = "NULL";
              break;
            } else if (!(prevCountry[0] <= 'A' && prevCountry[0] >= 'Z') && !(prevCountry == "First" || prevCountry == "first")){
              cout << "INVALID(previous country name)...Please enter a VALID previous country name!" << endl;
              getline(cin,prevCountry);
              ptr = CountryNet.searchNetwork(prevCountry);
            }
          }

          CountryNet.insertCountry(ptr,userCountry);

          CountryNet.printPath();
          break;

        case 5:
          cout << "Quitting..." << endl;
          cout << "Goodbye!" << endl;
          break;
        default:
            cout << "invalid input" << endl;
            cout << endl;
      }
    }

    return 0;
}
