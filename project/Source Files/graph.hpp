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
#include <thread>
#include <atomic>
#include <condition_variable>
#include <unordered_map>
#include <cassert>
#include "node.hpp"
#include "TransportLine.hpp"


using namespace std;

const double SEARCH_RADIUS = 8.25;
const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;
const int WALK_SPEED = 1;
const int BUS_SPEED = 10;
const int METRO_SPEED = 20;
const int PIXEL_TO_METER = 8;
const double FAV_TRANSPORT_MULTIPLIER = 0.01;



class Node;
class Edge;
class TransportLine;

typedef unordered_map<int, Node *> hashNodes;
typedef unordered_map<int, pair<Edge *,int>> hashEdges; //idEdge, pair<Edge*,idNoOrigem>
typedef unordered_map<int, TransportLine *> hashTL;
typedef vector<pair<int, int>> vii; typedef vector<vii> vvii;
typedef vector<int> vi;


typedef struct {
	int path;
	int dist;
	char wayToGetThere;
} PathTo;



/* ================================================================================================
* Class Graph
* ================================================================================================
*/

class Graph {
private:
	hashNodes nodeMap;
	hashEdges edgeMap;
	hashTL transportationLines;
	void dfs(Node *v, vector<int> &res) const;
	//exercicio 5
	int numCycles;
	void dfsVisit(Node *v);
	void dfsVisit();
	int highestEdgeId;
	int highestTransportLineId;
	
	vvii adjList; //stores vector<vector<pair<int,int>>> , For each node, stores a vector of <destNodeId,weight>
	vi dist;


public:
	Graph();
	~Graph();

	hashNodes* copyNodes();
	void copyEdges(hashNodes originalNodes);

	void setNodeMap(hashNodes *map);
	void setEdgeMap(hashEdges map);
	void setHighestEdgeId(int id);
	void setTransportationLines(const hashTL &tlMap);
	bool addNode(const int &in, Point coords);
	void addTransportationLine(TransportLine *t1);
	void setReverseTransportationLines();
	bool addEdge(int id,const int &sourc, const int &dest, int w=0);
	bool removeNode(const int &in);
	bool removeEdge(const int &sourc, const int &dest);
	
	hashNodes getNodeMap() const;
	Edge* getEdgeById(int id);
	Node* getNode(const int &v) const;
	TransportLine* getTransportLine(const int &id) const;
	vector<Node*> getSources() const;
	vector<PathTo> getPath(const int &origin, const int &dest);
	vector<Node *> getNodePath(const int &origin, const int &dest);
	vector<int> getCloseNodes(int max_dist, Node * n_source);
	vector<Edge *> getCloseEdges(const vector<int>& closeNodes, Node * n_source);

	void unweightedShortestPath(const int &v);

	void bellmanFordShortestPath(const int &v);

	bool checkWalkPercentage(const int &origin, const int &dest, float percentage);

	void SPFAWithAdjacencyList(const int &s);
	void dijkstraShortestDistance(const int & s);
	void dijkstraShortestDistance(const int & s, const int & d);
	void dijkstraBestTime(const int & s);
	void dijkstraBestTimeWithWaitingTime(const int &s);
	void dijkstraBestTimeWithFavoriteTransport(const int & s, char favorite);
	void dijkstraBestTimeWithFavoriteTransportAndWaitingTime(const int &s, char favorite);

	void addEdgesFoot(vector<Edge*> & edges, vector<Edge *> & onFoot);
	bool alreadyExists(vector<Edge*> & edges, Edge * e);
	bool isChangingTransport(unordered_set<string> &edgeLines, unordered_set<string> vPathLines);
	

	void preprocessGraphForWaitingTimes();
	void preprocessGraphForSPFA();
	Graph * copy();

};


#endif /* GRAPH_H_ */
