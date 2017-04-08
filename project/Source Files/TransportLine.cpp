#include "TransportLine.hpp"

#define WALK 'W'
#define BUS 'B'
#define TRAM 'T'

TransportLine::TransportLine(int transportLineId,int initialEdgeID, int finalEdgeID, string name, string bidirectional, int avg_wait_time) {
	this->id = transportLineId;
	this->initialEdgeId = initialEdgeID;
	this->finalEdgeId = finalEdgeID;
	this->name = name;
	this->avg_wait_time = avg_wait_time;
	if (bidirectional == "False") {
		this->bidirectional = false;
	}
	else this->bidirectional = true;
	type = WALK;
}


bool TransportLine::operator==(const TransportLine & b) const
{
	return (this->initialEdgeId == b.initialEdgeId && this->finalEdgeId == b.finalEdgeId);
}

void TransportLine::addLines(string lines)
{
	stringstream lineStream(lines);
	string line;
	while (getline(lineStream, line, ',')) {
		this->lines.insert(line);
	}
}

void TransportLine::setLines(unordered_set<string> &l)
{
	lines = l;
}

void TransportLine::setType(string type)
{
	if (type == "tram") {
		this->type = TRAM;
	}
	else if (type == "bus") {
		this->type = BUS;
	}
	else if (type == "walk")
	{
		this->type = WALK;
	}
}

void TransportLine::setType(char type)
{
	this->type = type;
}

string TransportLine::toString() const
{
	string toReturn = name + "-" + type + "-";
	unordered_set<string>::const_iterator it = lines.begin();
	unordered_set<string>::const_iterator ite = lines.end();
	for (; it != ite; it++) {
		toReturn += *it +  " ";
	}
	return toReturn;
}

int TransportLine::getId() const
{
	return id;
}

int TransportLine::getInitialEdgeId() const
{
	return initialEdgeId;
}

int TransportLine::getFinalEdgeId() const
{
	return finalEdgeId;
}

unordered_set<string>& TransportLine::getLines()
{
	return lines;
}

char TransportLine::getType()
{
	return type;
}

int TransportLine::getWaitTime()
{
	return avg_wait_time;
}

bool TransportLine::isBidirectional() {
	return bidirectional;
}

TransportLine * TransportLine::createReverseWalking(int id, int initialEdgeId, int finalEdgeId)
{
	return new TransportLine(id, initialEdgeId, finalEdgeId, name, "False", avg_wait_time);
}


TransportLine * TransportLine::createFullReverse(int id, int initialEdgeId, int finalEdgeId)
{	TransportLine* tl = new TransportLine(id, initialEdgeId, finalEdgeId, name, "False", avg_wait_time);
	tl->setType(type);
	tl->setLines(lines);
	return tl;
}

vector<int> TransportLine::getNodesIds(unordered_map<int, pair<Edge*, int>> &edgeMap)
{
	int size = finalEdgeId - initialEdgeId + 1;
	vector<int> returnNodes(size);
	for (int i = initialEdgeId; i <= finalEdgeId; i++) {
		returnNodes.at(i-initialEdgeId) = (edgeMap.at(i).second);
	}
	returnNodes.at(size-1) = (edgeMap.at(finalEdgeId).first->getDest());
	return returnNodes;
	
}
