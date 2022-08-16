/*
 * Graph.h
 *
 *  Created on: Feb 24, 2019
 *      Author: niloufar
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Graph {
	private:
		int graphSize;
		vector<string> nodeArray;
		vector<string> edge1Array;
		vector<string> edge2Array;
		void deleteEdge(string node1, string node2);
	public:
		void addEdge(string node1, string node2);
		void addNode(string node);
		void addUEdge(string node1, string node2);
		int connectedComponents(void);
		int checkNode(string node);
		int checkEdge(string node1 , string node2);
		void deleteNode(string node);
		void deleteUEdge(string node1, string node2);
		void printNodeList(void);
		Graph(int size); //Constructor of the class
};

#endif /* GRAPH_H_ */
