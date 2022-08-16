//
//  PDB.h
//  ActiveSiteFinder
//
//  Created by saman on 7/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef ActiveSiteFinder_PDB_h
#define ActiveSiteFinder_PDB_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"

#define NUMBER_OF_CLASSES 5

using namespace std;

class PDB {
private:

	vector<string> allaminos;
	// 2D vectors in which each row defines a specific class
	vector<vector<int> > aminos;
	vector<vector<string> > aminosName;
	vector<vector<float> > X;
	vector<vector<float> > Y;
	vector<vector<float> > Z;
	vector<float> xs;
	vector<float> ys;
	vector<float> zs;
	vector<vector<char> > chain;
public:
	vector<int> aminosNumber;
	vector<char> aminosChain;

	PDB(Parser&);
	~PDB();
	int getRealNumber(int aminosNumber, char chain);
	int getNumberOfAminos();
	string getAllAminos(int place);
	int getAmino(int classNumber, int place);
	string getAminoName(int classNumber, int place);
	char getChain(int classNumber, int place);
	float getX(int classNumber, int place);
	float getY(int classNumber, int place);
	float getZ(int classNumber, int place);
	void printResult();
	int getNumberOfAminosOfClass(int classNumber);
	void getXYZOfAmino(int classNumber, int resSeq, char Chain, float* x,
			float* y, float* z);
	void getXYZOfAmino(int place, float* x, float* y, float* z);

};

#endif
