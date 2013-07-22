#include "error.h"

void error(uint8_t e, std::ostream & stream){
    switch (e){
        case 1:
            stream << "KeyError: Key not set";
            break;
        case 2:
            stream << "KeyError: Key already set";
            break;
        case 3:
            stream << "KeySizeError: Key does not fit defined sizes";
            break;
        case 4:
            stream << "InputError: Undefined input value";
            break;
        case 5:
            stream << "InputError: Empty input";
            break;
        case 6:
            stream << "InputError: Input sizes are incorrect";
            break;
        default:
            break;
    }
    stream << std::endl;
    exit(e);
}
