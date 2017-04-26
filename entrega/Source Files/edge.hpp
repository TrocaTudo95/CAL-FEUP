#ifndef EDGE_HPP_
#define EDGE_HPP_

#pragma once
#include <unordered_set>

class Node;
class Graph;
class TransportLine;

/* ================================================================================================
* Class Edge
* ================================================================================================
*/


class Edge {
	int destNode;
	double weight;
	int id;
	int transportLineId;
public:
	/**
	* @brief Creates an Edge with id, destination node and weight;
	* @param id Edge id
	* @param destN This Edge Destination Node
	* @param w Edge weight, should be set as the distance between Source and Destination Nodes.
	*/
	Edge(int id,int destN, double w);
	friend class Graph;
	friend class Node;
	/**
	* @brief Comparates two edges by theirs destination nodes.
	* @param e Edge to comparate with.
	* @return true if the two edges have the same destination node.
	*/
	bool operator==(const Edge& e) const;
	/**
	* @brief sets the attribute transportLineId.
	* @param transportLineId TransportLine id.
	*/
	void setTransportLine(int transportLineId);
	/**
	* @brief function to return the destination node id. 
	* @return the destination node id .
	*/
	int getDest() const;
	/**
	* @brief function to return the Edge weight
	* @return the Edge weight, as distance.
	*/
	double getWeight() { return weight; }
	/**
	* @brief function to return the Tranportation Line id
	* @return the Tranportation Line id
	*/
	int getTransportLineId();
	/**
	* @brief function that makes a copy of the current Edge and returns it
	* @return A pointer to an Edge with same Id, Destination Node, weight and transportation line id;
	*/
	Edge* copyEdge();
};

#endif /* EGDE_HPP_ */