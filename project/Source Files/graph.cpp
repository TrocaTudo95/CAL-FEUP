#include "graph.hpp"



/* ================================================================================================
* Class Graph
* ================================================================================================
*/

Edge * Graph::getEdgeById(int id)
{
	typename hashEdges::const_iterator it = edgeMap.find(id);
	if (it == edgeMap.end())
		return NULL;
	return it->second.first;
}


hashNodes Graph::getNodeMap() const {
	return nodeMap;
}


Graph::Graph()
{
	highestEdgeId = 0;
	highestTransportLineId = 0;
	METER_PER_PIXEL_X = 1;
	METER_PER_PIXEL_Y = 1;
}

Graph::~Graph()
{
	cout << "Deallocating Memory\n";
	//Free Edges
	hashEdges::iterator itEdges = edgeMap.begin();
	hashEdges::iterator itEdgesEnd = edgeMap.end();
	for (; itEdges != itEdgesEnd; itEdges++) {
		delete(itEdges->second.first);
	}
	//Free Nodes
	hashNodes::iterator it = nodeMap.begin();
	hashNodes::iterator ite = nodeMap.end();
	for (; it != ite; it++) {
		delete(it->second);
	}
	cout << "Memory Dealocated\n";
}

void Graph::setMETER_PER_PIXEL_X(double d) {
	METER_PER_PIXEL_X = d;
}

void Graph::setMETER_PER_PIXEL_Y(double d) {
	METER_PER_PIXEL_Y = d;
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
		vector<Edge*> vEdges = v->getAdj();
		for (int i = 0; i < vEdges.size(); i++) {
			Edge* currentEdge = vEdges.at(i);
			addEdge(currentEdge->id, v->info,currentEdge->destNode);
			int tl = currentEdge->getTransportLineId();
			edgeMap[currentEdge->id].first->setTransportLine(tl);
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

void Graph::setTransportationLines(const hashTL &tlMap)
{	
	transportationLines = tlMap;
}


bool Graph::addNode(const int &in, Point coords) {
	Node *v1 = new Node(in, coords);
	pair<hashNodes::iterator, bool> insertResponse = nodeMap.insert(make_pair(in, v1));
	return insertResponse.second;
}

void Graph::addTransportationLine(TransportLine * tl)
{
	int initialEdge = tl->getInitialEdgeId();
	int finalEdge = tl->getFinalEdgeId();
	int tlId = tl->getId();
	transportationLines.insert(make_pair(tlId, tl));
	if (tlId > highestEdgeId) {
		highestEdgeId = tlId;
	}
	for (int i = initialEdge; i <= finalEdge; i++) {
		edgeMap[i].first->setTransportLine(tlId);
	}
	
	
}

void Graph::setReverseTransportationLines()
{
	hashTL::iterator it = transportationLines.begin();
	hashTL::iterator ite = transportationLines.end();
	int destRevId, oriRevId, initialEdge, finalEdge, numEdges;
	Node *destReverse;
	Node *oriReverse;
	double weight;
	bool isBidirectional;
	TransportLine *tl, *tlReverse;
	for (; it != ite; it++) {
		tl = it->second;
		isBidirectional = tl->isBidirectional();
		if (tl->getType() != 'T' || isBidirectional) {
			initialEdge = tl->getInitialEdgeId();
			finalEdge = tl->getFinalEdgeId();
			numEdges = finalEdge - initialEdge + 1;
			for (int i = finalEdge; i >= initialEdge; i--) {
				destRevId = edgeMap.at(i).second;
				oriRevId = edgeMap.at(i).first->getDest();
				destReverse = getNode(destRevId);
				oriReverse = getNode(oriRevId);
				weight = edgeMap.at(i).first->weight;
				addEdge(highestEdgeId + 1, oriRevId, destRevId, weight);
			}
			if (isBidirectional) {
				tlReverse = tl->createFullReverse(highestTransportLineId + 1, highestEdgeId-numEdges+1, highestEdgeId);
			}
			else {
				tlReverse = tl->createReverseWalking(highestTransportLineId + 1, highestEdgeId - numEdges + 1, highestEdgeId);

			}
			addTransportationLine(tlReverse);
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
			Node *d = getNode((*itAdj)->destNode);
			d->indegree--;
		}
		delete v;
		return true;
	}
	return false;
}


bool Graph::addEdge(int id,const int &sourc, const int &dest, int w) {
	typename hashNodes::iterator it = nodeMap.find(sourc);
	typename hashNodes::iterator ite = nodeMap.find(dest);
	if (it == nodeMap.end() || ite == nodeMap.end())
		return false;
	Node *vS = it->second;
	Node *vD = ite->second;
	vD->indegree++;
	if (w == 0) {
		w = sqrt(pow(vS->coords.x - vD->coords.x, 2) + pow(vS->coords.y - vD->coords.y, 2));
	}
	Edge* e = vS->addEdge(id,dest, w);
	edgeMap.insert(make_pair(id, make_pair(e,sourc)));

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

TransportLine * Graph::getTransportLine(const int & id) const
{
	hashTL::const_iterator it = transportationLines.find(id);
	if (it == transportationLines.end())
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

vector<int> Graph::getPathForSPFA(const int &origin, const int &dest) {
	list<int> buffer;
	vector<int> res;
	int v = dest;
	buffer.push_front(v);
	while (path[v] != 0 && path[v] != origin) {
		v = path[v];
		buffer.push_front(v);
	}
	if (path[v] != 0) {
		v = path[v];
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
			Node* w = getNode(v->adj[i]->destNode);
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
			Node* w = getNode(v->adj[i]->destNode);
			if (w->dist > v->dist + v->adj[i]->weight) {
				w->dist = v->dist + v->adj[i]->weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}



void Graph::SPFAWithAdjacencyList(const int & s, const int &d)
{
	int v, w, weight;
	for (int i = 0; i < dist.size(); i++) {
		dist[i] = INT_MAX;
		in_queue[i] = 0;
		path[i] = 0;
	}
	Node * dNode = getNode(d);
	Node * sNode = getNode(s);
	double alfa, xCenter, yCenter, semiA, semiB, dY, dX, distance;
	double R[2][3];
	dY = (sNode->coords.y - dNode->coords.y);
	dX = (sNode->coords.x - dNode->coords.x);
	xCenter = (sNode->coords.x + dNode->coords.x) / 2.0;
	yCenter = (sNode->coords.y + dNode->coords.y) / 2.0;
	distance = sqrt(pow(dX, 2) + pow(dY, 2));
	semiA = distance * 0.9;
	semiB = distance * 0.8;
	alfa = -atan(dY / dX);
	R[0][0] = cos(alfa); R[0][1] = -sin(alfa); R[0][2] = yCenter*sin(alfa) - xCenter*cos(alfa) + xCenter;
	R[1][0] = sin(alfa); R[1][1] = cos(alfa); R[1][2] = -xCenter*sin(alfa) - yCenter*cos(alfa) + yCenter;

	queue<int> q; q.push(s);
	dist.at(s) = 0;
	in_queue.at(s) = 1;
	vii adja;
	vii onFoot;
	vector<int> closeNodes;
	while (!q.empty()) {
		v = q.front(); q.pop(); in_queue[v] = 0;
		adja = adjList[v];
		Node * vN = getNode(v);
		closeNodes = getCloseNodes(SEARCH_RADIUS, vN);// the max_dist has to be defined
		onFoot = getCloseEdgesSPFA(closeNodes, vN);
		addEdgesFootSPFA(adja, onFoot);
		for (int j = 0; j < adja.size(); j++) {
			w = adja[j].first;
			Node * wNode = getNode(w);
			weight = adja[j].second;
			if (dist[v] + weight < dist[w]) {
				dist[w] = dist[v] + weight;
				path[w] = v;
				if (!in_queue[w]) {
					double xRotated, yRotated;
					xRotated = R[0][0] * wNode->coords.x + R[0][1] * wNode->coords.y + R[0][2];
					yRotated = R[1][0] * wNode->coords.x + R[1][1] * wNode->coords.y + R[1][2];
					if (pow(((xRotated - xCenter) / semiA), 2) + pow(((yRotated - yCenter) / semiB), 2) <= 1) {
						q.push(w);
						in_queue[w] = 1;
					}
					
				}
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
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty())
	{
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);

		for (unsigned int i = 0; i < adja.size(); i++)
		{
			Node* w = getNode(adja[i]->destNode);
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

//Optimized by elipse
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
	vector<int> closeNodes;
	while (!pq.empty())
	{
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);

		for (unsigned int i = 0; i < adja.size(); i++)
		{
			Node* w = getNode(adja[i]->destNode);
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
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = getNode(edge->destNode);
			TransportLine * currentTransportLine = getTransportLine(edge->transportLineId);
			int edgeDistance = edge->weight;
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

void Graph::dijkstraBestTimeWithWaitingTime(const int & s,const double & max_cost)
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
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int deltaTime;
			double cost;
			Edge *edge = adja[i];
			Node* w = getNode(edge->destNode);
			TransportLine * currentTransportLine = getTransportLine(edge->transportLineId);
			int edgeDistance = edge->weight;

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
				if (max_cost > 0)
					if (v->cost > max_cost)
						deltaTime = 99999;
				break;
			case 'T':
				if (onTransport)
					deltaTime = edgeDistance / METRO_SPEED;
				else
					deltaTime = edgeDistance / METRO_SPEED + currentTransportLine->getWaitTime();

				if (max_cost > 0)
					if (v->cost > max_cost)
						deltaTime = 99999;
				break;
			}

			if (w->dist > v->dist + deltaTime) {
				w->dist = v->dist + deltaTime;
				w->path = v;
				w->wayToGetThere = typeOfTransportLine;
				if (max_cost > 0) {
					cost = calculateCost(edgeDistance, typeOfTransportLine);
					w->cost = v->cost + cost;
				}
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
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = getNode(edge->destNode);
			TransportLine * currentTransportLine = getTransportLine(edge->transportLineId);
			int edgeDistance = edge->weight;

			char typeOfTransportLine;
		
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
				deltaTime = deltaTime *FAV_TRANSPORT_MULTIPLIER;
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
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int deltaTime;
			Edge *edge = adja[i];
			Node* w = getNode(edge->destNode);
			TransportLine * currentTransportLine = getTransportLine(edge->transportLineId);
			int edgeDistance = edge->weight;

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
				deltaTime = deltaTime *FAV_TRANSPORT_MULTIPLIER;
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
	vector<Edge* > adja;
	vector<Edge *> onFoot;
	vector<int> closeNodes;
	make_heap(pq.begin(), pq.end(), Node_greater_than());
	while (!pq.empty()) {
		v = pq.front();
		pop_heap(pq.begin(), pq.end(), Node_greater_than());
		pq.pop_back();
		adja = v->adj;
		closeNodes = getCloseNodes(SEARCH_RADIUS, v);// the max_dist has to be defined
		onFoot = getCloseEdges(closeNodes, v);
		addEdgesFoot(adja, onFoot);
		for (unsigned int i = 0; i < adja.size(); i++) {
			int weight = 0;
			Edge *edge = adja[i];
			Node* w = getNode(edge->destNode);
			TransportLine * tl = getTransportLine(edge->transportLineId);
			unordered_set<string> edgeLines;
			char wayToGetToW = v->wayToGetThere;
			if (tl != nullptr) {
				edgeLines = tl->getLines();
			}

			if (isChangingTransport(edgeLines, v->linesPath)) {
				weight = 1;
				if (edgeLines.begin()->size() > 1) {
					wayToGetToW = 'B';
				}
				else {
					wayToGetToW = 'T';
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
				make_heap(pq.begin(), pq.end(), Node_greater_than());
			}
		}
	}
}

void Graph::preprocessGraphForWaitingTimes()
{
	for (auto& tlIter : transportationLines) {
		TransportLine * t = tlIter.second;
		char typeOfTransport = t->getType();
		if (typeOfTransport == 'W' || typeOfTransport == 'T') {
			continue;
		}
		int initialEdgeId = t->getInitialEdgeId();
		vector<int> nodesIds = t->getNodesIds(edgeMap);
		if (nodesIds.size() < 3) {
			continue;
		}
		vector<int>::iterator it = nodesIds.begin();

		for (int i = 0; i < nodesIds.size() - 2; i++) {
			Node * src = getNode(*it);
			assert(src != NULL);
			int weight = 0;
			vector<int>::iterator itDest = it;
			for (int j = i; j < nodesIds.size() - 1; j++) {
				itDest++;
				weight += getEdgeById(initialEdgeId + j)->weight;
				if (i != j) {
					highestEdgeId++;
					Edge * e = src->addEdge(highestEdgeId, *itDest, weight);
					edgeMap.insert(make_pair(e->id, make_pair(e, *it)));
					e->setTransportLine(tlIter.first);
				}
			}
			it++;
		}
	}

}

void Graph::preprocessGraphForSPFA()
{
	dist.resize(nodeMap.size() + 1);
	in_queue.resize(nodeMap.size() + 1);
	adjList.resize(nodeMap.size() + 1);
	path.resize(nodeMap.size() + 1);

	hashNodes::iterator it = nodeMap.begin();
	hashNodes::iterator ite = nodeMap.end();

	for (; it != ite; it++) {
		Node *v = it->second;
		int vId = v->getInfo();
		vector<Edge*> edges = v->getAdj();
		int edgesSize = edges.size();
		adjList.at(vId).resize(edgesSize);
		for (int i = 0; i < edgesSize; i++) {
			Edge* actualEdge = edges.at(i);
			adjList.at(v->info).at(i).first = actualEdge->destNode;
			adjList.at(v->info).at(i).second = actualEdge->weight;
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
				Node *d = getNode(edges.at(j)->destNode);
				for (size_t k = 0; k < d->adj.size(); k++)
				{
					if (d->adj.at(k)->destNode == onFoot[i]->destNode)
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

void Graph::addEdgesFootSPFA(vii & edges, vii & onFoot)
{
	size_t startSize = edges.size();
	for (size_t i = 0; i < onFoot.size(); i++) {
		if (!alreadyExistsSPFA(edges, onFoot[i].first)) {
			bool found = false;
			for (size_t j = 0; j < startSize; j++)
			{
				Node *d = getNode(edges[j].first);
				for (size_t k = 0; k < d->adj.size(); k++)
				{
					if (d->adj.at(k)->destNode == onFoot[i].first)
					{
						found = true;
					}
				}
			}
			if (!found)
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


bool Graph::alreadyExistsSPFA(vii & edges, int e) {
	for (size_t i = 0; i < edges.size(); i++) {
		if (edges[i].first == e)
			return true;
	}
	return false;
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

double Graph::calculateCost(double distance, char transportation)
{
	switch (transportation) {
	case 'W':
		return 0.0;
	case 'T':
		return distance * 0.001;
	
	case'B':
		return distance *0.0005;

	}
}


vector<int> Graph::getCloseNodes(int max_dist, Node * n_source) {
	double dist;
	int x_dest;
	int y_dest;
	int x_src = n_source->getCoords().x;
	int y_src = n_source->getCoords().y;
	vector<int> closeNodes;

	typename hashNodes::const_iterator it = nodeMap.begin();
	typename hashNodes::const_iterator ite = nodeMap.end();
	for (; it != ite; it++)
	{
		Node *v = it->second;
		int vId = v->info;
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
				if (vId == n_source->adj.at(i)->destNode)
				{
					found = true;
					break;
				}
			}
			if (!found)
				closeNodes.push_back(vId);
		}
	}
	return closeNodes;
}


vector<Edge *> Graph::getCloseEdges(const vector<int>& closeNodes, Node * n_source) {
	vector<Edge *> closeEdges;
	double weight;
	int x_dest;
	int y_dest;
	int x_src = n_source->getCoords().x;
	int y_src = n_source->getCoords().y;

	for (size_t i = 0; i < closeNodes.size(); i++) {
		Node *dest = nodeMap.at(closeNodes.at(i));
		x_dest = dest->getCoords().x;
		y_dest = dest->getCoords().y;
		weight = sqrt(pow((x_src - x_dest)*METER_PER_PIXEL_X, 2) + pow((y_src - y_dest)*METER_PER_PIXEL_Y, 2));
		int nextId = highestEdgeId++;
		highestEdgeId = nextId;
		Edge * e = new Edge(nextId,closeNodes[i], weight);
		closeEdges.push_back(e);
	}
	return closeEdges;

}

vii Graph::getCloseEdgesSPFA(vector<int>& closeNodes, Node *src)
{
	vii closeEdges;
	double weight;
	int x_dest;
	int y_dest;
	int x_src = src->getCoords().x;
	int y_src = src->getCoords().y;

	for (size_t i = 0; i < closeNodes.size(); i++) {
		Node *dest = nodeMap.at(closeNodes.at(i));
		x_dest = dest->getCoords().x;
		y_dest = dest->getCoords().y;
		weight = sqrt(pow(x_src - x_dest, 2) + pow(y_src - y_dest, 2));
		closeEdges.push_back(make_pair(closeNodes[i], weight));
	}
	return closeEdges;
}
