#ifndef TO_GRAPH_H
#define TO_GRAPH_H
#include<string>
#include<vector>
#include<QDir>
using namespace std;
class To_Graph
{
public:

    To_Graph(string fileName,string residues, int thereshold,int* selected_thereshold);
    To_Graph(string fileName, int thereshold);
    int THRESHOLD=15;

    vector<string> get_aminos();

};


#endif // TO_GRAPH_H
