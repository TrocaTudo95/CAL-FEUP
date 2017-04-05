#include "graph.hpp"



/* ================================================================================================
* Class Graph
* ================================================================================================
*/


int Graph::getNumNode() const {
	return nodeMap.size();
}

Edge * Graph::getEdgeById(int id)
{
	typename hashEdges::const_iterator it = edgeMap.find(id);
	if (it == edgeMap.end())
		return NULL;
	return it->second;
}


hashNodes Graph::getNodeMap() const {
	return nodeMap;
}


int Graph::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}


bool Graph::isDAG() {
	return (getNumCycles() == 0);
}



Graph::Graph()
{
	highestEdgeId = 0;
}

bool Graph::addNode(const int &in, Point coords) {
	Node *v1 = new Node(in, coords);
	pair<hashNodes::iterator, bool> insertResponse = nodeMap.insert(make_pair(in, v1));
	return insertResponse.second;
}

void Graph::addTransportationLine(TransportLine * t1)
{
	int initialEdge = t1->getInitialEdgeId();
	int finalEdge = t1->getFinalEdgeId();
	
	for (int i = initialEdge; i <= finalEdge; i++) {
		edgeMap[i]->setTransportLine(t1);
	}
}



bool Graph::removeNode(const int &in) {
	typename hashNodes::iterator it = nodeMap.find(in);
	if (it != nodeMap.end())
	{
		Node * v = it->second;
		nodeMap.erase(it);
		typename hashNodes::iterator it1 = nodeMap.begin();
		typename hashNodes::iterator it1e = nodeMap.end();
		for (; it1 != it1e; it1++)
		{
			it1->second->removeEdgeTo(v);
		}

		typename vector<Edge*>::iterator itAdj = v->adj.begin();
		typename vector<Edge*>::iterator itAdje = v->adj.end();
		for (; itAdj != itAdje; itAdj++)
		{
			(*itAdj)->dest->indegree--;
		}
		delete v;
		return true;
	}
	return false;
}


bool Graph::addEdge(int id,const int &sourc, const int &dest) {
	typename hashNodes::iterator it = nodeMap.find(sourc);
	typename hashNodes::iterator ite = nodeMap.find(dest);
	if (it == nodeMap.end() || ite == nodeMap.end())
		return false;
	Node *vS = it->second;
	Node *vD = ite->second;
	vD->indegree++;
	double w = sqrt(pow(vS->coords.x - vD->coords.x, 2) + pow(vS->coords.y - vD->coords.y, 2));
	Edge* e = vS->addEdge(id,vD, w);
	edgeMap.insert(make_pair(id, e));
	if (id > highestEdgeId) {
		highestEdgeId = id;
	}

	return true;
}


bool Graph::removeEdge(const int &sourc, const int &dest) {
	typename hashNodes::iterator it = nodeMap.find(sourc);
	typename hashNodes::iterator ite = nodeMap.find(dest);
	if (it == nodeMap.end() || ite == nodeMap.end())
		return false;
	Node *vS = it->second;
	Node *vD = ite->second;

	vD->indegree--;
	return vS->removeEdgeTo(vD);
}





vector<int> Graph::dfs() const {
	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
		it->second->visited = false;
	vector<int> res;
	it = nodeMap.begin();
	for (; it != ite; it++)
		if (it->second->visited == false)
			dfs(it->second, res);
	return res;
}


void Graph::dfs(Node *v, vector<int> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge*>::iterator it = (v->adj).begin();
	typename vector<Edge*>::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if ((*it)->dest->visited == false) {
			dfs((*it)->dest, res);
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
		typename vector<Edge*>::iterator it = v1->adj.begin();
		typename vector<Edge*>::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Node *d = (*it)->dest;
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
		typename vector<Edge*>::iterator it = v1->adj.begin();
		typename vector<Edge*>::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Node *d = (*it)->dest;
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
	typename hashNodes::const_iterator it = nodeMap.find(v);
	if (it == nodeMap.end())
		return NULL;
	return it->second;
}


void Graph::resetIndegrees() {
	//colocar todos os indegree em 0;
	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
		it->second->indegree = 0;

	//actualizar os indegree
	it = nodeMap.begin();
	for (; it != ite; it++){
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < it->second->adj.size(); j++) {
			it->second->adj[j]->dest->indegree++;
		}
	}
}



vector<Node*> Graph::getSources() const {
	vector< Node* > buffer;
	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
		if (it->second->indegree == 0)
		{
			buffer.push_back(it->second);
		}
	return buffer;
}



void Graph::dfsVisit() {
	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
		it->second->visited = false;
	it = nodeMap.begin();
	for (; it != ite; it++)
		if (it->second->visited == false)
			dfsVisit(it->second);
}


void Graph::dfsVisit(Node *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge*>::iterator it = (v->adj).begin();
	typename vector<Edge*>::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if ((*it)->dest->processing == true) numCycles++;
		if ((*it)->dest->visited == false) {
			dfsVisit((*it)->dest);
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
			v->adj[i]->dest->indegree--;
			if (v->adj[i]->dest->indegree == 0) q.push(v->adj[i]->dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != nodeMap.size()) {
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
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++){
		it->second->path = NULL;
		it->second->dist = INT_INFINITY;
	}

	Node* v = getNode(s);
	v->dist = 0;
	queue< Node* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Node* w = v->adj[i]->dest;
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
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->dist = INT_INFINITY;
	}

	Node* v = getNode(s);
	v->dist = 0;
	queue< Node* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Node* w = v->adj[i]->dest;
			if (w->dist > v->dist + v->adj[i]->weight) {
				w->dist = v->dist + v->adj[i]->weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}


void Graph::dijkstraShortestPath(const int & s)
{
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->dist = INT_INFINITY;
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
			Node* w = v->adj[i]->dest;
			if (w->dist > v->dist + v->adj[i]->weight) {
				w->dist = v->dist + v->adj[i]->weight;
				w->path = v;
				pq.push_back(w);
				push_heap(pq.begin(), pq.end(), Node_greater_than());
			}
		}
	}
}

void Graph::dijkstraShortestPath_distance(const int & s)
{
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->processing = false;
		it->second->dist = INT_INFINITY;
	}

	Node* v = getNode(s);
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);
	vector<Edge *> adja;
	vector<Edge *> onFoot;
	vector<Node *> temp;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		temp = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(temp, v);
		addEdgesFoot(adja, onFoot);

		for (unsigned int i = 0; i < adja.size(); i++) {
			Node* w = adja[i]->dest;
			if (w->dist > v->dist + adja[i]->weight) {
				w->dist = v->dist + adja[i]->weight;
				w->path = v;
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}
				make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
			}
		}
	}
}


void Graph::dijkstraShortestPath_time(const int & s) {
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->processing = false;
		it->second->dist = INT_INFINITY;
		it->second->wayToGetThere = false;
	}

	Node* v = getNode(s);
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);
	vector<Edge* > adja;
	vector<Edge *> onFoot;
	vector<Node *> temp;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		temp = getCloseNodes(SEARCH_RADIUS, v);
		onFoot = getCloseEdges(temp, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int tempo;
			Edge *edge = adja[i];
			bool onTransport = true;
			if (v->wayToGetThere == 'W') {
				onTransport = false;
			}
			Node* w = edge->dest;
			char typeOfTransportLine = edge->line->getType();
			switch (typeOfTransportLine) {
			case 'W':
				tempo = WALK_SPEED / edge->weight;
				break;
			case 'B':
				if (onTransport)
				 tempo = BUS_SPEED / edge->weight;
				else {
					tempo = BUS_SPEED / edge->weight + edge->line->getWaitTime();

					if (WALK_SPEED / edge->weight < tempo) {
						tempo = WALK_SPEED / edge->weight;
						typeOfTransportLine = 'W';
					}
				}
				break;
			case 'T':
				if (onTransport)
				tempo = METRO_SPEED / edge->weight;
				else
					tempo = BUS_SPEED / edge->weight + edge->line->getWaitTime();

				break;
			}

			if (w->dist > v->dist + tempo) {
				w->dist = v->dist + tempo;
				w->path = v;
				w->wayToGetThere = typeOfTransportLine;
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}
				make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
			}
		}
	}
}

void Graph::addEdgesFoot(vector<Edge*> & edges, vector<Edge *> & onFoot) {
	size_t startSize = edges.size();
	for (size_t i = 0; i < onFoot.size(); i++) {
		if (!alreadyExists(edges, onFoot[i])) {
			bool found = false;
			for (size_t j = 0; j < startSize; j++)
			{
				for (size_t k = 0; k < edges.at(j)->dest->adj.size(); k++)
				{
					if (edges.at(j)->dest->adj.at(k)->dest == onFoot[i]->dest)
					{
						found = true;
					}
				}
			}
			if(!found)
				edges.push_back(onFoot[i]);
		}

	}
}

bool Graph::alreadyExists(vector<Edge*> & edges, Edge * e) {
	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i] == e)
			return true;
	}
	return false;
}

void Graph::dijkstraLessTransportsUsed(const int & s)
{
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->processing = false;
		it->second->dist = INT_INFINITY;
		it->second->linesPath.clear();
	}

	Node* v = getNode(s);
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);
	vector<Edge *> adja;
	vector<Edge *> onFoot;
	vector<Node *> temp;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		temp = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(temp, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int weight = 0;
			Node* w = adja[i]->dest;
			TransportLine * tl = adja.at(i)->line;
			unordered_set<string> edgeLines;
			if (tl != nullptr) {
				edgeLines = tl->getLines();
			}
			 
			if (isChangingTransport(edgeLines,v->linesPath)) {
				weight = 1;
			}
			if (w->dist > v->dist + adja[i]->weight) {
				w->dist = v->dist + adja[i]->weight;
				w->path = v;
				w->linesPath = edgeLines;
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}
				make_heap(pq.begin(), pq.end(), Node_greater_than()); 
			}
		}
	}
}


bool Graph::isChangingTransport(unordered_set<string> &edgeLines, unordered_set<string> vPathLines) {
	if (edgeLines.size() == 0) {
		return false;
	}

	unordered_set<string>::iterator itEdge = edgeLines.begin();
	unordered_set<string>::iterator itEdgeFinal = edgeLines.end();

	
	unordered_set<string>::iterator itVPathFinal = vPathLines.end();

	for (; itEdge != itEdgeFinal; itEdge++) {
		string actualLine = *(itEdge);
		for (unordered_set<string>::iterator itVPath = vPathLines.begin(); itVPath != itVPathFinal; itVPath++) {
			if (actualLine == *(itVPath)) {
				return false;
			}
		}
	}
	return true;
}


vector<Node*> Graph::getCloseNodes(int max_dist, Node * n_source) {
	double dist;
	int x_dest;
	int y_dest;
	int x_src=n_source->getCoords().x;
	int y_src= n_source->getCoords().y;
	vector<Node*> closeNodes;

	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		Node *v = it->second;
		if (*(it->second) == *(n_source)) {
			continue;
		}
		x_dest = v->getCoords().x;
		y_dest = v->getCoords().y;
		dist = sqrt(pow(x_src - x_dest, 2) + pow(y_src - y_dest, 2));
		if (dist <= max_dist) {
			closeNodes.push_back(it->second);
		}
	}
	return closeNodes;
}


vector<Edge *> Graph::getCloseEdges(const vector<Node*>& closeNodes, Node * n_source) {
	vector<Edge *> closeEdges;
	double weight;
	int x_dest;
	int y_dest;
	int x_src = n_source->getCoords().x;
	int y_src = n_source->getCoords().y;

	for (size_t i = 0; i < closeNodes.size(); i++) {
		Node *dest = nodeMap[closeNodes.at(i)->info];
		x_dest = dest->getCoords().x;
		y_dest = dest->getCoords().y;
		weight = sqrt(pow(x_src - x_dest, 2) + pow(y_src - y_dest, 2));
		int nextId = highestEdgeId++;
		highestEdgeId = nextId;
		Edge * e = new Edge(nextId,closeNodes[i], weight);
		closeEdges.push_back(e);
	}
	return closeEdges;

}