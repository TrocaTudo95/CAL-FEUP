#pragma once
#include <vector>
#include "edge.hpp"

using namespace std;

class Graph;


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
	vector<Edge> adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	Point coords;
	

public:

	Node(int info);
	friend class Graph;

	void addEdge(Node *dest, double w);
	bool removeEdgeTo(Node *d);

	int getInfo() const;
	void setInfo(int info);

	int getDist() const;
	int getIndegree() const;
	Point getCoords()const { return coords; };

	Node* path;
};

struct Node_greater_than {
	bool operator()(Node * a, Node * b) const {
		return a->getDist() > b->getDist();
	}
};