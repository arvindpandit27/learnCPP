#include <iostream>
#include <cmath>
using namespace std;

class Box{
public:
    float length ;
    float breadth ;
    float height ;
    float width ;

public:
    float getVolume(void){
        return length*breadth*height ;
    }
    
    Box(float len, float bre, float hei){
        length = len ;
        breadth = bre ;
        height = hei ;
        cout << "object is being created" << endl ;
    }

    ~Box(void){
        cout << "object is being deleted" << endl ;
    }
};


class smallBox : Box{
    public:
    void setSmallWidth(double wid){
        width = wid ;
    }
};

int main(){
    Box box1(10.0,5.0,3.0) ;
    cout << box1.getVolume() << endl ; 
    return 0;
}