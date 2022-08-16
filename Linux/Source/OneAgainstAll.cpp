//============================================================================
// Name        : Matching.cpp
// Author      : Niloufar Seyed Majidi
// Version     :
// Copyright   :
// Description : Protein Search Engine
//============================================================================

//#include <bits/types/clock_t.h>
//#include <bits/types/FILE.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
//#include <CGAL/Simple_cartesian.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/algorithm.h>
#include <CGAL/Side_of_triangle_mesh.h>

#include "argloader.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>

#include "Parser.h"
#include "PDB.h"
#include "Score.h"
#include "allocpool.h"
#include "argraph.h"
#include "match.h"
#include "vf2_sub_state.h"
#include "EdgeLabel.h"
#include "Label.h"
#include "TMScore.h"

#include "rmsd.h"

#include "math.h"

using namespace std;

#define DEBUG_MODE 0

#define ON_SERVER 0

#define Release 0

#define TEST 1

#define MAXNODES 8000

//#define EdgeDiff 1

//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef K::Point_3 Point_3;

typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;

double dist(Point_3 p1, Point_3 p2) {
	double d = sqrt(
			pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2)
					+ pow(p2.z() - p1.z(), 2));
	return d;
}

std::istream& operator>>(std::istream& in, EdgeLabel &l) {
	in >> l.score;
	return in;
}
std::ostream& operator>>(std::ostream& out, EdgeLabel &l) {
	out << l.score;
	return out;
}

//define comparator for edge labels
class EdgeComparator: public AttrComparator {

private:
	double threshold;
public:
	EdgeComparator(double thr) {
		threshold = thr;

	}
	virtual bool compatible(void *la, void*lb) {
		//SUBGRAPH
		EdgeLabel *a = (EdgeLabel *) la;
		//GRAPH
		EdgeLabel *b = (EdgeLabel *) lb;

		if ( DEBUG_MODE == 1) {
			cout << " a: " << a->score << " ";
			cout << " b: " << b->score << endl;
			cout << endl;
		}
		//if (b->score == 6.12215)

		float diff = a->score - b->score;
		//cout << "diff: " << diff << endl;
		if (diff > threshold || diff < -threshold)
			return false;
		//if (b->score > 6.121 && b->score < 6.14)
		//cout << "yeaaaaahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh";
		//cout << "a score: " << a->score;
		//cout << "b score: " << b->score << endl;
		return true;
	}
};

istream& operator>>(istream& in, Label &l) {
	in >> l.name >> l.id;
	return in;
}
ostream& operator>>(ostream& out, Label &l) {
	out << l.name << ' ' << l.id;
	return out;
}

//define comparator for node labels
class LabelComparator: public AttrComparator {

private:
	double threshold;
public:
	LabelComparator(double thr) {
		threshold = thr;

	}
	virtual bool compatible(void *la, void*lb) {
		//SUBGRAPH
		Label *a = (Label *) la;
		//GRAPH
		Label *b = (Label *) lb;

		if ( DEBUG_MODE == 1) {
			cout << " a: " << a->name << " ";
			cout << " b: " << b->name << endl;
			cout << endl;
		}

		if (a->name == "ALA") {
			if (b->name == "GLY" || b->name == "ALA" || b->name == "SER"
					|| b->name == "THR" || b->name == "VAL")
				return true;
			else
				return false;
		}
		if (a->name == "ARG") {
			if (b->name == "HIS" || b->name == "ARG" || b->name == "LYS"
					|| b->name == "GLN")
				return true;
			else
				return false;
		}
		if (a->name == "ASN") {
			if (b->name == "GLY" || b->name == "THR" || b->name == "SER"
					|| b->name == "HIS" || b->name == "ASN" || b->name == "ASP"
					|| b->name == "LYS")
				return true;
			else
				return false;
		}
		if (a->name == "ASP") {
			if (b->name == "GLY" || b->name == "GLU" || b->name == "SER"
					|| b->name == "ASN" || b->name == "ASP")
				return true;
			else
				return false;
		}
		if (a->name == "CYS") {
			if (b->name == "GLY" || b->name == "ALA" || b->name == "SER"
					|| b->name == "THR" || b->name == "CYS" || b->name == "VAL"
					|| b->name == "LEU")
				return true;
			else
				return false;
		}
		if (a->name == "GLU") {
			if (b->name == "ALA" || b->name == "LYS" || b->name == "ASP"
					|| b->name == "GLN" || b->name == "GLU")
				return true;
			else
				return false;
		}
		if (a->name == "GLN") {
			if (b->name == "LEU" || b->name == "ALA" || b->name == "SER"
					|| b->name == "HIS" || b->name == "LYS" || b->name == "GLN"
					|| b->name == "ARG" || b->name == "GLU")
				return true;
			else
				return false;
		}
		if (a->name == "GLY") {
			if (b->name == "GLY" || b->name == "ALA" || b->name == "SER"
					|| b->name == "GLU" || b->name == "ASN" || b->name == "ASP")
				return true;
			else
				return false;
		}
		if (a->name == "HIS") {
			if (b->name == "PHE" || b->name == "TYR" || b->name == "SER"
					|| b->name == "HIS" || b->name == "ASN" || b->name == "GLN"
					|| b->name == "ARG")
				return true;
			else
				return false;
		}
		if (a->name == "ILE") {
			if (b->name == "VAL" || b->name == "LEU" || b->name == "ILE"
					|| b->name == "MET")
				return true;
			else
				return false;
		}
		if (a->name == "LEU") {
			if (b->name == "VAL" || b->name == "LEU" || b->name == "ILE"
					|| b->name == "MET" || b->name == "PHE")
				return true;
			else
				return false;
		}
		if (a->name == "LYS") {
			if (b->name == "ARG" || b->name == "LYS" || b->name == "GLN"
					|| b->name == "ASN")
				return true;
			else
				return false;
		}
		if (a->name == "MET") {
			if (b->name == "VAL" || b->name == "LEU" || b->name == "ILE"
					|| b->name == "MET")
				return true;
			else
				return false;
		}
		if (a->name == "PHE") {
			if (b->name == "TYR" || b->name == "LEU" || b->name == "ILE"
					|| b->name == "PHE")
				return true;
			else
				return false;
		}
		if (a->name == "PRO") {
			if (b->name == "VAL" || b->name == "ALA" || b->name == "LEU"
					|| b->name == "PRO" || b->name == "SER" || b->name == "THR")
				return true;
			else
				return false;
		}
		if (a->name == "SER") {
			if (b->name == "GLY" || b->name == "ALA" || b->name == "SER"
					|| b->name == "THR" || b->name == "ASN")
				return true;
			else
				return false;
		}
		if (a->name == "THR") {
			if (b->name == "VAL" || b->name == "ALA" || b->name == "SER"
					|| b->name == "THR" || b->name == "ASN" || b->name == "ILE")
				return true;
			else
				return false;
		}
		if (a->name == "TRP") {
			if (b->name == "TRP" || b->name == "LEU" || b->name == "ARG"
					|| b->name == "PHE" || b->name == "TYR")
				return true;
			else
				return false;
		}
		if (a->name == "TYR") {
			if (b->name == "TRP" || b->name == "HIS" || b->name == "PHE"
					|| b->name == "TYR")
				return true;
			else
				return false;
		}
		if (a->name == "VAL") {
			if (b->name == "VAL" || b->name == "ILE" || b->name == "LEU"
					|| b->name == "ALA" || b->name == "THR")
				return true;
			else
				return false;
		} else {
//			cout << "non of above: " << a->name << endl;
			return true;
		}
		/*
		 if (a->name == b->name)
		 return true;
		 else
		 return false;
		 */
		/*
		 if (isPositionSpecific) {
		 string temp[20];
		 for (int i = 0; i < position.at(a->id).size(); i++)
		 temp[i] = position.at(a->id).at(i);
		 if (findor(temp, 20, b->name)) {
		 //				cout << "it is a match :" << a->name << " b: " << b->id
		 //						<< endl;
		 return true;
		 } else
		 return false;
		 //cout << "not a match";
		 } else {

		 //			if (a->name == "MET") {
		 //				cout << "a is MET "
		 //						<< findor(negative,
		 //								(sizeof(negative) / sizeof(negative[0])),
		 //								a->name) << endl;
		 //
		 //			}

		 if (findor(positive, (sizeof(positive) / sizeof(positive[0])),
		 a->name)) {
		 if (findor(positive, (sizeof(positive) / sizeof(positive[0])),
		 b->name)) {
		 if ( DEBUG_MODE == 1)
		 cout << "matchpositive: " << "a: " << a->name << " "
		 << a->id << " b: " << b->name << " " << b->id;
		 return true;
		 } else
		 return false;
		 }
		 if (findor(negative, (sizeof(negative) / sizeof(negative[0])),
		 a->name)) {
		 //cout << "matchnegativefirst: " << "a: " << a->name << " "
		 //	<< a->id << endl;
		 if (findor(negative, (sizeof(negative) / sizeof(negative[0])),
		 b->name)) {
		 if ( DEBUG_MODE == 1)
		 cout << "matchnegative: " << "a: " << a->name << " "
		 << a->id << " b: " << b->name << " " << b->id
		 << endl;
		 return true;
		 } else
		 return false;
		 }
		 if (findor(B, (sizeof(B) / sizeof(B[0])), a->name)) {
		 if (findor(B, (sizeof(B) / sizeof(B[0])), b->name)) {
		 if ( DEBUG_MODE == 1)
		 cout << "match" << "a: " << a->name << " " << a->id
		 << "b: " << b->name << " " << b->id;
		 return true;
		 } else
		 return false;
		 }
		 if (findor(C, (sizeof(C) / sizeof(C[0])), a->name)) {
		 if (findor(C, (sizeof(C) / sizeof(C[0])), b->name)) {
		 if ( DEBUG_MODE == 1)
		 cout << "match" << "a: " << a->name << " " << a->id
		 << "b: " << b->name << " " << b->id;
		 return true;
		 } else
		 return false;
		 }
		 if (findor(D, (sizeof(D) / sizeof(D[0])), a->name)) {
		 if (findor(D, (sizeof(D) / sizeof(D[0])), b->name)) {
		 if ( DEBUG_MODE == 1)
		 cout << "match D: " << "a: " << a->name << " " << a->id
		 << " b: " << b->name << " " << b->id;
		 return true;
		 } else
		 return false;
		 }
		 //cout << "not a match : " << "a: " << a->name << " " << a->id
		 //		<< " b: " << b->name << " " << b->id << endl;
		 return false;
		 }
		 */
	}
	bool findor(string array[], int size, string item) {
		for (int i = 0; i < size; i++) {
			if (array[i] == item) {
				if ( DEBUG_MODE == 1) {
					//cout << "the value" << array[i] << "is equal to: " << item;
				}
				return true;
			}
		}
		return false;
	}
};

//define a destroyer for all labels
class LabelDestroyer: public AttrDestroyer {
public:
	virtual void destroy(void *p) {
		delete p;

	}
};

string templatefile = "";		//stores the template protein name

bool isPositionSpecific = false; //true if there is a position specific scoring

vector<vector<string>> position; //use for the position in position specific mode

vector<pair<string, Score>> matches; //stores final matches

int scoring_Matrix[24][24]; //stores the defined scoring matrix(currently blosum62)
string labels[24];
//description of the pattern protein
vector<string> pat_aminos;
vector<int> pat_ids;
//description of the target protein
vector<string> tar_aminos;
vector<int> tar_ids;
vector<string> tar_nums;
vector<char> tar_chains;

int maxScore = -1000; //stores the maximum score

vector<float> finalEdgeScore;

//the scoring function for labels
int scoring(int ni1, int ni2) {
	string first = pat_aminos.at(ni1);
	int firstID = 0;
	int secondID = 0;
	string second = tar_aminos.at(ni2);
	for (int i = 0; i < 24; i++) {
		if (first == labels[i])
			firstID = i;
		if (second == labels[i])
			secondID = i;
	}
	if (DEBUG_MODE == 1) {
		cout << "score of " << first << " and " << second << " is: "
				<< scoring_Matrix[firstID][secondID] << endl;
	}
	return scoring_Matrix[firstID][secondID];
}

vector<vector<int>> gLabels;
int mcount = 0;

//the visitor function of matching (is called when two nodes are being visited)
bool my_visitor(int n, node_id ni1[], node_id ni2[], void *usr_data) {

	FILE *f = (FILE *) usr_data;

	vector<int> glabel;
//print match
	int i;
	int score = 0;
	fprintf(f, templatefile.c_str());

	string match = templatefile + " ";
	for (i = 0; i < n; i++) {
		match += /*to_string(ni1[i]) + " " + */tar_nums.at(ni2[i]) + " , ";
		int second = stoi(tar_nums.at(ni2[i]));
		fprintf(f, " (%hd,%hd)", ni1[i], second);
		glabel.push_back(ni2[i]);
		score = score + scoring(ni1[i], ni2[i]);
	}

	if (maxScore < score) {
		maxScore = score;
	}
	gLabels.push_back(glabel);
	fprintf(f, " %hd \n", score / n);
	Score s;
	s.score = ((float) score) / n;
	matches.push_back(make_pair(match, s));
	mcount++;
	return false;
}

//comparator for score
bool comparator(const pair<string, Score>& a, const pair<string, Score>& b) {
	return a.second.score > b.second.score;
}

//convert string to vector of strings with delimiter
vector<string> splitstr(const string& str, const string& delim) {
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == string::npos)
			pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty() && token != ",")
			tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

//check if a point is inside a polyhedorn or not
bool pointInside(Polyhedron &polyhedron, Point_3 &query) {
// Construct AABB tree with a KdTree
	Tree tree(faces(polyhedron).first, faces(polyhedron).second, polyhedron);
	tree.accelerate_distance_queries();
// Initialize the point-in-polyhedron tester
	Point_inside inside_tester(tree);

// Determine the side and return true if inside!
	return (inside_tester(query) == CGAL::ON_BOUNDED_SIDE
			|| inside_tester(query) == CGAL::ON_BOUNDARY);
}

bool useCH = false; //true if we want to check aminoacids inside the convexhull

float EdgeDiff = 1; //the max amount of edge difference which is allowed in a match
int main(int argc, const char * argv[]) {
	//clock_t tStart = clock();
	//Reading the input arguments
	string inputfile = argv[1];	//store the subgraph file name
	int numberOfResults = stoi(argv[2]);
	string selected_residues_to_match = argv[3];
	useCH = (argv[4] == "true");
	EdgeDiff = stof(argv[5]);
	string edge_graph_thereshold = argv[6];
	cout<<"The thereshold of making graphs is:"<<edge_graph_thereshold<<endl;
	//subgraph
	string data;
	string paternName;
	cout << "subprotein file name: " << inputfile << endl;

	if (ON_SERVER)
		paternName = "/home/majidi/data/uniprot_data/CSAs-withec/"/*"csa/"*/
		+ inputfile;
	else
		paternName = "subGraphs/" + inputfile;

	//open the subgraph
	ifstream graphInPat(paternName);

	//Allocate attributes to nodes and edges
	NewAllocator<Label> node_allocator;
	NewAllocator<EdgeLabel> edge_allocator;

	StreamARGLoader<Label, EdgeLabel> pattloader(&node_allocator,
			&edge_allocator, graphInPat);
	ARGraph<Label, EdgeLabel> p(&pattloader);
	p.SetNodeDestroyer(new LabelDestroyer());
	p.SetEdgeDestroyer(new LabelDestroyer());
	double my_threshold = 0.1;
	p.SetNodeComparator(new LabelComparator(my_threshold));
	p.SetEdgeComparator(new EdgeComparator(EdgeDiff));
	/*vector<float> pdist;
	 for (int i = 0; i < p.NodeCount(); i++)
	 for (int j = 0; j < p.NodeCount(); j++) {
	 //cout << "i: " << i << " j: " << j << endl;
	 if (i != j) {
	 if (p.GetEdgeAttr(i, j) != NULL) {
	 //								cout << "pdist:"
	 //										<< abs(p.GetEdgeAttr(i, j)->score)
	 //										<< endl;
	 pdist.push_back(
	 abs(p.GetEdgeAttr(i, j)->score));
	 }
	 }
	 //cout << "here " << p.NodeCount() << endl;
	 }*/
	graphInPat.close();

	//Read files of graphs to store more data
	ifstream graphInPat2(paternName);
	maxScore = -1000;
	pat_aminos.clear();
	pat_ids.clear();
	gLabels.clear();
	graphInPat2 >> data;
	int nOfresidues = stoi(data);
	for (int i = 0; i < nOfresidues; i++) {
		graphInPat2 >> data;
		pat_ids.push_back(stoi(data));
		graphInPat2 >> data;
		pat_aminos.push_back(data);
		graphInPat2 >> data;
	}

	graphInPat2.close();

	struct dirent *entry = nullptr;
	DIR *dp = nullptr;
	string templatedir ="PDBs-graphs"+edge_graph_thereshold;
	const char* templatedirchar=templatedir.c_str();
	if (ON_SERVER)
		dp = opendir("/home/majidi/data/uniprot_data/CSAs-withec/"/*"csa"*/);
	else
		dp = opendir(templatedirchar);

	if (dp != nullptr) {
		while ((entry = readdir(dp))) {
			templatefile = entry->d_name;
			if (templatefile != "." && templatefile != "..") {

				//graph

//	string targetName =
				string targetName = templatefile;
				cout << "template file name: " << targetName << endl;

				maxScore = -1000;
				tar_aminos.clear();
				tar_ids.clear();
				tar_nums.clear();

				//Read Scoring Matrix
				ifstream infile;
				if (ON_SERVER)
					infile.open(
							"/home/majidi/data/blosum62.txt"/*"blosum62.txt"*/);
				else
					infile.open("blosum62.txt");
				for (int i = 0; i < 24 && infile >> data; i++) {
					labels[i] = data;
				}
				for (int i = 0; i < 24; i++) {
					infile >> data;
					for (int j = 0; j < 24; j++) {
						infile >> data;
						scoring_Matrix[i][j] = stoi(data);
					}
				}
				infile.close();

				//Read position specific file if exists
				ifstream pfile;
				pfile.open("position.txt");
				//if there exist a file with position specific classification of Labels
				if (pfile.peek() == std::ifstream::traits_type::eof()
						== false) {
					isPositionSpecific = true;
					while (getline(pfile, data)) {
						string sample;
						vector<string> line = splitstr(data, " ");
						//line.push_back(data);
						if (DEBUG_MODE == 1)
							for (int i = 0; i < line.size(); i++)
								cout << i << " : " << line.at(i) << " ";
						position.push_back(line);
					}

				}
				pfile.close();

				//open the template graph
				ifstream graphInTarg(templatedir+"/" + targetName, ios::in);
				//Read graphs
				StreamARGLoader<Label, EdgeLabel> targloader(&node_allocator,
						&edge_allocator, graphInTarg);

				graphInTarg.close();

				//Read files of graphs to store more data
				ifstream graphInTarg2(templatedir+"/" + targetName);

				graphInTarg2 >> data;
				nOfresidues = stoi(data);
				for (int i = 0; i < nOfresidues; i++) {
					graphInTarg2 >> data;
					tar_ids.push_back(stoi(data));
					graphInTarg2 >> data;
					tar_aminos.push_back(data);
					graphInTarg2 >> data;
					tar_nums.push_back(data);
				}
				graphInTarg2.close();

				ARGraph<Label, EdgeLabel> g(&targloader);

				g.SetNodeDestroyer(new LabelDestroyer());
				g.SetEdgeDestroyer(new LabelDestroyer());
				int indexOfmatch = 0;

				//the starting state
				VF2SubState s0(&p, &g);

				//output file
				stringstream stream;
				if (ON_SERVER)
					stream << "/home/majidi/data/Results/output-"/*"Results/output-"*/
					<< targetName.erase(4, 8) << ".txt";
				else
					stream << "junk.txt";
				string str = stream.str();
				const char *output = str.c_str();
				if (DEBUG_MODE == 1)
					cout << "output is: " << output << endl;
				FILE * f = fopen(output, "w");
				//running the match algorithm
				//				cout << "before matching" << endl;

				int nOfmatches = match(&s0, my_visitor, f);
				fclose(f);
				cout << "numberOfmatches: " << nOfmatches << endl;

				/* //old edge scoring


				 //compute score for edges
				 for (int k = 0; k < nOfmatches; k++) {
				 int c = 0;
				 float edgeScore = 0;
				 for (int l1 = 0; l1 < gLabels.at(k).size(); l1++)
				 for (int l2 = 0; l2 < gLabels.at(k).size(); l2++)
				 if (l1 != l2) {
				 //								cout << "l1: " << l1 << "l2: " << l2 << endl;

				 //								cout << "edges: " << gLabels.at(k).size()
				 //										<< endl;
				 //								cout << gLabels.at(k).at(l1) << " "
				 //										<< gLabels.at(k).at(l2) << endl;
				 if (g.GetEdgeAttr(gLabels.at(k).at(l1),
				 gLabels.at(k).at(l2)) != NULL) {
				 //									cout << "not null"
				 //											<< g.GetEdgeAttr(
				 //													gLabels.at(k).at(l1),
				 //													gLabels.at(k).at(l2))->score
				 //											<< endl;
				 edgeScore += abs(
				 g.GetEdgeAttr(gLabels.at(k).at(l1),
				 gLabels.at(k).at(l2))->score
				 - pdist.at(c));

				 //									cout << " edge score: " << edgeScore
				 //											<< endl;
				 c++;
				 }
				 }
				 //edge /2 because it has been computed twice. once from a node and once toward a node
				 finalEdgeScore.push_back(edgeScore / 2);
				 //					cout << "e: " << edgeScore << endl;
				 float f2 = edgeScore / 2;
				 if (f2 != 0)
				 matches[indexOfmatch].second /= f2;
				 if (f2 == 0) {
				 matches[indexOfmatch].second += 1000;
				 }
				 indexOfmatch++;

				 }

				 sort(matches.begin(), matches.end(), comparator);
				 //				for (int k = 0; k < matches.size(); k++)
				 //					cout << k << " " << matches[k].second << endl;

				 //only keep top results

				 if (matches.size() > (numberOfResults * 10)) {
				 int diff = matches.size() - (numberOfResults * 10);
				 indexOfmatch -= diff;
				 matches.erase(matches.begin() + (numberOfResults * 10),
				 matches.end());
				 //					cout << matches[0].second << endl;
				 }


				 */

				/*node_id id = 0;
				 cout << "hey: " << g.NodeCount();
				 for (int i = 0; i < g.NodeCount(); i++) {
				 cout << "before";
				 Label* hi = g.GetNodeAttr(i);
				 cout << "atttr: " << hi->name;
				 }
				 */
				/*
				 int n;
				 node_id ni1[MAXNODES], ni2[MAXNODES];
				 if (!match(&s0, &n, ni1, ni2)) {
				 printf("NO MATCH!\n");
				 return 1;
				 }

				 printf("Found a match %d nodes :\n", n);
				 for (i = 0; i < n; i++)
				 printf("\tNode %hd of graph 1 is paired wiht node %hd of graph 2\n",

				 ni1, ni2);*/
//			}
//else
//cout << "directory skipped \n";
			}
		}
		closedir(dp);
	}
////edge label contribution in scoring
//	for (int i = 0; i < matches.size(); i++) {
//		float f = finalEdgeScore.at(i);
//		//multiply by 1/edgescore
//		if (f != 0)
//			matches[i].second /= f;
//		if (f == 0) {
//			cout << "yeah" << i << endl;
//			matches[i].second += 1000;
//		}
//	}

	/*	ifstream csa;
	 if (ON_SERVER)
	 csa.open("/home/majidi/data/CSA.txt");
	 else
	 csa.open("pro.txt");
	 */
	string subname = argv[1];
	subname = subname.substr(0, 4);
	vector<string> sub_residues_chains = splitstr(selected_residues_to_match,
			",");
	cout << subname << endl;
	string Parser_Address;
	if (ON_SERVER)
		Parser_Address = "/home/majidi/data/withec/" + subname + ".pdb";
	else
		Parser_Address = "PDBs/" + subname + ".pdb";
	Parser mysubParser(Parser_Address);
	PDB mysubPDB(mysubParser);
	vector<int> toRemove;
	vector<string> match_ids;
	vector<int> selected_residues;
	vector<char> selected_residues_chain;
	Polyhedron_3 poly;
	vector<int> sub_residues;
	vector<char> sub_chain;
	vector<int> sub_chain_num;
//	 vector<float> rmsds;

	int inside_sub = 0;
	int inside_pdb = 0;
	vector<Point_3> sub_points;
	vector<Point_3> points;
	bool is_sub_pdb = false;
	bool is_pdb = false;
	string sub_pdb_file = "Match_PDBs/" + subname + "_sub.pdb";
	ofstream Fout(sub_pdb_file);

	if (!Fout) {
		cerr << "Cannot open pdb output file " << subname << ".pdb" << endl;
		exit(1);
	}

	for (int j = 0; j < matches.size(); j++) {
		sub_points.clear();
		points.clear();
		match_ids.clear();
		selected_residues.clear();
		selected_residues_chain.clear();
		poly.clear();
		inside_pdb = 0;
		inside_sub = 0;
		sub_residues.clear();
		sub_chain.clear();

//		cout << "hi:" << matches[j].first << endl;
		//In this string we store the output of the founded match separately with this patern:
		//[0] : subgraphname.sub.grf
		//[1] : 0
		//[2] : first matched residue
		//[3] : 1
		//[4] : second matched residue
		//...
		char chain;
		float x1, y1, z1;
		string s;
		for (string c : sub_residues_chains) {
			chain = c.at(c.length() - 1);
			sub_chain.push_back(chain);
			c = c.substr(0, c.length() - 1);
//			cout << mysubPDB.getRealNumber(stoi(c), chain) << endl;
			sub_residues.push_back(mysubPDB.getRealNumber(stoi(c), chain));
			if (!is_sub_pdb) {
				for (int i_chain = 0;
						i_chain < mysubParser.models.at(0).chains.size();
						i_chain++) {
					if (mysubParser.models.at(0).chains.at(i_chain).aminos.at(0).atoms.at(
							0).chainID == chain) {
						int index_residue;
						for (int index = 0;
								index
										< mysubParser.models.at(0).chains.at(
												i_chain).aminos.size();
								index++) {
							if (stoi(c)
									== mysubParser.models.at(0).chains.at(
											i_chain).aminos.at(index).atoms.at(
											0).resSeq) {
								index_residue = index;
								cout << "residue num:" << index_residue << endl;
								for (int atom_index = 0;
										atom_index
												< mysubParser.models.at(0).chains.at(
														i_chain).aminos.at(
														index_residue).numberOfAtoms;
										atom_index++) {
									Fout << "ATOM  ";
									Fout << setw(5)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).serial << " ";
									Fout << setw(4)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).name << " ";
									Fout << setw(3)
											/*<< mysubParser.models.at(0).chains.at(
											 i_chain).aminos.at(
											 index_residue).atoms.at(
											 atom_index).iCode*/
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).residue << " "
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).chainID;
									Fout << setw(4)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).resSeq
											<< "    ";
									Fout.setf(ios::showpoint | ios::fixed);
									Fout << setprecision(3) << setw(8)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).X
											<< setprecision(3) << setw(8)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).Y
											<< setprecision(3) << setw(8)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).Z << "  1.00"
											<< setprecision(2) << setw(6)
											<< mysubParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).atoms.at(
													atom_index).tempFactor
											<< endl;
								}
								break;
							}
						}
						break;
					}
				}
			}
		}
		is_sub_pdb = true;
//		Fout << endl;
//		Fout << "END" << endl;
		Fout.close();
		for (int i = 0; i < sub_residues.size(); i++) {
			mysubPDB.getXYZOfAmino(sub_residues.at(i), &x1, &y1, &z1);
			sub_points.push_back(Point_3(x1, y1, z1));
		}
		if (useCH) {
			// define polyhedron to hold convex hull
			Polyhedron_3 polycsa;

			// compute convex hull of non-collinear points
			CGAL::convex_hull_3(sub_points.begin(), sub_points.end(), polycsa);
//		cout << "The convex hull of csa contains " << polycsa.size_of_vertices()
//				<< " vertices" << "\n";
			for (int i = 0; i < mysubPDB.getNumberOfAminos(); i++) {
				mysubPDB.getXYZOfAmino(i, &x1, &y1, &z1);
				Point_3 q(x1, y1, z1);
				if (pointInside(polycsa, q)) {
					inside_sub++;
//				cout << "This is inside" << endl;
				}
			}
		}
		match_ids = splitstr(matches[j].first, " ");
		string pdb_name = match_ids.at(0).substr(0, 4);
		cout << "pdb: " << pdb_name << endl;
		if (ON_SERVER)
			Parser_Address = "/home/majidi/data/withec/" + pdb_name + ".pdb";
		else
			Parser_Address = "PDBs/" + pdb_name + ".pdb";

		Parser mypdbParser(Parser_Address);
		PDB myPDB(mypdbParser);
		string match_pdb_file = "Match_PDBs/" + pdb_name + "_"
				+ to_string(j) + ".pdb";
		ofstream Fout(match_pdb_file);
		if (!Fout) {
			cerr << "Cannot open pdb output file " << subname << ".pdb" << endl;
			exit(1);
		}
		for (int i = 2; i < match_ids.size(); i ++) {
			s = match_ids[i];
			//			cout << " i : " << i << " " << i.at(i.length() - 1) << endl;
			chain = s.at(s.length() - 1);
			selected_residues_chain.push_back(chain);
			//cout << "chain: " << i.at(i.length() - 1) << endl;
			s = s.substr(0, s.length() - 1);
//			cout << myPDB.getRealNumber(stoi(s), chain) << endl;
			selected_residues.push_back(myPDB.getRealNumber(stoi(s), chain));
			//PDB of found matches
//			if (!is_pdb) {

			for (int i_chain = 0;
					i_chain < mypdbParser.models.at(0).chains.size();
					i_chain++) {
				if (mypdbParser.models.at(0).chains.at(i_chain).aminos.at(0).atoms.at(
						0).chainID == chain) {
					int index_residue;
					for (int index = 0;
							index
									< mypdbParser.models.at(0).chains.at(
											i_chain).aminos.size(); index++) {
						if (stoi(s)
								== mypdbParser.models.at(0).chains.at(i_chain).aminos.at(
										index).atoms.at(0).resSeq) {
							index_residue = index;
							cout << "residue num:" << index_residue << endl;

							for (int atom_index = 0;
									atom_index
											< mypdbParser.models.at(0).chains.at(
													i_chain).aminos.at(
													index_residue).numberOfAtoms;
									atom_index++) {
								Fout << "ATOM  ";
								Fout << setw(5)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).serial<<" ";
								Fout << setw(4)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).name << " ";
								Fout/*
								 << mypdbParser.models.at(0).chains.at(
								 i_chain).aminos.at(
								 index_residue).atoms.at(
								 atom_index).iCode
								 */<< setw(3)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).residue << " "
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).chainID;
								Fout << setw(4)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).resSeq << "    ";
								Fout.setf(ios::showpoint | ios::fixed);
								Fout << setprecision(3) << setw(8)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).X << setprecision(3)
										<< setw(8)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).Y << setprecision(3)
										<< setw(8)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).Z << "  1.00"
										<< setprecision(2) << setw(6)
										<< mypdbParser.models.at(0).chains.at(
												i_chain).aminos.at(
												index_residue).atoms.at(
												atom_index).tempFactor << endl;
							}
							break;
						}
					}
					break;
				}
			}
		}
//		Fout << endl;
//		Fout << "END" << endl;
		Fout.close();
		char* arguments[] = { "TMScore", strdup(sub_pdb_file.c_str()), strdup(
				match_pdb_file.c_str()) };

		double rmsd, TM_Score;
		TMScore tm(3, arguments, &rmsd, &TM_Score);

		cout << rmsd << " " << TM_Score << endl;
		matches[j].second.TMScore = TM_Score;
		matches[j].second.rmsd = rmsd;
//		}
//		is_pdb = true;
		for (int i = 0; i < selected_residues.size(); i++) {
			myPDB.getXYZOfAmino(selected_residues.at(i), &x1, &y1, &z1);
			//			cout << x1 << " " << y1 << " " << z1 << endl;
			points.push_back(Point_3(x1, y1, z1));
		}
		// define polyhedron to hold convex hull
		//		cout << poly.clear() << endl;
		if (useCH) {
			// compute convex hull of non-collinear points
			CGAL::convex_hull_3(points.begin(), points.end(), poly);

			//		cout << "The convex hull of pdb contains " << poly.size_of_vertices()
			//				<< " vertices" << "\n";
			for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
				myPDB.getXYZOfAmino(i, &x1, &y1, &z1);
				Point_3 q(x1, y1, z1);
				if (pointInside(poly, q)) {
					inside_pdb++;
//				cout << "This is convex hull of csa contains " << polycsa.size_of_vertices()
//				<< " inside" << endl;
				}
			}
			if (inside_sub != inside_pdb) {
				toRemove.push_back(j);

			}
		}
		/*
		 //Determine the points of PDB for RMSD
		 int level = points.size();
		 float **second2;
		 float **first2;
		 second2 = (float**) (malloc(sizeof(float*) * level));
		 for (int j = 0; j < level; j++) {
		 second2[j] = (float*) (malloc(sizeof(float) * 3));
		 second2[j][0] = points.at(j).x();
		 second2[j][1] = points.at(j).y();
		 second2[j][2] = points.at(j).z();

		 }*/

		//		cout << "number of aminos inside pdb: " << inside_pdb << endl;
		//		CGAL::set_ascii_mode(std::cout);
		//		std::copy(poly.points_begin(), poly.points_end(),
		//				std::ostream_iterator<Point_3>(std::cout, "\n"));
		//		cout << "csa: " << csa_name << endl;
		//		if (inside_csa == inside_pdb) {
		//			cout << "match hooooooray" << endl;
		//		}
		//		cout << "inside: " << inside_csa << "pdb: " << inside_pdb << endl;
		/*//Determine the points of CSA for RMSD

		 first2 = (float**) (malloc(sizeof(float*) * level));
		 for (int f = 0; f < level; f++) {
		 first2[f] = (float*) (malloc(sizeof(float) * 3));
		 first2[f][0] = csa_points.at(f).x();
		 first2[f][0] = csa_points.at(f).y();
		 first2[f][0] = csa_points.at(f).z();

		 }*/
		vector<double> d1;
		for (int l = 0; l < points.size(); l++) {
			for (int k = 0; k < points.size(); k++) {
				d1.push_back(dist(points.at(l), points.at(k)));
			}
		}
		vector<double> d2;
		for (int l = 0; l < sub_points.size(); l++) {
			for (int k = 0; k < sub_points.size(); k++) {
				d2.push_back(dist(sub_points.at(l), sub_points.at(k)));
			}
		}
		//to store distance and label score separately
		matches[j].second.label_score = matches[j].second.score;
		float newScore = 0;
		for (int l = 0; l < d1.size(); l++) {
			matches[j].second.distances.push_back(abs(d1.at(l) - d2.at(l)));
			newScore += (abs(d1.at(l) - d2.at(l)));
			//			cout << "abs: " << abs(d1.at(l) - d2.at(l)) << endl;
		}
		//		cout << "the score is: " << newScore << endl;
		if (newScore != 0)
			matches[j].second.score /= newScore;
		if (newScore == 0) {
			matches[j].second.score += 1000;
		}
		//Calculate RMSD
		float mov_com2[3];
		float mov_to_ref2[3];
		float U2[3][3];
		float currentRMSD2;

		//		calculate_rotation_rmsd(second2, first2, csa_residues.size(), mov_com2,
		//				mov_to_ref2, U2, &currentRMSD2);
		//		fast_rmsd(second2, first2, 4, &currentRMSD2);
		//		cout << "The RMSD is: " << currentRMSD2 << endl;
		//		while (isnan(currentRMSD2))
		//			calculate_rotation_rmsd(second2, first2, csa_residues.size(),
		//					mov_com2, mov_to_ref2, U2, &currentRMSD2);
		//		rmsds.push_back(currentRMSD2);

		//		CGAL::set_ascii_mode(std::cout);
		//		std::copy(polycsa.points_begin(), polycsa.points_end(),
		//				std::ostream_iterator<Point_3>(std::cout, "\n"));
		//		cout << "this is the end" << j << " " << matches.size() << endl;
	}
	//	cout << "going to erase " << toRemove.size() << " out of " << matches.size()
	//			<< endl;
	for (int i = toRemove.size(); i > 0; i--) {
		//		cout << "removing " << toRemove.at(i - 1) << endl;
		matches.erase(matches.begin() + toRemove.at(i - 1));
		//		cout << matches.size() << endl;

		//		rmsds.erase(rmsds.begin() + toRemove.at(i - 1));
	}

	//	for (int i = 0; i < matches.size(); i++) {
	//		matches.at(i).second = rmsds.at(i);
	//		cout << matches[i].second << endl;
	//
	//	}

	//parsing the PDB file
	//	Parser myParser("");
	//	PDB myPDB(myParser);
	//			cout
	//					<< "Please select the residues you want from the PDB (comma separated with chain) example: 10A,234B,141C"
	//					<< endl;
	//	string selectedResidues = residues;
	//	//			cin >> selectedResidues;
	//	vector<string> subString = splitstr(selectedResidues, ",");
	//	vector<int> selected_residues;
	//	vector<char> selected_residues_chain;
	//	char chain;
	//	for (string i : subString) {
	//		//cout << " i : " << i << " " << i.at(i.length() - 1) << endl;
	//		chain = i.at(i.length() - 1);
	//		selected_residues_chain.push_back(chain);
	//		//cout << "chain: " << i.at(i.length() - 1) << endl;
	//		i = i.substr(0, i.length() - 1);
	//		//cout << " i : " << i << " " << i.at(i.length() - 1) << endl;
	//		selected_residues.push_back(myPDB.getRealNumber(stoi(i), chain));
	//	}

	sort(matches.begin(), matches.end(), comparator);
	cout << "remaining number of matches is: " << matches.size() << endl;
	//write matches into this file
	ofstream matchesfile;
	matchesfile.open("output.txt");
	for (int i = 0; i < numberOfResults && i < matches.size(); i++) {
//		cout << "here I am" << endl;
		string m = matches[i].first;
//		if (m == "12as.sub.grf")
		cout << m << "s: " << matches[i].second.score
				<< " d: " /*<< " RMSD: " << rmsds.at(i)*/;
		for (float f : matches[i].second.distances) {
			cout << f << " ";
		}
		cout << "l: " << matches[i].second.label_score << endl;

		matchesfile << m.substr(0,4)<<"\t"<<m.substr(9,m.length()-12) << "\t"
				<< matches[i].second.score << "\t"<<matches[i].second.rmsd<<"\t"<<matches[i].second.TMScore<<"\n";

//		m = m.substr(m.find(" ") + 1);
//		do {
//			int token1 = stoi(m.substr(0, m.find(" ")));
//			m = m.substr(m.find(" ") + 1);
//			int token2 = stoi(m.substr(0, m.find(" ")));
//			m = m.substr(m.find(" ") + 3);
//			glabels.push_back(token2);
//			cout << "token1: " << token1 << " token2: " << token2 << endl;
//
//		} while (m != "");
//		for (int key : glabels) {
//			vector<int>::iterator itr = find(tar_nums.begin(), tar_nums.end(),
//					key);
//
//			if (itr != tar_nums.cend()) {
//				cout << "tarnums: " << tar_nums.at(119);
//				cout << "Element present at index " << key << " "
//						<< distance(tar_nums.begin(), itr) << endl;
//			} else {
//				std::cout << "Element not found";
//			}
//		}

	}
	matchesfile.close();

//cout << "maxScore: " << maxScore << endl;
//cout << "this is the end" << endl;
//	printf("Time taken: %.2fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
//cout << "hold your breath and count to 10" << endl;

	return 0;
}
/*void writePDB(char *pdbFile) {

 try {
 ofstream Fout(pdbFile);

 if (!Fout) {
 cerr << "Cannot open pdb output file " << pdbFile << endl;
 exit(1);
 }

 // output coordinate
 int i, j, k;
 i = 0;

 for (i = 0; i < chain.size(); i++) {
 for (j = 0; j < chain[i].atom_p.size(); j++) {
 Atom* atm = chain[i].atom_p[j];
 Fout << "ATOM  " << atm->No << atm->name << atm->isomer
 << atm->residueName << atm->chainName << atm->residueNo
 << "   ";
 Fout.setf(ios::showpoint | ios::fixed);
 Fout << setprecision(3) << setw(8) << atm->xyz[0]
 << setprecision(3) << setw(8) << atm->xyz[1]
 << setprecision(3) << setw(8) << atm->xyz[2] << "  1.00"
 << setprecision(2) << setw(6) << atm->TFactor << endl;
 }
 Fout << "TER" << endl;
 }

 //output connection

 if (bondAvailable) {
 for (i = 0; i < atom_p.size(); i++) {
 Fout << "CONNECT" << atom_p[i]->No;
 for (int j = 0; j < atom_p[i]->bondNo; j++)
 Fout << atom_p[i]->bond[j]->No;
 Fout << endl;
 }
 }

 Fout << "END" << endl;

 Fout.close();
 }

 catch (char* pMsg) {
 cerr << endl << "Exception:" << pMsg << endl;
 }

 }
 */
/*void Protein::writePDB(char *file, char *chainName, int order=0)

 /* output to a PDB file
 order=0: original order
 order=1: reorder atom number, starting from 1
 order=2: reorder residue number, starting from 1
 order=3: reorder both
 /


 {
 ofstream Fout(file);

 if(!Fout) throw strcat("Error: cannot open pdb output file ",file);

 // output coordinate
 int i,j;
 i=0;

 if(chainName[0]==' ' || chainName[0]=='_') {
 for(i=0; i<chain.size(); i++) {
 for(j=0; j<chain[i].atom_p.size(); j++) {
 Atom *atm= chain[i].atom_p[j];

 Fout << "ATOM  ";
 if( order!=1 && order!=-3 )
 Fout << atm->No;
 else
 Fout << setw(5)<< atm->seqlNo + 1;
 Fout << atm->name;
 Fout << atm->isomer;
 Fout << atm->residueName << atm->chainName;
 if( order!=-2 && order!=-3 )
 Fout << atm->residueNo;
 else
 Fout << setw(4)<< atm->residueSeqlNo+1 <<" ";
 Fout << "   ";
 Fout.setf(ios::showpoint|ios::fixed);
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[0];
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[1];
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[2];
 Fout<<"  1.00" <<setprecision(2)<<setw(6)<< atm->TFactor <<endl;
 }
 Fout <<"TER"<<endl;
 }
 }
 else
 {

 if(!mapChain.count(chainName)) throw strcat("No such a chain name as ",chainName);

 for(j=0; j<mapChain[chainName]->atom_p.size(); j++) {
 Atom *atm= mapChain[chainName]->atom_p[j];

 Fout << "ATOM  ";
 if( order!=1 && order!=-3 )
 Fout << atm->No;
 else
 Fout << setw(5)<< atm->seqlNo + 1;
 Fout << atm->name;
 Fout << atm->isomer;
 Fout << atm->residueName << atm->chainName;
 if( order!=-2 && order!=-3 )
 Fout << atm->residueNo;
 else
 Fout << setw(4)<< atm->residueSeqlNo+1 <<" ";
 Fout << "   ";
 Fout.setf(ios::showpoint|ios::fixed);
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[0];
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[1];
 Fout<<setprecision(3)<<setw(8)<<atm->xyz[2];
 Fout<<"  1.00" <<setprecision(2)<<setw(6)<< atm->TFactor <<endl;
 }
 }


 //output connection
 for( i=0; i<atom_p.size(); i++ ) {
 Atom *atm = atom_p[i];

 if( order!=1 && order!=3 )
 {
 Fout<<"CONNECT"<<atm->No;
 for(int j=0;j<atm->bondNo;j++)  Fout<< atm->bond[j]->No;
 }
 else
 {
 Fout<<"CONNECT"<< setw(5) << atm->seqlNo + 1;
 for(int j=0;j<atm->bondNo;j++)
 Fout<< setw(5) << atm->bond[j]->seqlNo + 1;
 }

 Fout<<endl;
 }

 Fout << "END"<<endl;

 Fout.close();
 }
 */

