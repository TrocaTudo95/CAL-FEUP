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
	Node* src;
	Node* dest;
	double weight;
	int id;
	TransportLine *line;
public:
	Edge(int id,Node* s,Node *d, double w);
	friend class Graph;
	friend class Node;
	bool operator==(const Edge& e) const;
	void setTransportLine(TransportLine *tl);
	TransportLine getTransportLine() { return (*line); };
	Node * getDest() const;
};

#endif /* EGDE_HPP_ */