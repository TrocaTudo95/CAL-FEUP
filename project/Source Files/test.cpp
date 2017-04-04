#include "test.hpp"


void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTH, HEIGHT);
	gv->defineEdgeColor(EDGE_COLOR);
	gv->defineVertexColor(VERTEX_COLOR);
}


void testDijkstraShortestDistance() {
	GraphViewer *gv = new GraphViewer(WIDTH, HEIGHT, false);
	Graph g;
	Point p;
	p.x = 1; p.y = 2;
	g.addNode(1,p);
	gv->addNode(1, p.x, p.y);
	p.x = 2; p.y = 3;
	g.addNode(2, p);
	gv->addNode(2, p.x, p.y);
	p.x = 5; p.y = 7;
	g.addNode(3, p);
	gv->addNode(3, p.x, p.y);
	p.x = 10; p.y = 1;
	g.addNode(4, p);
	gv->addNode(4, p.x, p.y);
	p.x = 1; p.y = 10;
	g.addNode(5, p);
	gv->addNode(5, p.x, p.y);


}


