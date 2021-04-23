#include <iostream>
#include <sstream>
using namespace std;

class  Student{
  public:
        string firstname ;
        string lastname ;
        int age ;
        int standard ;
        
        void set_first_name(string fname){
            firstname = fname ;
        }  
        void set_last_name(string lname){
            lastname = lname ;
        }  

        string get_first_name(void){
            return firstname ;
        }
        
        string get_last_name(void){
            return lastname ;
        }
        
        void set_age(int a){
            age = a ;
        }
        
        int get_standard(void){
            return standard ;
        }
        
        int get_age(void){
            return age ;
        }
        
        void set_standard(int s){
            standard = s ;
        }

        void to_string(void){
            cout << age <<"," << firstname <<"," << lastname <<","<< standard << endl ;
        }
};

int main() {
    int age, standard;
    string first_name, last_name;
    
    cin >> age >> first_name >> last_name >> standard;
    
    Student st;
    st.set_age(age);
    st.set_standard(standard);
    st.set_first_name(first_name);
    st.set_last_name(last_name);
    
    cout << st.get_age() << "\n";
    cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
    cout << st.get_standard() << "\n";
    cout << "\n";
    st.to_string();
    
    return 0;
}