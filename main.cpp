/*
Nick Alvarez, Jayam Sutariya
CPE 400, Fall 2020, Final Project
Dynamic Routing with a focus on Throughput

--driver file--
*/

#include "Router.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <set>
#include <time.h>
using namespace std;

//Globals
double timeFinal = 0;
int destination;
vector<Router*> networkMesh;

vector<pair<int, int>> shortestPath(int startID, int dest, vector<vector<pair<int, int>>> routerLinks)
{
  set<pair<int, int>> finalRoute;
  int cursor = 0;
  vector<pair<int, int>> minDistance;

  for (int x=0; x<routerLinks.size(); i++)
    minDistance.push_back(make_pair(INT_MAX, -1));
  minDistance[startID].first = 0;
  finalRoute.insert({0, startID});

  //Evaluating travel times
  while (!finalRoute.empty())
  {
    int location = finalRoute.begin()->second;
    if (location == dest)
      return minDistance;
    finalRoute.erase(finalRoute.begin());

    for (auto z : routerLinks[location])
    {
      //Better path found
      if (minDistance[z.first].first > minDistance[location].first + z.second)
      {
        finalRoute.erase({minDistance[z.first].first, z.first});
        minDistance[z.first].first = minDistance[location].first + z.second;
        minDistance[z.first].second = location;
        finalRoute.insert({minDistance[z.first].first, z.first});
      }
    }
  }
  return minDistance;
}

void printPath(vector<int> nodePath)
{
  cout << "Packet originates from router " << nodePath[nodePath.size()-2] << endl;
  for (int x=nodePath.size()-3; x>=0; x--)
    cout << "---> router " << nodePath[i] << endl;
  cout << "Packet has arrived." << endl;
}

int main()
{
  //Variables
  int packetSize = 256;
  int bufferSize = 4096;
  double bandwidth = 1500;
  double packetLoss = 0.05;
  double dProc = 0.05;
  double dTrans = 0.05;
  double dProp = 1;
  double dDist = 0;
  double dTotal = 0;
  int lostPackets = 0;
  int numberPackets = 1;
  int origin;
  int numberRouters = 15;

  vector<vector<pair<int, int>>> linkDistances;
  char input;

  cout << "##### Dynamic Routing Simulator #####" << endl;
  cout << "The network will be generated with " << numberRouters << " nodes." << endl;

  cout << "Origin ID: ";
  cin >> origin;
  cout << "Destination ID: ";
  cin >> destination;

  //Node Creation
  for (int x=0; x < numberRouters; x++)
  {
    Router * temp = new Router(x, bufferSize, dProc, dTrans, dProp, packetLoss, bandwidth);
    networkMesh.push_back(temp);
  }

  //Mesh Creation (TODO)

  for (int x=0; i<numberRouters; x++)
  {
    int totalLinks = networkMesh[i]->routerLinks.size();
    linkDistances.push_back(vector<pair<int, int>>());
    for (int y=0; y<totalLinks; y++)
    {
      dDist = networkMesh[x]->routerLinks[y].second;
      linkDistances[x].push_back(make_pair(networkMesh[x]->routerLinks[y].first->getID(), dDist));
    }
  }

  vector<pair<int, int>> pathInfo = shortestPath(origin, destination, linkDistances);
  int jumps = 0;
  int prevRouter = pathInfo[destination].second;
  vector<int> nodePath;
  nodePath.push_back(destination);
  nodePath.push_back(prevRouter);

  while (prevRouter != -1)
  {
    jumps++;
    prevRouter = pathInfo[prevRouter].second;
    nodePath.push_back(prevRouter);
  }
  printPath(nodePath);

  Router * parent;
  Router * child;
  bool lost = 0;
  double timer;
  int randMax = 100;
  int randProb;
  srand(time(NULL));
  int droppedRouter = 0;

  for (int x=nodePath.size()-2; x>0; x--)
  {
    randProb = (rand() % 101);
    if (randProb < packetLoss*100)
    {
      if (numberPackets == 1)
        droppedRouter = x;
      else
        droppedRouter = rand() % (nodePath.size()-2);
      
      cout << "Lost packet! From " << nodePath[droppedRouter] << " to " << nodePath[droppedRouter-1] << "." << endl;
      lost = 1;
    }

    parent = networkMesh[nodePath[x]];
    child = networkMesh[nodePath[x-1]];
    timer = parent->timeOfTravel(child, packetSize);
    if (lost)
    {
      x++;
      lostPackets++;
      lost = 0;
    }
    else if (numberPackets > 1)
    {
      numberPackets--;
      x++;
    }
    timeFinal += timer;
  }
  cout << "Travel time: " << timeFinal << " ms" << endl;
  cout << lostPackets << " lost packet(s)" << endl;

  return 0;
}