#pragma once
#include<vector>
#include<cstring>
#include "types.h"
using namespace std;
namespace enc_hash{
    namespace inside{
        class context_basis{
            public:
                vector<uint> buf;
                uint len[2],X[16];
                context_basis();
        };
    }
}
