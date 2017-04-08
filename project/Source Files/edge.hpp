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
	Edge(int id,int destN, double w);
	friend class Graph;
	friend class Node;
	bool operator==(const Edge& e) const;
	void setTransportLine(int transportLineId);
	int getDest() const;
	double getWeight() { return weight; }
	int getTransportLineId();
	Edge* copyEdge();

};

#endif /* EGDE_HPP_ */