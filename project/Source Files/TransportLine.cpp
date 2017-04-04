#include "TransportLine.hpp"

#define WALK 'W'
#define BUS 'B'
#define TRAM 'T'

TransportLine::TransportLine(int edgeID, string name, string bidirectional) {
	this->edgeID = edgeID;
	this->name = name;
	if (bidirectional == "False") {
		this->bidirectional = false;
	}
	else this->bidirectional = true;
	type = WALK;
	
}

bool TransportLine::operator==(const TransportLine & b) const
{
	return (this->edgeID == b.edgeID);
}

void TransportLine::addLines(string lines)
{
	char separator = ',';
	size_t nextSeparatorPos = lines.find(',');
	while (nextSeparatorPos != string::npos) {
		this->lines.insert(lines.substr(0, nextSeparatorPos));
		lines = lines.substr(nextSeparatorPos+1);
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


