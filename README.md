# Hyderabad Metro Network 

This is a C++ project that simulates the Hyderabad Metro network using graph data structures. It demonstrates the capabilities of graph algorithms in solving real-world problems related to transportation networks.

-----------------------
Usage and Instructions
-----------------------
- Just compile the main.cpp and run (do not compile fucntions.cpp as it is already included in main.cpp)
- Download all the files into a single folder and run the following commands in terminal.
g++ main.cpp
.\a.exe
- To get all the station names and the map, you can either view option 1.METRO MAP for simple representation or view option 5.METRO GRAPH for all the connections. Alternatively, just look at image provided in the git repository.

---------------------
Menu Options
---------------------
- 1) METRO MAP
Simple representation of all the stations line-wise (red, blue, and green). (not a graph implementation)
- 2) TRAVEL
To travel from one station to another, along with a "via" option to travel to another station station in between.
- 3) JUNCTION STATIONS
Get the junction stations (stations that come under multiple metro lines).
- 4) BRIDGE CONNECTIONS
Get the bridge connection (upon removing a bridge connection, the graph gets divided into separate components).
- 5) METRO GRAPH (for developers only)
This contains the actual connections between the stations along with the distance (weight) between them.
- 0) Exit the program
This will exit from the program.

