#include <cstdio>
#include "graphviewer.h"
#include "readFiles.cpp"

/* CONSTANTS */

#define EDGE_COLOR_DEFAULT "blue"
#define VERTEX_COLOR_DEFAULT "yellow"

const int WIDTHOFGRAPH = 1920;
const int HEIGHTOFGRAPH = 1080;



void initGV(GraphViewer *gv) {
	gv->createWindow(WIDTHOFGRAPH, HEIGHTOFGRAPH);
	gv->defineEdgeColor(EDGE_COLOR_DEFAULT);
	gv->defineVertexColor(VERTEX_COLOR_DEFAULT);
}

void run()
{
	GraphViewer *gv = new GraphViewer(WIDTHOFGRAPH, HEIGHTOFGRAPH, false);
	initGV(gv);

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile)
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string   line;

	int idNo = 0;
	int X = 0; 
	int Y = 0;

	while (std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string         data;

		linestream >> idNo;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y;
		gv->addNode(idNo, X, Y);
	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile)
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

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
		gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::UNDIRECTED);

	}

	inFile.close();

	gv->rearrange();
}

int main() {
	run();
	printf("Press to continue...\n");
	getchar();
	return 0;
}
