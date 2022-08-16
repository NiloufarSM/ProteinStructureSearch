#include<To_Graph.h>

#include <iostream>
#include <cmath>
#include "Parser.h"
#include "PDB.h"
#include "Graph.h"
#include<queue>
#include<QMessageBox>

#define DEBUG_MODE 0
//#define THRESHOLD 15

vector<string> splitstr(const string& str, const string& delim);
float dist(float x1, float y1, float z1, float x2, float y2, float z2);

void traverse(int s, bool visited[], int n, int graph[][6]) {
    //	cout << endl;
    //	for (int i = 0; i < 6; i++) {
    //		for (int j = 0; j < 6; j++)
    //			cout << graph[i][j] << " ";
    //		cout << endl;
    //	}
    visited[s] = true; //mark v as visited
    queue<int> que;
    que.push(s); //insert s into queue
    while (!que.empty()) {
        int u = que.front(); //delete from queue and print
        que.pop();
        for (int i = 0; i < n; i++) {
            if (graph[i][u]) {
                //when the node is non-visited
                if (!visited[i]) {
                    visited[i] = true;
                    que.push(i);
                }
            }
        }
    }
}
bool isConnected(int n, int graph[][6]) {
    bool *vis = new bool[n];
    //for all vertex u as start point, check whether all nodes are visible or not
    for (int u = 0; u < n; u++) {
        for (int i = 0; i < n; i++)
            vis[i] = false; //initialize as no node is visited
        traverse(u, vis, n, graph);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) //if there is a node, not visited by traversal, graph is not connected
                return false;
        }
    }
    return true;
}

To_Graph::To_Graph(string fileName, string residues,int thereshold,int* selected_thereshold) {
    vector<string> file_name;
    file_name=splitstr(fileName,"/");
    /*cout << "Please enter the PDB file address: ";
     cin >> PDBFileName;*/
    string pdbname=file_name.at(file_name.size()-1);
    try {

        //				if (pdbname == "1qum") {
        //					csa >> residues;
        //					continue;
        //				}
        //				cout << pdbname << '\n';
        ofstream protein;
        ofstream subprotein;
        //170,192,193,259,261
        protein.open("subGraphs/" + pdbname.substr(0,4) + ".grf");
        subprotein.open("subGraphs/" + pdbname.substr(0,4) + ".sub.grf");
        //                string PDBFileName;
        //                PDBFileName = "/home/niloufar/Desktop/ProteinSearchEngine/pdbs/pdb" + pdbname + ".ent";
        //				PDBFileName = "test/pdb" + pdbname + ".ent";

        //parsing the PDB file

        //                string CompletePDBFileName = PDBFileName;
        Parser myParser(fileName);

        if ( DEBUG_MODE == 1) {
            cout
                    << "--we have created the parser object with pdb file"
                       + fileName << endl;
            //myParser.printResult();
        }

        PDB myPDB(myParser);
        if (myPDB.getNumberOfAminos()==0){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Problem with PDB file");
            messageBox.setFixedSize(500,200);
        }
        //			cout
        //					<< "Please select the residues you want from the PDB (comma separated with chain) example: 10A,234B,141C"
        //					<< endl;
        string selectedResidues = residues;
        //			cin >> selectedResidues;
        vector<string> subString = splitstr(selectedResidues, ",");
        vector<int> selected_residues;
        vector<char> selected_residues_chain;
        char chain;
        for (string i : subString) {
            //cout << " i : " << i << " " << i.at(i.length() - 1) << endl;
            chain = i.at(i.length() - 1);
            selected_residues_chain.push_back(chain);
            //cout << "chain: " << i.at(i.length() - 1) << endl;
            i = i.substr(0, i.length() - 1);
            //cout << " i : " << i << " " << i.at(i.length() - 1) << endl;
            selected_residues.push_back(
                        myPDB.getRealNumber(stoi(i), chain));
        }
        if ( DEBUG_MODE == 1) {

            for (int b = 0; b < selected_residues.size(); b++) {
                //                cout << "here";
                cout << selected_residues.at(b) << endl;
            }
            //            cout << "tohere";

        }
        if (DEBUG_MODE == 1) {
            for (string i : subString) {
                cout << "i is:" << i << endl;
                //int index = stoi(i);
                /*cout
                         << myParser.models.at(0).chains.at(0).aminos.at(index).numberOfAtoms
                         << endl;*/
            }
        }
        if(thereshold==-1){
            THRESHOLD = 7;

            //findout the min threshold
            float mx1, my1, mz1;
            float mx2, my2, mz2;
            float md;
            vector<vector<float>> distances;
            for (int i = 0; i < selected_residues.size(); i++) {
                vector<int> end;
                vector<float> dists;
                string amino = myPDB.getAllAminos(selected_residues.at(i));
                for (int j = 0; j < selected_residues.size(); j++) {
                    //						if (i != j) {
                    myPDB.getXYZOfAmino(selected_residues.at(i), &mx1, &my1,
                                        &mz1);
                    myPDB.getXYZOfAmino(selected_residues.at(j), &mx2, &my2,
                                        &mz2);
                    dists.push_back(dist(mx1, my1, mz1, mx2, my2, mz2));
                    //						}
                }
                distances.push_back(dists);
            }
            //				vector<float> mins;
            //				float min = 1000000;
            //				for (int i = 0; i < distances.size(); i++) {
            //					min = 1000000;
            //					for (int j = 0; j < distances.at(i).size(); j++)
            //						if (min > distances.at(i).at(j))
            //							min = distances.at(i).at(j);
            //					if (min > THRESHOLD)
            //						THRESHOLD = min + 1;
            //					cout << "min: " << min << " ";
            //					mins.push_back(min);
            //
            //				}
            bool isGraphConnected;
            do {int c1 = 0, c2 = 0;
                int graph[selected_residues.size()][6];
                for (vector<float> vf : distances) {
                    c2 = 0;
                    for (float f : vf) {
                        if (distances.at(c1).at(c2) < THRESHOLD
                                && distances.at(c1).at(c2) != 0)
                            graph[c1][c2] = 1;
                        else
                            graph[c1][c2] = 0;
                        c2++;
                        //                    cout << "c2:" << c2 << endl;
                    }
                    c1++;
                    //                cout << "c1:" << c1 << endl;
                }
                //            for (int i = 0; i < selected_residues.size(); i++) {
                //                for (int j = 0; j < selected_residues.size(); j++)
                //                    cout << graph[i][j] << " ";
                //                cout << endl;
                //            }

                isGraphConnected=isConnected(selected_residues.size(), graph);
                //            cout << "the result is "
                //                 << isGraphConnected << endl;
                if(!isGraphConnected)
                    THRESHOLD++;
                if (THRESHOLD>15)
                {
                    THRESHOLD=15;
                    break;
                }
            }
            while(!isGraphConnected);
            cout << "\n" << "The chosen Threshold is: " << THRESHOLD<< endl;
        }
        else
            THRESHOLD = thereshold;
        *selected_thereshold=THRESHOLD;
        //construction of graph from PDB file
        Graph mygraph(0);
        float x1, y1, z1;
        float x2, y2, z2;
        float d;
        //        cout<<"number of aminos "<< myPDB.getNumberOfAminos()<<endl;
        protein << myPDB.getNumberOfAminos() << "\n";
        for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
            string amino = myPDB.getAllAminos(i);
            protein << i << " " << amino << " "
                    << myPDB.aminosNumber.at(i)
                    << myPDB.aminosChain.at(i) << "\n";
            mygraph.addNode(amino);
        }
        for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
            myPDB.getXYZOfAmino(i, &x1, &y1, &z1);
            vector<int> end;
            vector<float> dists;
            for (int j = 0; j < myPDB.getNumberOfAminos(); j++) {
                if (i != j) {
                    myPDB.getXYZOfAmino(j, &x2, &y2, &z2);
                    d = dist(x1, y1, z1, x2, y2, z2);
                    if (d < THRESHOLD) {
                        //if (myPDB.getAllAminos(i) > myPDB.getAllAminos(j)) {
                        mygraph.addEdge(myPDB.getAllAminos(i),
                                        myPDB.getAllAminos(j));
                        /*else {
                                 cout << myPDB.getAllAminos(j) << " > "
                                 << myPDB.getAllAminos(i) << " ";
                                 mygraph.addEdge(myPDB.getAllAminos(j),
                                 myPDB.getAllAminos(i));
                                 }*/
                        end.push_back(j);
                        dists.push_back(d);
                    }
                    //                    if ( DEBUG_MODE == 1) {

                    //                    cout << i << "and" << j << "Distance: " << d << endl;
                    //}
                    //                    }
                }
            }
            protein << end.size() << "\n";
            for (int j = 0; j < end.size(); j++) {
                protein << i << " " << end.at(j) << " " << dists.at(j)
                        << "\n";
            }

        }
        //        cout<<"here"<<endl;
        protein.close();
        //        cout<<"and here"<<endl;

        //mygraph.connectedComponents();

        Graph mySubgraph(0);
//        cout<<"subGraph"<<endl;
        float sx1, sy1, sz1;
        float sx2, sy2, sz2;
        float sd;
        //vector<string> selectedAminos;
        //130,131,132,127,128,126,129,133,134
        //        cout<<"number of residues"<<selected_residues.size()<<endl;
        subprotein << selected_residues.size() << endl;
        for (int i = 0; i < selected_residues.size(); i++) {
            string amino = myPDB.getAllAminos(selected_residues.at(i));
            subprotein << i << " " << amino << " " << i << endl;
        }
        for (int i = 0; i < selected_residues.size(); i++) {
            vector<int> end;
            vector<float> dists;
            string amino = myPDB.getAllAminos(selected_residues.at(i));
            mySubgraph.addNode(amino);
            for (int j = 0; j < selected_residues.size(); j++) {
                if (i != j) {
                    myPDB.getXYZOfAmino(selected_residues.at(i), &sx1,
                                        &sy1, &sz1);
                    myPDB.getXYZOfAmino(selected_residues.at(j), &sx2,
                                        &sy2, &sz2);
                    d = dist(sx1, sy1, sz1, sx2, sy2, sz2);
                    if (d < THRESHOLD) {
                        //if (myPDB.getAllAminos(selected_residues.at(i))
                        //		> myPDB.getAllAminos(selected_residues.at(j))) {

                        mySubgraph.addEdge(
                                    myPDB.getAllAminos(
                                        selected_residues.at(i)),
                                    myPDB.getAllAminos(
                                        selected_residues.at(j)));
                        /*else {
                                 cout << myPDB.getAllAminos(selected_residues.at(j))
                                 << " > "
                                 << myPDB.getAllAminos(selected_residues.at(i))
                                 << " ";
                                 mySubgraph.addEdge(
                                 myPDB.getAllAminos(selected_residues.at(j)),
                                 myPDB.getAllAminos(selected_residues.at(i)));}*/
                        end.push_back(j);
                        dists.push_back(d);
                        //	}
                    }
                    if ( DEBUG_MODE == 1) {

                        cout << i << "and" << j << "Distance: " << d
                             << endl;
                    }
                }
            }

            subprotein << end.size() << endl;
            //		if (end.size() == 0) {
            //			cout << "the " << i + 1
            //					<< "th node distance to other nodes is more than 15 angstrom please remove this node and try again"
            //					<< endl;
            //			return 0;
            //		}
            for (int j = 0; j < end.size(); j++) {
                subprotein << i << " " << end.at(j) << " "
                           << dists.at(j) << endl;

            }
        }
        //        cout<<"created subpro"<<endl;
        subprotein.close();
        if(mySubgraph.edge1Array.size()<mySubgraph.nodeArray.size()){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Selected residues are not close enough to each other!\nPlease reselect them.");
            messageBox.setFixedSize(500,200);
            throw 1;
        }
        //        cout<<"created subpro"<<endl;
        //mySubgraph.connectedComponents();
    } catch (const std::out_of_range& oor) {
        //        cout << "pdb: " << pdbname << endl;
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Out of Range error");
        messageBox.setFixedSize(500,200);
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

}
To_Graph::To_Graph(string fileName,int thereshold) {
    vector<string> file_name;
    file_name=splitstr(fileName,"/");
    /*cout << "Please enter the PDB file address: ";
     cin >> PDBFileName;*/
    string pdbname=file_name.at(file_name.size()-1);
    try {

        //				if (pdbname == "1qum") {
        //					csa >> residues;
        //					continue;
        //				}
        //				cout << pdbname << '\n';
        ofstream protein;
        //170,192,193,259,261
        QString path = "templateGraph/";
        QDir dir(path);
        dir.setNameFilters(QStringList() << "*.*");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
        protein.open("templateGraph/" + pdbname.substr(0,4) + ".grf");
        //parsing the PDB file

        Parser myParser(fileName);

        if ( DEBUG_MODE == 1) {
            cout
                    << "--we have created the parser object with pdb file"
                       + fileName << endl;
            //myParser.printResult();
        }

        PDB myPDB(myParser);
        if (myPDB.getNumberOfAminos()==0){
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Problem with PDB file");
            messageBox.setFixedSize(500,200);
        }
        //			cout
        //					<< "Please select the residues you want from the PDB (comma separated with chain) example: 10A,234B,141C"
        //					<< endl;
        if(thereshold!=-1){
            THRESHOLD = thereshold;}
        //construction of graph from PDB file
        Graph mygraph(0);
        float x1, y1, z1;
        float x2, y2, z2;
        float d;
        //        cout<<"number of aminos "<< myPDB.getNumberOfAminos()<<endl;
        protein << myPDB.getNumberOfAminos() << "\n";
        for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
            string amino = myPDB.getAllAminos(i);
            protein << i << " " << amino << " "
                    << myPDB.aminosNumber.at(i)
                    << myPDB.aminosChain.at(i) << "\n";
            mygraph.addNode(amino);
        }
        for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
            myPDB.getXYZOfAmino(i, &x1, &y1, &z1);
            vector<int> end;
            vector<float> dists;
            for (int j = 0; j < myPDB.getNumberOfAminos(); j++) {
                if (i != j) {
                    myPDB.getXYZOfAmino(j, &x2, &y2, &z2);
                    d = dist(x1, y1, z1, x2, y2, z2);
                    if (d < THRESHOLD) {
                        //if (myPDB.getAllAminos(i) > myPDB.getAllAminos(j)) {
                        mygraph.addEdge(myPDB.getAllAminos(i),
                                        myPDB.getAllAminos(j));
                        /*else {
                                 cout << myPDB.getAllAminos(j) << " > "
                                 << myPDB.getAllAminos(i) << " ";
                                 mygraph.addEdge(myPDB.getAllAminos(j),
                                 myPDB.getAllAminos(i));
                                 }*/
                        end.push_back(j);
                        dists.push_back(d);
                    }
                    //                    if ( DEBUG_MODE == 1) {

                    //                    cout << i << "and" << j << "Distance: " << d << endl;
                    //}
                    //                    }
                }
            }
            protein << end.size() << "\n";
            for (int j = 0; j < end.size(); j++) {
                protein << i << " " << end.at(j) << " " << dists.at(j)
                        << "\n";
            }

        }
        //        cout<<"here"<<endl;
        protein.close();
        //        cout<<"and here"<<endl;

        //mygraph.connectedComponents();
    } catch (const std::out_of_range& oor) {
        //        cout << "pdb: " << pdbname << endl;
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Out of Range error");
        messageBox.setFixedSize(500,200);
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

}

//Computing Euclidean Distance
float dist(float x1, float y1, float z1, float x2, float y2, float z2) {

    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2)));
}

//split the input string(index of selected residues)
vector<string> splitstr(const string& str, const string& delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
