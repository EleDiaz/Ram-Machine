/**

 */

#include <vector>
#include <functional>

using namespace std;

class UI;
/** Represents a input tape for Ram-Machine.

 */


class Memory {
private:
  // representar la memoria mediante un vector tal cual
    vector<int> memory_;
public:
    enum DirectionMode {
        Direct,
        Indirect,
        Immediate
    };

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

    string representAddressing(const DirectionMode & mod) {
        switch (mod) {
        case Immediate:
            return "=";
        case Direct:
            return "";
        case Indirect:
            return "*";
        }
    }
};
