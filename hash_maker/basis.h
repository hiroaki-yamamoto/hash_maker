#pragma once
#include "types.h"
#include <string>
#include <vector>
#include <cstring>
#include <istream>
#include "context.h"
using namespace std;
namespace enc_hash{
    namespace inside{
        class hash_basis{
            protected:
                uint left_rol(const uint &x,const uint &n)const;
                void left_rol_block(uint *array,uint blocksize,const uint n)const;
                vector<uint> __compute_hash(context_basis &context,const string &str);
                vector<uint> __compute_hash(context_basis &context,istream &stream);
                virtual void compress(context_basis &context)=0;
                void finish(context_basis &context,const uint *str);
        };
    }
}
