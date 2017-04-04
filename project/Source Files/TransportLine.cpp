#include "TransportLine.hpp"



TransportLine::TransportLine(int edgeID, string name, string bidirectional) {
	this->edgeID = edgeID;
	this->name = name;
	if (bidirectional == "False") {
		this->bidirectional = false;
	}
	else this->bidirectional = true;
	
}

bool TransportLine::operator==(const TransportLine & b) const
{
	return (this->edgeID == b.edgeID);
}

void TransportLine::addLine(string line)
{
	lines.insert(line);
}


