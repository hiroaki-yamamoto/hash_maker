#pragma once
#include<iostream>
#include<vector>
#include "types.h"
using namespace std;
ostream &operator<<(ostream &stream,const vector<uint> v){
    for(const uint value:v)
        for(const unsigned char *c=(const unsigned char*)&value;c<((const unsigned char*)&value)+sizeof(value);c++)
            cout<<hex<<(((*c)<0x10)?"0":"")<<(short)(*c)<<dec;
    return stream;
}
