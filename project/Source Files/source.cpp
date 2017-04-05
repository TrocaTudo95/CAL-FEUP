#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "graphviewer.h"
#include "graph.hpp"

 /*CONSTANTS */

#define EDGE_COLOR_DEFAULT "blue"
#define VERTEX_COLOR_DEFAULT "yellow"
#define NODES_FILENAME "nos.txt"
#define EDGES_FILENAME "arestas.txt"
#define LINES_FILENAME "names.txt"

const int WIDTHOFGRAPH = 1920;
const int HEIGHTOFGRAPH = 1080;


bool openFile(ifstream &inFile, const string filename) {
	//Ler o ficheiro arestas.txt
	inFile.open(filename);

	if (!inFile)
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}
	return true;
}


void readEdgesFile(Graph &graph, GraphViewer *gv) {
	ifstream inFile;

	openFile(inFile, EDGES_FILENAME);
	std::string line;

	int idAresta = 0;
	int idNoOrigem = 0;
	int idNoDestino = 0;

	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string data;
		linestream >> idAresta;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
		graph.addEdge(idAresta,idNoOrigem, idNoDestino);
	}

	inFile.close();

}

void readNodesFile(Graph &graph, GraphViewer *gv) {
	ifstream inFile;
	openFile(inFile, NODES_FILENAME);

	int idNo = 0;
	Point point;
	std::string line;

	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string coords;
		linestream >> idNo;
		std::getline(linestream, coords, ';');  // read up-to the first ; (discard ;).
		linestream >> point.x;
		std::getline(linestream, coords, ';');  // read up-to the first ; (discard ;).
		linestream >> point.y;
		gv->addNode(idNo, point.x, point.y);
		graph.addNode(idNo, point);
	}
	inFile.close();
}


void readNamesFile(Graph &graph) {
	ifstream inFile;
	openFile(inFile, LINES_FILENAME);
	int initialEdge, finalEdge;
	string line, junk, streetName, bidirectional, lines, typeOfLine;
	bool firstTime = true;
	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		if (!firstTime) {
			linestream >> finalEdge;
			TransportLine * tl = new TransportLine(initialEdge, finalEdge - 1, streetName, bidirectional,rand()%6 +5);
			graph.addTransportationLine(tl);
			initialEdge = finalEdge;
			if (lines.size() > 0) {
				tl->addLines(lines);
				tl->setType(typeOfLine);
			}
		}
		else {
			linestream >> initialEdge;
			firstTime = false;
		}
		std::getline(linestream, junk, ';');
		std::getline(linestream, streetName, ';');
		std::getline(linestream, bidirectional, ';');
		std::getline(linestream, lines, ';');
		std::getline(linestream, typeOfLine, ';');

		
	}
	inFile.close();
}

void readFiles(Graph &graph, GraphViewer *gv) {
	readNodesFile(graph, gv);
	readEdgesFile(graph, gv);
	readNamesFile(graph);
	gv->rearrange();
}


void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTHOFGRAPH, HEIGHTOFGRAPH);
	gv->defineEdgeColor(EDGE_COLOR_DEFAULT);
	gv->defineVertexColor(VERTEX_COLOR_DEFAULT);
}



void testDijkstraShortestDistance(Graph &g, GraphViewer *gv) {
	Point p;
	p.x = 10; p.y = 20;
	g.addNode(1, p);
	gv->addNode(1, p.x, p.y);
	p.x = 20; p.y = 30;
	g.addNode(2, p);
	gv->addNode(2, p.x, p.y);
	p.x = 50; p.y = 70;
	g.addNode(3, p);
	gv->addNode(3, p.x, p.y);
	p.x = 100; p.y = 10;
	g.addNode(4, p);
	gv->addNode(4, p.x, p.y);
	p.x = 10; p.y = 100;
	g.addNode(5, p);
	gv->addNode(5, p.x, p.y);
	g.addEdge(1, 1, 4);
	g.addEdge(2, 4, 3);
	g.addEdge(3, 3, 5);
	g.addEdge(4, 3, 2);
	g.addEdge(5, 2, 5);
	gv->addEdge(1, 1, 4,EdgeType::DIRECTED);
	gv->addEdge(2, 4, 3, EdgeType::DIRECTED);
	gv->addEdge(3, 3, 5, EdgeType::DIRECTED);
	gv->addEdge(4, 3, 2, EdgeType::DIRECTED);
	gv->addEdge(5, 2, 5, EdgeType::DIRECTED);
	gv->setVertexColor(1, "black");
	gv->setVertexColor(5, "black");
	g.dijkstraShortestPath_distance(1);
	vector<int> path = g.getPath(1, 5);
	cout << "Path : ";
	for (int i = 0; i < path.size(); i++) {
		cout << path.at(i) << " | ";
	}

}



void testDijkstraNumTransportsUsed(Graph &g, GraphViewer *gv) {
	Point p;
	p.x = 10; p.y = 20;
	g.addNode(1, p);
	gv->addNode(1, p.x, p.y);
	p.x = 20; p.y = 30;
	g.addNode(2, p);
	gv->addNode(2, p.x, p.y);
	p.x = 50; p.y = 70;
	g.addNode(3, p);
	gv->addNode(3, p.x, p.y);
	p.x = 100; p.y = 10;
	g.addNode(4, p);
	gv->addNode(4, p.x, p.y);
	p.x = 10; p.y = 100;
	g.addNode(5, p);
	gv->addNode(5, p.x, p.y);
	g.addEdge(1, 1, 4);
	g.addEdge(2, 4, 3);
	g.addEdge(3, 3, 5);
	g.addEdge(4, 3, 2);
	g.addEdge(5, 2, 5);
	gv->addEdge(1, 1, 4, EdgeType::DIRECTED);
	gv->addEdge(2, 4, 3, EdgeType::DIRECTED);
	gv->addEdge(3, 3, 5, EdgeType::DIRECTED);
	gv->addEdge(4, 3, 2, EdgeType::DIRECTED);
	gv->addEdge(5, 2, 5, EdgeType::DIRECTED);
	TransportLine * t1 = new TransportLine(1, 1, "Rua dos malmequeres", "False", rand() % 6 + 5);
	t1->addLines("205"); t1->setType("bus");
	TransportLine * t2 = new TransportLine(2, 3, "Rua dos benditos", "False", rand() % 6 + 5);
	t2->addLines("205,206"); t2->setType("metro");
	TransportLine * t3 = new TransportLine(4, 5, "Rua das carvalhas", "False", rand() % 6 + 5);
	t3->addLines("207"); t3->setType("bus");
	g.addTransportationLine(t1);
	g.addTransportationLine(t2);
	g.addTransportationLine(t3);
	g.dijkstraLessTransportsUsed(1);
	vector<int> path = g.getPath(1, 5);
	for (int i = 0; i < path.size(); i++) {
		cout << " " << path[i] << " ";
	}
}
void testDijkstraTime(Graph &g, GraphViewer *gv) {
	Point p;
	p.x = 10; p.y = 20;
	g.addNode(1, p);
	gv->addNode(1, p.x, p.y);
	p.x = 20; p.y = 30;
	g.addNode(2, p);
	gv->addNode(2, p.x, p.y);
	p.x = 50; p.y = 70;
	g.addNode(3, p);
	gv->addNode(3, p.x, p.y);
	p.x = 100; p.y = 10;
	g.addNode(4, p);
	gv->addNode(4, p.x, p.y);
	p.x = 10; p.y = 100;
	g.addNode(5, p);
	gv->addNode(5, p.x, p.y);
	g.addEdge(1, 1, 4);
	g.addEdge(2, 4, 3);
	g.addEdge(3, 3, 5);
	g.addEdge(4, 3, 2);
	g.addEdge(5, 2, 5);
	gv->addEdge(1, 1, 4, EdgeType::DIRECTED);
	gv->addEdge(2, 4, 3, EdgeType::DIRECTED);
	gv->addEdge(3, 3, 5, EdgeType::DIRECTED);
	gv->addEdge(4, 3, 2, EdgeType::DIRECTED);
	gv->addEdge(5, 2, 5, EdgeType::DIRECTED);
	TransportLine * t1 = new TransportLine(1, 1, "Rua dos malmequeres", "False", rand() % 6 + 5);
	t1->addLines("205"); t1->setType("bus");
	TransportLine * t2 = new TransportLine(2,3, "Rua dos benditos", "False", rand() % 6 + 5);
	t2->addLines("205,206"); t2->setType("bus");
	TransportLine * t3 = new TransportLine(4,5, "Rua das carvalhas", "False", rand() % 6 + 5);
	t3->addLines("207"); t3->setType("bus");
	g.addTransportationLine(t1); 
	g.addTransportationLine(t2);
	g.addTransportationLine(t3);
	gv->setEdgeLabel(1, t1->toString());
	gv->setEdgeLabel(2, t2->toString());
	gv->setEdgeLabel(3, t2->toString());
	gv->setEdgeLabel(4, t3->toString());
	gv->setEdgeLabel(5, t3->toString());
	g.dijkstraShortestPath_time(1);
	vector<int> path = g.getPath(1, 5);

	cout << "Path : ";
	for (int i = 0; i < path.size(); i++) {
		cout << path.at(i) << " | ";
	}


}

void testReadGraph(Graph &g) {
	clock_t begin = clock();
	g.dijkstraShortestPath_distance(1);
	clock_t end = clock();
	cout << double(end - begin) / CLOCKS_PER_SEC << "s";
	vector<int> path = g.getPath(1,150);

}

int main() {
	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	readFiles(graph, gv);
	//testDijkstraTime(graph,gv);
	//readFiles(graph,gv);
	//testReadGraph(graph);
	//testDijkstraNumTransportsUsed(graph, gv);
	//testDijkstraTime(graph, gv);
	printf("Press to continue...\n");
	getchar();
	return 0;
}
