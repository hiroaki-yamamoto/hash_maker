#include "context.h"
using namespace std;
using namespace enc_hash::inside;
context_basis::context_basis(){
    memset(this->X,0,sizeof(this->X));
    memset(this->len,0,sizeof(this->len));
}
