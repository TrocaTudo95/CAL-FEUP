#include "edge.hpp"

/* ================================================================================================
* Class Edge
* ================================================================================================
*/
Edge::Edge(int idN,int destN, double w) : id(idN),destNode(destN), weight(w) {
}

void Edge::setTransportLine(int transportLineId)
{
	this->transportLineId = transportLineId;
}

int Edge::getTransportLineId()
{
	return transportLineId;
}

int Edge::getDest() const
{
	return destNode;
}

Edge* Edge::copyEdge()
{
	Edge *copied = new Edge(id, destNode, weight);
	copied->setTransportLine(transportLineId);
	return copied;
}

bool Edge::operator==(const Edge& e) const {
	return destNode == e.destNode;
}



