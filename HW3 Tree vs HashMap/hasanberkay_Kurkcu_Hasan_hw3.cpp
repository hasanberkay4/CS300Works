#include "HashTable.cpp"
#include "BST.cpp"
#include <fstream>
#include <chrono>

#pragma comment(linker, "/STACK:2000000")
#pragma comment(linker, "/HEAP:2000000")

using namespace std;

struct DocumentItem {
	string documentName;
	int count;

	DocumentItem(){};
	DocumentItem(string dn, int c): documentName(dn), count(c){};
};

struct WordItem {
	string word;
	vector<DocumentItem> freqList;

	WordItem(){};
	WordItem(string w): word(w){};

	friend bool operator > ( const WordItem & x, const WordItem & rhs)	{ return rhs.word < x.word; };
	friend bool operator < ( const WordItem & x, const WordItem & rhs)	{ return rhs.word > x.word; };
	friend bool operator == ( const WordItem & x, const WordItem & rhs)	{ return rhs.word == x.word; };
	friend bool operator != ( const WordItem & x, const WordItem & rhs)	{ return rhs.word != x.word; };
};

int fileExist(WordItem & word, const string & fName){
	for(unsigned int i = 0; i < word.freqList.size(); i++){
		if(word.freqList[i].documentName == fName){
			return i;
		}
	}
	return -1;
}

void insertTable(HashTable<WordItem>& table, const string& toInsert, const string& fName) {

	WordItem currWordItem(toInsert);
	WordItem* foundWord = table.find(currWordItem);

	if (foundWord == nullptr) {
		currWordItem.freqList.push_back(DocumentItem(fName, 1));
		table.insert(currWordItem);
	}

	else {
		int filePos = fileExist(*foundWord, fName);
		if (filePos != -1) {
			foundWord->freqList[filePos].count += 1;
		}
		else {
			foundWord->freqList.push_back(DocumentItem(fName, 1));
		}
	}
}

void insertTree(BinarySearchTree<WordItem>& tree, const string& toInsert, const string& fName) {
	WordItem currWordItem(toInsert);

	WordItem* foundWord = tree.find(currWordItem);
	if (foundWord == nullptr) {
		currWordItem.freqList.push_back(DocumentItem(fName, 1));
		tree.insert(currWordItem);
	}

	else {
		int filePos = fileExist(*foundWord, fName);
		if (filePos != -1) {
			foundWord->freqList[filePos].count += 1;
		}
		else {
			foundWord->freqList.push_back(DocumentItem(fName, 1));
		}
	}
}

void initStructures(const int& docNum, BinarySearchTree<WordItem>& tree, HashTable<WordItem>& table, vector<string>& distinctFiles) {
	string currFile;
	for (int i = 0; i < docNum; i++) {
		cout << "Enter " << i + 1 << ". file name: ";	cin >> currFile;
		distinctFiles.push_back(currFile);
	}

	string currWord = "";
	for (unsigned int i = 0; i < distinctFiles.size(); i++) {
		fstream myFile(distinctFiles[i]);

		string currLine;
		while (getline(myFile, currLine)) {
			for (unsigned int l = 0; l < currLine.length(); l++) {
				if (isalpha(currLine[l]))
					currWord += tolower(currLine[l]);

				else if (currWord != "") {
					insertTable(table, currWord, distinctFiles[i]);
					insertTree(tree, currWord, distinctFiles[i]);
					currWord = "";
				}
			}

			if (currWord != "") { // for end of the line
				insertTable(table, currWord, distinctFiles[i]);
				insertTree(tree, currWord, distinctFiles[i]);
			}
			currWord = "";
		}
		myFile.close();
	}
}

void processTree(BinarySearchTree<WordItem> & tree, const vector<string> & queriesSeperated, const vector<string> & distinctFiles, const int testTime, string & result){
	bool printedResult = false;		string finalizedResult;
	int foundTxt, notFoundTxt = 0;
		for(int i = 0; i < testTime; i++){ // 20 Times
		string tempResult = "";

			for (int j = 0; j < distinctFiles.size(); j++){ // For every txt
				foundTxt = 0;
				string currFile = distinctFiles[j];

				for(int w = 0; w < queriesSeperated.size(); w++){ // For every query
					WordItem* foundItem = tree.find(WordItem(queriesSeperated[w]));

					if(foundItem != nullptr){
						for(int u = 0; u < foundItem->freqList.size(); u++){
							string docName = foundItem->freqList[u].documentName;
							int count = foundItem->freqList[u].count;

							if(docName == currFile){
								tempResult += ", " + foundItem->word + " found " + to_string(count) + " times";
								foundTxt++;
							}
						}
					}
				}
				if (foundTxt == queriesSeperated.size())
					finalizedResult += "in Document " + currFile + tempResult + ".\n";
				else
					notFoundTxt++;

				tempResult = "";
			}
			if (!printedResult) {
				if (notFoundTxt == distinctFiles.size())
					result = "No document contains the given query\n";

				else
					result = finalizedResult;

				printedResult = true;
			}
		}
}

void processTable(HashTable<WordItem>& table, const vector<string>& queriesSeperated, const vector<string>& distinctFiles, const int testTime, string & result) {
	bool printedResult = false;	string finalizedResult;
	int foundTxt, notFoundTxt = 0;
	for (int i = 0; i < testTime; i++) { // 20 Times
		string tempResult = "";

		for (int j = 0; j < distinctFiles.size(); j++) { // For every txt
			foundTxt = 0;
			string currFile = distinctFiles[j];

			for (int w = 0; w < queriesSeperated.size(); w++) { // For every query
				WordItem* foundItem = table.find(WordItem(queriesSeperated[w]));

				if (foundItem != nullptr) {
					for (int u = 0; u < foundItem->freqList.size(); u++) {
						string docName = foundItem->freqList[u].documentName;
						int count = foundItem->freqList[u].count;

						if (docName == currFile) {
							tempResult += ", " + foundItem->word + " found " + to_string(count) + " times";
							foundTxt++;
						}
					}
				}
			}
			if (foundTxt == queriesSeperated.size())
				finalizedResult += "in Document " + currFile + tempResult + ".\n";
			else
				notFoundTxt++;

			tempResult = "";
		}
		if (!printedResult) {
			if (notFoundTxt == distinctFiles.size())
				result = "No document contains the given query\n";

			else
				result = finalizedResult;

			printedResult = true;
		}
	}
}

void processQueries(BinarySearchTree<WordItem> & tree, HashTable<WordItem> & table, vector<string> & distinctFiles){
	string query;	cout << "Enter queried words in one line: ";
	cin.ignore();	getline(cin, query);

	int k = 100;
	vector<string> queriesSeperated;

	string currWord = "";
	for(unsigned int l = 0; l < query.length(); l++){
		if(isalpha(query[l]))
			currWord += tolower(query[l]);

		else if(currWord != ""){
			queriesSeperated.push_back(currWord);
			currWord = "";
		}
	}

	if(currWord != "") // for end of the line
		queriesSeperated.push_back(currWord);

	string resultHT, resultBST;

	auto start = chrono::high_resolution_clock::now();
	processTree(tree, queriesSeperated, distinctFiles, k, resultBST);
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
	cout << resultBST;

	start = std::chrono::high_resolution_clock::now();
	processTable(table, queriesSeperated, distinctFiles, k, resultHT);
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
	cout << resultHT;

	cout << "\nTime: " << BSTTime / k << endl;
	cout << "Time: " << HTTime / k << endl;
	cout << "Speed Up: " << (float(BSTTime) / k) / (float(HTTime) / k) << endl;
}

int main(){
	int docNum;
	cout << "Enter number of input files: ";	cin >> docNum;

	BinarySearchTree<WordItem> wordTree;
	HashTable<WordItem> wordTable(101);

	vector<string> distinctFiles;

	initStructures(docNum, wordTree, wordTable, distinctFiles);
	wordTable.printFinalStat();

	processQueries(wordTree, wordTable, distinctFiles);

	return 0;
}