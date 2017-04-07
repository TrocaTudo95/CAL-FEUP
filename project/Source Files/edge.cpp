#include "edge.hpp"

/* ================================================================================================
* Class Edge
* ================================================================================================
*/
Edge::Edge(int idN,Node *d, double w) : id(idN),dest(d), weight(w) {
	line = nullptr;
}

void Edge::setTransportLine(TransportLine *tl)
{
	line = tl;
}

Node * Edge::getDest() const
{
	return dest;
}

Edge* Edge::copyEdge()
{
	Edge *copied = new Edge(id, dest, weight);
	copied->setTransportLine(line);
	return copied;
}

bool Edge::operator==(const Edge& e) const {
	return dest == e.dest;
}



