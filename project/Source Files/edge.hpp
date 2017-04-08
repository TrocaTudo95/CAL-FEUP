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
	* @brief constructor of class Edge
	* @param id Edge id
	* @param destN destiny Node
	* @param w Edge weight
	*/
	Edge(int id,int destN, double w);
	friend class Graph;
	friend class Node;
	/**
	* @brief comparates two edges by theirs destiny nodes
	* @param e Edge to comparate with
	* @return returns true if the two edges are equal, false otherwise
	*/
	bool operator==(const Edge& e) const;
	/**
	* @brief sets the attribute transportLineId
	* @brief transportLineId TransportLine id
	*/
	void setTransportLine(int transportLineId);
	/**
	* @brief function to return the destiny node id 
	* @return returns the destiny node id 
	*/
	int getDest() const;
	/**
	* @brief function to return the Edge weight
	* @return returns the Edge weight
	*/
	double getWeight() { return weight; }
	/**
	* @brief function to return the Tranportation Line id
	* @return returns the Tranportation Line id
	*/
	int getTransportLineId();
	/**
	* @brief function that makes a copy of the current Edge and returns it
	* @return returns the Edge copy that was created
	*/
	Edge* copyEdge();
};

#endif /* EGDE_HPP_ */