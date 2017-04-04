#pragma once

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphviewer.h"
#include "graph.hpp"

/* CONSTANTS */

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


void readEdgesInfoFile(Graph &graph, GraphViewer *gv) {

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
	int idEdge;
	string line, junk, streetName, bidirectional, lines, typeOfLine;
	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		linestream >> idEdge;
		std::getline(linestream, junk, ';');
		std::getline(linestream, streetName, ';');
		std::getline(linestream, bidirectional, ';');
		std::getline(linestream, lines, ';');
		std::getline(linestream, typeOfLine, ';');

		TransportLine * tl = new TransportLine(idEdge, streetName, bidirectional);
		graph.getEdgeById(idEdge)->setTransportLine(tl);

		if (lines.size() > 0) {
			tl->addLines(lines);
			tl->setType(typeOfLine);
		}
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


int main() {
	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	//readFiles(graph, gv);
	testDijkstraShortestDistance(graph,gv);
	printf("Press to continue...\n");
	getchar();
	return 0;
}
