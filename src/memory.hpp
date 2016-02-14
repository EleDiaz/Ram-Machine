/**

 */

#include <vector>
#include <functional>

using namespace std;

class UI;
/** Represents a input tape for Ram-Machine.

 */
enum DirectionMode {
    Direct,
    Indirect,
    Immediate
};


class Memory {
private:
  // representar la memoria mediante un vector tal cual
    vector<int> memory_;
public:
    Memory(int size, UI & ui);
    void setValue(int direction, int value, DirectionMode mode) {
        switch (mode) {
        case Direct:
            memory_[direction] = value;
            break;
        case Indirect:
            memory_[memory_[direction]] = value;
            break;
        case Immediate:
            break; // TODO error
        }
    }

    int getValue(int direction, DirectionMode mode) {
        switch (mode) {
        case Direct:
            return memory_[direction];
        case Indirect:
            return memory_[memory_[direction]];
        case Immediate:
            return direction; // TODO error incoherente
        }
    }
};
