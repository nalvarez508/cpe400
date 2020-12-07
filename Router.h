/*
Nick Alvarez, Jayam Sutariya
CPE 400, Fall 2020, Final Project
Dynamic Routing with a focus on Throughput

--router header file (class declaration)--
*/

#include <time.h>
#include <vector>
#include <climits>
using namespace std;

class Router
{
  private:
    int ID;
    double delayProcessing;
    double delayTransmission;
    double delayQueuing;
    double delayPropagation;
    double speedPropagation;
    double lossProbability;
    double bandwidth;
  public:
    Router();
    Router(int id, double s_prop, double loss, double band);
    ~Router();

    void newLink(Router * newRouter, int length);
    double totalDelay(Router * r, int packetSize, int x);
    double timeOfTravel(Router * dest, int packetSize);
    int getID();

    vector<pair<Router*, int> > routerLinks;
};