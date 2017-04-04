#include "edge.hpp"

/* ================================================================================================
* Class Edge
* ================================================================================================
*/
Edge::Edge(int idN,Node *d, double w) : id(idN),dest(d), weight(w) {}

bool Edge::operator==(const Edge& e) const {
	return dest == e.dest;
}



