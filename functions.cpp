#include "classes.h"

using namespace std;

void metroMap::addStation(string &name, vector<string> &lines)
{
    station a;
    a.name = name;
    a.lines = lines;
    network[name] = a; // Add the station to the network
    // cout << "Inside addStation: Added station " << name << endl; // Debugging statement
}

void metroMap::addConnection(string src, string nbr, int dist)
{
    network[src].neighbours[nbr] = dist;
    network[nbr].neighbours[src] = dist;
    // cout << "Added connection between: " << src << " and " << nbr << " with distance " << dist << endl; // Debugging statement
}

void metroMap::printMap()
{
    for(auto &Station:network)
    {
        cout << Station.second.name << " : ";
        for(auto &line:Station.second.lines){
            cout<<line<<" ";
        }
        for(auto &nbr:Station.second.neighbours)
        {
            cout <<endl<< "          "<<nbr.first << " at distance " << nbr.second;
        }
        cout << endl;
    }
}

vector<pair<string, int>> metroMap::shortestPath(string &src, string &dest){
    vector<pair<string, int>> route;
    unordered_map<string, string> parent;
    unordered_map<string, int> distance;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> minHeap;

    for(auto statn:network)
        distance[statn.first] = int(1e8);

    minHeap.push({0, src});
    distance[src] = 0;

    while(!minHeap.empty())
    {
        auto top = minHeap.top();
        string statn = top.second;
        int dist = top.first;
        minHeap.pop();

        for(auto nbr:network[statn].neighbours)
        {
            string nbrstation = nbr.first;
            int newDistance = nbr.second + dist;
            //cout<<"nbr.second "<<nbr.second<<endl<<endl;
            // cout<<"New distance is "<<newDistance<<" for "<<statn<<" to "<<nbrstation<<endl;
            if(newDistance < distance[nbrstation])
            {
                parent[nbrstation] = statn;
                distance[nbrstation] = newDistance;
                minHeap.push({newDistance, nbrstation});
            }
        }
    }

    // for(auto it:parent)
    // {
    //     cout<<"Parent of "<<it.first<<" is "<<it.second<<endl;
    // }

    string curStation = dest;
    int dist=0;
    while(curStation != src)
    {
        string nextStation = parent[curStation];
        if(curStation != dest)  dist = network[curStation].neighbours[nextStation];
        route.push_back({curStation, dist});
        curStation = nextStation;
    }
    route.push_back({src, dist});

    return route;
}

vector<pair<string, vector<string>>> metroMap::junctions(){
    vector<pair<string, vector<string>>> ans;

    for(auto statn:network){
        int totLines = statn.second.lines.size();

        if(totLines>1){
            vector<string> allLines;
            for(auto it:statn.second.lines){
                allLines.push_back(it);
            }
            ans.push_back({statn.first, allLines});
        }
    }

    return ans;
}

vector<string> allLines(station statn){
    vector<string> ans;
    for(auto it:statn.lines){
        ans.push_back(it);
    }

    return ans;
}

void bridgesUtil(unordered_map<string, station> &network, string statnName, vector<pair<string, string>> &ans, unordered_map<string, bool> &visited, unordered_map<string, int> &disc, unordered_map<string, int> &minTime, int timer, string parent){
    visited[statnName] = true;                          //mark the station as visited
    disc[statnName] = minTime[statnName] = timer++;     //set discovery time and initial minimum time to discover as timer, and increase the timer for next iteration

    //iterate over the neighbours of current station
    for(auto nbr:network[statnName].neighbours){
        //continue to next neighbour if current neighbour is a parent
        if(parent==nbr.first)   continue;       
        
        //if the neighbour is visited and not a parent, we will adjust the minimum time of discovering our current station
        if(visited[nbr.first])               
            minTime[statnName] = min(minTime[statnName], disc[nbr.first]);
        
        //if the neighbour is unvisited, call the function for neighbour and while coming back, update the minTime for current station
        else{
            bridgesUtil(network, nbr.first, ans, visited, disc, minTime, timer, statnName);
            minTime[statnName] = min(minTime[statnName], minTime[nbr.first]);

            //check for bridge
            if(disc[statnName]<minTime[nbr.first]){
                ans.push_back({statnName, nbr.first});
            }
        }
    }

}

vector<pair<string, string>> metroMap::bridges(){
    vector<pair<string, string>> ans;           //will store the bridges 
    unordered_map<string, bool> visited;        //will track the stations already visited
    unordered_map<string, int> disc, minTime;   //will track the dicovery time and the minimum time to find a station

    for(auto statn:network){
        string statnName = statn.first;
        visited[statnName] = false;             //initiate all stations as unvisited
        disc[statnName] = -1;                   //initiate discovery time as -1 for every station
        minTime[statnName] = -1;                //initiate discovery time and minimum time to be found as -1 for every station
    }

    int timer = 0;                              //will track the time for discovering a station
    string parent = "";

    for(auto statn:network){
        if(!visited[statn.first]){
            bridgesUtil(network, statn.first, ans, visited, disc, minTime, timer, parent);
        }
    }

    return ans;
}

void printSimpleMap(vector<string> stationNames){
    cout<<"~~RED LINE~~"<<endl;
    for(int i=0; i<26; i++){
        cout<<stationNames[i]<<" -- ";
    }
    cout<<stationNames[26]<<endl<<endl;

    cout<<"~~BLUE LINE~~"<<endl;
    for(int i=27; i<48; i++){
        if(i==40)   cout<<stationNames[10]<<" -- ";
        cout<<stationNames[i]<<" -- ";
    }
    cout<<stationNames[48]<<endl<<endl;

    cout<<"~~GREEN LINE~~"<<endl;
    cout<<stationNames[35]<<" -- ";
    for(int i=49; i<56; i++){
        cout<<stationNames[i]<<" -- ";
    }
    cout<<stationNames[19]<<endl<<endl;
}