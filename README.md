# CPE 400: Computer Communication Networks
## Dynamic Routing Mechanism Design with Focus on Throughput
### Fall 2020, S. Sengupta
Created by Nick Alarez and Jayam Sutariya

# Overview of Project Components
## Class: Router
### Private Member Variables
```C++
int ID //The router identifier
int bufferSize //Size of router's buffer (bytes)
double delayProcessing //Nodal processing delay (seconds)
double delayTransmission //Link delay (seconds)
double speedPropagation //Propagation speed of medium
double lossProbability //Chance of losing packet en route to destination
double bandwidth //Uplink speed, used in calculating propagation delay
bool bufferFull //Congestion flag
bool canRoute //Deprecated, unused
```
### Public Member Functions
```C++
Router() //Default constructor
Router(int id, int bSize, double d_proc, double d_trans, double s_prop, double loss, double band) //Parameterized constructor
~Router(); //Destructor
void newLink(Router * newRouter, int length) //Creates new connection on graph, taking in a Router object and distance
double timeOfTravel(Router * dest, int packetSize) //Used to calculate packet transmission time by adding propagation delay and transmission delay. Propagation delay is calculated by dividing the size of packet by bandwidth and adding that to the length divided by propagation speed.
int getID() //Returns router identifier
```
### Public Member Variables
```C++
vector<pair<Router*, int>> routerLinks //Vector representation of the network graph
```

## Driver File
### Global Variables
```C++
double timeFinal //Packet travel time
int destination //Destination router ID
vector<Router*> networkMesh //Stores graph outside of class, similar to routerLinks
```
### Initial Variables
Only variables that are not already listed under the Router class will be mentioned here.
```C++
int packetSize //Size of packet (bytes, default 256)
double dDist
double dTotal //Total delay (seconds)
int lostPackets //Number of lost packets
int numberPackets //Packets to send (default 1)
int origin //Source router ID
int numberRouters //Number of routers in network (default 15)
vector<vector<pair<int, int>>> linkDistances //Deprecated, unused
char input //Deprecated, unused
```
### Functions
#### shortestPath()
```C++
vector<pair<int, int>> shortestPath(int startID, int dest, vector<vector<pair<int, int>>> routerLinks)
```
Creates a `finalRoute` set which contains the step number and the ID of the router.

Creates a `minDistance` vector pair with distance and router ID.

#### printPath()
```C++
void printPath(vector<int> nodePath)
```
This function uses the `nodePath` vector to step through the packet's route and print each iteration.

### main() Code
Initial variables are created. User is asked for source and destination router IDs.

The Router objects are created in a for loop using the initialized variables and each router is put into the `networkMesh` vector correlating to their IDs.

The network mesh is created. The graph is arbitrary.

![Image of Network Graph](Graph.png?raw=true "Network Mesh")

Next, the the `totalLinks` variable is created which