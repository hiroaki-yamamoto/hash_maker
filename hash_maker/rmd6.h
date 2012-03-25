#pragma once
#include <string>
#include <cstring>
#include <istream>
#include "types.h"
#include "rmd6_context.h"
#include "basis.h"
using namespace std;
using namespace enc_hash::inside;
namespace enc_hash{
    class rmd6:virtual public inside::hash_basis{
        public:
            vector<uint> compute_hash(const string &str);
            vector<uint> compute_hash(istream &stream);
        private:
            uint f1(const uint *xyz) const;
            uint f2(const uint *xyz) const;
            uint f3(const uint *xyz) const;
            uint f4(const uint *xyz) const;
            uint f5(const uint *xyz) const;
            void left(uint *buf,const uint &x,const uint &s,const uint round)const;
            void right(uint *buf,const uint &x,const uint &s,const uint round) const;
            void compress(context_basis &context);
    };
}
