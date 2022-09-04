#include "AVL.cpp"
#include "BST.cpp"
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <queue>
#include <vector>

#pragma comment(linker, "/STACK:2000000")
#pragma comment(linker, "/HEAP:2000000")

using namespace std;

void createNotebooks(BinarySearchTree<BSTSection> & BSTSections,  AvlTree<AVLSection> & AVLSections){
	
	queue<long long> bTimes, aTimes;
	vector<string> sectNames;

	fstream myFile("data.txt");
	string currLine, iTitle, iInfo, parseValue;
	
	getline(myFile, currLine);
	AVLSection currSectionA;
	currSectionA.title = currLine;

	BSTSection currSection;
	currSection.title = currLine;
	sectNames.push_back(currLine);

	long long totalTimeAVL = 0.0;
	long long totalTimeBST = 0.0;

	while(getline(myFile, currLine)){
		if(currLine.at(0) == '-'){
			istringstream sStream(currLine, '-');
		
			getline(sStream, parseValue, '-');
			getline(sStream, parseValue, '-');
			iTitle = parseValue;
			getline(sStream, parseValue, '-');
			iInfo = parseValue;

			item currItem(iTitle, iInfo);

			auto startA = std::chrono::high_resolution_clock::now();
			currSectionA.items.insert(currItem);
			auto endA = std::chrono::high_resolution_clock::now();
			totalTimeAVL += (endA-startA).count() / 1000.0;

			auto start = std::chrono::high_resolution_clock::now();
			currSection.items.insert(currItem);
			auto end = std::chrono::high_resolution_clock::now();
			totalTimeBST += (end-start).count() / 1000.0;
		}

		else{
			auto startA = std::chrono::high_resolution_clock::now();
			AVLSections.insert(currSectionA);
			auto endA = std::chrono::high_resolution_clock::now();
			totalTimeAVL += (endA-startA).count() / 1000.0;

			aTimes.push(totalTimeAVL);	totalTimeAVL = 0.0;

			currSectionA.items.~AvlTree();
			currSectionA = AVLSection();
			currSectionA.title = currLine;

			sectNames.push_back(currLine);
			auto start = std::chrono::high_resolution_clock::now();
			BSTSections.insert(currSection);
			auto end = std::chrono::high_resolution_clock::now();
			totalTimeBST += (end-start).count() / 1000.0;
			bTimes.push(totalTimeBST);	totalTimeBST = 0.0;

			currSection.items.~BinarySearchTree();
			currSection = BSTSection();
			currSection.title = currLine;
		}
	} 

	auto startA = std::chrono::high_resolution_clock::now();
	AVLSections.insert(currSectionA);
	auto endA = std::chrono::high_resolution_clock::now();
	totalTimeAVL += (endA-startA).count() / 1000.0;
	aTimes.push(totalTimeAVL);

	auto start = std::chrono::high_resolution_clock::now();
	BSTSections.insert(currSection);
	auto end = std::chrono::high_resolution_clock::now();
	totalTimeBST += (end-start).count() / 1000.0;
	bTimes.push(totalTimeBST);

	myFile.close();

	cout << "Welcome to the Notebook!\n\n";

	for(int i = 0; i < sectNames.size(); i++){
		long long bTime = bTimes.front();	bTimes.pop();		long long aTime = aTimes.front();	aTimes.pop();
		cout << "Section \"" << sectNames[i] << "\" has been inserted into the AVL notebook.\n";
		std::cout << "[AVL] Elapsed time: " << aTime << " microseconds" << endl;

		cout << "Section \"" << sectNames[i] << "\" has been inserted into the BST notebook.\n";
		std::cout << "[BST] Elapsed time: " << bTime << " microseconds" << endl << endl;
	}
}

void displayInfo(BinarySearchTree<item>* & subTree, AvlTree<item>* & subTreeA){
	string itemName;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, itemName);

	item toFind(itemName, "");

	auto startA = std::chrono::high_resolution_clock::now();
	item* foundItemA = subTreeA->find(toFind);
	auto endA = std::chrono::high_resolution_clock::now();
	long long timer = (endA-startA).count() / 1000.0;
	std::cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;

	auto start = std::chrono::high_resolution_clock::now();
	item* foundItem = subTree->find(toFind);
	auto end = std::chrono::high_resolution_clock::now();
	timer = (end-start).count() / 1000.0;
	std::cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;

	if(foundItemA == nullptr){
		cout << "Invalid title." << endl;
	}

	else{
		cout << foundItemA->info << endl;
	}
}

void addItem(BinarySearchTree<item>* & subTree, const string & sectTitle, AvlTree<item>* & subTreeA){
	string itemName, itemDef;
	cout << "Enter a title for the item: ";
	cin.ignore();
	getline(cin, itemName);
	

	item toFind(itemName, "");

	item* foundItem = subTree->find(toFind);

	item* foundItemA = subTreeA->find(toFind);

	if(foundItem != nullptr){
		cout << "Item \"" << itemName << "\" already exists in the \"" << sectTitle << "\"." << endl;
	}

	else{
		cout << "Enter a description for the item: ";
		getline(cin, itemDef);

		item itemToAdd(itemName, itemDef);

		auto start = std::chrono::high_resolution_clock::now();
		subTreeA->insert(itemToAdd);
		auto end = std::chrono::high_resolution_clock::now();
		long long timer = (end-start).count() / 1000.0;
		std::cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;
		
		auto startA = std::chrono::high_resolution_clock::now();
		subTree->insert(itemToAdd);
		auto endA = std::chrono::high_resolution_clock::now();
		timer = (endA-startA).count() / 1000.0;
		std::cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;

		cout << "The new item \"" << itemName << "\" has been inserted.\n"; 
	}
}

void updateItem(BinarySearchTree<item>* & subTree, const string & sectTitle, AvlTree<item>* & subTreeA){
	string itemName;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, itemName);

	item toFind(itemName, "");

	auto start = std::chrono::high_resolution_clock::now();
	item* foundItemA = subTreeA->find(toFind);
	auto end = std::chrono::high_resolution_clock::now();
	long long timer = (end-start).count() / 1000.0;
	std::cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;

	auto startA = std::chrono::high_resolution_clock::now();
	item* foundItem = subTree->find(toFind);
	auto endA = std::chrono::high_resolution_clock::now();
	timer = (endA-startA).count() / 1000.0;
	std::cout << "[BST] Elapsed time: " << timer << " microseconds" << endl;

	if(foundItem == nullptr){
		cout << "Item \"" << itemName << "\" does not exist in the \"" << sectTitle << "\"." << endl;
	}

	else{
		string info;
		cout << "Enter the new information: ";
		getline(cin, info);

		foundItem->info = info;
		foundItemA->info = info;
		cout << "The content \"" << itemName << "\" has been updated." << endl;
	}
}

void deleteItem(BinarySearchTree<item>* & subTree, const string & BT, AvlTree<item>* & subTreeA){
	string itemName;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, itemName);

	item toFind(itemName, "");

	item* foundItem = subTree->find(toFind);
	item* foundItemA = subTreeA->find(toFind);
	
	if(foundItem == nullptr){
		cout << "Item \"" << itemName << "\" does not exist in the \"" << BT << "\"." << endl;
	}

	else{
		subTree->remove(*foundItem);	subTreeA->remove(*foundItemA);
		cout << "The item \"" << itemName << "\" has been deleted." << endl;
	}
}

void subMenu(BinarySearchTree<item>* subTree, const string & title, AvlTree<item>* subTreeA){
	int choice;

	cout << "Please enter an input between [1 - 7]:" << endl
	<< "1- Display the items [AVL]" << endl
	<< "2- Display the items [BST]" << endl
	<< "3- Display the information of a item" << endl
	<< "4- Add new item" << endl
	<< "5- Update the information of a item" << endl
	<< "6- Delete an item" << endl
	<< "7- Return to main menu" << endl
	<< "Input: ";

	cin >> choice;		cout << "\n";

	while(choice != 7){
		if(choice == 1){
			cout << "*****" << endl;
			subTreeA->printTree();
			cout << "*****" << endl;
		}
		else if(choice == 2){
			cout << "*****" << endl;
			subTree->printTree();
			cout << "*****" << endl;
		}

		else if(choice == 3){
			displayInfo(subTree, subTreeA);
		}

		else if(choice == 4){
			addItem(subTree, title, subTreeA);
		}

		else if(choice == 5){
			updateItem(subTree, title, subTreeA);
		}

		else if(choice == 6){
			deleteItem(subTree, title, subTreeA);
		}

		cout << "\nInput: ";		cin >> choice;
	}
}

bool selectSec(BinarySearchTree<BSTSection> & BST, AvlTree<AVLSection> & AVL){
	string secName;
	cout << "Enter the title of the section: ";
	cin >> secName;

	BSTSection toFind(secName);	
	BSTSection* foundSect = BST.find(toFind);

	AVLSection toFindA(secName);
	AVLSection* foundSectA = AVL.find(toFindA);

	if(foundSect == nullptr){
		cout << "Invalid title!" << endl;
		return false;
	}

	else{
		BinarySearchTree<item>* subTree = &(foundSect->items);
		AvlTree<item>* subTreeA = &(foundSectA->items);

		cout << "\nSelected section -> " << secName << endl;
		subMenu(subTree, foundSect->title, subTreeA);

		return true;
	}
}

void addSec(BinarySearchTree<BSTSection> & BST, AvlTree<AVLSection> & AVL){
	string secName;
	cin.ignore();
	cout << "Enter a title for the section: ";
	cin >> secName;

	BSTSection toFind(secName);		BSTSection* found = BST.find(toFind);

	if(found != nullptr){
		cout << "Section \"" << secName << "\" already exists." << endl;
	}
	else{
		BSTSection currSection(secName);	
		BST.insert(currSection);

		AVLSection currSectionA(secName);	
		AVL.insert(currSectionA);

		cout << "The new section \"" << secName << "\" has been inserted.\n"; 
	}
}

void deleteSec(BinarySearchTree<BSTSection> & BST, AvlTree<AVLSection> & AVL){
	string secName;
	cout << "Enter the title of the section: ";
	cin >> secName;

	BSTSection toFind(secName);
	AVLSection toFindA(secName);

	BSTSection* foundSect = BST.find(toFind);
	AVLSection* foundSectA = AVL.find(toFindA);

	if(foundSect == nullptr){
		cout << "Section \"" << secName << "\" does not exist." << endl;
	}
	else{
		BST.remove(*foundSect);		AVL.remove(*foundSectA);
		cout << "The section has been deleted." << endl;
	}
}

void displayMenu(){
	cout << "MENU" << endl
	<< "Please enter an input between [1 - 6]:" << endl
	<< "1- Display the sections [AVL]" << endl
	<< "2- Display the sections [BST]" << endl
	<< "3- Select a section" << endl
	<< "4- Add new section" << endl
	<< "5- Delete a section" << endl
	<< "6- Exit" << endl;
}

bool mainMenu(BinarySearchTree<BSTSection> & BST, AvlTree<AVLSection> & AVL){
	int choice;

	displayMenu();
	
	cout <<	"Input: ";

	cin >> choice;	cout << "\n";

	while(choice != 6){
		if(choice == 1){
			cout << "*****\n";
			AVL.printTree();
			cout << "*****" << endl;
		}
		else if(choice == 2){
			cout << "*****\n";
			BST.printTree();
			cout << "*****" << endl;
		}
		else if(choice == 3){
			if(selectSec(BST, AVL))
				displayMenu();
		}

		else if(choice == 4){
			addSec(BST, AVL);
		}

		else if(choice == 5){
			deleteSec(BST, AVL);
		}

		cout << "\nInput: ";		cin >> choice;
	}

	return false;
}


int main(){
	BinarySearchTree<BSTSection> BSTSections;
	AvlTree<AVLSection> AVLSections;

	createNotebooks(BSTSections, AVLSections);

	bool locked = mainMenu(BSTSections, AVLSections);
	while( locked ){
		mainMenu(BSTSections, AVLSections);
	}

	return 0;
}