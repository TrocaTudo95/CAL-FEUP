#pragma once

#ifdef linux
#define OS 0;
#else
#define OS 1;
#endif

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
#define TAB_SPACE_INITIAL "     "
#define TAB_SPACE "         "
#define WALKING_LIMIT 0.5

const int WIDTHOFGRAPH = 1920;
const int HEIGHTOFGRAPH = 1080;


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------READ FILES AREA --------------------------------------------------------------*/

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
	int id = 0;
	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		if (id!=0) {
			linestream >> finalEdge;
			TransportLine * tl = new TransportLine(id,initialEdge, finalEdge - 1, streetName, bidirectional,(rand()%6 +5)*60);
			if (lines.size() > 0) {
				tl->addLines(lines);
				tl->setType(typeOfLine);
			}
			graph.addTransportationLine(tl);
			initialEdge = finalEdge;
			
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
		id++;
	}
	inFile.close();
	graph.setReverseTransportationLines();
}

void readFiles(Graph &graph, GraphViewer *gv) {
	double time_spent;

	clock_t begin = clock();
	readNodesFile(graph, gv);
	clock_t end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Nodes Read In: " << time_spent << " seconds.\n";


	begin = clock();
	readEdgesFile(graph, gv);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Edges Read In: " << time_spent << " seconds.\n";
	

	begin = clock();
	readNamesFile(graph);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Names Read In: " << time_spent << " seconds.\n";
	gv->rearrange();
}

/*------------------------------------------------------READ FILES AREA --------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/


void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTHOFGRAPH, HEIGHTOFGRAPH);
	gv->defineEdgeColor(EDGE_COLOR_DEFAULT);
	gv->defineVertexColor(VERTEX_COLOR_DEFAULT);
}


void printPath(vector<PathTo> path, string type, GraphViewer *gv);
void testSPFA(Graph &g, GraphViewer *gv);
void testDijkstraShortestDistance(Graph &g, GraphViewer *gv);
void testDijkstraBestTime(Graph &g, GraphViewer *gv);
void testDijkstraBestTimeWithWaitingTime(Graph &g, GraphViewer *gv);
void testDijkstraBestTimeWithFavoriteTransport(Graph &g, GraphViewer *gv, char favorite);
void testDijkstraBestTimeWithFavoriteTransportAndWaitingTime(Graph &g, GraphViewer *gv, char favorite);

void exitFunction(Graph &graph, GraphViewer *gv);
void cleanScreen();
void displayTimeTravel(Graph &graph, GraphViewer *gv);
void displayMenu(Graph &graph, GraphViewer *gv);


int main() {
	/*#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	system("chcp 65001");
	#endif*/

	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	readFiles(graph, gv);
	//displayMenu(graph, gv);
	testDijkstraShortestDistance(graph, gv);
	return 0;
}


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------TEST ALGORITHMS AREA --------------------------------------------------------------*/


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
		Sleep(16);
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

	system("pause");
	for (int i = 1; i < path.size(); i++)
	{
		PathTo p = path.at(i);
		gv->setVertexColor(p.path, "yellow");
	}
	gv->rearrange();
}


void testSPFA(Graph &g, GraphViewer *gv) {
	int initialVertex = 482, finalVertex = 775;
	clock_t begin = clock();
	//Testing SPFA
	g.preprocessGraphForSPFA();
	g.SPFAWithAdjacencyList(initialVertex,finalVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "SPFA Distance Calculated In: " << time_spent << " seconds.\n";
	vector<int> path = g.getPathForSPFA(initialVertex, finalVertex);
	gv->setVertexColor(initialVertex, "black");
	for (int i = 0; i < path.size(); i++) {
		cout << "Go To Node " << path[i] << ";\n";
	}
	gv->setVertexColor(finalVertex, "black");
	system("pause");
}

void testDijkstraShortestDistance(Graph &g, GraphViewer *gv) {

	int initialVertex = 482, finalVertex = 775;
	clock_t begin = clock();
	//Testing dijkstra optimized by Elipse
	g.dijkstraShortestDistance(initialVertex, finalVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Shortest Distance Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	gv->setVertexColor(initialVertex, "black");
	printPath(path, "meters", gv);
	gv->setVertexColor(finalVertex, "black");
}

void testDijkstraBestTime(Graph &g, GraphViewer *gv) {
	int initialVertex = 187, finalVertex = 673;
	clock_t begin = clock();
	g.dijkstraBestTime(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	if (g.checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	gv->setVertexColor(initialVertex, "black");
	printPath(path, "seconds", gv);
	gv->setVertexColor(finalVertex, "black");
}

void testDijkstraBestTimeWithWaitingTime(Graph &g, GraphViewer *gv) {
	clock_t begin, end; double time_spent;
	Graph * copiedGraph = g.copy();
	cout << "Preprocessing graph...\n";
	begin = clock();
	copiedGraph->preprocessGraphForWaitingTimes();
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Graph Preprocessed In: " << time_spent << " seconds.\n";
	int initialVertex = 187, finalVertex = 673;
	begin = clock();
	copiedGraph->dijkstraBestTimeWithWaitingTime(initialVertex);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time and Avg. Waiting Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = copiedGraph->getPath(initialVertex, finalVertex);
	if (copiedGraph->checkWalkPercentage(initialVertex, finalVertex,WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT*100 << "% of the way"<< endl;
	}
	gv->setVertexColor(initialVertex, "black");
	printPath(path, "seconds", gv);
	gv->setVertexColor(finalVertex, "black");
	delete copiedGraph;

}

void testDijkstraBestTimeWithFavoriteTransport(Graph &g, GraphViewer *gv, char favorite)
{
	int initialVertex = 187, finalVertex = 673;
	clock_t begin = clock();
	g.dijkstraBestTimeWithFavoriteTransport(initialVertex,favorite);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time,Fav.Transport Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	if (g.checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	gv->setVertexColor(initialVertex, "black");
	printPath(path, "seconds", gv);
	gv->setVertexColor(finalVertex, "black");
}

void testDijkstraBestTimeWithFavoriteTransportAndWaitingTime(Graph &g, GraphViewer *gv, char favorite)
{
	Graph * copiedGraph = g.copy();
	copiedGraph->preprocessGraphForWaitingTimes();
	int initialVertex = 187, finalVertex = 673;

	clock_t begin = clock();
	copiedGraph->dijkstraBestTimeWithFavoriteTransportAndWaitingTime(initialVertex,favorite);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time,Fav.Transport and Avg. Waiting Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = copiedGraph->getPath(initialVertex, finalVertex);
	if (copiedGraph->checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	gv->setVertexColor(initialVertex, "black");
	printPath(path, "seconds", gv);
	gv->setVertexColor(finalVertex, "black");
	delete copiedGraph;
}



/*-------------------------------------------------TEST ALGORITHMS AREA --------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------USER INTERFACE AREA------------------------------------------------------------------*/

void exitFunction(Graph &graph, GraphViewer *gv) {
	exit(1);
}

void cleanScreen() {
	system("CLS");
}

void displayTimeTravel(Graph &graph, GraphViewer *gv) {
	cleanScreen();
	void(*functions[2])(Graph &graph, GraphViewer* gv) = { &testDijkstraBestTime, &testDijkstraBestTimeWithWaitingTime };
	cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
	cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
	cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
	cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.1. Sem tempo de espera" << endl;
	cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.2. Com tempo de espera" << endl;
	cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
	cout << TAB_SPACE << "*. Minimizacao ..." << endl;
	cout << TAB_SPACE << "0. Back" << endl;
	cout << endl << "Escolha uma opcao: ";
	int option;
	cin >> option;
	if (cin.fail())
	{
		cout << endl << "Introduza uma opcao valida!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
	}
	if (option >= 1 && option < 3)
		functions[--option](graph, gv);
}

void displayMenu(Graph &graph, GraphViewer *gv) {
	void(*functions[4])(Graph &graph, GraphViewer* gv) = {
		&exitFunction,
		&testDijkstraShortestDistance,
		&displayTimeTravel,
		&exitFunction };
	while (1)
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
		cout << TAB_SPACE << "1. Minimizacao da distância a percorrer" << endl;
		cout << TAB_SPACE << "2. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << "3. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "4. Minimizacao ..." << endl;
		cout << TAB_SPACE << "0. Exit" << endl;
		cout << endl << "Escolha uma opcao: ";
		int option;
		cin >> option;
		if (option >= 0 && option < 4)
			functions[option](graph, gv);
	}
}

/*-----------------------------------------------USER INTERFACE AREA------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/



