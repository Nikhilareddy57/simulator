#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "functions.h"
//#include "variables.h"

using namespace std;

vector<int> getIndexVector(vector<vector<VEHICLE> > lane,int k){
    vector<int> Index;
    int rows = lane.size();
    for( int i=0;i<=rows-k;i++){
        bool temp = true;
        for( int j=i;j<i+k;j++){
           if(lane[j].size() != 0) {
              VEHICLE v = (lane[j][(lane[j].size()-1)]);
              float x = v.x_pos - (float)v.length;
              if(x<=0){
                 temp = false;
                 i = i+(v.width-1);
                 j = i+k;
              } 
           }
        }
        if(temp == true){Index.push_back(((int) i));}
    }
    return Index; 
}

void  printLane(vector<vector<VEHICLE> > l){
    for(int i=0;i<(int)l.size();i++){
        for(int j=0;j<(int)l[i].size();j++){
        	cout << l[i][j].type << " ";
        }
        cout << "\n";
    }
}
 
int distance(vector<vector<VEHICLE> > lane,int index,float maxSpeed,int k){
    int temp = (maxSpeed-1);
    for( int j=0;j<index+k;j++){
        if(lane[j].size() != 0) {
              VEHICLE v = (lane[j][(lane[j].size()-1)]);
              if(v.y_pos+v.width-1>=index || j>=index){
                int x = v.x_pos - v.length;
                if(x<temp) temp = x;
              }
          }
    }
    return temp;
}
/*float distance(vector<vector<VEHICLE> > lane,int index,float maxSpeed,int k){
    float temp = (maxSpeed-1);
    for( int j=0;j<index+k;j++){
        if(lane[j].size() != 0) {
              VEHICLE v = (lane[j][(lane[j].size()-1)]);
              if(v.y_pos+v.width-1>=index || j>=index){
                int x = v.x_pos - v.length;
                if(x<temp) temp = x;
              }
          }
    }
    return temp;
}*/

vector<VEHICLE> sortVehicles(vector<vector<VEHICLE> > myVector){
    vector<VEHICLE> result;
    for( int i=0;i<(int)myVector.size();i++){
        for( int j=0;j<(int)myVector[i].size();j++){
            result.push_back(myVector[i][j]);
        }
    }
    if(result.size()>=1){
    int maxIndex; int j; int i;
    for(i=0;i<(int)result.size()-1;i++){
        maxIndex = i;
        for(j=i+1;j<(int)result.size();j++){
            if(result[maxIndex].x_pos < result[j].x_pos){
                maxIndex =  j;
            }
        }
        if(maxIndex != i){
        VEHICLE temp = result[i];
        result.erase(result.begin()+i);
        result.insert(result.begin()+i,result[maxIndex-1]);
        result.erase(result.begin()+maxIndex);
        result.insert(result.begin()+maxIndex,temp);
        }
    }
    }
    return result;
}

int findVehicleIndex(vector<VEHICLE> v,string type){
    for( int i=0;i<(int)v.size();i++){
        if(v[i].type == type){
            return i;
        }
    }
    return (-1);
}

float findPositionInLanes(float* arr,int i,int width,float value){
    for( int j=i;j<i+width;j++){
        if(arr[j] < value) value = arr[j];
    }
    return value;
}
float overTakeNthLane(float* distSoFar,float max,int n,vector<VEHICLE> myVector,int index,int roadWidth){
    VEHICLE v = myVector[index];
    int w = v.width;
    bool flag = true;
    if(n >= 0 && n < roadWidth){
        for(int j=index+1;j<(int)myVector.size();j++){
            if(myVector[j].y_pos <= n && (myVector[j].y_pos+myVector[j].width-1)>=n){
               if(myVector[j].x_pos > v.x_pos-v.length) flag = false;  //Check >=
               
            }
        }
        float d0 = findPositionInLanes(distSoFar,n,w,2*roadLength);
       // cout << flag <<"\n";
        if(flag == true){
           // cout << v.type <<" "<< n<<" "<<"d0 :" << d0 <<"\n";
            return d0;
        }
        return (-1);
    }
    else return (-1);
}
int findPresentIndex(vector<VEHICLE> vec,int id){
    for( int i=0;i<(int)vec.size();i++){
        if(vec[i].Id == id) return i;
    }
    return -1;
}
int findNewIndex(vector<VEHICLE> vec,int x){
    for( int i=0;i<(int)vec.size();i++){
        if(vec[i].x_pos < x){
            return i;
        }
    }
    return 0;
}

vector<float> color_RGB(string colour)
{   
    vector<float> RGB;
    for(int i = 0; i<3; i++)
        RGB.push_back(0.0f);
    if(colour == "red" ||colour == "RED")
        {RGB[0] = 0.8f;RGB[1] = 0.0f;RGB[2] = 0.0f;}
    else if(colour == "green"||colour == "GREEN")
        {RGB[0] = 0.0f;RGB[1] = 0.8f;RGB[2] = 0.0f;}
    else if(colour == "blue"||colour == "BLUE")
        {RGB[0] = 0.0f;RGB[1] = 0.0f;RGB[2] = 0.8f;}
    else if(colour == "ORANGE")
        {RGB[0] = 1;RGB[1] = 0.3;RGB[2] = 0;}
    else if(colour == "VIOLET")
        {RGB[0] = 0.5f;RGB[1] = 0;RGB[2] = 0.9;}
    else if(colour == "YELLOW")
        {RGB[0] = 0.9;RGB[1] = 0.9;RGB[2] = 0;}
    else if(colour == "WHITE")
      {RGB[0] = 0.9;RGB[1] = 0.9;RGB[2] = 0.9;}
    else if(colour == "BLACK")
        {RGB[0] = 0.1;RGB[1] = 0.1;RGB[2] = 0.1;}
    else if(colour == "CHOCOLATE")
      {RGB[0] = 0.35f;RGB[1] = 0.19f;RGB[2] = 0.089f;}
  else
    {RGB[0] = 0.0f;RGB[1] = 0.8f;RGB[2] = 0.0f;}
    return RGB; 
}
