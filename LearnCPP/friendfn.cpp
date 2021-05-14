#include <iostream>
 
using namespace std;
 
class Box {
   double width;
   
   public:
    void setWidth( double wid ) {
    width = wid;
}

    friend void printWidth( Box box ) {
   /* Because printWidth() is a friend of Box, it can
   directly access any member of this class */
   cout << "Width of box : " << box.width <<endl;
    }
};


 
// Main function for the program
int main() {
   Box box;
 
   // set box width without member function
   box.setWidth(10.0);
   
   // Use friend function to print the wdith.
   printWidth( box );
 
   return 0;
}