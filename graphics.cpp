#include <bits/stdc++.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "functions.h"
//#include "variables.h"

using namespace std;

void update(int value)
{
        if(readWord == true) inFile >> word;
        if(word != "Signal")
        {
            time1 = time1 + delT;
        }
        for(int i=0;i<roadLength;i++){
            cout << "-";
        }
        cout << "\n";
      //END OF TIME UPDATION AND PRINTING BOUNDARIES
        float distSoFar[roadWidth];
        if(word == "Signal"){
            inFile >> word1;
            if(word1 == "RED") red = true;
            else red = false;
        }
        if(word == "Pass"){
            inFile >> word1;
            stringstream temp(word1);
            temp >> c1;c2 = 0;word = "xxx";readWord=false;
            c1 = c1-1;
        }
        if(word == "xxx"){
           if(c2 == c1){
            c2=0;c1=0;readWord=true;
           }else c2=c2+1;
        }
        // Updation of positions of Vehicles when it is not a signal turn off/on command
        if(word != "Signal"){
        // myVector has all the vehicles sorted by their x position
        myVector = sortVehicles(lane);  
        //It keeps track of the updated length of road in different lanes
        for(int i=0;i<roadWidth;i++){
            distSoFar[i] = 2*roadLength;         
        }
        //Updating the position of each Vehicle one by one with the farthest first
        for( int i=0;i<(int)myVector.size();i++){
            VEHICLE v=myVector[i];
            float xoriginal = v.x_pos; 
            if(v.x_pos+v.maxSpeed*delT-v.length >= roadLength+roadLength/4){
                int laneNum = v.y_pos;int num = v.Id;
                for( int k=0;k<(int)lane[laneNum].size();k++){
                    if(lane[laneNum][k].Id == num){
                        lane[laneNum].erase(lane[laneNum].begin()+k);
                    }
                }
                distSoFar[laneNum] = 2*roadLength;  
            }else{                                              /// int temp1 = v.x_pos + v.maxSpeed;
                int laneNum = v.y_pos;int w = v.width;          /// v.speed = v.speed + v.maxAcc or v.speed = v.maxSpeed
                float max;int num = v.Id;float temp;              /// temp1 = v.x_pos+(v.speed+(v.maxAcc)/2) or v.xpos + v.MaxSpeed
                if(v.speed+v.maxAcc*delT>=v.maxSpeed||infAcc == true) max = v.x_pos+v.maxSpeed*delT;
                else max = v.x_pos+(v.speed+(v.maxAcc*delT)/2)*delT;
                float temp1 = 2*roadLength;
                //Finding the max x position that a vehicle v can move.The x position is in temp1
                int newYPOS = v.y_pos, newIndex, presentIndex;
                for( int j=v.y_pos;j<v.y_pos+w;j++){
                    if(distSoFar[j] < temp1) temp1 = distSoFar[j];
                }


                 
                int laneLf = laneNum-1, laneRt = laneNum+1;
                float dmax= temp1; int laneMax = laneNum;
                //finding extreme left lane it can shift to 
                for(; laneLf >= 0; laneLf--)
                {
                    float d = overTakeNthLane(distSoFar,max,laneLf,myVector,i,roadWidth);
                    if((int)d == -1 || d < v.x_pos) break;
                    if(d > dmax)
                    {
                        dmax = d;
                        laneMax = laneLf;
                    }   

                }
                for(; laneRt + v.width <= roadWidth; laneRt++)
                {
                    float d = overTakeNthLane(distSoFar,max,laneRt,myVector,i,roadWidth);
                    if((int)d == -1 || d < v.x_pos) break;
                    if(d > dmax)
                    {
                        dmax = d;
                        laneMax =  laneRt;
                    }       
                }

                
                if(laneMax != laneNum && temp1 != 0)
                {
                    int laneNew;
                    if(laneMax > laneNum) laneNew = laneNum + 1;
                    else laneNew = laneNum - 1; //laneMax < laneNum
                    temp1 = overTakeNthLane(distSoFar,max,laneNew,myVector,i,roadWidth);
                    newYPOS = laneNew;
                    newIndex = findNewIndex(lane[laneNew],v.x_pos);
                    presentIndex = findPresentIndex(lane[v.y_pos],v.Id);                
                }

                if(temp1 > max)
                {
                    temp1 = max;
                }
                
                //Updating the x position such thst it does not cross the signal when signal is red.
                if(red ==true && ((temp1>=roadSignal-1)&& (v.x_pos<roadSignal-1)))
                {
                        temp = stopLine-1;

                }    //Should I have <= or <
                if(red == true && (v.x_pos < roadSignal-1 && v.x_pos >= stopLine-1))
                {
                    temp = v.x_pos;
                }
                else temp = temp1;
               
                //Updating the length of the road covered till now among different lanes
                if(newYPOS == v.y_pos || overtake == false){
                   for( int j=v.y_pos;j<v.y_pos+w;j++){
                    distSoFar[j] = temp - v.length;
                   }
                   for( int k=0;k<(int)lane[laneNum].size();k++){
                      if(lane[laneNum][k].Id == num){
                          lane[laneNum][k].speed = temp - lane[laneNum][k].x_pos;
                          lane[laneNum][k].x_pos = temp;
                      }
                   }
                }else{
                    for( int j=newYPOS;j<newYPOS+w;j++){
                    distSoFar[j] = temp - v.length;
                    }
                    lane[v.y_pos].erase(lane[v.y_pos].begin()+presentIndex);
                    v.x_pos = temp;v.y_pos=newYPOS;v.speed=temp-v.x_pos;
                    lane[newYPOS].insert(lane[newYPOS].begin()+newIndex,v);
                }
                
                //Finding the vehicle on the road with VehicleId = num and updating its x position
            }
        }
        }
        // Generation of Cars, Buses, bikes, Trucks and other Vehicles
        if(findVehicleIndex(objects,word) != -1){
            int index = findVehicleIndex(objects,word);
            int length = objects[index].length;int width = objects[index].width;
            float maxSpeed = objects[index].maxSpeed, maxAcc = objects[index].maxAcc;
            int y_pos=-1;vector<int> IndexVector = getIndexVector(lane,width);int initPos=-1; // What if ypos is -1 ?If ypos = -1 then vehicle will not be generated.It will be ignored
            for( int i=0;i<(int)IndexVector.size();i++){
                int temp1 = IndexVector[i];
                float temp2 = distSoFar[temp1];
                if(initPos<temp2){
                    y_pos = temp1;initPos = temp2;
                }
            }
            if(y_pos>=0){
                float x_pos;
                inFile >> word1;  //Color of the vehicle is stored in word1
                if(gen == 1) x_pos = distance(lane,y_pos,maxSpeed,width) - roadLength/4;
                else{
                    x_pos = distance(lane,IndexVector[0],maxSpeed,width)- roadLength/4;
                    y_pos = IndexVector[0];
                } 
                VEHICLE temp(word,word1,id,length,width,(x_pos+1),maxSpeed,maxAcc,x_pos,y_pos);
                lane[y_pos].push_back(temp);
                id = id+1;
                readWord = true;
            }
            else{
                if(cont == 1){
                    readWord = false;
                }
                else{
                    inFile >> word1;readWord = true;
                }
            }
        }
        //printLane(lane);
        //Encoding the signal as '|' in a 2D Matrix at the correct position
        char mat[roadWidth][roadLength];
        for(int i=0;i<roadWidth;i++){
            for(int j=0;j<roadLength;j++){
                mat[i][j] = ' ';
            }
            if(red == true) mat[i][roadSignal-1] = '|';
        }
        //Encoding the objects as Characters in a 2D Matrix
        for( int i=0;i<roadWidth;i++){
          if(lane[i].size()>=1){
            for( int j=0;j<(int)lane[i].size();j++){
                VEHICLE v = lane[i][j];
                float x1, x2= (v.x_pos);int y = v.y_pos; //If we want a smooth change remove %roadLength and simulate it 
                int length = v.length; int width = v.width;
                if(v.x_pos-length <= -1){ x1=0;}
                else x1 = v.x_pos+1.0-(float)length;
                for(int i1=y;i1<y+width;i1++){
                    for(int j1=x1;j1<=x2;j1++){
                        if(j1<roadLength) 
                        mat[i1][j1] = (v.type)[0];
                    }
                }
            }
          }
        }
        //Printing the answer to the terminal and checking for end of simulation(road is clear)
        bool clear = true;
        for(int i=0;i<roadWidth;i++){
            for(int j=0;j<roadLength;j++){
                if(mat[i][j] != ' ') clear = false;
                cout << mat[i][j];
            }
            cout << "\n";
        }
        for(int i=0;i<roadLength;i++){
            cout << "-";
        }
        cout << "\n";
        cout << "Time = " << time1<<" "<<"word: "<<word<<"\n";
        if(word == "END" && clear == true) return;
        glutPostRedisplay(); // Inform GLUT that the display has changed
        glutTimerFunc(25,update,delT);//Call update after each 25 millisecond
}


void drawScene() 
{
glClear(GL_COLOR_BUFFER_BIT);

float signalX = 2*((float)roadSignal-1)/(float)roadLength - 1;
float roadTop = 0.30, roadBottom = -0.55;
float x_stop = 2*((float)(stopLine -2 - roadLength/2))/ (float) roadLength;
//road
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex3f(-1,roadTop + 0.04,0);
    glVertex3f(1,roadTop + 0.04,0);
    glVertex3f(1,roadBottom - 0.04,0);
    glVertex3f(-1,roadBottom - 0.04,0);
    glEnd();

    glColor3f(0.95,0.95,0.95); 
    glLineWidth(10.0);  
    glBegin(GL_LINES);
    glVertex2d(-1, roadTop + 0.01);
    glVertex2d(1, roadTop + 0.01);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-1, roadBottom -0.01);
    glVertex2d(1, roadBottom -0.01);
    glEnd();

    //stop line
    glLineWidth(4.0);  
    glBegin(GL_LINES);
    glVertex2d( x_stop, roadTop);
    glVertex2d( x_stop, roadBottom);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d( signalX, roadTop);
    glVertex2d( signalX, roadBottom);
    glEnd();

    //draws lane partitions
    for(float posX = -1; posX <= 1; posX += 0.1)
    {
        if((posX+0.025 < x_stop)||(posX-0.025 > signalX))
        {
            glLineWidth(10.0);  
            glBegin(GL_LINES);//line width = line width of road side lines
            glVertex2d(posX + 0.025, (roadBottom + roadTop)/2);
            glVertex2d(posX - 0.025, (roadBottom + roadTop)/2);
            glEnd();            
        }
    }

//draws zebra crossing

    for(float posY = roadTop - 0.04; posY >= roadBottom+0.04; posY -= 0.1)
    {   
        glLineWidth(10.0);  
        glBegin(GL_LINES);
        glVertex2d(signalX -0.015, posY);
        glVertex2d(x_stop + 0.015 ,posY);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(signalX -0.015, posY-0.015);
        glVertex2d(x_stop + 0.015 ,posY -0.015);
        glEnd();
    }

//red signal
    if(red)
    glColor3f(1,0,0);
    else glColor3f(0.5,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(signalX+0.05,0.875,0);
    glVertex3f(signalX+0.05,0.775,0);   
    glVertex3f(signalX-0.05,0.775,0);
    glVertex3f(signalX-0.05,0.875,0);
    glEnd();
//green signal
    if(red)
    glColor3f(0,0.25,0);
    else glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(signalX+0.05,0.725,0);
    glVertex3f(signalX+0.05,0.625,0);
    glVertex3f(signalX-0.05,0.625,0);
    glVertex3f(signalX-0.05,0.725,0);
    glEnd();

    for(int i=0; i < (int)myVector.size(); i++)
    { 
        string color = myVector[i].color;
        float fact1 = (roadLength/2)/(roadTop - roadBottom), fact2 = roadWidth/(roadTop - roadBottom);
        float x =myVector[i].x_pos - roadLength/2, y = (float)myVector[i].y_pos - roadWidth/2, w = (float) myVector[i].width, lt = myVector[i].length;
        glBegin(GL_POLYGON);
        glColor3f(color_RGB(color)[0], color_RGB(color)[1], color_RGB(color)[2]);
        glVertex3f(x/fact1 - 0.003, -y/fact2 + (roadBottom+roadTop)/2 -0.003,0);
        glVertex3f((x-lt)/fact1 + 0.003,-y/fact2+ (roadBottom+roadTop)/2 -0.003,0);
        glVertex3f((x-lt)/fact1 + 0.003, -(y+w)/fact2+ (roadBottom+roadTop)/2+0.003,0);
        glVertex3f(x/fact1 -0.003, -(y+w)/fact2+ (roadBottom+roadTop)/2+0.003,0);
        glEnd();//+(roadTop + roadBottom)/2.0
    }
    
   // float y1 = 0.0 - roadWidth/2, y2 = 10.0 - roadWidth/2;
   // cout << -y1/fact2 + (roadBottom+roadTop)/2 << " " << -y2/fact2+ (roadBottom+roadTop)/2;
    
    glFlush();
    glutSwapBuffers(); //Send the 3D scene to the screen
}
