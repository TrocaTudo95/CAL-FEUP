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




Graph::Graph()
{
	highestEdgeId = 0;
}

Graph::~Graph()
{
	cout << "Deallocating Memory\n";
	//Free Edges
	hashEdges::iterator itEdges = edgeMap.begin();
	hashEdges::iterator itEdgesEnd = edgeMap.end();
	for (; itEdges != itEdgesEnd; itEdges++) {
		delete(itEdges->second);
	}
	//Free Nodes
	hashNodes::iterator it = nodeMap.begin();
	hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++) {
		delete(it->second);
	}
	cout << "Memory Dealocated\n";
}

hashNodes* Graph::copyNodes()
{
	hashNodes* nodeMapCopy = new hashNodes();
	hashNodes::iterator it = nodeMap.begin();
	hashNodes::iterator ite = nodeMap.end();

	for (; it != ite; it++) {
		nodeMapCopy->insert(make_pair(it->first, it->second->copy()));
	}
	return nodeMapCopy;
}
void Graph::copyEdges(hashNodes originalNodes)
{
	hashNodes::iterator it = originalNodes.begin();
	hashNodes::iterator ite = originalNodes.end();
	for (; it != ite; it++) {
		Node*v = it->second;
		vector<Edge*> vEdges = v->getEdges();
		for (int i = 0; i < vEdges.size(); i++) {
			Edge* currentEdge = vEdges.at(i);
			addEdge(currentEdge->id, getNode(v->info)->info, getNode(currentEdge->dest->info)->info);
			TransportLine *tl = currentEdge->getTransportLine();
			edgeMap[currentEdge->id]->setTransportLine(tl);
		}
	}
}
void Graph::setNodeMap(hashNodes *map)
{
	nodeMap = *map;
}
void Graph::setEdgeMap(hashEdges map)
{
	edgeMap = map;
}
void Graph::setHighestEdgeId(int id)
{
	highestEdgeId = id;
}

void Graph::setTransportationLines(vector<TransportLine*> tlVector)
{	
	transportationLines.resize(tlVector.size());
	for (int i = 0; i < tlVector.size(); i++) {
		transportationLines.at(i) = tlVector.at(i);
	}
}


bool Graph::addNode(const int &in, Point coords) {
	Node *v1 = new Node(in, coords);
	pair<hashNodes::iterator, bool> insertResponse = nodeMap.insert(make_pair(in, v1));
	return insertResponse.second;
}

void Graph::addTransportationLine(TransportLine * t1,unordered_map<int, pair<int, int>> &edgeOD)
{

	int initialEdge = t1->getInitialEdgeId();
	int finalEdge = t1->getFinalEdgeId();
	t1->setEdgeMap(edgeOD);
	TransportLine *TP = nullptr;
	
	for (int i = initialEdge; i <= finalEdge; i++) {
		edgeMap[i]->setTransportLine(t1);
		if (t1->getType() != 'T'){
			Node *ori = nodeMap[edgeOD.at(i).first];
			Node *dest = nodeMap[edgeOD.at(i).second];
			double w = sqrt(pow(ori->getCoords().x - dest->getCoords().x, 2) + pow(ori->getCoords().y - dest->getCoords().y, 2));
			highestEdgeId++;
			Edge * addedEdge = dest->addEdge(highestEdgeId,ori, w);
			edgeMap.insert(make_pair(highestEdgeId, addedEdge));
			if (t1->isBidirectional())
			{
			edgeMap[highestEdgeId]->setTransportLine(t1);
			}
			else
			{
			TP = t1->createReverse();
			edgeMap[highestEdgeId]->setTransportLine(TP);
			transportationLines.push_back(TP);
			}
		}
	}
	transportationLines.push_back(t1);
	if (TP != nullptr) {
		transportationLines.push_back(TP);
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



Node* Graph::getNode(const int &v) const {
	typename hashNodes::const_iterator it = nodeMap.find(v);
	if (it == nodeMap.end())
		return NULL;
	return it->second;
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


bool Graph::checkWalkPercentage(const int &origin, const int &dest, float percentage) {
	vector<Node *> nodePath = getNodePath(origin, dest);
	float total_dist = nodePath[nodePath.size() - 1]->getDist();
	float walk_dist = 0;
	int prev_dist = nodePath[0]->getDist();
	float percentage_a;


	for (size_t i = 1; i < nodePath.size(); i++) {

		if (nodePath[i]->getWayTogetThere() == 'W')
			walk_dist += (nodePath[i]->getDist() - prev_dist);

		prev_dist = nodePath[i]->getDist();
	}

	return(percentage_a > percentage);

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



void Graph::dijkstraShortestDistance(const int & s) {
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
					w->processing = true;
					pq.push_back(w);
				}
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
	}
}


void Graph::dijkstraShortestDistance(const int & s, const int & d) {
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
	double R[2][3];
	dY = (v->coords.y - dNode->coords.y);
	dX = (v->coords.x - dNode->coords.x);
	xCenter = (v->coords.x + dNode->coords.x) / 2.0;
	yCenter = (v->coords.y + dNode->coords.y) / 2.0;
	distance = sqrt(pow(dX, 2) + pow(dY, 2));
	semiA = distance * 0.9;
	semiB = distance * 0.8;
	alfa = -atan(dY / dX);
	R[0][0] = cos(alfa); R[0][1] = -sin(alfa); R[0][2] = yCenter*sin(alfa) - xCenter*cos(alfa) + xCenter;
	R[1][0] = sin(alfa); R[1][1] = cos(alfa); R[1][2] = -xCenter*sin(alfa) - yCenter*cos(alfa) + yCenter;
	v->dist = 0;
	vector<Node *> pq;
	pq.push_back(v);
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	vector<Edge *> adja;
	vector<Edge *> onFoot;
	vector<Node *> temp;
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
					xRotated = R[0][0] * w->coords.x + R[0][1] * w->coords.y + R[0][2];
					yRotated = R[1][0] * w->coords.x + R[1][1] * w->coords.y + R[1][2];
					w->processing = true;
					if (pow(((xRotated - xCenter)/semiA), 2)+pow(((yRotated-yCenter)/semiB),2) <= 1)
						pq.push_back(w);
				}
			}
		}
		make_heap(pq.begin(), pq.end(), Node_greater_than()); //changed to make instead of push
	}
}


void Graph::dijkstraBestTime(const int & s) {
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
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = edge->dest;
			TransportLine * currentTransportLine = edge->line;
			int edgeDistance = edge->weight * PIXEL_TO_METER;
			char typeOfTransportLine;
			bool onTransport = true;
			if (v->wayToGetThere == 'W') {
				onTransport = false;
			}
			if (currentTransportLine != nullptr) {
				typeOfTransportLine = currentTransportLine->getType();
			}
			else typeOfTransportLine = 'W';
			switch (typeOfTransportLine) {
			case 'W':
				deltaTime = edgeDistance/ WALK_SPEED;
				break;
			case 'B':
				 deltaTime = edgeDistance/ BUS_SPEED;
				break;
			case 'T':
				deltaTime = edgeDistance / METRO_SPEED;
				break;
			}

			if (w->dist > v->dist + deltaTime) {
				w->dist = v->dist + deltaTime;
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

void Graph::dijkstraBestTimeWithWaitingTime(const int & s)
{
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
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = edge->dest;
			TransportLine * currentTransportLine = edge->line;
			int edgeDistance = edge->weight * PIXEL_TO_METER;
			char typeOfTransportLine;
			bool onTransport = true;
			if (v->wayToGetThere == 'W') {
				onTransport = false;
			}

			if (currentTransportLine != nullptr) {
				typeOfTransportLine = currentTransportLine->getType();
			}
			else typeOfTransportLine = 'W';
			switch (typeOfTransportLine) {
			case 'W':
				deltaTime = edgeDistance / WALK_SPEED;
				break;
			case 'B':
				if (onTransport)
					deltaTime = edgeDistance / BUS_SPEED;
				else {
					deltaTime = edgeDistance / BUS_SPEED + currentTransportLine->getWaitTime();

					if (edgeDistance / WALK_SPEED < deltaTime) {
						deltaTime = edgeDistance / WALK_SPEED;
						typeOfTransportLine = 'W';
					}
				}
				break;
			case 'T':
				if (onTransport)
					deltaTime = edgeDistance / METRO_SPEED;
				else
					deltaTime = edgeDistance / METRO_SPEED + currentTransportLine->getWaitTime();

				break;
			}

			if (w->dist > v->dist + deltaTime) {
				w->dist = v->dist + deltaTime;
				w->path = v;
				w->wayToGetThere = typeOfTransportLine;
				if (!w->processing) {
					w->processing = true;
					pq.push_back(w);
				}
				make_heap(pq.begin(), pq.end(), Node_greater_than());
			}
		}
	}
}

void Graph::dijkstraBestTimeWithFavoriteTransport(const int & s, char favorite)
{
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
			int deltaTime;
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
				deltaTime = edgeDistance / WALK_SPEED;
				break;
			case 'B':
				deltaTime = edgeDistance / BUS_SPEED;
				break;
			case 'T':
				deltaTime = edgeDistance / METRO_SPEED;
				break;
			}
			int realTime = deltaTime;
			if (typeOfTransportLine == favorite) {
				deltaTime = deltaTime *0.05;
			}
			if (w->dist > v->dist + deltaTime) {
				w->dist = v->dist + realTime;
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

void Graph::dijkstraBestTimeWithFavoriteTransportAndWaitingTime(const int & s, char favorite)
{
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
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = edge->dest;
			TransportLine * currentTransportLine = edge->line;
			int edgeDistance = edge->weight * PIXEL_TO_METER;
			char typeOfTransportLine;
			bool onTransport = true;
			if (v->wayToGetThere == 'W') {
				onTransport = false;
			}

			if (currentTransportLine != nullptr) {
				typeOfTransportLine = currentTransportLine->getType();
			}
			else typeOfTransportLine = 'W';
			switch (typeOfTransportLine) {
			case 'W':
				deltaTime = edgeDistance / WALK_SPEED;
				break;
			case 'B':
				if (onTransport)
					deltaTime = edgeDistance / BUS_SPEED;
				else {
					deltaTime = edgeDistance / BUS_SPEED + currentTransportLine->getWaitTime();

					if (edgeDistance / WALK_SPEED < deltaTime) {
						deltaTime = edgeDistance / WALK_SPEED;
						typeOfTransportLine = 'W';
					}
				}
				break;
			case 'T':
				if (onTransport)
					deltaTime = edgeDistance / METRO_SPEED;
				else
					deltaTime = edgeDistance / METRO_SPEED + currentTransportLine->getWaitTime();

				break;
			}
			int realTime = deltaTime;
			if (typeOfTransportLine == favorite) {
				deltaTime = deltaTime *0.05;
			}
			if (w->dist > v->dist + deltaTime) {
				w->dist = v->dist + realTime;
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



void Graph::preprocessGraphForWaitingTimes()
{
	for (int tl = 0; tl < transportationLines.size(); tl++) {
		TransportLine * t = transportationLines.at(tl);
		char typeOfTransport = t->getType();
		if (typeOfTransport == 'W' || typeOfTransport == 'T') {
			continue;
		}
		int initialEdgeId = t->getInitialEdgeId();
		vector<int> nodesIds = t->getNodesIds();
		if (nodesIds.size() < 3) {
			continue;
		}
		vector<int>::iterator it = nodesIds.begin();
		
		for (int i = 0; i < nodesIds.size()-2; i++) {
			Node * src = getNode(*it);
			assert(src != NULL);
			int weight = 0;
			vector<int>::iterator itDest = it;
			for (int j = i; j < nodesIds.size()-1; j++) {
				itDest++;
				weight += getEdgeById(initialEdgeId + j)->weight;
				if (i != j) {
					Node * dest = getNode(*itDest);
					assert(dest != NULL);
					highestEdgeId++;
					Edge * e = src->addEdge(highestEdgeId, dest, weight);
					edgeMap.insert(make_pair(e->id, e));
					e->setTransportLine(t);
				}
			}
			it++;
		}
	}


}

Graph * Graph::copy()
{
	Graph *g = new Graph();
	g->setNodeMap(copyNodes());
	g->setTransportationLines(transportationLines);
	g->copyEdges(nodeMap);
	
	return g;
	
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
	int x_src = n_source->getCoords().x;
	int y_src = n_source->getCoords().y;
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
			if (!found)
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