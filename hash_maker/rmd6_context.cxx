#include "rmd6_context.h"
using namespace std;
using namespace enc_hash::inside;
rmd6_context::rmd6_context(){
    this->buf.push_back(0x67452301);
    this->buf.push_back(0xefcdab89);
    this->buf.push_back(0x98badcfe);
    this->buf.push_back(0x10325476);
    this->buf.push_back(0xc3d2e1f0);
}
