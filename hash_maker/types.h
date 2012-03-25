//cl.exe doesn't define unsigned int as uint. This is why this file exists.

#if defined(_WIN32)||defined(_WIN64)
    typedef unsigned int uint;
    typedef unsigned short ushort;
    typedef unsigned long ulong;
    typedef unsigned char uchar;
#else
extern "C"{
    #include <sys/types.h>
}
#endif
