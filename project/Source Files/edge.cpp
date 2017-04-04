#include "edge.hpp"

/* ================================================================================================
* Class Edge
* ================================================================================================
*/
Edge::Edge(int idN,Node *d, double w) : id(idN),dest(d), weight(w) {
	
}

void Edge::setTransportLine(TransportLine *tl)
{
	line = tl;
}

