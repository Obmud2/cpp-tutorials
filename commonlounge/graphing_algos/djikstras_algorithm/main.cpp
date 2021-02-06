//
//  main.cpp
//  djikstras_algorithm
//
//  Created by Jon Pring on 05/02/2021.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

void djikstra_algo(vector<tuple<int, int, int>> edges, const int m, const int n, ofstream &ofs){
    // n = number of nodes
    // m = number of edges
    // edges = (x, y, w)
    vector<bool> visited(n, 0);
    vector<vector<pair<int, int>>> adj_list(n);
    
    // create adjacency matrix
    for (int i{0}; i<m; i++){
        int x {get<0>(edges[i])};
        int y {get<1>(edges[i])};
        int w {get<2>(edges[i])};
        adj_list[x].push_back({y, w});
        adj_list[y].push_back({x, w});
    }
    
    // initiate queue (node, dist) and tentative distance vector
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n, 0x7fffffff);
    
    // visit first node of graph and add to queue
    int src{0};
    dist[src] = 0;
    pq.push({dist[src], src});
    
    while(!pq.empty()){
        // visit node at the front of the queue
        int node {pq.top().second};
        pq.pop();
        
        if (visited[node]){continue;}
        visited[node] = 1;
        
        // assign tentative distance to all unvisited neighbours of the curent node
        for (auto neighbour:adj_list[node]){
            int v {neighbour.first}; // node
            int w {neighbour.second}; // weight
            // assign new best distance
            if (dist[v] > dist[node] + w){
                dist[v] = dist[node] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    // write output to ofs
    for (auto d:dist){
        ofs << d << " ";
    }
    ofs << endl;
}

int main(int argc, const char * argv[]) {
    
    ifstream ifs;
    ofstream ofs;
    
    ifs.open("input");
    ofs.open("output");
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
        
        // apply djikstra's shortest path algorithm
        djikstra_algo(edges, m, n, ofs);
    }
    
    ifs.close();
    ofs.close();
    
    return 0;
}
