#include "vehicle.h"

using namespace std;

float findPositionInLanes(float*, int, int, float);
float overTakeNthLane(float*, float, int,vector<VEHICLE> , int, int);
vector<float> color_RGB(string);
vector<int> getIndexVector(vector<vector<VEHICLE> > ,int );
int distance(vector<vector<VEHICLE> >, int, float, int);
vector<VEHICLE> sortVehicles(vector<vector<VEHICLE> >);
int findVehicleIndex(vector<VEHICLE>, string);
int findPresentIndex(vector<VEHICLE>, int);
int findNewIndex(vector<VEHICLE>, int);
void update (int);
void drawScene();
void  printLane(vector<vector<VEHICLE> >);

extern vector<VEHICLE> objects, myVector;
extern vector<vector<VEHICLE> > lane;
extern fstream inFile;
extern int roadLength,roadWidth,roadId,roadSignal, stopLine,cont, gen, parameter,id, c1, c2;
extern float defaultSpeed, defaultAcc,time1, delT;
extern bool readWord, overtake,infAcc, red ;
extern string VehicleType, filename,word,word1,word2;