#pragma once
#include<cstring>
#include"types.h"
#include"context.h"
using namespace std;
namespace enc_hash{
    namespace inside{
        class md5_context:virtual public context_basis{
            public:
                md5_context();
        };
    }
}
