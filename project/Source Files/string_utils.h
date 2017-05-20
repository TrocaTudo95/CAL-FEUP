#pragma once

#include "graph.hpp"

typedef pair<int, Street*> APR;

struct APR_Greater_Than {
	bool operator()(APR a, APR b) const {
		return a.first > b.first;
	}
};
void eliminateRedudantWords(vector<string> &text);
int aproximate_matching(string pattern,string text);
vector<Street *> aproximado(const StreetCleaned &streets, const string &nameStreet);
int editDistance(string pattern, string text);
vector<Street*> exata(const StreetCleaned &streets, const string &nameStreet);
