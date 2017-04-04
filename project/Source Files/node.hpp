
#ifndef NODE_HPP_
#define NODE_HPP_

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
	Point coords;
	vector<Edge> adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	bool processing;
	

public:
	Node* path;

	friend class Graph;
	Node(int info, Point coords);

	void addEdge(Node *dest, double w);
	bool removeEdgeTo(Node *d);

	int getInfo() const;
	void setInfo(int info);

	int getDist() const;
	int getIndegree() const;

	void setCoords(Point coords);
	Point getCoords() const;
};

struct Node_greater_than {
	bool operator()(Node * a, Node * b) const {
		return a->getDist() > b->getDist();
	}
};

bool operator==(const Node& a, const Node& b) {
	return a.getInfo() == b.getInfo();
}

#endif /* NODE_HPP_ */