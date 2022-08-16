//
//  Parser.cpp
//  atomParser
//
//  Created by saman on 7/11/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Parser.h"
#include "Atom.h"
#include <cstdlib>
#include <string.h>
#include<QMessageBox>
#define DEBUG_MODE 0
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
void Parser::get(char* temp1, int temp2, ifstream* file) {

	for (int i = 0; i < temp2; i++) {
		temp1[i] = (char) (*file).get();
	}

}

Parser::Parser(string nameOfFile) {
	bool isFirstModel = true;
	int in;
	numberOfModels = 0;
	inFile.open(nameOfFile.c_str(), fstream::in);
	if (inFile.is_open() == 0) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","cannot open the specified file.");
        messageBox.setFixedSize(500,200);
		cout << "ERROR: cannot open the specified file." << endl;
	}
	if ( DEBUG_MODE == 1)
		cout << "every thing is alright." << endl;

	char tempChain = '#';
	char tempRes[4] = { '\0' };
	int tempResNum = -1;
	strcpy(tempRes, "xxx");

	char ATOM[7] = { '\0' };
	char Serial[6] = { '\0' };
	char AtomName[5] = { '\0' };
	char resName[4] = { '\0' };
	char chainID;
	char resSeq[5] = { '\0' };
	char iCode;
	char X[9] = { '\0' };
	char Y[9] = { '\0' };
	char Z[9] = { '\0' };
	char occupancy[7] = { '\0' };
	char tempFactor[7] = { '\0' };
	char chert[80] = { '\0' };

	Model newModel;
	models.push_back(newModel);
	numberOfModels++;
	bzero(HEADER, 80);

	while (!inFile.eof()) {

		get(ATOM, 6, &inFile);

		if ( DEBUG_MODE == 1)
			cout << "ATOM is " << ATOM << "saman" << endl;

		if (!strcmp(ATOM, "HEADER")) {
			char trash[80] = { '\0' };
			inFile.get(trash, 4, '\n');
			inFile.get(HEADER, 40, '\n');
			inFile.get(trash, 80, '\n');
			inFile.get();

		}

		else if (!strcmp(ATOM, "ATOM  ")) {
			isFirstModel == false;
			get(Serial, 5, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "Serial is " << Serial << endl;
			}
			inFile.get();

			get(AtomName, 4, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "Atom is " << AtomName << endl;
			}
			inFile.get();

			get(resName, 3, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "resName is " << resName << endl;
			}
			inFile.get();
			chainID = (char) inFile.get();
			if ( DEBUG_MODE == 1) {
				cout << "chainID is " << chainID << endl;
			}

			get(resSeq, 4, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "resSeq is " << resSeq << endl;
			}
			iCode = (char) inFile.get();
			if ( DEBUG_MODE == 1) {
				cout << "iCode is " << iCode << endl;
			}

			get(chert, 3, &inFile);

			get(X, 8, &inFile);

			if ( DEBUG_MODE == 1) {
				cout << "X is " << X << endl;
			}

			get(Y, 8, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "Y is " << Y << endl;
			}

			get(Z, 8, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "Z is " << Z << endl;
			}

			get(occupancy, 6, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "Occupancy is " << occupancy << endl;
			}

			get(tempFactor, 6, &inFile);
			if ( DEBUG_MODE == 1) {
				cout << "tempFactor is " << tempFactor << endl;
			}
			inFile.get(chert, 80);
			inFile.get();

			if ( DEBUG_MODE == 1) {
				cout << "integer of serial is " << atoi(Serial) << endl;
			}

			if (tempChain == chainID) {

				if (!strcmp(tempRes, resName) && tempResNum == atoi(resSeq)) {
					int tNumOfCh =
							(models.at(numberOfModels - 1)).numberOfChains;
					Atom tempAtom;
					tempAtom.serial = atoi(Serial);
					string tempName = AtomName;
					tempAtom.name = tempName;
					string tempResidue = resName;
					tempAtom.residue = tempResidue;
					tempAtom.chainID = chainID;
					tempAtom.resSeq = atoi(resSeq);
					tempAtom.iCode = iCode;
					tempAtom.X = atof(X);
					tempAtom.Y = atof(Y);
					tempAtom.Z = atof(Z);
					tempAtom.occupancy = atof(occupancy);
					tempAtom.tempFactor = atof(tempFactor);
					int tNumOfAmino =
							((models.at(numberOfModels - 1)).chains.at(
									tNumOfCh - 1)).numberOfAminos;

					(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
							tNumOfAmino - 1)).atoms.push_back(tempAtom);
					(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
							tNumOfAmino - 1)).numberOfAtoms++;

				} else {

					if ( DEBUG_MODE == 1)
						cout << "new residue" << endl;

					int tNumOfCh =
							(models.at(numberOfModels - 1)).numberOfChains;

					//for( int l = (((models.at( numberOfModels - 1 )).chains.at( tNumOfCh - 1 ))).numberOfAminos - 12; l <= atoi( resSeq ); l++ )
					((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).addNewAmino();
					Atom tempAtom;
					tempAtom.serial = atoi(Serial);
					string tempName = AtomName;
					tempAtom.name = tempName;
					string tempResidue = resName;
					tempAtom.residue = tempResidue;
					tempAtom.chainID = chainID;
					tempAtom.resSeq = atoi(resSeq);
					tempAtom.iCode = iCode;
					tempAtom.X = atof(X);
					tempAtom.Y = atof(Y);
					tempAtom.Z = atof(Z);
					tempAtom.occupancy = atof(occupancy);
					tempAtom.tempFactor = atof(tempFactor);
					int tNumOfAmino =
							((models.at(numberOfModels - 1)).chains.at(
									tNumOfCh - 1)).numberOfAminos;

					(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
							tNumOfAmino - 1)).atoms.push_back(tempAtom);
					(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
							tNumOfAmino - 1)).numberOfAtoms++;

					strcpy(tempRes, resName);
					tempResNum = atoi(resSeq);

				}

			} else {

				if ( DEBUG_MODE == 1)
					cout << "new Chain ID" << endl;

				(models.at(numberOfModels - 1)).createNewChain();
				int tNumOfCh = (models.at(numberOfModels - 1)).numberOfChains;
				//for( int l = (((models.at( numberOfModels - 1 )).chains.at( tNumOfCh - 1 ))).numberOfAminos - 12; l <= atoi( resSeq ); l++ )
				((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).addNewAmino();

				Atom tempAtom;
				tempAtom.serial = atoi(Serial);
				string tempName = AtomName;
				tempAtom.name = tempName;
				string tempResidue = resName;
				tempAtom.residue = tempResidue;
				tempAtom.chainID = chainID;
				tempAtom.resSeq = atoi(resSeq);
				tempAtom.iCode = iCode;
				tempAtom.X = atof(X);
				tempAtom.Y = atof(Y);
				tempAtom.Z = atof(Z);
				tempAtom.occupancy = atof(occupancy);
				tempAtom.tempFactor = atof(tempFactor);
				int tNumOfAmino = ((models.at(numberOfModels - 1)).chains.at(
						tNumOfCh - 1)).numberOfAminos;

				(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
						tNumOfAmino - 1)).atoms.push_back(tempAtom);
				(((models.at(numberOfModels - 1)).chains.at(tNumOfCh - 1)).aminos.at(
						tNumOfAmino - 1)).numberOfAtoms++;

				tempChain = chainID;
				strcpy(tempRes, resName);
				tempResNum = atoi(resSeq);

			}

			bzero(ATOM, 7);
			bzero(Serial, 6);
			bzero(AtomName, 5);
			bzero(resName, 4);
			bzero(resSeq, 5);
			bzero(X, 9);
			bzero(Y, 9);
			bzero(Z, 9);
			bzero(occupancy, 7);
			bzero(tempFactor, 7);

			//cout << endl << endl;

		} else if (!strcmp(ATOM, "MODEL ") || !strcmp(ATOM, "MODEL")) {
			if (isFirstModel) {
				isFirstModel = false;
				//cout << "atom: " << ATOM << endl;
//				if ( DEBUG_MODE == 0)
//					cout << "new model" << endl;

//Model newModel;
//models.push_back(newModel);
//numberOfModels++;
				tempChain = '#';
				strcpy(tempRes, "zzz");
				continue;
			} else {
				break;
			}
		} else {
//			cout << "atom: " << ATOM << endl;
//			if (strcmp(ATOM, "REMARK")) {
//				string test;
//				cin >> test;
//			}
			inFile.get(chert, 80, '\n');
			inFile.get();
			if ( DEBUG_MODE == 1)
				cout << "we didn't see, an atom" << endl;
			bzero(ATOM, 7);
			continue;

		}

	}

	inFile.close();

}

void Parser::printResult() {

	for (int i = 0; i < numberOfModels; i++) {

		cout << "---Model " << i << "---" << endl;

		for (int j = 0; j < (models.at(i)).numberOfChains; j++) {

			cout << "---Chain " << j << "---" << endl;

			for (int k = 0; k < ((models.at(i)).chains.at(j)).numberOfAminos;
					k++) {

				cout << "---Amino " << k - 12 << "---" << endl;

				for (int p = 0;
						p
								< (((models.at(i)).chains.at(j)).aminos.at(k)).numberOfAtoms;
						p++) {

					cout << "---Atom " << p << "---" << endl;
					cout << " serial is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).serial << endl;
					cout << " name is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).name << endl;
					cout << " residue is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).residue << endl;
					cout << " chainId is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).chainID << endl;
					cout << " resSeq is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).resSeq << endl;
					cout << " iCode is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).iCode << endl;
					cout << " X is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).X << endl;
					cout << " Y is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).Y << endl;
					cout << " Z is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).Z << endl;
					cout << " occupancy is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).occupancy << endl;
					cout << " tempFactor is: "
							<< ((((models.at(i)).chains.at(j)).aminos.at(k)).atoms.at(
									p)).tempFactor << endl;
					cout << endl;

				}

			}

		}

	}

}
