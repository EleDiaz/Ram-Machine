#pragma once
/**

 */

#include <list>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class ITape {
private:
    list<int> tape_;
public:
    ITape(list<int> vec) {
      tape_ = vec;
    }
    int readTape(void) {
        int aux = tape_.front();
        tape_.pop_front();
        return aux;
    }
};
