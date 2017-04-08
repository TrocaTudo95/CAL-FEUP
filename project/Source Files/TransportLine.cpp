#include "TransportLine.hpp"

#define WALK 'W'
#define BUS 'B'
#define TRAM 'T'

TransportLine::TransportLine(int initialEdgeID, int finalEdgeID, string name, string bidirectional, int avg_wait_time) {
	reverse = nullptr;
	assert(reverse == nullptr);
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



void TransportLine::setEdgeMap(unordered_map<int, pair<int, int>>& edgesOD)
{
	edgeMap = edgesOD;
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

TransportLine * TransportLine::createReverse() {
	if (reverse == nullptr) {
		string b;
		if (bidirectional)
		{
			b = "True";
		}
		else
		{
			b = "False";
		}
		reverse = new TransportLine(finalEdgeId, initialEdgeId, name, b, avg_wait_time);
	}
	return reverse;
}



vector<int> TransportLine::getNodesIds()
{
	int size = finalEdgeId - initialEdgeId + 1;
	vector<int> returnNodes(size);
	for (int i = initialEdgeId; i <= finalEdgeId; i++) {
		returnNodes.at(i-initialEdgeId) = (edgeMap.at(i).first);
	}
	returnNodes.at(size-1) = (edgeMap.at(finalEdgeId).second);
	return returnNodes;
	
}

TransportLine * TransportLine::copy()
{
	string biDirectional;
	if (bidirectional) {
		biDirectional = "True";
	}
	else {
		biDirectional = "False";
	}
	TransportLine* tl = new TransportLine(initialEdgeId, finalEdgeId, name, biDirectional, avg_wait_time);
	tl->setType(type);
	tl->setEdgeMap(edgeMap);
	return tl;
}


