#include "basis.h"
#include <istream>
using namespace std;
using namespace enc_hash::inside;
uint hash_basis::left_rol(const uint &x,const uint &n)const{return ((x<<n)|(x>>(32-n)));}
void hash_basis::left_rol_block(uint *array,uint blocksize,const uint n)const{
    for(uint c=0;c<n;c++){
        uint tmp=array[blocksize-1];
        for(ushort i=(blocksize-1);i>0;i--) array[i]=array[i-1];
        array[0]=tmp;
    }
}
vector<uint> hash_basis::__compute_hash(context_basis &context,const string &str){
    const uint *msg=(const uint*)str.c_str();
    context.len[0]=str.length();
    for(uint size=str.size();size>63;size-=64,msg+=16){
        memcpy(context.X,msg,sizeof(context.X));
        this->compress(context);
    }
    this->finish(context,msg);
    return context.buf;
}
vector<uint> hash_basis::__compute_hash(context_basis &context,istream &stream){
    if(!stream)return vector<uint>(0);
    uint index,data[0x100];
    size_t Xsize=sizeof(context.X)/sizeof(context.X[0]),size;
    while((size=stream.rdbuf()->sgetn((char*)data,sizeof(data)))>0){
        for(uint i=0;i<(size>>6);i++){
            memcpy(context.X,data+(Xsize*i),sizeof(context.X));
            this->compress(context);
        }
        if(context.len[0]+size<context.len[0]) context.len[1]++;
        context.len[0]+=size;
    }
    //Take modulo 64*15
    index=(context.len[0]&0x3c0)>>2;

    this->finish(context,data+index);
    return context.buf;
}
void hash_basis::finish(context_basis &context,const uint *str){
    memset(context.X,0,sizeof(context.X));
    uint len64=context.len[0]&63;
    memcpy(context.X,str,len64);
    context.X[(context.len[0]>>2)&15]^=(uint)1<<(8*(context.len[0]&3)+7);
    if(len64>55){
        this->compress(context);
        memset(context.X,0,sizeof(context.X));
    }
    context.X[14]=context.len[0]<<3;
    context.X[15]=(context.len[0]>>29)|(context.len[1]<<3);
    this->compress(context);
}
