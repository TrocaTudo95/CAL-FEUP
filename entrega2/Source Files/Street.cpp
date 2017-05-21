#include "Street.hpp"

#define WALK 'W'
#define BUS 'B'
#define TRAM 'T'

Street::Street(int transportLineId,int initialEdgeID, int finalEdgeID, string name, string bidirectional, int avg_wait_time) {
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


bool Street::operator==(const Street & b) const
{
	return (this->initialEdgeId == b.initialEdgeId && this->finalEdgeId == b.finalEdgeId);
}

void Street::addLines(string lines)
{
	stringstream lineStream(lines);
	string line;
	while (getline(lineStream, line, ',')) {
		this->lines.insert(line);
	}
}

void Street::setLines(unordered_set<string> &l)
{
	lines = l;
}

void Street::setType(string type)
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

void Street::setType(char type)
{
	this->type = type;
}

string Street::toString() const
{
	string toReturn = name + "-" + type + "-";
	unordered_set<string>::const_iterator it = lines.begin();
	unordered_set<string>::const_iterator ite = lines.end();
	for (; it != ite; it++) {
		toReturn += *it +  " ";
	}
	return toReturn;
}

int Street::getId() const
{
	return id;
}

int Street::getInitialEdgeId() const
{
	return initialEdgeId;
}

int Street::getFinalEdgeId() const
{
	return finalEdgeId;
}

unordered_set<string>& Street::getLines()
{
	return lines;
}

char Street::getType()
{
	return type;
}

int Street::getWaitTime()
{
	return avg_wait_time;
}

bool Street::isBidirectional() {
	return bidirectional;
}

Street * Street::createReverseWalking(int id, int initialEdgeId, int finalEdgeId)
{
	return new Street(id, initialEdgeId, finalEdgeId, name, "False", avg_wait_time);
}


Street * Street::createFullReverse(int id, int initialEdgeId, int finalEdgeId)
{	Street* tl = new Street(id, initialEdgeId, finalEdgeId, name, "False", avg_wait_time);
	tl->setType(type);
	tl->setLines(lines);
	return tl;
}

vector<int> Street::getNodesIds(unordered_map<int, pair<Edge*, int>> &edgeMap)
{
	int size = finalEdgeId - initialEdgeId + 1;
	vector<int> returnNodes(size);
	for (int i = initialEdgeId; i <= finalEdgeId; i++) {
		returnNodes.at(i-initialEdgeId) = (edgeMap.at(i).second);
	}
	returnNodes.at(size-1) = (edgeMap.at(finalEdgeId).first->getDest());
	return returnNodes;
	
}
