#pragma once
#include <iostream>
#include <cassert>
#include "graph.hpp"
#include "graphviewer.h"
#include "graph.hpp"

const int WIDTH = 1920;
const int HEIGHT = 1080;

#define EDGE_COLOR "blue"
#define VERTEX_COLOR "yellow"

void initGV(GraphViewer *gv);

void testDijkstraShortestDistance();