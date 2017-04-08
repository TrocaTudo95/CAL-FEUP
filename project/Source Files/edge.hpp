#ifndef EDGE_HPP_
#define EDGE_HPP_

#pragma once
#include <unordered_set>
#include "TransportLine.hpp"

class Node;
class Graph;
class TransportLine;

/* ================================================================================================
* Class Edge
* ================================================================================================
*/


class Edge {
	Node* dest;
	double weight;
	double money_cost;
	int id;
	TransportLine *line;
public:
	Edge(int id,Node *d, double w);
	friend class Graph;
	friend class Node;
	bool operator==(const Edge& e) const;
	void setTransportLine(TransportLine *tl);
	Node * getDest() { return dest; }
	double getWeight() { return weight; }
	double getMoneyCost() { return money_cost; };
	TransportLine* getTransportLine();
	Node * getDest() const;
	Edge* copyEdge();
};

#endif /* EGDE_HPP_ */