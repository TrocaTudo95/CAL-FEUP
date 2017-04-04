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
	if(openFile(inFile, NODES_FILENAME));

	int idNo = 0;
	Point point;
	std::string line;

	while (std::getline(inFile, line))
	{
		std::istringstream linestream(line);
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
	if (openFile(inFile, LINES_FILENAME));
	std::string line;
	int idEdge;
	string streetName;
	string bidirectional;
	string lines;
	string typeOfLine;
	while (std::getline(inFile, line))
	{
		size_t previousSeparator = line.find(';');
		size_t nextSeparator;
		
		if (previousSeparator != string::npos) {
			idEdge = stoi(line.substr(0, previousSeparator));
			
		}
		if ((nextSeparator = line.find(';', previousSeparator + 1)) != string::npos) {
			streetName = line.substr(previousSeparator+1, nextSeparator - previousSeparator-1);
			previousSeparator = nextSeparator;
		}
		if ((nextSeparator = line.find(';', previousSeparator + 1)) != string::npos) {
			bidirectional = line.substr(previousSeparator+1, nextSeparator - previousSeparator - 1);
			previousSeparator = nextSeparator;
		}

		TransportLine * tl = new TransportLine(idEdge, streetName, bidirectional);

		graph.getEdgeById(idEdge)->setTransportLine(tl);
	

		if ((nextSeparator = line.find(';', previousSeparator + 1)) != string::npos) {
			lines = line.substr(previousSeparator+1, nextSeparator - previousSeparator - 1);
			previousSeparator = nextSeparator;
		}
		if (lines.size() > 0) {
			tl->addLines(lines);
			typeOfLine = line.substr(previousSeparator+1);
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

int main() {
	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	readFiles(graph, gv);
	printf("Press to continue...\n");
	getchar();
	return 0;
}
