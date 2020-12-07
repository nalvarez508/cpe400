/*
Nick Alvarez, Jayam Sutariya
CPE 400, Fall 2020, Final Project
Dynamic Routing with a focus on Throughput

--router source file (class implementation)--
*/

#include "Router.h"
#include <iostream>
using namespace std;

//default constructor
Router::Router()
{
  ID = -1;
  bufferSize = 0;
  delayProcessing = INT_MAX;
  delayTransmission = 0;
  speedPropagation = 200000000;
  lossProbability = 1;
  bandwidth = 1000000;
  bufferFull = 0;
  canRoute = 0;
}

//parameterized constructor
Router::Router(int id, int bSize, double d_proc, double d_trans, double s_prop, double loss, double band)
{
  ID = id;
  bufferSize = bSize;
  delayProcessing = d_proc;
  delayTransmission = d_trans;
  speedPropagation = s_prop;
  lossProbability = loss;
  bandwidth = band;
}

void Router::newLink(Router * newRouter, int length)
{
  routerLinks.push_back(make_pair(newRouter, length));
}

double Router::totalDelay(Router * r, int packetSize, int x)
{
  //double delayNodal = dest->delayProcessing;
  double delayQueueing; //Some rand
  double delayTransmission = packetSize/bandwidth;
  double delayPropagation = routerLinks[x].second/speedPropagation;
  return (delayQueueing + delayPropagation + delayTransmission);
}

double Router::timeOfTravel(Router * dest, int packetSize)
{
  for (int x=0; x<routerLinks.size(); x++) //Checks all links from child (passed) router
  {
    if (routerLinks[x].first == dest) //Finds link chosen in nodePath
    {
      //nodal + queue + trans + prop
      //Nodal: Arbitrary
      //Queueing: Congestion based
      //Transmission: packet size / bandwidth
      //Propagation: length / speed
      //double delayNodal = dest->delayProcessing;
      double delayQueueing; //Some rand
      double delayTransmission = packetSize/bandwidth;
      double delayPropagation = routerLinks[x].second/speedPropagation;
      return (delayPropagation + delayTransmission); //Router found
    }
  }

  //Router not found
  cout << "The packet was not able to find a path to the specified router." << endl;
}

int Router::getID()
{
  return ID;
}