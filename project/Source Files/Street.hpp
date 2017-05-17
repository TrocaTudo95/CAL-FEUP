#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "edge.hpp"

using namespace std;

class Graph;
class Node;
class Edge;

class Street {
private:
	int id;
	string name;
	unordered_set<string>lines;
	char type;
	int initialEdgeId;
	int finalEdgeId;
	bool bidirectional;
	int avg_wait_time;
public:
	friend class Edge;
	/**
	* @brief constructor of class Street
	* @param id Street's id
	* @param initialEdgeID represents the id of the first Edge contained in the Street
	* @param finalEdgeID represents the id of the last Edge contained in the Street
	* @param name Street's name
	* @param bidirectional string that represents a boolean with the value true or false to indicate if the Street is bidirectional
	* @param avg_wait_time represent the average waiting time on the Street
	*/
	Street(int id,int initialEdgeID,int finalEdgeID, string name, string bidirectional,int avg_wait_time);
	/**
	* @brief Comparates two TransportationLines by theirs initial and final Edge Id's.
	* @param b Street to comparate with.
	* @return  true if the two TransportLines have the same initial and final Edges.
	*/
	bool operator==(const Street& b) const;
	/**
	* @brief Adds the lines specified in the string line separated by ','  to the unordered_set of lines
	* @param line specifies the lines to be added to the Street unordered_set of lines
	*/
	void addLines(string line);
	/**
	* @brief Sets the unordered_set of lines
	* @param l unordered_set of lines
	*/
	void setLines(unordered_set<string> &l);
	/**
	* @brief Sets the type of Street by a string read from the parser, the type can be walk, bus or tram defined by a char
	* @param type type of Street on a string
	*/
	void setType(string type);
	/**
	* @brief Sets the type of Street by a char
	* @param type transportLine's type
	*/
	void setType(char type);
	/**
	* @brief returns a string that represents a Street
	* @return a string containing the name, the type and all the lines on the unorded_set
	*/
	string toString() const;
	/**
	* @brief get the Street id
	* @return Street's id
	*/
	int getId()const;
	/**
	* @brief get the Initial Edge's id
	* @return Initial Edge's id
	*/
	int getInitialEdgeId() const;
	/**
	* @brief get the Final Edge's id
	* @return Final Edge's id
	*/
	int getFinalEdgeId() const;
	/**
	* @brief get the unorded_set containing all the lines name
	* @return unorded_set containing all the lines names
	*/
	unordered_set<string>& getLines();
	/**
	* @brief get the Street's type
	* @return char representing the type of the Street
	*/
	char getType();
	/**
	* @brief get the Street's average waiting time
	* @return Street's average waiting time in seconds
	*/
	int getWaitTime();
	/**
	* @brief returns a boolean indicating if the Street is bidirectional or not
	* @return true if the Street is bidirectional
	*/
	bool isBidirectional();
	/**
	* @brief creates a new Street with the same name and average time of the current Street
	* @param id Street's id
	* @param initialEdgeId id of the initial edge 
	* @param initialEdgeId id of the final edge
	* @return Street pointer that points to the created Street
	*/
	Street* createReverseWalking(int id, int initialEdgeId, int finalEdgeId);
	/**
	* @brief creates a new Street with the name, average time, type and lines of the current Street
	* @param id Street's id
	* @param initialEdgeId id of the initial edge
	* @param initialEdgeId id of the final edge
	* @return Street pointer that points to the created Street
	*/
	Street* createFullReverse(int id, int initialEdgeId,int finalEdgeId);
	/**
	* @brief creates a new Street with the name, average time, type and lines of the current Street
	* @param edgeMap unorded_map containing a pair of pair TODO
	* @return vector of integers representing the unorded_map nodes' ids 
	*/
	vector<int> getNodesIds(unordered_map<int,pair<Edge*,int>> &edgeMap);

	string getName() {
		return name;
	}
};

