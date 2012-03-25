#include "md5_context.h"
using namespace std;
using namespace enc_hash::inside;
md5_context::md5_context(){
    this->buf.push_back(0x67452301);
    this->buf.push_back(0xefcdab89);
    this->buf.push_back(0x98badcfe);
    this->buf.push_back(0x10325476);
}
