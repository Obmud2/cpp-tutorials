//
//  main.cpp
//  prims_algorithm
//
//  Created by Jon Pring on 08/02/2021.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

int prims_algorithm (vector<tuple<int, int, int>> edges, const int n, ofstream &ofs){
    // n = number of nodes
    // m = number of edges
    // edges = (x, y, w)
    vector<bool> visited(n, 0);
    vector<vector<pair<int, int>>> adj_list(n);
    
    // create adjacency matrix
    for (int i{0}; i<edges.size(); i++){
        adj_list[get<0>(edges[i])].push_back({get<1>(edges[i]), get<2>(edges[i])});
        adj_list[get<1>(edges[i])].push_back({get<0>(edges[i]), get<2>(edges[i])});
    }
    
    // minimum spanning tree
    vector<pair<int, int>> mst;
    
    // initiate queue (w, x, y) for nodes to compare
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    
    int cost {0};
    
    // visit first node
    int src {0};
    for (auto i:adj_list[src]){
        pq.push({i.second, src, i.first});
    }
    visited[src] = 1;
    
    while(!pq.empty()){
        
        int weight    {get<0>(pq.top())};
        int prev_node {get<1>(pq.top())};
        int node      {get<2>(pq.top())};
        pq.pop();
        
        if (visited[node]){continue;}
        
        cost += weight;
        mst.push_back({prev_node, node});
        visited[node] = 1;
        
        for (auto i:adj_list[node]){
            pq.push({i.second, node, i.first});
        }
    }
    
    for (auto v:visited){
        if (!v){
            ofs << "INF" << endl;
            return 0x7fffffff;
        }
    }
    
    ofs << cost << " ";
    
    for (auto branch:mst){
        ofs << branch.first << " " << branch.second;
        if (branch != mst.back()){
            ofs << ", ";
        }
    }
    ofs << endl;
    
    return cost;
    
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
        
        // apply mst algorithm (Prim's algorithm)
        cout << "Min cost: " << prims_algorithm(edges, n, ofs) << endl;
    }
    
    ifs.close();
    ofs.close();
    
    /*
    vector<tuple<int, int, int>> edges {
        {0, 1, 5},
        {1, 2, 13},
        {2, 3, 6},
        {3, 4, 14},
        {4, 5, 4},
        {5, 6, 10},
        {0, 6, 17},
        {1, 6, 12},
        {1, 4, 8},
        {2, 4, 11},
        {4, 6, 8}
    };
    int n{7};
    
    prims_algorithm(edges, n);
    */
    
    return 0;
}
