#pragma once
#include<cstring>
#include"types.h"
#include"context.h"
using namespace std;
namespace enc_hash{
    namespace inside{
        class rmd6_context:virtual public context_basis{
        public:
            rmd6_context();
        };
    }
}
