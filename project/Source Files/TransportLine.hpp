#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "edge.hpp"

using namespace std;

class Graph;
class Node;
class Edge;

class TransportLine {
private:
	int id;
	string name;
	unordered_set<string>lines;
	char type;
	int initialEdgeId;
	int finalEdgeId;
	bool bidirectional;
	int avg_wait_time;
public:
	friend class Edge;
	TransportLine(int id,int initialEdgeID,int finalEdgeID, string name, string bidirectional,int avg_wait_time);
	bool operator==(const TransportLine& b) const;
	void addLines(string line);
	void setLines(unordered_set<string> &l);
	void setType(string type);
	void setType(char type);
	string toString() const;
	int getId()const;
	int getInitialEdgeId() const;
	int getFinalEdgeId() const;
	unordered_set<string>& getLines();
	char getType();
	int getWaitTime();
	bool isBidirectional();
	TransportLine* createReverseWalking(int id, int initialEdgeId, int finalEdgeId);
	TransportLine* createFullReverse(int id, int initialEdgeId,int finalEdgeId);
	vector<int> getNodesIds(unordered_map<int,pair<Edge*,int>> &edgeMap);
};

