/* Author: Gage Zahn
*  Date: 7/7/2022
*  Class: COP3530 
*/

#include <iostream>
#include <iomanip>  
#include<map>
#include<vector>
#include<iterator>
using namespace std;

class AdjacencyList {
private:
    struct Vertex {//Stores all Node information
        vector<string> inwardEdges;
        unsigned int outwardEdgeCount;
        float rank;
        Vertex();
    };
    map<string, Vertex>* graph; //Stores all nodes in the graph using their URL as the key
public:
    AdjacencyList();
    ~AdjacencyList();
    void insert(string from, string to);
    void PageRank(int n);
};

//Constructors/Destructors
AdjacencyList::AdjacencyList() {
    graph = new map<string, Vertex>;
}

AdjacencyList::~AdjacencyList() {
    delete graph;
}

AdjacencyList::Vertex::Vertex() {
    inwardEdges = {};
    rank = 0;
    outwardEdgeCount = 0;
}


//Insert
void AdjacencyList::insert(string from, string to) {
    (* graph)[to].inwardEdges.push_back(from);      //Add the edge to the inwardEdge list of the Node the Edge points to: Ex. a -> b... add a to b's inwardEdges
    (*graph)[from].outwardEdgeCount++;              //Create a from node if needed and Increment its outwardEdgeCount 
}


void AdjacencyList::PageRank(int n) { // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places
    for (int i = 0; i < n; i++) { // Power Iterations
        map<string, float> temp;
        
        for (auto j = graph->begin(); j != graph->end(); j++) { //Once per Node
            if (i == 0) { //r(0)
                j->second.rank = 1.0f / graph->size();
                continue;
            }

            //r(t) | t > 0
            float newRank = 0;
            for (string k : j->second.inwardEdges) { //Once per Node Connection: matrix multiplication by row
                newRank += (*graph)[k].rank * 1.0f / (*graph)[k].outwardEdgeCount;
            }
            temp[j->first] = newRank; //Store new ranks
        }
        
        if(i != 0){ //Update Ranks to newRank
            for (auto j = graph->begin(); j != graph->end(); j++) {
                j->second.rank = temp[j->first];
            }
        }
    }

    //Print Results
    for (auto i = graph->begin(); i != graph->end(); i++) {
        cout << i->first << " " << fixed << setprecision(2) << i->second.rank << endl;
    }
} 

int main()
{
    AdjacencyList graph;
    int no_of_lines, power_iterations;
    string from, to;

    //Input
    cin >> no_of_lines;
    cin >> power_iterations;
    for (int i = 0; i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        graph.insert(from, to); //Add edge to graph
    }
    graph.PageRank(power_iterations); //Calculate page rank and print results
}