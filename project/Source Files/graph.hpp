/*
* Graph.hpp
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#pragma once

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "node.hpp"

using namespace std;


const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

typedef unordered_map<int, Node *> hashNodes;


/* ================================================================================================
* Class Graph
* ================================================================================================
*/

class Graph {
	hashNodes nodeSet;
	void dfs(Node *v, vector<int> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Node *v);
	void dfsVisit();
	//void getPathTo(Node *origin, list<int> &res);

public:
	bool addNode(const int &in, Point coords);
	bool addEdge(const int &sourc, const int &dest);
	bool removeNode(const int &in);
	bool removeEdge(const int &sourc, const int &dest);
	vector<int> dfs() const;
	vector<int> bfs(Node *v) const;
	int maxNewChildren(Node *v, int &inf) const;
	hashNodes getnodeSet() const;
	int getNumNode() const;

	//exercicio 5
	Node* getNode(const int &v) const;
	void resetIndegrees();
	vector<Node*> getSources() const;
	int getNumCycles();
	vector<int> topologicalOrder();
	vector<int> getPath(const int &origin, const int &dest);
	void unweightedShortestPath(const int &v);
	bool isDAG();
	//exercicio 6
	void bellmanFordShortestPath(const int &v);
	void dijkstraShortestPath(const int &s);
	vector<Node *> getCloseNodes(int max_dist, Node * n_source);
	vector<Edge *> getCloseEdges(const vector<Node*>& closeNodes, Node * n_source);
	void dijkstraShortestPath_distance(const int & s);
	void dijkstraLessTransportsUsed(const int &s);
};


#endif /* GRAPH_H_ */
