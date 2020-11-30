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
    int bufferSize;
    double delayProcessing;
    double delayTransmission;
    double speedPropagation;
    double lossProbability;
    double bandwidth;
    bool bufferFull;
    bool canRoute;
  public:
    Router();
    Router(int id, int bSize, double d_proc, double d_trans, double s_prop, double loss, double band);
    ~Router();

    void newLink(Router * newRouter, int length);
    double timeOfTravel(Router * dest, int packetSize);
    int getID();

    vector<pair<Router*, int>> routerLinks;
};