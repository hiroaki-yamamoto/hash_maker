#include "rmd6.h"
/*#ifdef _OPENMP
    #include <omp.h>
#endif*/

using namespace std;
using namespace enc_hash;
using namespace enc_hash::inside;

vector<uint> rmd6::compute_hash(const string &str){
    rmd6_context context;
    return this->__compute_hash(context,str);
}
vector<uint> rmd6::compute_hash(istream &stream){
    rmd6_context context;
    return this->__compute_hash(context,stream);
}
uint rmd6::f1(const uint *xyz) const{return (xyz[0]^xyz[1]^xyz[2]);}
uint rmd6::f2(const uint *xyz) const{return (xyz[0]&xyz[1])|(~xyz[0]&xyz[2]);}
uint rmd6::f3(const uint *xyz) const{return (xyz[0]|~xyz[1])^xyz[2];}
uint rmd6::f4(const uint *xyz) const{return (xyz[0]&xyz[2])|(xyz[1]&~xyz[2]);}
uint rmd6::f5(const uint *xyz) const{return xyz[0]^(xyz[1]|~xyz[2]);}
void rmd6::left(uint *buf,const uint &x,const uint &s,const uint round)const{
    const uint constants[]={0,0x5a827999UL,0x6ed9eba1UL,0x8f1bbcdcUL,0xa953fd4eUL};
    switch(round){
        case 0: buf[0]=this->left_rol(buf[0]+this->f1(buf+1)+x+constants[round],s)+buf[4];break;
        case 1: buf[0]=this->left_rol(buf[0]+this->f2(buf+1)+x+constants[round],s)+buf[4];break;
        case 2: buf[0]=this->left_rol(buf[0]+this->f3(buf+1)+x+constants[round],s)+buf[4];break;
        case 3: buf[0]=this->left_rol(buf[0]+this->f4(buf+1)+x+constants[round],s)+buf[4];break;
        case 4: buf[0]=this->left_rol(buf[0]+this->f5(buf+1)+x+constants[round],s)+buf[4];break;
    }
    buf[2]=this->left_rol(buf[2],10);
}
void rmd6::right(uint *buf,const uint &x,const uint &s,const uint round) const{
    const uint constants[]={0x50a28be6UL,0x5c4dd124UL,0x6d703ef3UL,0x7a6d76e9UL,0};
    switch(round){
        case 0: buf[0]=this->left_rol(buf[0]+this->f5(buf+1)+x+constants[round],s)+buf[4];break;
        case 1: buf[0]=this->left_rol(buf[0]+this->f4(buf+1)+x+constants[round],s)+buf[4];break;
        case 2: buf[0]=this->left_rol(buf[0]+this->f3(buf+1)+x+constants[round],s)+buf[4];break;
        case 3: buf[0]=this->left_rol(buf[0]+this->f2(buf+1)+x+constants[round],s)+buf[4];break;
        case 4: buf[0]=this->left_rol(buf[0]+this->f1(buf+1)+x+constants[round],s)+buf[4];break;
    }
    buf[2]=this->left_rol(buf[2],10);
}
void rmd6::compress(context_basis &context){
    uint np_buf[5],p_buf[5];
    memcpy(p_buf,context.buf.data(),sizeof(p_buf));
    memcpy(np_buf,context.buf.data(),sizeof(np_buf));
    uint np_i[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
        3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
        1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
        4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13},
    np_s[]={11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
        7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
        11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
        11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
        9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6},
    p_i[]={5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
        6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
        15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
        8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
        12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11},
    p_s[]={8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
        9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
        9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
        15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
        8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11};
/*#ifdef _OPENMP
#pragma omp parallel
{
    #pragma omp sections
    {
        #pragma omp section
            for(uint count=0,round=0;count<80;count++,round=count>>4){
                this->left(np_buf,context.X[np_i[count]],np_s[count],round);
                left_rol_block(np_buf,5,1);
            }
        #pragma omp section
            for(uint count=0,round=0;count<80;count++,round=count>>4){
                this->right(p_buf,context.X[p_i[count]],p_s[count],round);
                left_rol_block(p_buf,5,1);
            }
    }
}
#else*/
    for(uint count=0,round=0;count<80;count++,round=count>>4){
        this->left(np_buf,context.X[np_i[count]],np_s[count],round);
        this->right(p_buf,context.X[p_i[count]],p_s[count],round);
        left_rol_block(np_buf,5,1);
        left_rol_block(p_buf,5,1);
    }
//#endif
    p_buf[3]+=np_buf[2]+context.buf[1];
    for(ushort i=1;i<5;i++) context.buf[i]=context.buf[(i+1)%5]+np_buf[(i+2)%5]+p_buf[(i+3)%5];
    context.buf[0]=p_buf[3];
}
