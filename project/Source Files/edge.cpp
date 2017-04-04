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

