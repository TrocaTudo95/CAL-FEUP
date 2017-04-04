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



class Edge {
	Node * dest;
	double weight;
	int id;
public:
	Edge(int id,Node *d, double w);
	friend class Graph;
	friend class Node;
	bool operator==(const Edge& e) const;

	
};

#endif /* EGDE_HPP_ */