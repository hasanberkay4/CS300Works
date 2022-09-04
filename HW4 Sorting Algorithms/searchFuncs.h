#ifndef _SEARCHFUNCS_H
#define _SEARCHFUNCS_H

#include <iostream>
#include <string>
#include <vector>
#include "sortFuncs.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////

template <class Comparable>
int fullLSearch(vector<Comparable>& sorted, string query) {
	person p(query);
	for (int i = 0; i < sorted.size(); i++)
		if (sorted[i] == p)
			return i;
	return -1;
}

template <class Comparable>
int fullBSearch(vector<Comparable>& sorted, string query, int l, int r) {
	person p(query);

	if (r >= l) {
		int mid = (l + r) / 2;

		if (sorted[mid] == p)
			return mid;

		if (sorted[mid] > p)
			return fullBSearch(sorted, query, l, mid - 1);

		return fullBSearch(sorted, query, mid + 1, r);
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////

vector<person> partialLSearch(vector<person>& sorted, string query) {
	person p(query);
	vector<person> result;

	int subLen = query.length();
	for (int i = 0; i < sorted.size(); i++)
		if (sorted[i].name.substr(0, subLen) == p) {
			result.push_back(sorted[i]);
			while (++i <= sorted.size() - 1 && sorted[i].name.substr(0, subLen) == p)
				result.push_back(sorted[i]);

			return result;
		}

	return result;
}

vector<person> partialBSearch(vector<person>& sorted, string query, int l, int r) {
	person p(query);
	static vector<person> result;

	int subLen = query.length();

	if (r >= l) {
		int mid = (l + r) / 2;

		if (sorted[mid].name.substr(0, subLen) == p) {
			result.push_back(sorted[mid]);

			int templ = mid;
			int tempr = mid;

			while (--templ >= 0 && sorted[templ].name.substr(0, subLen) == p)
				result.push_back(sorted[templ]);

			while (++tempr <= sorted.size() - 1 && sorted[tempr].name.substr(0, subLen) == p)
				result.push_back(sorted[tempr]);

			return result;
		}

		if (sorted[mid] > query)
			partialBSearch(sorted, query, l, mid - 1);

		partialBSearch(sorted, query, mid + 1, r);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////

#endif