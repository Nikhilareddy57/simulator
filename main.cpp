#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "functions.h"
//#include "variables.h"

using namespace std;


vector<VEHICLE> objects;   // Vector which contains all types of Vehicles
vector<vector<VEHICLE> > lane;
vector<VEHICLE> myVector;
fstream inFile;
int roadLength ,roadWidth,roadId,roadSignal, stopLine = 29;
int cont =1, gen = 0; //Variables to store the Road Parameters 
//Variables to read the Vehicle Parameters
string VehicleType;
int parameter;
float defaultSpeed=-1.0;
float defaultAcc=-1.0;  
bool readWord = true;bool overtake = true;bool infAcc = false;bool red = true;
string filename,word,word1,word2;
    // We read Road and Vehicle Parameters here  
float time1=0, delT = 0.3;int id = 0;int c1=0;int c2=0;//float time = 0;

int main(int argc, char** argv){
    cout << "Input configuration file name:\n";
    cin >> filename;
    inFile.open(filename.c_str());
     //gen = 1 makes the vehicle generates the vehicle in the best possible
    while(inFile >> word){
        if(word == "GenerateAtBestLane"){
            gen = 1;
        }
     //cont = 1 generates the vehicles in the order specified by the config file.It doesnot ignore any vehicle if there is no space
        if(word == "Ignore"){
            cont = 0;         
        }
        if(word == "NoOvertaking"){
            overtake = false;
        }
        if(word == "InfiniteAcceleration"){
            infAcc = true;
        }
     //Road Parametrs are read here
        if(word == "Road_Id" || word == "Road_Length" || word == "Road_Width" || word == "Road_Signal"|| word == "Stop_Line")
        {
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            if(word == "Road_Id"){
                temp >> roadId;
            }else if(word == "Road_Length"){
                temp >> roadLength;
            }else if(word == "Road_Width"){
                temp >> roadWidth;
            }else if(word == "Stop_Line"){
                temp >> stopLine;
            }else{
                temp >> roadSignal;
            }
        }
        //Default values of MaxSpeed and MaxAcceleration are read here
        if(word == "Default_MaxSpeed" || word == "Default_Acceleration"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            if(word == "Default_MaxSpeed"){
                temp >> defaultSpeed;
            }else{
                temp >> defaultAcc;
            }
        }
        //The type of Vehicle whose parametrs are to be read is determined here.We create a VEHICLE object with default parameters and push it on the vector
        if(word == "Vehicle_Type"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            temp >> VehicleType;
            VEHICLE v(VehicleType,"GREEN",-1,0,0,0,defaultSpeed,defaultAcc,0,0);
            objects.push_back(v);
        }
        //The parametrs of the Vehicles which are on the vector are updated here
        if(word == "Vehicle_Length" || word == "Vehicle_Width" || word == "Vehicle_MaxSpeed" || word == "Vehicle_Acceleration"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            temp >> parameter;
            int index = findVehicleIndex(objects,VehicleType);
            if(word == "Vehicle_Length"){
                objects[index].length = parameter;
            }else if(word == "Vehicle_Width"){
                objects[index].width = parameter;
            }else if(word == "Vehicle_MaxSpeed"){
                objects[index].maxSpeed = parameter;
            }else{
                objects[index].maxAcc = parameter;
            }
        }
        if(word == "START") break;
    }
    //lane is a 2d vector containing the vehicles in the lanes
    for(int i=0;i<roadWidth;i++){
        vector<VEHICLE> temp;
        lane.push_back(temp);
    } 
    // update(0);
    //lane is a 2d vector containing the vehicles in the lanes
       glutInit(&argc, argv);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(1600, 900);
        glClearColor (0.0, 0.0, 0.0, 0.0);
 //initialize viewing values 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
     //   glOrtho(0, roadLength,-roadWidth,0.0, 0, 0);
        glutCreateWindow("two_dimension");
        
        glutDisplayFunc(drawScene);
    //  glutReshapeFunc(handleResize);
        glutTimerFunc(200,update,delT);
        glutMainLoop(); 
    return 0; /* ISO C requires main to return int. */
}