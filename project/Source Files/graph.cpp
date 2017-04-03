#include "graph.hpp"



/* ================================================================================================
* Class Graph
* ================================================================================================
*/



int Graph::getNumNode() const {
	return NodeSet.size();
}

vector<Node * > Graph::getNodeSet() const {
	return NodeSet;
}


int Graph::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}


bool Graph::isDAG() {
	return (getNumCycles() == 0);
}



bool Graph::addNode(const int &in) {
	typename vector<Node*>::iterator it = NodeSet.begin();
	typename vector<Node*>::iterator ite = NodeSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in) return false;
	Node *v1 = new Node(in);
	NodeSet.push_back(v1);
	return true;
}


bool Graph::removeNode(const int &in) {
	typename vector<Node*>::iterator it = NodeSet.begin();
	typename vector<Node*>::iterator ite = NodeSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Node * v = *it;
			NodeSet.erase(it);
			typename vector<Node*>::iterator it1 = NodeSet.begin();
			typename vector<Node*>::iterator it1e = NodeSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge >::iterator itAdj = v->adj.begin();
			typename vector<Edge >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}


bool Graph::addEdge(const int &sourc, const int &dest, double w) {
	typename vector<Node*>::iterator it = NodeSet.begin();
	typename vector<Node*>::iterator ite = NodeSet.end();
	int found = 0;
	Node *vS = nullptr, *vD = nullptr;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (found != 2) return false;
	vD->indegree++;
	vS->addEdge(vD, w);

	return true;
}


bool Graph::removeEdge(const int &sourc, const int &dest) {
	typename vector<Node*>::iterator it = NodeSet.begin();
	typename vector<Node*>::iterator ite = NodeSet.end();
	int found = 0;
	Node *vS = nullptr, *vD = nullptr;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	return vS->removeEdgeTo(vD);
}





vector<int> Graph::dfs() const {
	typename vector<Node*>::const_iterator it = NodeSet.begin();
	typename vector<Node*>::const_iterator ite = NodeSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<int> res;
	it = NodeSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}


void Graph::dfs(Node *v, vector<int> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge >::iterator it = (v->adj).begin();
	typename vector<Edge >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			dfs(it->dest, res);
		}
}


vector<int> Graph::bfs(Node *v) const {
	vector<int> res;
	queue<Node *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Node *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge >::iterator it = v1->adj.begin();
		typename vector<Edge >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Node *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}


int Graph::maxNewChildren(Node *v, int &inf) const {
	vector<int> res;
	queue<Node *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Node *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop(); l++;
		int nChildren = 0;
		typename vector<Edge >::iterator it = v1->adj.begin();
		typename vector<Edge >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Node *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}



Node* Graph::getNode(const int &v) const {
	for (unsigned int i = 0; i < NodeSet.size(); i++)
		if (NodeSet[i]->info == v) return NodeSet[i];
	return NULL;
}


void Graph::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < NodeSet.size(); i++) NodeSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < NodeSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < NodeSet[i]->adj.size(); j++) {
			NodeSet[i]->adj[j].dest->indegree++;
		}
	}
}



vector<Node*> Graph::getSources() const {
	vector< Node* > buffer;
	for (unsigned int i = 0; i < NodeSet.size(); i++) {
		if (NodeSet[i]->indegree == 0) buffer.push_back(NodeSet[i]);
	}
	return buffer;
}



void Graph::dfsVisit() {
	typename vector<Node*>::const_iterator it = NodeSet.begin();
	typename vector<Node*>::const_iterator ite = NodeSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = NodeSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}


void Graph::dfsVisit(Node *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge >::iterator it = (v->adj).begin();
	typename vector<Edge >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true) numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}


vector<int> Graph::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<int> res;

	//verificar se � um DAG
	if (getNumCycles() > 0) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Node*> q;

	vector<Node*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!q.empty()) {
		Node* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if (v->adj[i].dest->indegree == 0) q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != NodeSet.size()) {
		while (!res.empty()) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}




vector<int> Graph::getPath(const int &origin, const int &dest) {

	list<int> buffer;
	Node* v = getNode(dest);

	//cout << v->info << " ";
	buffer.push_front(v->info);
	while (v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if (v->path != NULL)
		buffer.push_front(v->path->info);


	vector<int> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}



void Graph::unweightedShortestPath(const int &s) {

	for (unsigned int i = 0; i < NodeSet.size(); i++) {
		NodeSet[i]->path = NULL;
		NodeSet[i]->dist = INT_INFINITY;
	}

	Node* v = getNode(s);
	v->dist = 0;
	queue< Node* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Node* w = v->adj[i].dest;
			if (w->dist > v->dist + 1) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}



void Graph::bellmanFordShortestPath(const int & s)
{
	for (unsigned int i = 0; i < NodeSet.size(); i++) {
		NodeSet[i]->path = NULL;
		NodeSet[i]->dist = INT_INFINITY;
	}

	Node* v = getNode(s);
	v->dist = 0;
	queue< Node* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Node* w = v->adj[i].dest;
			if (w->dist > v->dist + v->adj[i].weight) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}


void Graph::dijkstraShortestPath(const int & s)
{
	for (unsigned int i = 0; i < NodeSet.size(); i++) {
		NodeSet[i]->path = NULL;
		NodeSet[i]->dist = INT_INFINITY;
	}
	Node* v = getNode(s);
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Node* w = v->adj[i].dest;
			if (w->dist > v->dist + v->adj[i].weight) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				pq.push_back(w);
				push_heap(pq.begin(), pq.end(), Node_greater_than());
			}
		}
	}
}