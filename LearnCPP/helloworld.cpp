#include <iostream>
#include <cmath>
using namespace std;

class Box{
public:
    float length ;
    float breadth ;
    float height ;

    void setLength(float len){
        length = len;
    }

    void setBreadth(float bre){
        breadth = bre ;
    }

    void SetHeight(float hei){
        height = hei ;
    }

    float getVolume(void){
        return length*breadth*height ;
    }
    
};

int main(){
    cout << "Hello World!" << endl ;
    Box box1 ;
    box1.setLength(10.0) ;
    box1.setBreadth(5.0) ;
    box1.SetHeight(2.0) ;
    cout << box1.getVolume() << endl ; 
    return 0;
}