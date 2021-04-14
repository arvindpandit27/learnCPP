#include <iostream>
#include <cmath>
using namespace std ;



class Shape{
protected:  // with protected and private functions, we have data abstraction and encapsulation
    float length ;
    float width ;
    float height ;

public:

    virtual float getArea(){  // polymorphism
        cout << "This is a parent class function, shouldnt run in this program" << endl ;
        return 0.0 ;
    }

};

class Rectangle: public Shape{ // Inheritance
public :
    Rectangle(float l, float b){ // Constructor 
        length = l ;
        width = b ;
    }

    float getArea(void){
        return (length*width);
    }

};

class Triangle : public Shape{
public :
    Triangle(float h, float w){
        height = h ;
        width = w ;
    }

    float getArea(void){
        return (0.5*height*width);
    }
};

int main(){

    Rectangle rect(10.0,5.0);
    Triangle tri(3.0, 6.0) ;

    cout << rect.getArea() << endl ;
    cout << tri.getArea() << endl ; 

    return 0 ;
}