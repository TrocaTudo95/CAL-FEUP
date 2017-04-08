
#ifndef NODE_HPP_
#define NODE_HPP_

#pragma once

#include <vector>
#include "edge.hpp"

using namespace std;

class Graph;
class Edge;

typedef struct {
	int x;
	int y;
}Point;

/*
* ================================================================================================
* Class Node
* ================================================================================================
*/
class Node {
	int info;
	Point coords;
	vector<Edge*> adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	unordered_set<string> linesPath;
	char wayToGetThere;

public:
	Node* path;
	friend class Graph;
	Node(int info, Point coords);
	vector<Edge*> getAdj();

	Edge* addEdge(int id, int dest, double w);
	bool removeEdgeTo(Node *d);

	int getInfo() const;
	void setInfo(int info);

	int getDist() const;
	void setDist(int dist);

	bool getProcessing();
	void setProcessing(bool pro);

	int getIndegree() const;

	void setCoords(Point coords);
	Point getCoords() const;

	vector<int> getEdgesId();

	bool operator==(const Node& b);
	Node* copy();

	char getWayTogetThere() { return wayToGetThere; };

};

struct Node_greater_than {
	bool operator()(Node * a, Node * b) const {
		return a->getDist() > b->getDist();
	}
};



#endif /* NODE_HPP_ */