#pragma once
#include<iostream>
#include<cmath>
using namespace std;
void print_const_rmd6(){
    double p2=pow(2,30);
    double k[8]={(p2*sqrt(2)),(p2*sqrt(3)),(p2*sqrt(5)),(p2*sqrt(7)),(p2*pow(2,1.0/3.0)),(p2*pow(3,1.0/3.0)),(p2*pow(5,1.0/3.0)),(p2*pow(7,1.0/3.0))};
    cout<<"unsigned int const[]={";
    for(double *pointer=k;pointer<&k[sizeof(k)/sizeof(double)];pointer++){
        cout<<"0x"<<hex<<(unsigned int)*pointer<<dec;
        if(pointer<&k[7])cout<<",";
    }
    cout<<"};"<<endl;
}
void print_const_md5(){
    cout<<"unsinged int t[]={";
    for(int count=1;count<65;count++){
        cout<<"0x"<<hex<<(unsigned int)(0x100000000*fabs(sin(count)))<<dec;
        if(count<64)cout<<",";
    }
    cout<<"};"<<endl;
}
