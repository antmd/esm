

#ifndef UT_ERROR_MESSAGES_H
#define UT_ERROR_MESSAGES_H

#include <iostream>

namespace ESM
{
#define DEBUG_1(arg1) {    \
    std::cout << "DEBUG: " \
              << "(" << __FILE__ << ":" << __LINE__ << "): " \
              << arg1 \
              << std::endl; \
}
#define DEBUG_2(arg1,arg2) {    \
    std::cout << "DEBUG: " \
              << "(" << __FILE__ << ":" << __LINE__ << "): " \
              << arg1 << ":" << arg2\
              << std::endl; \
}
#define DEBUG_3(arg1,arg2,arg3) {    \
    std::cout << "DEBUG: " \
              << "(" << __FILE__ << ":" << __LINE__ << "): " \
              << arg1 << ":" << arg2 << ":" << arg3 \
              << std::endl; \
}
#define DEBUG_4(arg1,arg2,arg3,arg4) {    \
    std::cout << "DEBUG: " \
              << "(" << __FILE__ << ":" << __LINE__ << "): " \
              << arg1 << ":" << arg2 << ":" << arg3 << ":" << arg4 \
              << std::endl; \
}
}

#endif // UT_ERROR_MESSAGES_H
