#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class Graph;
class Node;
class Edge;

class TransportLine {
private:
	string name;
	unordered_set<string>lines;
	char type;
	int initialEdgeId;
	int finalEdgeId;
	bool bidirectional;
	int avg_wait_time;
	unordered_map<int, pair<int, int>> edgeMap;
public:
	friend class Edge;
	TransportLine(int initialEdgeID,int finalEdgeID, string name, string bidirectional,int avg_wait_time);
	void setEdgeMap(unordered_map<int, pair<int, int>> &edgesOD);
	bool operator==(const TransportLine& b) const;
	void addLines(string line);
	void setType(string type);
	void setType(char type);
	string toString() const;
	int getInitialEdgeId() const;
	int getFinalEdgeId() const;
	unordered_set<string>& getLines();
	char getType();
	int getWaitTime();
	bool isBidirectional();
	TransportLine* createReverse();
	unordered_set<int> TransportLine::getNodesIds();
	TransportLine* copy();
};

