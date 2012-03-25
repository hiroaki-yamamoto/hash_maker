#pragma once
#include<iostream>
using namespace std;
inline int PI(int i){return (9*i+5)%16;}
void print_order_rmd6(){
        int p[]={7,4,13,1,10,6,15,3,12,0,9,5,2,14,11,8};
        int s[5][16]=
            {{11,14,15,12,5,8,7,9,11,13,14,15,6,7,9,8},
            {12,13,11,15,6,9,9,7,12,15,11,13,7,8,7,7},
            {13,15,14,11,7,7,6,8,13,14,13,12,5,5,6,9},
            {14,11,12,14,8,6,5,5,15,12,15,14,9,9,8,6},
            {15,12,13,13,9,5,8,6,14,11,12,11,8,6,5,5}};
        cout<<"unsigned int np_i[]={"<<endl;
            for(int i=0;i<16;i++) cout<<i<<((i<15)?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<*p2<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<p[*p2]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<p[p[*p2]]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<p[p[p[*p2]]]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":"\n");
        cout<<"}"<<endl<<"unsigned int p_i[]={"<<endl;
            for(int count=0;count<16;count++) cout<<PI(count)<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<p[PI(count)]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<p[p[PI(count)]]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<p[p[p[PI(count)]]]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<p[p[p[p[PI(count)]]]]<<((count<15)?",":"\n");
        cout<<"}"<<endl<<"unsigned int np_s[]={"<<endl;
            for(int i=0;i<16;i++) cout<<s[0][i]<<((i<15)?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<s[1][*p2]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<s[2][p[*p2]]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<s[3][p[p[*p2]]]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":",\n");
            for(int *p2=p;p2!=&p[sizeof(p)/sizeof(int)];p2++) cout<<s[4][p[p[p[*p2]]]]<<((p2<&p[(sizeof(p)/sizeof(int))-1])?",":"\n");
        cout<<"}"<<endl<<"unsigned int p_s[]={"<<endl;
            for(int count=0;count<16;count++) cout<<s[0][PI(count)]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<s[1][p[PI(count)]]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<s[2][p[p[PI(count)]]]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<s[3][p[p[p[PI(count)]]]]<<((count<15)?",":",\n");
            for(int count=0;count<16;count++) cout<<s[4][p[p[p[p[PI(count)]]]]]<<((count<15)?",":"\n");
        cout<<"};"<<endl;
}
void print_order_md5(){
    cout<<"unsigned int i[]={"<<endl;
    for(unsigned int count=0;count<16;count++) cout<<count<<((count<15)?",":",\n");
    for(unsigned int count=1;count<77;count+=5) cout<<(count&15)<<((count<76)?",":",\n");
    for(unsigned int count=5;count<51;count+=3) cout<<(count&15)<<((count<50)?",":",\n");
    for(unsigned int count=0;count<106;count+=7) cout<<(count&15)<<((count<105)?",":"\n");
    cout<<"};"<<endl;
}
