#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "opcode.hpp"
#include "state.hpp"

using std::cout;
using std::dec;
using std::endl;
using std::hex;
using std::ifstream;
using std::ios;
using std::setfill;
using std::setw;
using std::string;
using std::vector;

using namespace chip8;

void load(const std::string &file);

int main(int argc, char *argv[]) {
    load(argv[1]);
    return 0;
}

void load(const std::string &_programFile) {
    vector<byte> program;

    if (!_programFile.empty()) {
        auto _programStream{ifstream(_programFile, ios::binary)};
        size_t line{State::CODE_ADDRESS};
        while (_programStream) {
            word _word{0};
            char b;
            _programStream.get(b);
            _word = (b << 8);
            _programStream.get(b);
            _word |= byte(b);

            auto &opcode = makeOpcode(_word & 0xF000);
            if (opcode.valid(_word))
                cout << "0x" << setfill('0') << hex << setw(2) << line << dec << setfill(' ') << "\t"
                     << opcode.toString(_word & 0x0FFF) << "\t\t## 0x" << setw(4) << setfill('0') << hex << _word << dec
                     << setfill(' ') << endl;
            else
                cout << "0x" << setfill('0') << hex << setw(2) << line << dec << setfill(' ') << "\t\t\t\t## 0x"
                     << setw(4) << setfill('0') << hex << _word << dec << setfill(' ') << endl;

            line += State::OPCODE_BYTES;
        }
    }
}
