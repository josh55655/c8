#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <boost/program_options.hpp>

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

namespace po = boost::program_options;

namespace {

string filename;
bool displayUnknown{false};

void parseArgs(int argc, char *argv[]);
void load(const std::string &file);

}  // namespace

int main(int argc, char *argv[]) {
    parseArgs(argc, argv);
    load(filename);
    return 0;
}

namespace {

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
            else if (displayUnknown)
                cout << "0x" << setfill('0') << hex << setw(2) << line << dec << setfill(' ') << "\t\t\t\t## 0x"
                     << setw(4) << setfill('0') << hex << _word << dec << setfill(' ') << endl;

            line += State::OPCODE_BYTES;
        }
    }
}

void parseArgs(int argc, char *argv[]) {
    // Declare the supported options.
    po::options_description desc("De-assembler for chip8 ");
    po::positional_options_description pd;
    po::variables_map vm;

    // clang-format off
    desc.add_options()
        ("help", "produce help message")
        ("show-unknown,u", "report unknown bytes")
        ("file", po::value<string>()->required(), "file to decode");
    // clang-format on

    pd.add("file", 1);
    try {
        auto parsed = po::command_line_parser(argc, argv).options(desc).positional(pd).run();

        po::store(parsed, vm);
        po::notify(vm);
    } catch (po::required_option &e) {
        cout << desc << "\n";
        exit(1);
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        exit(1);
    }

    displayUnknown = vm.count("show-unknown");
    filename = vm["file"].as<string>();
}

}  // namespace