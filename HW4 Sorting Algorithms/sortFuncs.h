#ifndef _SORTFUNCS_H
#define _SORTFUNCS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct person {
	string name;
	string no;
	string city;

	person() {}

	person(string n) :
		name(n) {}

	person(string n, string no, string c) :
		name(n), no(no), city(c) {}


	friend bool operator > (const person& x, const person& rhs) { return rhs.name < x.name; };
	friend bool operator < (const person& x, const person& rhs) { return rhs.name > x.name; };
	friend bool operator == (const person& x, const person& rhs) { return rhs.name == x.name; };

	string convert(const person& x) {
		string n = x.name;
		for (int i = 0; i < n.size(); i++)
			n.at(i) = toupper(n.at(i));

		return n + " " + x.no + " " + x.city + "\n";
	}

	friend ostream& operator << (ostream& stream, person& curr) {
		string n = curr.convert(curr);

		stream << n;
		return stream;
	};
};

template <class Comparable>
void insertionSort(vector <Comparable>& a)
{
	int j;

	for (int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];

		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{

	int child;
	Comparable tmp;

	for (tmp = a[i]; 2 * i + 1 < n; i = child)
	{
		child = 2 * i + 1;
		if (child != n - 1 && a[child] < a[child + 1])
			child++;
		if (a[child] > tmp)
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable>& a)
{
	for (int i = a.size() / 2; i >= 0; i--)
		percDown(a, i, a.size());

	for (int j = a.size() - 1; j > 0; j--)
	{
		swap(a[0], a[j]);
		percDown(a, 0, j);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

template <class Comparable>
void merge(vector<Comparable>& a,
	int leftPos, int rightEnd)
{
	int size = rightEnd - leftPos + 1;

	int j;
	for (int gap = size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < size; i++) {
			Comparable toCompare = a[i];

			for (j = i; j >= gap && toCompare < a[j - gap]; j -= gap)
				a[j] = a[j - gap];
			a[j] = toCompare;
		}
	}
}

template <class Comparable>
void mergeSort(vector<Comparable>& a, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, left, center);
		mergeSort(a, center + 1, right);
		merge(a, left, right);
	}
}

template <class Comparable>
void mergeSort(vector<Comparable>& a)
{
	mergeSort(a, 0, a.size() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////

template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
	for (int p = left + 1; p <= right; p++)
	{
		Comparable tmp = a[p];
		int j;

		for (j = p; j > left && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

template <class Comparable>
const Comparable& median3(vector<Comparable>& a,
	int left, int right)
{
	int center = (left + right) / 2;
	if (a[center] < a[left])
		swap(a[left], a[center]);
	if (a[right] < a[left])
		swap(a[left], a[right]);
	if (a[right] < a[center])
		swap(a[center], a[right]);

	swap(a[center], a[right - 1]);
	return a[right - 1];
}

template <class Comparable>
void quicksort(vector<Comparable>& a,
	int left, int right)
{
	if (left + 10 <= right)
	{
		Comparable pivot = median3(a, left, right);

		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i] < pivot) {}

			while (pivot < a[--j]) {}

			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}

		swap(a[i], a[right - 1]);

		quicksort(a, left, i - 1);
		quicksort(a, i + 1, right);
	}
	else
		insertionSort(a, left, right);
}

template <class Comparable>
void quicksort(vector<Comparable>& a)
{
	quicksort(a, 0, a.size() - 1);
}

///////////////////////////////////////////////////////////////////////////////////////////

#endif