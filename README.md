# Hyderabad Metro Network 

This is a C++ project that simulates the Hyderabad Metro network using graph data structures. It demonstrates the capabilities of graph algorithms in solving real-world problems related to transportation networks.

-----------------------
Usage and Instructions
-----------------------
- Compile the **main.cpp** and run *(do not compile **functions.cpp** as it is already included in main.cpp)*
- Download all the files into a single folder and run the following commands in terminal.<br>
 **g++ main.cpp**<br>
 **.\a.exe**
- To get all the station names and the map, you can either view option **1.METRO MAP** for simple representation or view option **5.METRO GRAPH** for all the connections. Alternatively, just look at image **Hyd_Metro_Map** provided in the git repository.
- Make sure to enter the station names accurately and also the letter case.

---------------------
Menu Options
---------------------
- METRO MAP
Simple representation of all the stations line-wise (**red**, **blue**, and **green**). *(not a graph implementation)*
- TRAVEL
To travel from one station to another, along with a **via** option to travel to another station station in between.
- JUNCTION STATIONS
Get the junction stations *(stations that come under multiple metro lines).*
- BRIDGE CONNECTIONS
Get the bridge connections *(upon removing a bridge connection, the graph gets divided into separate components)*.
- METRO GRAPH (for developers only)
This contains the actual connections between the stations along with the distance (*weight*) between them.
- Exit the program
This will exit from the program.

