//
//  main.cpp
//  breadth_search
//
//  Created by Jon Pring on 28/01/2021.
//

#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

void breadth_search (vector<pair<int, int>> edges, int m, int n, ofstream &ofs){
    vector<bool> vis(n, 0);
    vector<vector<int>> adj_list(n);
    
    // Create adjacency matrix from edges
    for (int i{0}; i < m; i++){
        int x { edges[i].first  };
        int y { edges[i].second };
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }
    
    queue<int> q;
    vector<int> dist(m, 0);
    
    // Visit first node of graph and add to queue
    q.push(0);
    vis[0] = 1;
    dist[0] = 0;
    
    while (!q.empty()){
        // Take first node in queue (FIFO)
        int node {q.front()};
        q.pop();
        //cout << "Visted node: " << node << endl;
        
        // Add each connected edge to queue
        for (auto neighbour:adj_list[node]){
            if (!vis[neighbour]){
                q.push(neighbour);
                vis[neighbour] = 1;
                dist[neighbour] = dist[node] + 1;
            }
        }
    }
    
    for (int v{0}; v < n; v++){
        if (vis[v] == 0){
            ofs << "INF ";
        }
        else {
            ofs << dist[v] << " ";
        }
    }
    ofs << endl;
}

int main() {
    
    ifstream ifs;
    ofstream ofs;
    
    ifs.open("input");
    ofs.open("output");
    string testcase;
    
    while(getline(ifs, testcase)){
        cout << testcase << endl;
        int n, m;
        vector<pair<int, int>> edges;
        
        // get testcase from input file
        ifs >> n >> m;
        cout << "n=" << n << " m=" << m << endl;
        for (int i{0}; i < m; i++){
            pair<int, int> temp_pair;
            ifs >> temp_pair.first >> temp_pair.second;
            edges.push_back(temp_pair);
        }
        ifs.ignore(100, '\n');
        
        breadth_search(edges, m, n, ofs);
    }
    
    ifs.close();
    ofs.close();
    
    return 0;
}
