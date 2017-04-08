#include "node.hpp"


/*
* ================================================================================================
* Class Node
* ================================================================================================
*/

bool Node::removeEdgeTo(Node *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge*>::iterator it = adj.begin();
	typename vector<Edge*>::iterator ite = adj.end();
	while (it != ite) {
		if ((*it)->destNode == d->info) {
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
	this->linesPath = {};
}



Edge* Node::addEdge(int id,int dest, double w) {
	Edge *edgeD = new Edge(id,dest, w);
	adj.push_back(edgeD);
	return edgeD;
}




int Node::getInfo() const {
	return this->info;
}


int Node::getDist() const {
	return this->dist;
}

void Node::setDist(int dist) {
	this->dist = dist;
}

bool Node::getProcessing() {
	return this->processing;
}

void Node::setProcessing(bool pro) {
	this->processing = pro;
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

vector<int> Node::getEdgesId()
{
	vector<int> idsToReturn;
	for (int i = 0; i < adj.size(); i++) {
		idsToReturn.push_back(adj.at(i)->id);
	}
	return idsToReturn;
}

vector<Edge*> Node::getAdj()
{
	return adj;
}


bool Node::operator==(const Node & b)
{
	return this->info == b.getInfo();
}

Node * Node::copy()
{
	Node* copyN = new Node(info, coords);
	return copyN;
}

