
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
	int dist;
	double cost;
	unordered_set<string> linesPath;
	char wayToGetThere;

public:
	Node* path;
	friend class Graph;
	/**
	* @brief constructor of class Node
	* @param info Node's id
	* @param coords represents the x and y, that will be used to calculate distances between nodes.
	*/
	Node(int info, Point coords);


	vector<Edge*> getAdj();
	/**
	* @brief function to return the Tranportation Line id
	* @return returns the Tranportation Line id
	*/
	Edge* addEdge(int id, int dest, double w);
	/**
	* @brief remove the Edge specified by the Node pointer d (destiny node of the Edge) from the adj vector
	* @param d Node pointer to specify the Edge destiny to remove
	* @return true if successfully removes the Edge and false otherwise
	*/
	bool removeEdgeTo(Node *d);
	/**
	* @brief function to return Node id
	* @return Node id
	*/
	int getInfo() const;
	/**
	* @brief function to set Node id
	* @param info Node id
	*/
	void setInfo(int info);
	/**
	* @brief function to return the Node dist
	* @return Node dist
	*/
	int getDist() const;
	/**
	* @brief function to set Node id
	* @param dist Node distance to the first Node
	*/
	void setDist(int dist);
	/**
	* @brief function to return the boolean processing that indicates if the Node is being processed in the heap.
	* @return True if it is being processed, False otherwise;
	*/
	bool getProcessing();
	/**
	* @brief function to set the boolean processing that indicates if the Node is being processed
	* @param pro processing value
	*/
	void setProcessing(bool pro);
	/**
	* @brief function to set the Node cordinates through a struct named Point containing the x and y
	* @param coords struct containing Node's x and y
	*/
	void setCoords(Point coords);
	/**
	* @brief function to return Node cordinates through a struct named Point containing the x and y
	* @return struct containing Node's x and y
	*/
	Point getCoords() const;
	/**
	* @brief function to return a vector of ints containing the adjacent Edges' Ids
	* @return vector of ints containing the adjacent Edges' Ids
	*/
	vector<int> getEdgesId();
	/**
	* @brief comparates two edges by theirs ids
	* @param b Node to comparate with
	* @return True if the two id's are equal, false otherwise
	*/
	bool operator==(const Node& b);
	/**
	* @brief function that makes a copy of the current Node and returns it
	* @return A pointer to a node with same Id and Coordinates;
	*/
	Node* copy();
	/**
	* @brief function to return WayTogetThere that represents after the graph is processed the transportation taken to get to the Node
	* @return wayToGetThere
	*/
	char getWayTogetThere() { return wayToGetThere; };

};

struct Node_greater_than {
	bool operator()(Node * a, Node * b) const {
		return a->getDist() > b->getDist();
	}
};



#endif /* NODE_HPP_ */