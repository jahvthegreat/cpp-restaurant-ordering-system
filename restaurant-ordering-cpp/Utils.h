// Restaurant Ordering and Billing System - C++ Academic Project

#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H
#include <iosfwd>
#include <iostream>

namespace seneca {
    //string operations
    char* aloCopy(const char* src);
    void strCpy(char* des, const char* src); 
    int strLen(const char* str);
    int getInt(int minVal, int maxVal, const char* message = nullptr);
    void getStr(char* output, int bufferSize, const char* message = nullptr);
}
#endif // !SENECA_UTILS_H