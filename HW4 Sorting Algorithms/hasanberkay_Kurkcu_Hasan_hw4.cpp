#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include "sortFuncs.h"
#include "searchFuncs.h"

using namespace std;

string convertName(const string & x) {
	string n = x;
	for (int i = 0; i < n.size(); i++)
		n.at(i) = toupper(n.at(i));

	return n;
}

void readAndProcess(vector<person>& v1, vector<person>& v2, vector<person>& v3, vector<person>& v4, string& query) {
	string fName;
	cout << "Please enter the contact file name: " << endl;
	cin >> fName;

	fstream myFile(fName);

	string i1, i2, i3, i4;

	string currLine;
	while (getline(myFile, currLine)) {
		istringstream ss(currLine);

		ss >> i1 >> i2 >> i3 >> i4;
		person p(i1 + " " + i2, i3, i4);

		v1.push_back(p);	v2.push_back(p);
		v3.push_back(p);	v4.push_back(p);
	}

	cout << "Please enter the word to be queried: " << endl;
	cin.ignore();
	getline(cin, query);
}

///////////////////////////////////////////////////////////////////////////////////////////

void findSortSpeedUp(string& sortSpeedUp, long long& slowest, long long& qsTime, long long& msTime, long long& hsTime, long long isTime){
	if (slowest == qsTime) {
		sortSpeedUp = "(Insertion Sort / Quick Sort) SpeedUp = " + to_string(float(isTime) / (slowest)) +
			"\n(Merge Sort / Quick Sort) SpeedUp = " + to_string(float(msTime) / (slowest)) +
			"\n(Heap Sort / Quick Sort) SpeedUp = " + to_string(float(hsTime) / (slowest)) + "\n";
	}

	else if (slowest == isTime) {
		sortSpeedUp = "(Quick Sort / Insertion Sort) SpeedUp = " + to_string(float(qsTime) / (slowest)) +
			"\n(Merge Sort / Insertion Sort) SpeedUp = " + to_string(float(msTime) / (slowest)) +
			"\n(Heap Sort / Insertion Sort) SpeedUp = " + to_string(float(hsTime) / (slowest)) + "\n";
	}

	else if (slowest == msTime) {
		sortSpeedUp = "(Quick Sort / Merge Sort) SpeedUp = " + to_string(float(qsTime) / (slowest)) +
			"\n(Insertion Sort / Merge Sort) SpeedUp = " + to_string(float(isTime) / (slowest)) +
			"\n(Heap Sort / Merge Sort) SpeedUp = " + to_string(float(hsTime) / (slowest)) + "\n";
	}

	else {
		sortSpeedUp = "(Quick Sort / Heap Sort) SpeedUp = " + to_string(float(qsTime) / (slowest)) +
			"\n(Insertion Sort / Heap Sort) SpeedUp = " + to_string(float(isTime) / (slowest)) +
			"\n(Merge Sort / Heap Sort) SpeedUp = " + to_string(float(msTime) / (slowest)) + "\n";
	}
}

template <class Comparable>
void sortings(vector<Comparable>& k1, vector<Comparable>& k2, vector<Comparable>& k3, vector<Comparable>& k4, string & sortSpeedUp) {
	vector<long long> times;
	cout << "\nSorting the vector copies\n";
	cout << "======================================\n";

	auto start = chrono::high_resolution_clock::now();
	quicksort(k1);
	auto qsTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
	
	start = chrono::high_resolution_clock::now();
	insertionSort(k2);
	auto isTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

	start = chrono::high_resolution_clock::now();
	mergeSort(k3);
	auto msTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

	start = chrono::high_resolution_clock::now();
	heapsort(k4);
	auto hsTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

	vector<long long> speedupTimes;
	speedupTimes.push_back(qsTime);
	speedupTimes.push_back(isTime);
	speedupTimes.push_back(msTime);
	speedupTimes.push_back(hsTime);

	insertionSort(speedupTimes);

	long long slowest = speedupTimes[0];

	findSortSpeedUp(sortSpeedUp, slowest, qsTime, msTime, hsTime, isTime);
		
	cout << "Quick Sort Time: " << qsTime << " Nanoseconds" << endl;
	cout << "Insertion Sort Time: " << isTime << " Nanoseconds" << endl;
	cout << "Merge Sort Time: " << msTime << " Nanoseconds" << endl;
	cout << "Heap Sort Time: " << hsTime << " Nanoseconds" << endl;
}

void queries(vector<person>& sorted, const string & query, string & searchSpeedUp) {
	cout << "\nSearching for " << query << "\n";
	cout << "======================================\n";

	string result;

	if (query.find(" ") != string::npos) {

		auto start = chrono::high_resolution_clock::now();
		int resultL = fullLSearch(sorted, query);
		auto lFTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

		start = chrono::high_resolution_clock::now();
		int resultB = fullBSearch(sorted, query, 0, sorted.size() - 1);
		auto bFTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
		
		result = (resultB == -1) ? convertName(query) + " does NOT exist in the dataset\n" : sorted[resultL].convert(sorted[resultL]);

		cout << result << "Binary Search Time: " << bFTime << " Nanoseconds\n";

		cout << "\nSearch results for Sequential Search: \n";
		cout << result << "Sequential Search Time: " << lFTime << " Nanoseconds\n";

		if (lFTime > bFTime)
			searchSpeedUp = "(Sequential Search / Binary Search) SpeedUp = " + to_string(float(lFTime) / (bFTime)) + "\n";

		else
			searchSpeedUp = "(Binary Search / Sequential Search) SpeedUp = " + to_string(float(bFTime) / (lFTime)) + "\n";
	}

	else {
		auto start = chrono::high_resolution_clock::now();
		vector<person> resultB = partialBSearch(sorted, query, 0, sorted.size() - 1);
		auto bTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

		start = chrono::high_resolution_clock::now();
		vector<person> resultL = partialLSearch(sorted, query);
		auto lTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();

		if (resultB.size() == 0)
			cout << convertName(query) + " does NOT exist in the dataset\n";
		else
			for (int i = 0; i < resultL.size(); i++)
				cout << resultB[i];
		cout << result << "Binary Search Time: " << bTime << " Nanoseconds\n";


		cout << "\nSearch results for Sequential Search: \n";
		if (resultL.size() == 0)
			cout << convertName(query) + " does NOT exist in the dataset\n";

		else
			for (int i = 0; i < resultL.size(); i++)
				cout << resultL[i];

		cout << result << "Sequential Search Time: " << lTime << " Nanoseconds\n";

		if(lTime > bTime)
			searchSpeedUp = "(Sequential Search / Binary Search) SpeedUp = " + to_string(float(lTime) / (bTime)) + "\n";
		
		else
			searchSpeedUp = "(Binary Search / Sequential Search) SpeedUp = " + to_string(float(bTime) / (lTime)) + "\n";
	}
}

int main() {
	vector<person> k1;		vector<person> k2;
	vector<person> k3;		vector<person> k4;

	string query;

	string sortSpeedUp = "";
	string searchSpeedUp = "";

	readAndProcess(k1, k2, k3, k4, query);
	sortings(k1, k2, k3, k4, sortSpeedUp);
	queries(k1, query, searchSpeedUp);

	cout << "\nSpeedUp between Search Algorithms\n" <<
		"======================================\n" <<
		searchSpeedUp;

	cout << "\nSpeedUps between Sorting Algorithms\n" <<
		"======================================\n" <<
		sortSpeedUp;

	return 0;
}