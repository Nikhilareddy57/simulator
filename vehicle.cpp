#include <string>
#include "vehicle.h"

using namespace std;

VEHICLE::VEHICLE(string type,string color,int Id,int length,int width,float speed,float maxSpeed,float maxAcc,float x_pos,int y_pos){
        this->type = type;
        this->color = color;
        this->Id = Id;
        this->length = length;
        this->width = width;
        this->speed = speed;
        this->maxSpeed = maxSpeed;
        this->maxAcc = maxAcc;
        this->x_pos = x_pos;
        this->y_pos = y_pos;
    }