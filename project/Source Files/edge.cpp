#include "edge.hpp"

/* ================================================================================================
* Class Edge
* ================================================================================================
*/
Edge::Edge(int idN,Node* s,Node *d, double w) : id(idN),src(s),dest(d), weight(w) {
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

bool Edge::operator==(const Edge& e) const {
	return dest == e.dest;
}



