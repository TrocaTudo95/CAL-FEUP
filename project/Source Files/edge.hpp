#ifndef EDGE_HPP_
#define EDGE_HPP_

#pragma once

class Node;
class Graph;

/* ================================================================================================
* Class Edge
* ================================================================================================
*/

class Edge {
	Node * dest;
	double weight;
public:
	Edge(Node *d, double w);
	friend class Graph;
	friend class Node;
};

#endif /* EGDE_HPP_ */