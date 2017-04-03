/*
* Graph.hpp
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <algorithm>
using namespace std;

class Edge;
class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

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
public:

	Node(int info);
	friend class Graph;

	void addEdge(Node *dest, double w);
	bool removeEdgeTo(Node *d);

	int getInfo() const;
	void setInfo(int info);

	int getDist() const;
	int getIndegree() const;

	Node* path;
};

struct Node_greater_than {
	bool operator()(Node * a, Node * b) const {
		return a->getDist() > b->getDist();
	}
};



/* ================================================================================================
* Class Edge
* ================================================================================================
*/

class Edge {
	Node * dest;
	double weight;
public:
	Edge(Node *d, double w);
	friend class Graph;
	friend class Node;
};


/* ================================================================================================
* Class Graph
* ================================================================================================
*/

class Graph {
	vector<Node *> NodeSet;
	void dfs(Node *v, vector<int> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Node *v);
	void dfsVisit();
	//void getPathTo(Node *origin, list<int> &res);

public:
	bool addNode(const int &in);
	bool addEdge(const int &sourc, const int &dest, double w);
	bool removeNode(const int &in);
	bool removeEdge(const int &sourc, const int &dest);
	vector<int> dfs() const;
	vector<int> bfs(Node *v) const;
	int maxNewChildren(Node *v, int &inf) const;
	vector<Node * > getNodeSet() const;
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
};





#endif /* GRAPH_H_ */
