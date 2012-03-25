/*
This is a memo for myself.
It's a little bit dirrent from offical code.
*/
#pragma once
#include<string>
#include<cstring>
#include<istream>
#include"types.h"
#include"md5_context.h"
#include"basis.h"
using namespace std;
using namespace enc_hash::inside;
namespace enc_hash{
    class md5:virtual public inside::hash_basis{
        public:
        vector<uint> compute_hash(const string &str);
        vector<uint> compute_hash(istream &stream);
        private:
            uint f1(const uint *buf)const;
            uint f2(const uint *buf)const;
            uint f3(const uint *buf)const;
            uint f4(const uint *buf)const;
            void operate(uint *buf,const uint &x_element, const uint &s,const uint &constant,const uint &round)const;
            void compress(context_basis &md5);
    };
}
