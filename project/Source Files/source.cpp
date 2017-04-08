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

#define EDGE_COLOR_DEFAULT GRAY
#define VERTEX_COLOR_DEFAULT YELLOW
#define NODES_FILENAME "nos.txt"
#define EDGES_FILENAME "arestas.txt"
#define LINES_FILENAME "names.txt"
#define METER_PER_PIXEL_FILENAME "meter_per_pixel.txt"
#define TAB_SPACE_INITIAL "     "
#define TAB_SPACE "         "
#define WALKING_LIMIT 0.5

const int WIDTHOFGRAPH = 1920;
const int HEIGHTOFGRAPH = 1080;

int initialVertex = -1;
int finalVertex = -1;

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

void readMeter_Per_Pixel(Graph &graph) {
	ifstream inFile;
	openFile(inFile, METER_PER_PIXEL_FILENAME);
	std::string line;
	getline(inFile, line);
	double d = stod(line.substr());
	graph.setMETER_PER_PIXEL_X(d);
	getline(inFile, line);
	d = stod(line.substr());
	graph.setMETER_PER_PIXEL_Y(d);
	inFile.close();
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
		gv->setVertexLabel(idNo, to_string(idNo));
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
			TransportLine * tl = new TransportLine(initialEdge, finalEdge - 1, streetName, bidirectional,(rand()%6 +5)*60);
			if (lines.size() > 0) {
				tl->addLines(lines);
				tl->setType(typeOfLine);
			}
			graph.addTransportationLine(tl, edgeMap);
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
	}
	inFile.close();
}

void readFiles(Graph &graph, GraphViewer *gv) {
	readMeter_Per_Pixel(graph);
	readNodesFile(graph, gv);
	unordered_map<int, pair<int, int>> edgeInfo;
	readEdgesFile(graph, gv, edgeInfo);
	readNamesFile(graph, edgeInfo);
	gv->rearrange();
}

/*------------------------------------------------------READ FILES AREA --------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/

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
		if (i != path.size() - 1)
			gv->setVertexColor(p.path, GREEN);
		gv->rearrange();
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
	for (int i = 1; i < path.size() - 1; i++)
	{
		PathTo p = path.at(i);
		gv->setVertexColor(p.path, VERTEX_COLOR_DEFAULT);
	}
	gv->rearrange();
}


void testDijkstraShortestDistance(Graph &g, GraphViewer *gv) {

	clock_t begin = clock();
	//Testing dijkstra optimized by Elipse
	g.dijkstraShortestDistance(initialVertex, finalVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Shortest Distance Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	printPath(path, "meters", gv);
}

void testDijkstraBestTime(Graph &g, GraphViewer *gv) {
	clock_t begin = clock();
	g.dijkstraBestTime(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	if (g.checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	printPath(path, "seconds", gv);
}

void testDijkstraBestTimeWithWaitingTime(Graph &g, GraphViewer *gv) {
	Graph * copiedGraph = g.copy();
	copiedGraph->preprocessGraphForWaitingTimes();

	clock_t begin = clock();
	copiedGraph->dijkstraBestTime(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time and Avg. Waiting Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = copiedGraph->getPath(initialVertex, finalVertex);
	if (copiedGraph->checkWalkPercentage(initialVertex, finalVertex,WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT*100 << "% of the way"<< endl;
	}
	printPath(path, "seconds", gv);
	delete copiedGraph;

}

void testDijkstraBestTimeWithFavoriteTransport(Graph &g, GraphViewer *gv, char favorite)
{
	clock_t begin = clock();
	g.dijkstraBestTimeWithFavoriteTransport(initialVertex,favorite);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time,Fav.Transport Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	if (g.checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	printPath(path, "seconds", gv);
}

void testDijkstraBestTimeWithFavoriteTransportAndWaitingTime(Graph &g, GraphViewer *gv, char favorite)
{
	Graph * copiedGraph = g.copy();
	copiedGraph->preprocessGraphForWaitingTimes();

	clock_t begin = clock();
	copiedGraph->dijkstraBestTimeWithFavoriteTransportAndWaitingTime(initialVertex,favorite);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time,Fav.Transport and Avg. Waiting Time Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = copiedGraph->getPath(initialVertex, finalVertex);
	if (copiedGraph->checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT)) {
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	printPath(path, "seconds", gv);
	delete copiedGraph;
}

void testDijkstraNumTransportsUsed(Graph &g, GraphViewer *gv) {

	clock_t begin = clock();
	g.dijkstraLessTransportsUsed(initialVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	vector<PathTo> path = g.getPath(initialVertex, finalVertex);
	printPath(path, "transport changes", gv);
}


void runTestSuite(Graph &g, GraphViewer *gv) {
	readFiles(g, gv);
	testDijkstraShortestDistance(g, gv);
	testDijkstraShortestDistance(g, gv);
}


/*-------------------------------------------------TEST ALGORITHMS AREA --------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------USER INTERFACE AREA------------------------------------------------------------------*/

void cleanScreen() {
	system("CLS");
}

void displayTimeTravel(Graph &graph, GraphViewer *gv) {
	int option;
	do
	{
		cleanScreen();
		void(*functions[3])(Graph &graph, GraphViewer* gv) = { 
			NULL,
			&testDijkstraBestTime,
			&testDijkstraBestTimeWithWaitingTime };
		cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.1. Sem tempo de espera" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.2. Com tempo de espera" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "*. Minimizacao ..." << endl;
		cout << TAB_SPACE << "0. Back" << endl;
		cout << endl << "Escolha uma opcao: ";
		cin >> option;
		if (cin.fail())
		{
			cout << endl << "Introduza uma opcao valida!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option >= 1 && option < 3)
			functions[option](graph, gv);
	} while (option != 0);
}

void displayLessTransportTravelWithFavorite(Graph &graph, GraphViewer *gv) {
	void(*functions[3])(Graph &graph, GraphViewer* gv, char favorite) = {
		NULL,
		&testDijkstraBestTimeWithFavoriteTransport, 
		&testDijkstraBestTimeWithFavoriteTransportAndWaitingTime };
	int option;
	do
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Sem Tranporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Com Tranporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.1. Sem tempo de espera" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.2. Com tempo de espera" << endl;
		cout << TAB_SPACE << "*. Minimizacao ..." << endl;
		cout << TAB_SPACE << "0. Back" << endl;
		cout << endl << "Escolha uma opcao: ";
		cin >> option;
		if (cin.fail())
		{
			cout << endl << "Introduza uma opcao valida!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option >= 1 && option < 3)
		{
			cout << endl << "Qual o Transporte Favorito? W - Walk; B - Bus; T - Metro\n";
			char favorite;
			cin >> favorite;
			if (favorite == 'W' || favorite == 'B' || favorite == 'T')
				functions[option](graph, gv, favorite);
		}
	} while (option != 0);
}

void displayLessTransportTravel(Graph &graph, GraphViewer *gv) {
	void(*functions[3])(Graph &graph, GraphViewer* gv) = {
		NULL,
		&testDijkstraNumTransportsUsed,
		&displayLessTransportTravelWithFavorite };
	int option;
	do
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "3.1. Sem Tranporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "3.2. Com Tranporte Favorito" << endl;
		cout << TAB_SPACE << "*. Minimizacao ..." << endl;
		cout << TAB_SPACE << "0. Back" << endl;
		cout << endl << "Escolha uma opcao: ";
		cin >> option;
		if (cin.fail())
		{
			cout << endl << "Introduza uma opcao valida!" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option >= 1 && option < 3)
			functions[option](graph, gv);
	} while (option != 0);
}

void displayMenu(Graph &graph, GraphViewer *gv) {
	void(*functions[4])(Graph &graph, GraphViewer* gv) = {
		NULL,
		&testDijkstraShortestDistance,
		&displayTimeTravel,
		&displayLessTransportTravel };
	int option;
	do
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl;
		cout << TAB_SPACE << "1. Minimizacao da distância a percorrer" << endl;
		cout << TAB_SPACE << "2. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << "3. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "4. Minimizacao ..." << endl;
		cout << TAB_SPACE << "0. Select Other Nodes" << endl;
		cout << endl << "Escolha uma opcao: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option > 0 && option < 4)
			functions[option](graph, gv);
	} while (option != 0);
}

void selectVertex(Graph &graph, GraphViewer* gv) {
	if (initialVertex != -1)
	{
		gv->setVertexColor(initialVertex, VERTEX_COLOR_DEFAULT);
		initialVertex != -1;
	}
	if (finalVertex != -1)
	{
		gv->setVertexColor(finalVertex, VERTEX_COLOR_DEFAULT);
		finalVertex != -1;
	}
	while (initialVertex == -1 || finalVertex == -1)
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Selecao de Nos" << endl;
		cout << TAB_SPACE << "Selecione o Nó de Origem:" << endl;
		cin >> initialVertex;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			initialVertex = -1;
		}
		cout << TAB_SPACE << "Selecione o Nó de Destino" << endl;
		cin >> finalVertex;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			finalVertex = -1;
		}
		if (graph.getNode(initialVertex) == NULL)
		{
			cout << "Nó de Origem não encontrado\n";
			initialVertex = -1;
			system("pause");
		}
		else if (graph.getNode(finalVertex) == NULL)
		{
			cout << "Nó de Destino não encontrado\n";
			finalVertex = -1;
			system("pause");
		}
		gv->setVertexColor(initialVertex, RED);
		gv->setVertexColor(finalVertex, RED);
	}
}

void startMenu(Graph &graph, GraphViewer *gv) {
	void(*functions[4])(Graph &graph, GraphViewer* gv) = {NULL, &selectVertex, &displayMenu};
	int option;
	do
	{
		cleanScreen();
		cout << TAB_SPACE_INITIAL << "Bem vindo ao Sistema MultiModal" << endl;
		cout << TAB_SPACE << "1. Selecione Nodes" << endl;
		cout << TAB_SPACE << "2. Escolha do Caminho a Percorrer" << endl;
		cout << TAB_SPACE << "0. Exit" << endl;
		cout << endl << "Escolha uma opcao: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option > 0 && option < 3)
			functions[option](graph, gv);
	} while (option != 0);
}

/*-----------------------------------------------USER INTERFACE AREA------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/


void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTHOFGRAPH, HEIGHTOFGRAPH);
	gv->defineEdgeColor(EDGE_COLOR_DEFAULT);
	gv->defineVertexColor(VERTEX_COLOR_DEFAULT);
	gv->defineEdgeCurved(false);
}

int main() {
	/*#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	system("chcp 65001");
	#endif*/

	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);
	Graph graph;
	readFiles(graph, gv);
	startMenu(graph, gv);
	return 0;
}