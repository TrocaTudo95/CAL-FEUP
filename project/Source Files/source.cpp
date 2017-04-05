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


void readEdgesFile(Graph &graph, GraphViewer *gv, unordered_map<int, pair<int,int>> &edgeMap) {
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
		edgeMap.insert(make_pair(idAresta, make_pair(idNoOrigem, idNoDestino)));
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


void readNamesFile(Graph &graph, unordered_map<int, pair<int, int>> &edgeMap) {
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
			graph.addTransportationLine(tl, edgeMap);
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
	unordered_map<int, pair<int, int>> edgeInfo;
	readEdgesFile(graph, gv, edgeInfo);
	readNamesFile(graph, edgeInfo);
	gv->rearrange();
}


void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTHOFGRAPH, HEIGHTOFGRAPH);
	gv->defineEdgeColor(EDGE_COLOR_DEFAULT);
	gv->defineVertexColor(VERTEX_COLOR_DEFAULT);
}



void testDijkstraShortestDistance(Graph &g, GraphViewer *gv);
void testReadGraph(Graph &g);
void testDijkstraTime(Graph &g, GraphViewer *gv);
void testDijkstraNumTransportsUsed(Graph &g, GraphViewer *gv);
void runTestSuite(Graph &g, GraphViewer *gv);
void useTestGraph(Graph &g, GraphViewer *gv);
void printPath(vector<PathTo> path, string type, GraphViewer *gv);


int main() {
	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	runTestSuite(graph,gv);
	printf("Press to continue...\n");
	getchar();
	return 0;
}



void runTestSuite(Graph &g, GraphViewer *gv) {
	readFiles(g, gv);
	//testDijkstraTime(g, gv);
	//testDijkstraShortestDistance(g, gv);
	testDijkstraNumTransportsUsed(g, gv);
}


void useTestGraph(Graph &g, GraphViewer *gv) {
	Point p;
	p.x = 10; p.y = 20;
	g.addNode(1, p);
	gv->addNode(1, p.x, p.y);
	p.x = 12; p.y = 23;
	g.addNode(2, p);
	gv->addNode(2, p.x, p.y);
	p.x = 50; p.y = 70;
	g.addNode(3, p);
	gv->addNode(3, p.x, p.y);
	p.x = 100; p.y = 10;
	g.addNode(4, p);
	gv->addNode(4, p.x, p.y);
	p.x = 100; p.y = 200;
	g.addNode(5, p);
	gv->addNode(5, p.x, p.y);
	g.addEdge(1, 1, 4);
	g.addEdge(2, 4, 3);
	g.addEdge(3, 3, 5);
	g.addEdge(4, 3, 2);
	g.addEdge(5, 2, 3);
	g.addEdge(6, 2, 5);
	gv->addEdge(1, 1, 4, EdgeType::DIRECTED);
	gv->addEdge(2, 4, 3, EdgeType::DIRECTED);
	gv->addEdge(3, 3, 5, EdgeType::DIRECTED);
	gv->addEdge(4, 3, 2, EdgeType::DIRECTED);
	gv->addEdge(5, 2, 3, EdgeType::DIRECTED);
	gv->addEdge(6, 2, 5, EdgeType::DIRECTED);

	TransportLine * t1 = new TransportLine(1, 1, "Rua dos malmequeres", "False", (rand() % 6 + 5) * 60);
	t1->addLines("205"); t1->setType("bus");
	TransportLine * t2 = new TransportLine(2, 3, "Rua dos benditos", "False", (rand() % 6 + 5) * 60);
	t2->addLines("206"); t2->setType("metro");
	TransportLine * t3 = new TransportLine(4, 6, "Rua das carvalhas", "False", (rand() % 6 + 5) * 60);
	t3->addLines("207"); t3->setType("bus");
	g.addTransportationLine(t1);
	g.addTransportationLine(t2);
	g.addTransportationLine(t3);
	gv->setEdgeLabel(1, t1->toString());
	gv->setEdgeLabel(2, t2->toString());
	gv->setEdgeLabel(3, t2->toString());
	gv->setEdgeLabel(4, t3->toString());
	gv->setEdgeLabel(5, t3->toString());
	gv->setEdgeLabel(6, t3->toString());
}

void testDijkstraTime(Graph &g, GraphViewer *gv) {

	int initialVertex = 284, finalVertex = 117;
	clock_t begin = clock();
	g.dijkstraShortestPath_time(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	gv->setVertexColor(initialVertex, "black");
	gv->setVertexColor(finalVertex, "black");
	printPath(path, "seconds", gv);

}

void testDijkstraNumTransportsUsed(Graph &g, GraphViewer *gv) {

	int initialVertex = 655, finalVertex = 313;
	clock_t begin = clock();
	g.dijkstraLessTransportsUsed(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	gv->setVertexColor(initialVertex, "black");
	gv->setVertexColor(finalVertex, "black");
	printPath(path, "transport changes", gv);
}

void testDijkstraShortestDistance(Graph &g, GraphViewer *gv) {

	int initialVertex = 655, finalVertex = 313;
	clock_t begin = clock();
	g.dijkstraShortestPath_distance(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	gv->setVertexColor(initialVertex, "black");
	gv->setVertexColor(finalVertex, "black");
	printPath(path, "meters", gv);
}


void printPath(vector<PathTo> path, string type, GraphViewer *gv) {
	int previousDist = 0;
	string units = type;
	cout << "Start in " << path.at(0).path << "\n";
	for (int i = 1; i < path.size(); i++) {
		PathTo p = path.at(i);
		string message;
		switch (p.wayToGetThere) {
		case 'W':
			message = "walking";
			break;
		case 'T':
			message = "metro";
			break;
		case 'B':
			message = "bus";
			break;
		}
		cout << "Go by " << message << " to node " << p.path << " in " << p.dist - previousDist << " " << units << " \n";
		gv->setVertexColor(p.path, "red");
		gv->rearrange();
		Sleep(100);
		previousDist = p.dist;
	}
	int totalDist = path.at(path.size() - 1).dist;
	if (type == "seconds") {
		cout << "Total Time: " << totalDist / 60 << "m:" << totalDist % 60 << "s \n";
	}
	else if (type == "meters") {
		cout << "Total Distance: " << totalDist << " meters\n";
	}
	else if (type == "transport changes") {
		cout << "Transports Used : " << totalDist << "\n";
	}

}
