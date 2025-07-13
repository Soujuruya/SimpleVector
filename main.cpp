#include <iostream>
#include "SimpleVector.hpp"
#include "SimpleVector.cpp"

using namespace std;

int main(){

    SimpleVector vec(2);

    vec.push_back(10);
    vec.push_back(1);
    vec.pop_back();
    for(size_t i = 0;i<vec.size();i++){
        cout << vec[i] << " ";
    }
    
}
