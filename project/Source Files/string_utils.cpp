/*
* matcher.cpp
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include "string_utils.h"
using namespace std;

vector<string> splitSentence(string sentence) {
	istringstream iss(sentence);
	vector<string> tokens{ istream_iterator<string>{iss},
		istream_iterator<string>{} };

	if (tokens.size() == 0) {
		tokens.push_back("");
	}
	return tokens;
}

int aproximate_matching(string pattern, string text) {
	vector<string> textSplitted = splitSentence(text);
	vector<string> patternSplitted = splitSentence(pattern);
	int totalEditDistance = 0;
	int currentMinDistance;
	int currentEditDistance;
	for (vector<string>::iterator itP = patternSplitted.begin(); itP != patternSplitted.end(); itP++) {
		currentMinDistance = 9999;
		for (vector<string>::iterator itT = textSplitted.begin(); itT != textSplitted.end(); itT++) {
			currentEditDistance = editDistance(*itP, *itT);
			if (currentEditDistance == 0) {
				currentMinDistance = 0;
				break;
			}
			if (currentEditDistance < currentMinDistance) {
				currentMinDistance = currentEditDistance;
			}
		}
		totalEditDistance += currentMinDistance;
	}
	if (textSplitted.size() > patternSplitted.size()) {
		totalEditDistance += (textSplitted.size() - patternSplitted.size());
	}
	return totalEditDistance;
}
void pre_kmp(string pattern, vector<int> & prefix) {
	int m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++)
	{
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q]) k = k + 1;
		prefix[q] = k;
	}
}

int kmp(string text, string pattern) {
	int num = 0;
	int m = pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n = text.length();

	int q = -1;
	for (int i = 0; i < n; i++)
	{
		while (q > -1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i])
			q++;
		if (q == m - 1)
		{
			cout << "pattern occurs with shift" << i - m + 1 << endl;
			num++;
			q = prefix[q];
		}
	}
	return num;
}


int numStringMatching(string filename, string toSearch) {
	ifstream fich(filename.c_str());
	if (!fich)
	{
		cout << "Erro a abrir ficheiro de leitura\n"; return 0;
	}

	string line1;
	int num = 0;

	while (!fich.eof())
	{
		getline(fich, line1);
		num += kmp(line1, toSearch);
	}
	fich.close();
	return num;
}


int editDistance(string pattern, string text) {
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

float numApproximateStringMatching(string filename, string toSearch) {
	ifstream fich(filename.c_str());
	if (!fich)
	{
		cout << "Erro a abrir ficheiro de leitura\n"; return 0;
	}

	string line1, word1;
	int num = 0, nwords = 0;

	while (!fich.eof())
	{
		getline(fich, line1);
		stringstream s1(line1);
		while (!s1.eof())
		{
			s1 >> word1;
			num += editDistance(toSearch, word1);
			nwords++;
		}
	}
	fich.close();
	float res = (float)num / nwords;
	return res;
}



vector<Street *> aproximado(const StreetCleaned &streets, const string &nameStreet) {
	int minValue = INT_MAX;
	APR current;
	vector<APR> heap;
	vector<Street *> topToReturn;
	for (StreetCleaned::const_iterator it = streets.begin(); it != streets.end(); it++)
	{
		string temp = (*it)->getName();
		int actualValue = aproximate_matching(nameStreet, (*it)->getName());

		current.first = actualValue;
		current.second = (*it);
		heap.push_back(current);
	}
	make_heap(heap.begin(), heap.end(), APR_Greater_Than());
	heap = vector<APR>(heap.begin(), heap.begin() + 10);
	for (vector<APR>::iterator it = heap.begin(); it != heap.end(); it++)
	{
		topToReturn.push_back(it->second);
	}
	return topToReturn;
}
/*
hashTL exata(hashTL transportatingLines, string nameStreet) {
	for (hashTL::iterator it = transportatingLines.begin(); it != transportatingLines.end(); it++)
	{

	}
}
*/





