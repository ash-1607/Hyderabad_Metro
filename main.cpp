#include "classes.h"
#include "functions.cpp"

// using namespace std;

int main()
{
    int totalStations = 56;
    vector<string> stationNames = {
        // Red Line (starting from top left)
        "Miyapur", "JNTU College", "KPHB Colony", "Kukatpally", "Balanagar", "Moosapet", "Bharat Nagar", "Erragadda", "ESI Hospital", "S R Nagar", "Ameerpet", "Punjagutta", "Irrum Manzil", "Khairatabad", "Lakdikapul", "Assembly", "Nampally", "Gandhi Bhavan", "Osmania Medical College", "MG Bus Station", "Malakpet", "New Market", "Musarambagh", "Dilsukhnagar", "Chaitanyapuri", "Victoria Memorial", "LB Nagar",

        // Blue Line (starting from right side)
        "Nagole", "Uppal", "Stadium", "NGRI", "Habsiguda", "Tarnaka", "Mettuguda", "Secunderabad East", "Parade Ground", "Paradise", "Rasoolpura", "Prakash Nagar", "Begumpet", "Madhura Nagar", "Yusufguda", "Jubilee Hills Road No. 5", "Jubilee Hills Check Post", "Peddamma Gudi", "Madhapur", "Durgam Cheruvu", "HITEC City", "Raidurg",

        // Green Line (starting from top to bottom)
        "Secunderabad West", "Gandhi Hospital", "Musheerabad", "RTC X Roads", "Chikkadpally", "Narayanaguda", "Sultan Bazaar"
    };
    
    // unordered_map<string, int> stationNumber;
    metroMap HydMetro;


    //adding stations
    for(int i=0; i<totalStations; i++)     
    {
        //stationNumber[stationNames[i]] = i+1;
        vector<string> lines;
        if(i<27)    lines.push_back("Red");
        else if(i<49)   lines.push_back("Blue");
        else    lines.push_back("Green");

        if(i==10)   lines.push_back("Blue");
        else if(i==19)   lines.push_back("Green");
        else if(i==35)   lines.push_back("Green");

        HydMetro.addStation(stationNames[i], lines);
        // cout << "i is: "<<i<<endl<< "Added station: " << stationNames[i]; // Debugging statement
        // cout<<endl;
        // for(auto it:lines){
        //     cout<<it<<" ";
        // }
        // cout<<endl;
    }

    // cout<<"Stations added"<<endl;            Debugging statement

    //adding connections
    for(int i=0; i<totalStations-1; i++)
    {
        if(i==26)   continue;
        if(i==39)   continue;
        if(i==48)   continue;
        HydMetro.addConnection(stationNames[i], stationNames[i+1], 1);
    }
    HydMetro.addConnection("Ameerpet", "Begumpet", 1);
    HydMetro.addConnection("Ameerpet", "Madhura Nagar", 1);
    HydMetro.addConnection("Parade Ground", "Secunderabad West", 1);
    HydMetro.addConnection("MG Bus Station", "Sultan Bazaar", 1);
    // cout<<"Connections added"<<endl;         Debugging statement

    //HydMetro.printMap();
    
    while(true){
        int option = -1;
        cout<<endl<<endl;
        cout<<"\t\t\t***************************************************"<<endl;
        cout<<"\t\t\t*                                                 *"<<endl;
        cout<<"\t\t\t*                                                 *"<<endl;
        cout<<"\t\t\t*         ------------------------------          *"<<endl;
        cout<<"\t\t\t*           WELCOME TO HYDERABAD METRO            *"<<endl;
        cout<<"\t\t\t*         ------------------------------          *"<<endl;
        // cout<<"*              by: Ashmeet Sidhu                  *"<<endl;
        cout<<"\t\t\t*                                                 *"<<endl;
        cout<<"\t\t\t*                                                 *"<<endl;
        cout<<"\t\t\t***************************************************"<<endl<<endl<<endl;
        cout<<"\t\t\t***************************************************"<<endl<<endl;
        cout<<"\t\t\t            1. METRO MAP                           "<<endl;
        cout<<"\t\t\t            2. TRAVEL                              "<<endl;
        cout<<"\t\t\t            3. JUNCTION STATIONS                   "<<endl;
        cout<<"\t\t\t            4. BRIDGE CONNECTIONS                  "<<endl;
        // cout<<"Enter 5 to get the Minimum Spanning Tree"<<endl;
        cout<<"\t\t\t            5. METRO GRAPH (for developers only)   "<<endl;
        cout<<"\t\t\t            0. Exit the program                    "<<endl<<endl;
        cout<<"\t\t\t***************************************************"<<endl;
        cout<<"\t\t\t\tENTER YOUR CHOICE: ";

        int choice;
        cin>>choice;
        switch(choice)
        {
            case 0: {
                cout<<"Exiting the program..."<<endl<<endl;
                return 0;
            }
            case 1: {
                printSimpleMap(stationNames);
                break;
            }
            case 2: {
                string src, dest;
                cout<<"Enter the starting station: ";   
                getline(cin, src);
                getline(cin, src); 
                cout<<"Enter the destination: ";        
                getline(cin, dest); 

                // ask for a via option
                cout<<"Do you want to travel via some other station in between? YES/NO"<<endl;
                string via, viaStation;
                getline(cin, via);

                //if via station is there
                if((via) == "YES"){
                    cout<<"Enter the via station: ";
                    getline(cin, viaStation);

                    // cout<<"Checkpoint 1"<<endl;
                    vector<pair<string, int>> route1 = HydMetro.shortestPath(src, viaStation);
                    
                    vector<pair<string, int>> route2 = HydMetro.shortestPath(viaStation, dest);
                    

                    int pathLen1 = route1.size(), pathLen2 = route2.size();
                    int dist1 = 0, dist2 = 0;

                    cout<<endl<<"== YOUR ROUTE =="<<endl;

                    string line = " ";
                    if(HydMetro.network[src].lines.size()<=1){
                        line = HydMetro.network[src].lines[0];
                        cout<<"-> Start from line "<<line<<":"<<endl;
                    }   
                    else{
                        line = HydMetro.network[route1[pathLen1-2].first].lines[0];
                        cout<<"-> Start from line "<<line<<":"<<endl;
                    }       
                    string curLine = line;

                    //print first route
                    for(int i=pathLen1-1; i>0; i--){
                        station curStation = HydMetro.network[route1[i].first];
                        if(curStation.lines.size()<=1)   curLine = curStation.lines[0];
                        // cout<<" curStation: "<<curStation.name<<endl;

                        //if line changes
                        if(curLine != line){
                            cout<<endl<<endl<<"-> Switch to line "<<curLine<<" at "<<route1[i+1].first<<endl;
                            line = curLine;
                        }

                        cout<<route1[i].first<<" --"<<route1[i].second<<"-- ";
                        dist1 += route1[i].second;
                    }
                    // cout<<"first route printed"<<endl;
                    //print second route
                    for(int i=pathLen2-1; i>0; i--){
                        station curStation = HydMetro.network[route2[i].first];
                        if(curStation.lines.size()<=1)   curLine = curStation.lines[0];
                        // cout<<" curStation: "<<curStation.name<<endl;

                        //if line changes
                        if(curLine != line){
                            string prevStation;
                            if(i!=pathLen2-1)   prevStation = route2[i+1].first;
                            else    prevStation = route1[1].first;
                            cout<<endl<<endl<<"-> Switch to line "<<curLine<<" at "<<prevStation<<endl;
                            line = curLine;
                        }

                        cout<<route2[i].first<<" --"<<route2[i].second<<"-- ";
                        dist2 += route2[i].second;
                    }
                    if(HydMetro.network[route2[0].first].lines.size()<=1 && HydMetro.network[route2[0].first].lines[0]!=line){
                        curLine = HydMetro.network[route2[0].first].lines[0];       //Error rectified
                        cout<<endl<<endl<<"-> Switch to line "<<curLine<<" at "<<route2[1].first<<endl;
                    }
                    cout<<route2[0].first;
                    // cout<<endl<<endl<<"Total hmm distance is: "<<dist1+dist2<<endl<<endl;
                    // cout<<"hehe "<<route2[1].second<<endl;

                    break;
                }

                //if no via station
                else{
                    vector<pair<string, int>> route = HydMetro.shortestPath(src, dest);
                    int pathLen = route.size();
                    int dist = 0;

                    //Troubleshooting
                    // for(auto it:route){
                    //     cout<<"# "<<it.first<<" "<<it.second<<endl;
                    // }

                    cout<<endl<<"== YOUR ROUTE =="<<endl<<endl;

                    string line = " ";
                    if(HydMetro.network[src].lines.size()<=1){
                        line = HydMetro.network[src].lines[0];
                        cout<<"-> Start from line "<<line<<":"<<endl;
                    }   
                    else{
                        line = HydMetro.network[route[pathLen-1].first].lines[0];
                        cout<<"-> Start from line "<<line<<":"<<endl;
                    }       
                    string curLine = line;

                    for(int i=pathLen-1; i>0; i--)
                    {
                        station curStation = HydMetro.network[route[i].first];
                        if(curStation.lines.size()<=1)   curLine = curStation.lines[0];
                        // cout<<" curStation: "<<curStation.name<<endl;

                        //if line changes
                        if(curLine != line){
                            cout<<endl<<endl<<"-> Switch to line "<<curLine<<" at "<<route[i+1].first<<endl;
                            line = curLine;
                        }

                        cout<<route[i].first<<" --"<<route[i].second<<"-- ";
                        // cout<<" Line is: "<<curLine<<endl;
                        dist += route[i].second;
                    }
                    cout<<route[0].first;
                    cout<<endl<<endl<<"Total distance is: "<<dist<<endl<<endl;

                    break;
                }
            }

            case 3:{
                vector<pair<string, vector<string>>> junctns = HydMetro.junctions();

                int num=1;
                cout<<endl<<"==JUNCTION STATIONS=="<<endl;
                for(auto statn:junctns){
                    cout<<num<<") "<<statn.first<<", comes under: ";
                    num++;
                    for(auto line:statn.second){
                        cout<<" =>"<<line<<" ";
                    }
                    cout<<endl;
                }

                break;
            }

            case 4:{
                vector<pair<string, string>> bridges = HydMetro.bridges();
                cout<<endl<<"==BRIDGES=="<<endl;

                int num=1;
                for(auto bridge:bridges){
                    cout<<num<<") "<<bridge.first<<" -- "<<bridge.second<<endl;
                    num++;
                }
                break;
            }
            case 5:{
                HydMetro.printMap();        //CHECK, map is incorrect
                break;
            }
            default: {
                cout<<"ERROR: Invalid choice!!!"<<endl;
            }
        }
    }


    

    return 0;
}