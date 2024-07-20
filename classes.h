#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits.h>

using namespace std;

class station{
public:
    string name;
    //int stationNum;
    vector<string> lines;
    unordered_map<string, int> neighbours;  //adj list with neighbours and their distances
};

class metroMap{
public:
    unordered_map<string, station> network;
    
    void addStation(string &name, vector<string> &lines);
    void addConnection(string src, string nbr, int dist);

    void printMap();


    //shortest route and distance using Dijkstra
    vector<pair<string, int>> shortestPath(string& src, string& dest);

    //returns junction stations which connect with multiple metro lines
    vector<pair<string, vector<string>>> junctions();

    vector<pair<string, string>> bridges();

    //Minimum Spanning Tree

};

void printSimpleMap(vector<string> stationNames);