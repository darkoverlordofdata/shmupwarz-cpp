#pragma once
#include <exception>

namespace system::exceptions {

    using namespace std;
    
    class OverflowException : public exception {
        const char* what() const throw () {
            return "OverflowException";
        }
    };

}