#include "node.hpp"


/*
* ================================================================================================
* Class Node
* ================================================================================================
*/

bool Node::removeEdgeTo(Node *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge>::iterator it = adj.begin();
	typename vector<Edge>::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercício 5
Node::Node(int in) : info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}



void Node::addEdge(Node *dest, double w) {
	Edge edgeD(dest, w);
	adj.push_back(edgeD);
}



int Node::getInfo() const {
	return this->info;
}


int Node::getDist() const {
	return this->dist;
}



void Node::setInfo(int info) {
	this->info = info;
}


int Node::getIndegree() const {
	return this->indegree;
}