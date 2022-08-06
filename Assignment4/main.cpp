/****************************************************************/
/*                   Assignment 4 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.cpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <cstdlib>
// you may include more libraries as needed

using namespace std;

//void displayMenu();

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Add Country " << endl;
    cout << " 4. Delete Country " << endl;
    cout << " 5. Reverse Network" << endl;
    cout << " 6. Rotate Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

int main(int argc, char* argv[])
{
    // Object representing our network of cities.
    // (Linked list representation is in CountryNetwork)
    CountryNetwork CountryNet;
    string choice;
    string userCountry;
    string prevCountry;
    //string userMessage;
    Country *ptr = NULL;
    string value;
    int rotValue=0;

    while(choice != "8"){
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
          cout << "Enter a new country name:" << endl;
          getline(cin,userCountry);
          if(!(userCountry[0] >= 'A' && userCountry[0] <= 'Z')){
            userCountry[0] = userCountry[0]- 32;
          }
          cout << "Enter the previous country name (or First):" << endl;
          getline(cin,prevCountry);
          ptr = CountryNet.searchNetwork(prevCountry);
          while (ptr == nullptr){
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
        case 4:
          cout << "Enter a country name:" << endl;
          getline(cin,userCountry);
          CountryNet.deleteCountry(userCountry);
          CountryNet.printPath();
          break;
        case 5:
          CountryNet.reverseEntireNetwork();
          CountryNet.printPath();
          break;

        case 6:
          cout << "Enter the count of values to be rotated:" << endl;
          getline(cin,value);
          rotValue = stoi(value);
          CountryNet.rotateNetwork(rotValue);
          CountryNet.printPath();
          break;

        case 7:
          cout << "Network before deletion" << endl;
          CountryNet.printPath();
          CountryNet.deleteEntireNetwork();
          cout << "Network after deletion" << endl;
          CountryNet.printPath();
          break;

        case 8:
          cout << "Quitting... cleaning up path: " << endl;
          CountryNet.printPath();
          CountryNet.deleteEntireNetwork();
          if(CountryNet.isEmpty()){
            cout << "Path cleaned" << endl;
          }
          else {cout << "Error: Path NOT cleaned" << endl;}

          cout << "Goodbye!" << endl;
          break;
        default:
            cout << "invalid input" << endl;
            cout << endl;
      }
    }

    return 0;
}
