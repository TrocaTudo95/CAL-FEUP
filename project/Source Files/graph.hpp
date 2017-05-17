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
#include <float.h>
#include "node.hpp"
#include "Street.hpp"


using namespace std;

const double SEARCH_RADIUS = 8.25;
const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;
const double DOUBLE_INFINITY = DBL_MAX;
const double WALK_SPEED = 0.8;
const double BUS_SPEED = 10.0;
const double METRO_SPEED = 20.0;


const double FAV_TRANSPORT_MULTIPLIER = 0.01;




class Node;
class Edge;
class Street;

typedef unordered_map<int, Node *> hashNodes;
typedef unordered_map<int, pair<Edge *,int>> hashEdges; //idEdge, pair<Edge*,idNoOrigem>
typedef unordered_map<int, Street *> hashTL;
typedef vector<pair<int, int>> vii; typedef vector<vii> vvii;
typedef vector<int> vi;


typedef struct {
	int path;
	double dist;
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
	//exercicio 5
	int numCycles;
	int highestEdgeId;
	int highestTransportLineId;
	
	vvii adjList; //stores vector<vector<pair<int,int>>> , For each node, stores a vector of <destNodeId,weight>
	vi dist;
	vi in_queue;
	vi path;

	double METER_PER_PIXEL_X;
	double METER_PER_PIXEL_Y;



public:
	/**
	* @brief Creates a Graph initializing highestEdgeId and highestTransportLineId to 0.
	*/
	Graph();
	/**
	* @brief Graph's destructor to free memory alocated by a graph
	*/
	~Graph();
	/**
	* @brief intitalizes METER_PER_PIXEL_X that defines the number of meters which a pixel corresponds to
	* @param d value to initialize METER_PER_PIXEL_X
	*/
	void setMETER_PER_PIXEL_X(double d);
	/**
	* @brief intitalizes METER_PER_PIXEL_Y that defines the number of meters which a pixel corresponds to
	* @param d value to initialize METER_PER_PIXEL_Y
	*/
	void setMETER_PER_PIXEL_Y(double d);
	/**
	* @brief creates a copy of the variable nodeMap and returns a pointer to it
	* @return a pointer to a copy of the nodeMap Graph's variable
	*/
	hashNodes* copyNodes();
	/**
	* @brief introduces the edges passed by the adjacencies on originalNodes in the graph
	* @param originalNodes unordered_map containing the Nodes from which the edges will be added to the graph
	*/
	void copyEdges(hashNodes originalNodes);
	/**
	* @brief initializes nodeMap with map
	* @param map hashNodes containing the Nodes to set
	*/
	void setNodeMap(hashNodes *map);
	/**
	* @brief initializes edgeMap with map
	* @param map hashNodes containing the Edges to set
	*/
	void setEdgeMap(hashEdges map);
	/**
	* @brief initializes highestEdgeId that represents the highest Edge id
	* @param id highest Edge id
	*/
	void setHighestEdgeId(int id);
	/**
	* @brief initializes transportationLines with the unorded set passed by argument
	* @param tlMap unorded set with the transportations lines
	*/
	void setTransportationLines(const hashTL &tlMap);

	//TODO: complete

	/**
	* @brief 
	* @return 
	*/
	hashTL getStreets();
	/**
	* @brief creates a new Node and inserts it in the nodeMap
	* @param in Node's id
	* @param coords struct containing x and y to create the Node
	* @return false if node already exists
	*/
	bool addNode(const int &in, Point coords);
	void addTransportationLine(Street *t1);
	void setReverseTransportationLines();
	/**
	* @brief creates a new Edge with the id specified between the source Node and the destiny Node calculating the weight for the Edge
	* @param id Edge's id
	* @param sourc source Node's id
	* @param dest destiny Node's id
	* @param w Edge's weight
	* @return false if the destiny or the source Node is the last one
	*/
	bool addEdge(int id,const int &sourc, const int &dest, double w=0);
	/**
	* @brief removes the node specified by its id
	* @param in Node's id to remove
	* @return false if the Node does not exist
	*/
	bool removeNode(const int &in);
	/**
	* @brief removes the Edge that links the nodes passed by argument through theirs id's
	* @param sourc source Node's id
	* @param dest destiny Node's id
	* @return false if the Edge does not exist
	*/
	bool removeEdge(const int &sourc, const int &dest);
	/**
	* @brief function to return the nodeMap
	* @return nodeMap
	*/
	hashNodes getNodeMap() const;
	/**
	* @brief returns a Edge pointer of the graph specified by its id
	* @param id Edge's id
	* @return Edge pointer to the pretended Edge
	*/
	Edge* getEdgeById(int id);
	/**
	* @brief returns a Node pointer of the graph specified by its id
	* @param id Node's id
	* @return Edge pointer to the pretended Node
	*/
	Node* getNode(const int &v) const;
	/**
	* @brief returns a Street pointer of the transportationLines unorded set specified by its id
	* @param id Street's id
	* @return Street pointer to the pretended transportationLine
	*/
	Street* getTransportLine(const int &id) const;
	/**
	* @brief returns the shortest path between the Node origin and the Node destiny through a vector of PathTo
	* @param origin source Node's id
	* @param dest destiny Node's id
	* @return vector of PathTo which is a struct containing Node's path, dist and wayToGetThere
	*/
	vector<PathTo> getPath(const int &origin, const int &dest);
	/**
	* @brief returns the shortest path between the Node origin and the Node destiny through a vector of Node pointers
	* @param origin source Node's id
	* @param dest destiny Node's id
	* @return vector of Node pointers which refers to the Nodes that the shortest path go through
	*/
	vector<Node *> getNodePath(const int &origin, const int &dest);
	/**
	* @brief returns the shortest path between the Node origin and the Node destiny through a vector of Node's ids
	* @param origin source Node's id
	* @param dest destiny Node's id
	* @return vector of Node's ids which refers to the Nodes that the shortest path go through
	*/
	vector<int> getPathForSPFA(const int &origin, const int &dest);
	/**
	* @brief calculates and returns a vector of the close Nodes, which is defined by the max_dist
	* @param n_source source Node
	* @param max_dist defines the range in meters to include the Nodes
	* @return vector of near Node's ids 
	*/
	vector<int> getCloseNodes(int max_dist, Node * n_source);
	/**
	* @brief calculates and returns a vector of the close Edges by reciving a node and a vector of Nodes and creates edges to all of them to allow go on foot
	* @param origin source Node's id
	* @param dest destiny Node's id
	* @return vector of near Node's ids
	*/
	vector<Edge *> getCloseEdges(const vector<int>& closeNodes, Node * n_source);
	vii getCloseEdgesSPFA(vector<int> &closeNodes, Node *src);
	/**
	* @brief check through the path calculated by the function getNodePath and calculates the percentage of walk distance/time
	* @param origin source Node's id
	* @param dest destiny Node's id
	* @float percentage defines the max_percentage of the way that the person can go on foot
	* @return true if the percentage calculated is greater than the percentage passed by argument 
	*/
	bool checkWalkPercentage(const int &origin, const int &dest, float percentage);
	void SPFAWithAdjacencyList(const int &s,const int &d);
	/**
	* @brief processes the graph updating all the nodes with the shortest distance from the Node source in meters using the METER_PER_PIXEL
	* @param s Node's source id
	*/
	void dijkstraShortestDistance(const int & s);
	/**
	* @brief processes the graph updating all the nodes with the shortest distance from the Node source optimized by an elipse, this way only some nodes are processed
	* @param s Node's source id
	* @param d Node's destiny id
	*/
	void dijkstraShortestDistance(const int & s, const int & d);
	/**
	* @brief processes the graph updating all the nodes with the shortest time from the Node source, where the time is calculated used constant speeds for the diferents transports
	* @param s Node's source id
	*/
	void dijkstraBestTime(const int & s);
	/**
	* @brief processes the graph updating all the nodes with the shortest time from the Node source, where the time is calculated used constant speeds 
	for the diferents transports and each Street has also a waiting time and a if the max_cost is bigger than 0 the cost is also calculated and if the cost exceeds the max_cost value it forces to go on foot
	* @param s Node's source id
	*/
	void dijkstraBestTimeWithWaitingTime(const int &s, const double & max_cost);
	/**
	* @brief processes the graph updating all the nodes with the shortest time from the Node source, where the time is calculated used constant speeds for the diferents transports
	* @param s Node's source id
	*/
	void dijkstraBestTimeWithFavoriteTransport(const int & s, char favorite);
	void dijkstraBestTimeWithFavoriteTransportAndWaitingTime(const int &s, char favorite);
	void dijkstraBestTimeWithWaitingTimeCostandFavoriteTransport(const int &s, const double &max_cost, char favorite);
	/**
	* @brief processes the graph updating all the nodes with the shortest number of transports used from the Node source
	* @param s Node's source id
	*/
	void dijkstraLessTransportsUsed(const int &s);
	/**
	* @brief add a vector of edges to another one if the edges dont exist yet, this is used to add the walking edges that are created
	* @param edges vector which has to be updated 
	* @param onFoot vector of edges to add
	*/
	void addEdgesFoot(vector<Edge*> & edges, vector<Edge *> & onFoot);
	void addEdgesFootSPFA(vii & edges,vii & onFoot);
	/**
	* @brief checks if a edge exists or not in a vector of edges
	* @param edges vector of edges
	* @param e edge to test
	* @return true if the edge already exists on the vector
	*/
	bool alreadyExists(vector<Edge*> & edges, Edge * e);
	bool alreadyExistsSPFA(vii & edges, int e);
	bool isChangingTransport(unordered_set<string> &edgeLines, unordered_set<string> vPathLines);
	/**
	* @brief calculates the cost in euros to do a distance in a specified transport
	* @param distance distance on meters
	* @param transportation char to specify the way of transport
	* @return cost in euros
	*/
	double calculateCost(double distance, char transportation);
	

	void preprocessGraphForWaitingTimes();
	void preprocessGraphForSPFA();
	/**
	* @brief function that makes a copy of the current Graph and returns a pointer to it
	* @return A pointer to an Graph with same  nodeMap, edgeMap and transportationLines
	*/
	Graph * copy();

};


#endif /* GRAPH_H_ */
