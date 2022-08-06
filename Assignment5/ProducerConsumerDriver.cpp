/****************************************************************/
/*                Producer Consumer Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "ProducerConsumer.cpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}

int main(int argc, char const *argv[]){
	string choice;
	ProducerConsumer Prod;
	string queueItem;
	string sizeSelect;
	int itemSize = 0;
	int i = 0;

	while(choice != "3"){
		menu();
		getline(cin,choice);
		int intChoice = stoi(choice);
		switch (intChoice) {

			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				getline(cin,sizeSelect);
				itemSize = stoi(sizeSelect);
				i=0;
				while(i<itemSize){
				    getline(cin,queueItem);
					cout << "Item" << i+1 << ":" << endl;
					Prod.enqueue(queueItem);
					i++;
				}
				break;

			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				getline(cin,sizeSelect);
				itemSize = stoi(sizeSelect);
				i=0;
				while(!Prod.isEmpty() && i<itemSize){
					if(i<itemSize){
						cout << "Consumed: " << Prod.peek() << endl;
						Prod.dequeue();
						i++;
					}else{
						cout<< "No more items to consume from queue" << endl;
						break;
					}
				}
				if(Prod.isEmpty()){
				    cout<< "No more items to consume from queue" << endl;
				    break;
				}
				break;

			case 3:
				cout << "Number of items in the queue:" << Prod.queueSize() << endl;
				break;
			}
	}
}
