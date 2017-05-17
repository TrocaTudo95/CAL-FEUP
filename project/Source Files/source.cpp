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
#include <iomanip>
#include "graphviewer.h"
#include "graph.hpp"
#include "string_utils.h"

 /*CONSTANTS */

#define EDGE_COLOR_DEFAULT GRAY
#define VERTEX_COLOR_DEFAULT YELLOW
string NODES_FILENAME;
string EDGES_FILENAME;
string LINES_FILENAME;
string METER_PER_PIXEL_FILENAME;
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
		gv->setVertexLabel(idNo, to_string(idNo));
		graph.addNode(idNo, point);
	}
	inFile.close();
}


void readNamesFile(Graph &graph) {
	ifstream inFile;
	openFile(inFile, LINES_FILENAME);
	int initialEdge, finalEdge;
	string line, junk, streetName, bidirectional, lines, typeOfLine;
	int id = 0;
	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		if (id!=0) {
			linestream >> finalEdge;
			Street * tl = new Street(id,initialEdge, finalEdge - 1, streetName, bidirectional,(rand()%5 +3)*60);

			if (lines.size() > 0) {
				tl->addLines(lines);
				tl->setType(typeOfLine);
			}
			graph.addTransportationLine(tl);
			initialEdge = finalEdge;

		}
		else {
			linestream >> initialEdge;
		}
		id++;
		std::getline(linestream, junk, ';');
		std::getline(linestream, streetName, ';');
		std::getline(linestream, bidirectional, ';');
		std::getline(linestream, lines, ';');
		std::getline(linestream, typeOfLine, ';');

	}
	inFile.close();
	graph.setReverseTransportationLines();
}

void readFiles(Graph &graph, GraphViewer *gv) {

	readMeter_Per_Pixel(graph);
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

void printPath(vector<PathTo> path, string type, GraphViewer *gv) {
	double previousDist = 0;
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
		cout << "Go by " << message << " to node " << p.path << " in " << fixed << setprecision(1) << p.dist - previousDist << " " << units << " \n";
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


void testSPFA(Graph &g, GraphViewer *gv) {
	clock_t begin = clock();
	//Testing SPFA
	g.preprocessGraphForSPFA();
	g.SPFAWithAdjacencyList(initialVertex,finalVertex);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "SPFA Distance Calculated In: " << time_spent << " seconds.\n";
	vector<int> path = g.getPathForSPFA(initialVertex, finalVertex);
	for (int i = 1; i < path.size() - 1; i++) {
		cout << "Go To Node " << path[i] << ";\n";
	}
	system("pause");
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
	double option;
	cout << endl << "Custo Máximo da viagem? (0 - Significa sem limite de Custo)" << endl;
	cin >> option;
	while (cin.fail() || option <= 0)
	{
		cout << endl << "Introduza uma opcao valida!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Custo Máximo da viagem?" << endl;
		cin >> option;
	}
	clock_t begin, end; double time_spent;
	Graph * copiedGraph = g.copy();
	cout << "Preprocessing graph...\n";
	begin = clock();
	copiedGraph->preprocessGraphForWaitingTimes();
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Graph Preprocessed In: " << time_spent << " seconds.\n";
	begin = clock();
	copiedGraph->dijkstraBestTimeWithWaitingTime(initialVertex,option);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

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


void testDijkstraCost(Graph &g, GraphViewer *gv, char favorite, const double &maxcost) {
	Graph * copiedGraph = g.copy();
	copiedGraph->preprocessGraphForWaitingTimes();

	clock_t begin = clock();
	copiedGraph->dijkstraBestTimeWithWaitingTimeCostandFavoriteTransport(initialVertex, maxcost, favorite);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Dijkstra Best Time,Fav.Transport, Avg. Waiting Time and Max Cost Calculated In: " << time_spent << " seconds.\n";
	vector<PathTo> path = copiedGraph->getPath(initialVertex, finalVertex);
	if (copiedGraph->checkWalkPercentage(initialVertex, finalVertex, WALKING_LIMIT))
	{
		cout << "You walked more than " << WALKING_LIMIT * 100 << "% of the way" << endl;
	}
	printPath(path, "seconds", gv);
	delete copiedGraph;
}


/*-------------------------------------------------TEST ALGORITHMS AREA --------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------USER INTERFACE AREA------------------------------------------------------------------*/

void cleanScreen() {
	system("CLS");
}

void displayBestTimeWithFavorite(Graph &graph, GraphViewer *gv) {
	void(*functions[3])(Graph &graph, GraphViewer* gv, char favorite) = {
		NULL,
		&testDijkstraBestTimeWithFavoriteTransport,
		&testDijkstraBestTimeWithFavoriteTransportAndWaitingTime };
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Sem Transporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Com Transporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.1. Sem tempo de espera" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.2. Com tempo de espera" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "*. Minimizacao do Custo" << endl;
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

void displayCost(Graph &graph, GraphViewer *gv) {
	double option = 0;
	cout << endl << "Quanto pretende gastar?: ";
	cin >> option;
	while (cin.fail())
	{
		cout << endl << "Introduza uma opcao valida!" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> option;
	}
	char favorite;
	do
	{
		cout << endl << "Qual o Transporte Favorito? W - Walk; B - Bus; T - Metro\n";
		cin >> favorite;
	} while (favorite != 'W' && favorite != 'B' && favorite != 'T');
	testDijkstraCost(graph, gv, favorite, option);
}

void displayBestTimeWithoutFavorite(Graph &graph, GraphViewer *gv) {
	void(*functions[3])(Graph &graph, GraphViewer* gv) = {
		NULL,
		&testDijkstraBestTime,
		&testDijkstraBestTimeWithWaitingTime };
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Sem Tranporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.1. Sem tempo de espera" << endl;
		cout << TAB_SPACE << TAB_SPACE << "3.2.2. Com tempo de espera" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "*.*. Com Tranporte Favorito" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "*. Minimizacao do Custo" << endl;
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

void displayTimeTravel(Graph &graph, GraphViewer *gv) {
	void(*functions[3])(Graph &graph, GraphViewer* gv) = {
		NULL,
		&displayBestTimeWithoutFavorite,
		&displayBestTimeWithFavorite };
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl << endl;
		cout << TAB_SPACE << "*. Minimizacao da distancia a percorrer" << endl;
		cout << TAB_SPACE << "*. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.1. Sem Tranporte Favorito" << endl;
		cout << TAB_SPACE << TAB_SPACE_INITIAL << "2.2. Com Tranporte Favorito" << endl;
		cout << TAB_SPACE << "*. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "*. Minimizacao do Custo" << endl;
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
	void(*functions[5])(Graph &graph, GraphViewer* gv) = {
		NULL,
		&testDijkstraShortestDistance,
		&displayTimeTravel,
		&testDijkstraNumTransportsUsed,
		&displayCost };
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Escolha a Minimizacao a efetuar:" << endl << endl;
		cout << TAB_SPACE << "1. Minimizacao da distância a percorrer" << endl;
		cout << TAB_SPACE << "2. Minimizacao do tempo de viagem" << endl;
		cout << TAB_SPACE << "3. Minimizacao das mudancas de linha de transporte" << endl;
		cout << TAB_SPACE << "4. Minimizacao do Custo" << endl;
		cout << TAB_SPACE << "0. Select Other Nodes" << endl;
		cout << endl << "Escolha uma opcao: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option > 0 && option < 5)
			functions[option](graph, gv);
	} while (option != 0);
}

void selectVertex(Graph &graph, GraphViewer* gv) {
	if (initialVertex != -1)
	{
		gv->setVertexColor(initialVertex, VERTEX_COLOR_DEFAULT);
		initialVertex = -1;
	}
	if (finalVertex != -1)
	{
		gv->setVertexColor(finalVertex, VERTEX_COLOR_DEFAULT);
		finalVertex = -1;
	}
	while (initialVertex == -1 || finalVertex == -1)
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Selecao de Nos" << endl << endl;
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



void searchVertexByName(Graph &graph, GraphViewer *gv){
	vector<Street*>(*functions[3])(const hashTL &streets,const string &streetName) = { NULL, NULL, &aproximado};
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Selecione a pesquisa pretendida" << endl << endl;
		cout << TAB_SPACE << "1. Pesquisa Exata\n";
		cout << TAB_SPACE << "2. Pesquisa Aproximada\n";
		cout << TAB_SPACE << "0. Back\n";
		cout << endl << "Escolha uma opcao: ";
		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (option > 0 && option < 3)
		{
			string streetName;
			cout << "Insera o nome da rua\n";
			cin.ignore();
			getline(cin, streetName);
			while (streetName.size() == 0)
			{
				cin.ignore();
				getline(cin, streetName);
			}
			vector<Street *> topStreets =
				functions[option](graph.getStreets(), streetName);

			for (vector<Street *>::iterator it = topStreets.begin(); it != topStreets.begin(); it++)
			{
				cout << (*it)->getName() << endl;
			}
		}
	} while (option != 0);
}

void startMenu(Graph &graph, GraphViewer *gv) {
	void(*functions[4])(Graph &graph, GraphViewer* gv) = {NULL, &selectVertex,&searchVertexByName, &displayMenu};
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Bem vindo ao Sistema MultiModal" << endl << endl;
		cout << TAB_SPACE << "1. Selecione Nodes by ID" << endl;
		cout << TAB_SPACE << "2. Selecione Nodes by Name" << endl;
		cout << TAB_SPACE << "3. Escolha do Caminho a Percorrer" << endl;
		cout << TAB_SPACE << "0. Exit" << endl;
		cout << endl << "Escolha uma opcao: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		if (initialVertex != -1 && finalVertex != -1 && option == 3)
			functions[option](graph, gv);
		else if (initialVertex != -1 && finalVertex != -1 && option == 4)
			testSPFA(graph, gv);
		if (option == 1)
			functions[option](graph, gv);
		else if (option ==2){
			functions[option](graph,gv);
		}
	} while (option != 0);
}

void selectGraphToLoad() {
	int option;
	do
	{
		cleanScreen();
		cout << endl << TAB_SPACE_INITIAL << "Bem vindo ao Sistema MultiModal" << endl;
		cout << TAB_SPACE << "Selecione Nodes o Mapa desejado:" << endl << endl;
		cout << TAB_SPACE << "1. Aliados        - N: 820;   A: 850" << endl;
		cout << TAB_SPACE << "2. FEUP           - N: 1987;  A: 2172" << endl;
		cout << TAB_SPACE << "3. FEUP2          - N: 3693;  A: 4036" << endl;
		cout << TAB_SPACE << "4. Campo Alegre   - N: 6739;  A: 7107" << endl;
		cout << TAB_SPACE << "5. Porto          - N: 13164; A: 14303" << endl;
		cout << endl << "Escolha uma opcao: ";

		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
		}
		switch (option)
		{
		case 1:
			NODES_FILENAME = "aliados_nos.txt";
			EDGES_FILENAME = "aliados_arestas.txt";
			LINES_FILENAME = "aliados_names.txt";
			METER_PER_PIXEL_FILENAME = "aliados_meter_per_pixel.txt";
			option = 0;
			break;
		case 2:
			NODES_FILENAME = "feup_nos.txt";
			EDGES_FILENAME = "feup_arestas.txt";
			LINES_FILENAME = "feup_names.txt";
			METER_PER_PIXEL_FILENAME = "feup_meter_per_pixel.txt";
			option = 0;
			break;
		case 3:
			NODES_FILENAME = "feup2_nos.txt";
			EDGES_FILENAME = "feup2_arestas.txt";
			LINES_FILENAME = "feup2_names.txt";
			METER_PER_PIXEL_FILENAME = "feup2_meter_per_pixel.txt";
			option = 0;
			break;
		case 4:
			NODES_FILENAME = "campo_alegre_nos.txt";
			EDGES_FILENAME = "campo_alegre_arestas.txt";
			LINES_FILENAME = "campo_alegre_names.txt";
			METER_PER_PIXEL_FILENAME = "campo_alegre_meter_per_pixel.txt";
			option = 0;
			break;
		case 5:
			NODES_FILENAME = "centro_nos.txt";
			EDGES_FILENAME = "centro_arestas.txt";
			LINES_FILENAME = "centro_names.txt";
			METER_PER_PIXEL_FILENAME = "centro_meter_per_pixel.txt";
			option = 0;
			break;
		default:
			break;
		}
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
	selectGraphToLoad();
	readFiles(graph, gv);
	startMenu(graph, gv);
	return 0;
}
