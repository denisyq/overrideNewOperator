#include <iostream>
using namespace std;
#include "debugNew.h"
int main(void){
    int *p =  new int;
    int *p2 = new int[5];
    delete[] p2;
    delete p;

    return 0;
}
