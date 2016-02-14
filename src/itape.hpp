#pragma once
/**

 */

#include <list>

using namespace std;

class UIBind;
/** Represents a input tape for Ram-Machine.

 */
class ITape {
private:
    list<int> tape_;
public:
    ITape(UIBind & ui, list<int> vec) {

    }
    int readTape(void) {
        int aux = tape_.front();
        tape_.pop_front();
        return aux;
    }
};
