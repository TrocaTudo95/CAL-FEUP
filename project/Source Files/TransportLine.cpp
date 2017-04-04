#include "TransportLine.hpp"

#define WALK 'W'
#define BUS 'B'
#define TRAM 'T'

TransportLine::TransportLine(int initialEdgeID, int finalEdgeID, string name, string bidirectional) {
	this->initialEdgeId = initialEdgeID;
	this->finalEdgeId = finalEdgeID;
	this->name = name;
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
{	//Problem here when there is more than 1 line;
	char separator = ',';
	size_t nextSeparatorPos = lines.find(separator);
	while (nextSeparatorPos != string::npos) {
		this->lines.insert(lines.substr(0, nextSeparatorPos));
		lines = lines.substr(nextSeparatorPos+1);
		nextSeparatorPos = lines.find(separator);
	}
	this->lines.insert(lines);
}

void TransportLine::setType(string type)
{
	if (type == "tram") {
		this->type = TRAM;
	}
	else if (type == "bus") {
		this->type = BUS;
	}
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


