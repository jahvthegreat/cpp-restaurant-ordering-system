#include <limits>
/*
   Name: Jahvyn Griffiths
*/

#include <iostream>
#include "Utils.h"

namespace seneca {

    char* aloCopy(const char* src) {
        char* newStr = nullptr;
        if (src != nullptr) {
            int count = 0;
            for (; src[count]; count++);
            newStr = new char[count + 1];
            for (int i = 0; i <= count; i++) 
                newStr[i] = src[i];
        }
        return newStr;
    }

    void strCpy(char* des, const char* src) {
        if (des && src) {
            int i = 0;
            do {
                des[i] = src[i];
            } while (src[i++]);
        }
    }

    int strLen(const char* str) {
        int counter = 0;
        if (str) {
            while (str[counter]) counter++;
        }
        return counter;
    }

    int getInt(int minVal, int maxVal, const char* message) {
        int input;
        bool valid = false;
        
        if (message) std::cout << message;

        while (!valid) {
            if (std::cin.peek() == '\n') {
                std::cin.ignore();
                std::cout << "Please enter a value: ";
                continue;
            }

            std::cin >> input;
            
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid number: ";
            } else {
                if (std::cin.get() != '\n') {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Numbers only please: ";
                } else if (input < minVal || input > maxVal) {
                    std::cout << "Value must be between " << minVal 
                              << " and " << maxVal << ": ";
                } else {
                    valid = true;
                }
            }
        }
        return input;
    }

    void getStr(char* output, int bufferSize, const char* message) {
        if (message) std::cout << message;
        while (std::cin.peek() == '\n') 
            std::cin.ignore();
        std::cin.get(output, bufferSize, '\n');
        std::cin.ignore(10000, '\n');
    }
}
