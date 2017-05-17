#pragma once

#include "graph.hpp"

typedef pair<int, Street*> APR;

struct APR_Greater_Than {
	bool operator()(APR a, APR b) const {
		return a.first < b.first;
	}
};

int distanceBetweenWords(string pattern, string text) {
	int n = text.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	int m = pattern.length();
	for (int i = 1; i <= m; i++)
	{
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++)
		{
			if (pattern[i - 1] == text[j - 1]) neww = old;
			else
			{
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

vector<Street *> aproximado(const hashTL &streets, const string &nameStreet) {
	hashTL::iterator minTL;
	int minValue = INT_MAX;
	APR current;
	vector<APR> heap;
	vector<Street *> topToReturn;
	for (hashTL::const_iterator it = streets.begin(); it != streets.end(); it++)
	{
		int actualValue = distanceBetweenWords(nameStreet, it->second->getName());
		current.first = actualValue;
		current.second = minTL->second;
		heap.push_back(current);
	}
	make_heap(heap.begin(), heap.end(), APR_Greater_Than());
	heap = vector<APR>(heap.begin(), heap.begin() + 9);
	for (vector<APR>::iterator it = heap.begin(); it != heap.end(); it++)
	{
		topToReturn.push_back(it->second);
	}
	return topToReturn;
}

hashTL exata(hashTL transportatingLines, string nameStreet) {
	for (hashTL::iterator it = transportatingLines.begin(); it != transportatingLines.end(); it++)
	{

	}
}

