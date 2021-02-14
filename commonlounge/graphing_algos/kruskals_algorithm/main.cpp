//
//  main.cpp
//  kruskals_algorithm
//
//  Created by Jon Pring on 13/02/2021.
//

#include <iostream>
#include <fstream>
#include <tuple>
#include <queue>
#include <vector>
using namespace std;

// find representative root of the node (which set the node is in)
int root(vector<int>&parent, int x){
    if (parent[x] == x){
        return x;
    }
    // compress tree by assigning visited node's parent to root
    int rt = root(parent, parent[x]);
    parent[x] = rt;
    return rt;
}

// add nodes to set by joining sets
void join(vector<int> &parent, vector<int> &rank, int x_root, int y_root){
    
    if (rank[x_root] > rank[y_root]){
        parent[y_root] = x_root;
    }
    else if (rank[x_root] < rank[y_root]){
        parent[x_root] = y_root;
    }
    else {
        parent[y_root] = x_root;
        rank[x_root]++;
    }
}

bool kruskals_algorithm(vector<tuple<int, int, int>> edges, const int n, ofstream &ofs){
    // n = number of nodes
    // edges = (x, y, w)
    
    // initiate mst and cost
    vector<pair<int, int>> mst;
    int cost {0};
    
    // sort unique edges (queue)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    for (int i{0}; i < edges.size(); i++){
        pq.push({get<2>(edges[i]), get<0>(edges[i]), get<1>(edges[i])});
    }
    
    // create disjoint sets
    vector<int> parent, rank;
    for (int i{0}; i < n; i++){
        parent.push_back(i);
        rank.push_back(1);
    }
    
    
    while (!pq.empty()){
        // select lowest cost edge
        int w {get<0>(pq.top())};
        int x {get<1>(pq.top())};
        int y {get<2>(pq.top())};
        int x_root {root(parent, x)};
        int y_root {root(parent, y)};
        pq.pop();
        
        // if nodes do not share root (< 2 nodes in set), add nodes to set and edge to mst
        if (x_root != y_root){
            join(parent, rank, x_root, y_root);
            cost += w;
            mst.push_back({x, y});
        }
        
    }
    
    // if not all nodes are added to the set, return false
    for (auto i:parent){
        if (i != parent[0]){
            ofs << "INF" << endl;
            return 0;
        }
    }
    
    // else return mst and cost when queue is empty
    ofs << cost << ": ";
    for (auto branch:mst){
        ofs << branch.first << " " << branch.second;
        if (branch == mst.back()){
            ofs << endl;
        }
        else {
            ofs << ", ";
        }
    }
    return 1;
    
}

int main(int argc, const char * argv[]) {
    
    ifstream ifs;
    ofstream ofs;
    ifs.open("mst_input");
    ofs.open("mst_output");
    
    string testcase;
    
    while(getline(ifs, testcase)){
        cout << testcase << endl;
        int n, m;
        vector<tuple<int, int, int>> edges;
        
        // get testcase from input file
        ifs >> n >> m;
        cout << "n=" << n << " m=" << m << endl;
        for (int i{0}; i < m; i++){
            tuple<int, int, int> temp_input;
            ifs >> get<0>(temp_input) >> get<1>(temp_input) >> get<2>(temp_input);
            edges.push_back(temp_input);
        }
        ifs.ignore(100, '\n');
        
        // apply mst algorithm (Kruskal's algorithm)
        cout << "Min cost: " << kruskals_algorithm(edges, n, ofs) << endl;
    }
    
    ifs.close();
    ofs.close();
    return 0;
}
