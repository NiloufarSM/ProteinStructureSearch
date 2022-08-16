//
//  PDB.cpp
//  ActiveSiteFinder
//
//  Created by saman on 7/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define DEBUG_MODE 0

#include "PDB.h"

PDB::PDB(Parser& myParser) {

	for (int i = 0; i < NUMBER_OF_CLASSES; i++) {

		aminos.push_back(vector<int>());
		X.push_back(vector<float>());
		Y.push_back(vector<float>());
		Z.push_back(vector<float>());
		chain.push_back(vector<char>());
		aminosName.push_back(vector<string>());

	}

	int in;

	if ( DEBUG_MODE == 1) {
		cout << endl << endl
				<< myParser.models.at(0).chains.at(0).numberOfAminos;
		cout << "we are in PDB constructor." << endl;
	}

	for (int i = 0; i < myParser.models.at(0).numberOfChains; i++) {
		for (int j = 0; j < myParser.models.at(0).chains.at(i).numberOfAminos;
				j++) {
			// checking whether that amino acid is validate or not. we didnt want
			// to calculate coordinates for aminos which their residue number has not
			// been mentioned in PDB file.

			if (myParser.models.at(0).chains.at(i).aminos.at(j).numberOfAtoms
					> 1) {

				float x = 0;
				float y = 0;
				float z = 0;
				int numberOfAtoms =
						myParser.models.at(0).chains.at(i).aminos.at(j).numberOfAtoms;

				// here we must calculate the x, y and z coordinates of our amino acid.
				// because we just have the coordinates of single atoms of each amino acid here I
				// calculate the average of all their coordinates and add it as the real coordinate of
				// the amino acid.

				/* traditional approach
				 for( int k = 0; k < numberOfAtoms; k++ ){
				 x = x + myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(k).X;
				 y = y + myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(k).Y;
				 z = z + myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(k).Z;
				 }

				 // calculating the average

				 x /= numberOfAtoms;
				 y /= numberOfAtoms;
				 z /= numberOfAtoms;
				 */

				x =
						myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								1).X;

				y =
						myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								1).Y;
				z =
						myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								1).Z;
				if ( DEBUG_MODE == 1) {
					cout << "--The amino number is: " << j << endl;
					cout << "--The amino type is: "
							<< myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue << " or "
							<< myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).residue << endl;

					cout << "--The amino resseq is: "
							<< myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq << endl;

				}

				//cin >> in;

				if (myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(0).residue
						== "ARG"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "HIS"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "LYS") {

					aminos.at(0).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).resSeq);
					X.at(0).push_back(x);
					Y.at(0).push_back(y);
					Z.at(0).push_back(z);
					chain.at(0).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).chainID);
					aminosName.at(0).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					allaminos.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					aminosNumber.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq);
					aminosChain.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).chainID);

					xs.push_back(x);
					ys.push_back(y);
					zs.push_back(z);

				} else if (myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
						0).residue == "ASP"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "GLU") {

					aminos.at(1).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).resSeq);
					X.at(1).push_back(x);
					Y.at(1).push_back(y);
					Z.at(1).push_back(z);
					chain.at(1).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).chainID);
					aminosName.at(1).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					allaminos.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					aminosNumber.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq);
					aminosChain.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).chainID);
					xs.push_back(x);
					ys.push_back(y);
					zs.push_back(z);

				} else if (myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
						0).residue == "SER"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "THR"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "ASN"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "GLN") {

					aminos.at(2).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).resSeq);
					X.at(2).push_back(x);
					Y.at(2).push_back(y);
					Z.at(2).push_back(z);
					chain.at(2).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).chainID);
					aminosName.at(2).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					allaminos.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					aminosNumber.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq);
					aminosChain.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).chainID);
					xs.push_back(x);
					ys.push_back(y);
					zs.push_back(z);

				} else if (myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
						0).residue == "CYS"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "SEC"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "GLY"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "PRO") {

					aminos.at(3).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).resSeq);
					X.at(3).push_back(x);
					Y.at(3).push_back(y);
					Z.at(3).push_back(z);
					chain.at(3).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).chainID);
					aminosName.at(3).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					allaminos.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					aminosNumber.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq);
					aminosChain.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).chainID);
					xs.push_back(x);
					ys.push_back(y);
					zs.push_back(z);

				} else if (myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
						0).residue == "ALA"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "ILE"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "LEU"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "MET"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "PHE"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "TRP"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "TYR"
						|| myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
								0).residue == "VAL") {

					aminos.at(4).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).resSeq);
					X.at(4).push_back(x);
					Y.at(4).push_back(y);
					Z.at(4).push_back(z);
					chain.at(4).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).chainID);
					aminosName.at(4).push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					allaminos.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									0).residue);
					aminosNumber.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).resSeq);
					aminosChain.push_back(
							myParser.models.at(0).chains.at(i).aminos.at(j).atoms.at(
									1).chainID);
					xs.push_back(x);
					ys.push_back(y);
					zs.push_back(z);

				}

			}

		}

	}

}

PDB::~PDB() {

}

string PDB::getAllAminos(int place) {
	return allaminos.at(place);
}

int PDB::getAmino(int classNumber, int place) {
	return aminos.at(classNumber).at(place);
}

string PDB::getAminoName(int classNumber, int place) {
	return aminosName.at(classNumber).at(place);
}

char PDB::getChain(int classNumber, int place) {
	return chain.at(classNumber).at(place);
}

float PDB::getX(int classNumber, int place) {
	return X.at(classNumber).at(place);
}

float PDB::getY(int classNumber, int place) {
	return Y.at(classNumber).at(place);
}

float PDB::getZ(int classNumber, int place) {
	return Z.at(classNumber).at(place);
}

void PDB::printResult() {

	cout << "class one aminos: " << endl;
	for (int i = 0; i < aminos.at(0).size(); i++) {
		cout << aminos.at(0).at(i) << " " << chain.at(0).at(i) << " "
				<< X.at(0).at(i) << " " << Y.at(0).at(i) << " " << Z.at(0).at(i)
				<< endl;
	}

	cout << "class two aminos: " << endl;
	for (int i = 0; i < aminos.at(1).size(); i++) {
		cout << aminos.at(1).at(i) << " " << " " << chain.at(1).at(i) << " "
				<< X.at(1).at(i) << " " << Y.at(1).at(i) << " " << Z.at(1).at(i)
				<< endl;
	}

	cout << "class three aminos: " << endl;
	for (int i = 0; i < aminos.at(2).size(); i++) {
		cout << aminos.at(2).at(i) << " " << " " << chain.at(2).at(i) << " "
				<< X.at(2).at(i) << " " << Y.at(2).at(i) << " " << Z.at(2).at(i)
				<< endl;
	}

	cout << "class four aminos: " << endl;
	for (int i = 0; i < aminos.at(3).size(); i++) {
		cout << aminos.at(3).at(i) << " " << " " << chain.at(3).at(i) << " "
				<< X.at(3).at(i) << " " << Y.at(3).at(i) << " " << Z.at(3).at(i)
				<< endl;
	}

	cout << "class five aminos: " << endl;
	for (int i = 0; i < aminos.at(4).size(); i++) {
		cout << aminos.at(4).at(i) << " " << " " << chain.at(4).at(i) << " "
				<< X.at(4).at(i) << " " << Y.at(4).at(i) << " " << Z.at(4).at(i)
				<< endl;
	}

}
int PDB::getRealNumber(int aminoNumber, char chain) {
	for (int i = 0; i < aminosNumber.size(); i++)
		if (aminoNumber == aminosNumber.at(i) && chain == aminosChain.at(i))
			return i;
	return -1;
}
int PDB::getNumberOfAminos() {
	return (int) allaminos.size();
}

int PDB::getNumberOfAminosOfClass(int classNumber) {
	return (int) aminos.at(classNumber).size();
}

void PDB::getXYZOfAmino(int classNumber, int resSeq, char Chain, float *x,
		float *y, float *z) {

	int place;

	for (int i = 0; i < aminos.at(classNumber).size(); i++) {

		if (aminos.at(classNumber).at(i) == resSeq
				&& chain.at(classNumber).at(i) == Chain) {
			*x = X.at(classNumber).at(i);
			*y = Y.at(classNumber).at(i);

			for (int i = 0; i < aminos.at(classNumber).size(); i++) {

				if (aminos.at(classNumber).at(i) == resSeq
						&& chain.at(classNumber).at(i) == Chain) {
					*x = X.at(classNumber).at(i);
					*y = Y.at(classNumber).at(i);
					*z = Z.at(classNumber).at(i);
					break;
				}

			}
			*z = Z.at(classNumber).at(i);
			break;
		}

	}
}
void PDB::getXYZOfAmino(int place, float *x, float *y, float *z) {
	*x = xs.at(place);
	*y = ys.at(place);
	*z = zs.at(place);

}

