#include <string>

using namespace std;

class VEHICLE{
    public: string type;
    public: string color;
    public: int Id;
    public: int length;
    public: int width;
    public: float speed; 
    public: float maxSpeed;
    public: float maxAcc;
    public: float x_pos;
    public: int y_pos;
    VEHICLE(string type,string color,int Id,int length,int width,float speed,float maxSpeed,float maxAcc,float x_pos,int y_pos);
};
