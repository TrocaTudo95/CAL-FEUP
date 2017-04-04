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
Node::Node(int in, Point coords){
	this->info = in;
	this->coords = coords;
	this->visited = false;
	this->processing = false;
	this->indegree = 0;
	this->dist = 0;
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

void Node::setCoords(Point coords) {
	this->coords = coords;
}

Point Node::getCoords() const {
	return this->coords;
}

