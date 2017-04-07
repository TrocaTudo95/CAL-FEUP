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

void Graph::addTransportationLine(TransportLine * t1) {
	int initialEdge = t1->getInitialEdgeId();
	int finalEdge = t1->getFinalEdgeId();

	for (int i = initialEdge; i <= finalEdge; i++)
	{
		edgeMap[i]->setTransportLine(t1);
	}
}

void Graph::addTransportationLine(TransportLine * t1,const unordered_map<int, pair<int, int>> &edgeOD)
{
	int initialEdge = t1->getInitialEdgeId();
	int finalEdge = t1->getFinalEdgeId();
	
	for (int i = initialEdge; i <= finalEdge; i++) {
		edgeMap[i]->setTransportLine(t1);
		Node *ori = nodeMap[edgeOD.at(i).first];
		Node *dest = nodeMap[edgeOD.at(i).second];
		double w = sqrt(pow(ori->getCoords().x - dest->getCoords().x, 2) + pow(ori->getCoords().y - dest->getCoords().y, 2));
		highestEdgeId++;
		Edge * addedEdge = dest->addEdge(highestEdgeId, ori, w);
		edgeMap.insert(make_pair(highestEdgeId, addedEdge));
		if (t1->isBidirectional())
		{
			edgeMap[highestEdgeId]->setTransportLine(t1);
		}
		else
		{
			TransportLine *TP = t1->createReverse();
			edgeMap[highestEdgeId]->setTransportLine(TP);
		}
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



vector<PathTo> Graph::getPath(const int &origin, const int &dest) {

	list<PathTo> buffer;
	Node* v = getNode(dest);
	PathTo pathTo; pathTo.path = v->info; pathTo.dist = v->dist; pathTo.wayToGetThere = v->wayToGetThere;
	buffer.push_front(pathTo);
	while (v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		pathTo.path = v->info; pathTo.dist = v->dist; pathTo.wayToGetThere = v->wayToGetThere;
		buffer.push_front(pathTo);
	}
	if (v->path != NULL) {
		v = v->path;
		pathTo.path = v->info; pathTo.dist = v->dist; pathTo.wayToGetThere = v->wayToGetThere;
		buffer.push_front(pathTo);
	}
		
	vector<PathTo> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}

vector<Node *> Graph::getNodePath(const int &origin, const int &dest) {
	list<Node *> buffer;
	vector<Node *> res;
	Node* v = getNode(dest);
	buffer.push_front(v);
	while (v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v);
	}
	if (v->path != NULL) {
		v = v->path;
		buffer.push_front(v);
	}

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
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
	}
}

void Graph::dijkstraShortestPath_distance(const int & s, const int & d) {
	typename hashNodes::iterator it = nodeMap.begin();
	typename hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		it->second->path = NULL;
		it->second->processing = false;
		it->second->dist = INT_INFINITY;
	}

	Node* dNode = getNode(d);
	Node* v = getNode(s);
	double alfa, xCenter, yCenter, semiA, semiB, dY, dX, distance;
	double xR[3], yR[3];
	dY = (v->coords.y - dNode->coords.y);
	dX = (v->coords.x - dNode->coords.x);
	xCenter = (v->coords.x + dNode->coords.x) / 2.0;
	yCenter = (v->coords.y + dNode->coords.y) / 2.0;
	distance = sqrt(pow(dX, 2) + pow(dY, 2));
	semiA = distance * 1.2;
	semiB = distance;
	alfa = -atan(dY / dX);
	xR[0] = cos(alfa); xR[1] = -sin(alfa); xR[2] = yCenter*sin(alfa) - xCenter*cos(alfa) + xCenter;
	yR[0] = sin(alfa); yR[1] = cos(alfa); yR[2] = -xCenter*sin(alfa) - yCenter*cos(alfa) + yCenter;
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);
	vector<Edge *> adja;
	vector<Edge *> onFoot;
	vector<Node *> temp;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty())
	{
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		temp = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(temp, v);
		addEdgesFoot(adja, onFoot);

		for (unsigned int i = 0; i < adja.size(); i++)
		{
			Node* w = adja[i]->dest;
			if (w->dist > v->dist + adja[i]->weight)
			{
				w->dist = v->dist + adja[i]->weight;
				w->path = v;
				if (!w->processing)
				{
					double xRotated, yRotated;
					xRotated = xR[0] * w->coords.x + xR[1] * w->coords.y + xR[2];
					yRotated = yR[0] * w->coords.x + yR[1] * w->coords.y + yR[2];
					w->processing = true;
					if (pow(((xRotated - xCenter)/semiA), 2)+pow(((yRotated-yCenter)/semiB),2) <= 1)
						pq.push_back(w);
				}
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
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
		it->second->wayToGetThere = 'W';
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
			TransportLine * currentTransportLine = edge->line;
			int edgeDistance = edge->weight * PIXEL_TO_METER;
			char typeOfTransportLine;
			Node* w = edge->dest;
			if (currentTransportLine != nullptr) {
				typeOfTransportLine = currentTransportLine->getType();
			}
			else typeOfTransportLine = 'W';
			switch (typeOfTransportLine) {
			case 'W':
				tempo = edgeDistance/ WALK_SPEED;
				break;
			case 'B':
				 tempo = edgeDistance/ BUS_SPEED;
				break;
			case 'T':
				tempo = edgeDistance / METRO_SPEED;
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
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
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
		it->second->wayToGetThere = 'W';
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
			//Little Optimization
			if (w->dist < v->dist) {
				continue;
			}
			//End Of Optimization
			TransportLine * tl = adja.at(i)->line;
			unordered_set<string> edgeLines;
			char wayToGetToW = v->wayToGetThere;
			if (tl != nullptr) {
				edgeLines = tl->getLines();
			}
			 
			if (isChangingTransport(edgeLines,v->linesPath)) {
				weight = 1;
				if (edgeLines.begin()->size() > 1) {
					wayToGetToW = 'B';
				}
				else {
					wayToGetToW = 'M';
				}
			}
			if (w->dist > v->dist + weight) {
				w->dist = v->dist + weight;
				w->path = v;
				w->wayToGetThere = wayToGetToW;
				w->linesPath = edgeLines;
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than());
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
			bool found = false;
			for (size_t i = 0; i < n_source->adj.size(); i++)
			{
				if (it->second == n_source->adj.at(i)->dest)
				{
					found = true;
					break;
				}
			}
			if(!found)
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