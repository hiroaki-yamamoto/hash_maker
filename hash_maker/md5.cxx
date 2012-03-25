#include "md5.h"
using namespace std;
using namespace enc_hash::inside;
using namespace enc_hash;
vector<uint> md5::compute_hash(const string &str){
    md5_context context;
    return this->__compute_hash(context,str);
}
vector<uint> md5::compute_hash(istream &stream){
    md5_context context;
    return this->__compute_hash(context,stream);
}
uint md5::f1(const uint *buf)const{return (buf[0]&buf[1])|((~buf[0])&buf[2]);}
uint md5::f2(const uint *buf)const{return (buf[0]&buf[2])|(buf[1]&(~buf[2]));}
uint md5::f3(const uint *buf)const{return buf[0]^buf[1]^buf[2];}
uint md5::f4(const uint *buf)const{return buf[1]^(buf[0]|(~buf[2]));}
void md5::operate(uint *buf,const uint &x_element,const uint &s,const uint &constant,const uint &round)const{
                switch(round){
                case 0: buf[0]=buf[1]+this->left_rol(buf[0]+this->f1(buf+1)+x_element+constant,s);break;
                case 1:	buf[0]=buf[1]+this->left_rol(buf[0]+this->f2(buf+1)+x_element+constant,s);break;
                case 2:	buf[0]=buf[1]+this->left_rol(buf[0]+this->f3(buf+1)+x_element+constant,s);break;
                case 3:	buf[0]=buf[1]+this->left_rol(buf[0]+this->f4(buf+1)+x_element+constant,s);break;
            }
}
void md5::compress(context_basis &md5){
    uint buf[4];
    memcpy(buf,&md5.buf[0],sizeof(buf));
    const uint rotation_size[][4]={{7,12,17,22},{5,9,14,20},{4,11,16,23},{6,10,15,21}},
    i[]={
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
        1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
        5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
        0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9},
    //These constants are made from a sine function, equals to the integer part of 4294967296*abs(sin i) (1<i<65).
    t[]={0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
        0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
        0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x2441453,0xd8a1e681,0xe7d3fbc8,
        0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
        0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
        0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
        0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
        0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};
    for(uint counter=0,round=0,rotation_index=0;counter<64;
        counter++,round=(counter>>4),rotation_index=(rotation_index+1)&3){
        this->operate(buf,md5.X[i[counter]],rotation_size[round][rotation_index],t[counter],round);
        left_rol_block(buf,4,1);
    }
    for(uint counter=0;counter<4;counter++)	md5.buf[counter]+=buf[counter];
}
