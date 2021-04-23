#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

 void parseInts(string str){
     stringstream ss(str);  
     vector<string> result;
     string token;
     while (ss >> token)
    {
    cout << token.c_str();
    }
 }

//     char ch;
//     string tmp;
//     while(ss >> tmp) {     
//         result.push_back(tmp);
//         ss >> ch;        
//     }
//     return result ;
// }




int main()
{
    string str;
    cin >> str;
    //vector<string> integers = parseInts(str);
    parseInts(str) ;
    //cout << integers.size() << endl ;
    //for(int i = 0; i < integers.size(); i++) {
     //   cout << integers[i] << "\n";
    //}
    
    return 0;
}
