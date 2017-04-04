#ifndef EDGE_HPP_
#define EDGE_HPP_

#pragma once
#include <unordered_set>
#include "TransportLine.hpp"

class Node;
class Graph;

/* ================================================================================================
* Class Edge
* ================================================================================================
*/


typedef std::unordered_set<TransportLine> linesSet;

class Edge {
	Node * dest;
	double weight;
	int id;
public:
	Edge(Node *d, double w);
	friend class Graph;
	friend class Node;
};

#endif /* EGDE_HPP_ */