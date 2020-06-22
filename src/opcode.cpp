#include "opcode.hpp"
#include "opcode_impl.hpp"

#include <map>
#include <memory>
#include <sys/time.h>

#include "opcode.hpp"
#include "state.hpp"

using std::make_unique;
using std::map;
using std::unique_ptr;

namespace chip8 {

namespace {

using OpcodePtr = unique_ptr<Opcode>;

class OpCodeContainer {
public:
    static OpCodeContainer &instance() {
        static OpCodeContainer _instance;
        return _instance;
    }

    OpCodeContainer(const OpCodeContainer &) = delete;
    OpCodeContainer(OpCodeContainer &&) = delete;

    OpCodeContainer &operator=(const OpCodeContainer &) = delete;
    OpCodeContainer &operator=(OpCodeContainer &&) = delete;

    Opcode &find(word code) { return *_codes.find(code)->second; }

private:
    OpCodeContainer() { _codes[Opcode::MVI_OPCODE] = make_unique<opcode::MVI>(); }

    map<word, OpcodePtr> _codes;
};

}  // namespace

Opcode &makeOpcode(word opcode) {
    word code = opcode & 0xF000;
    return OpCodeContainer::instance().find(code);
}

Opcode::Opcode(const std::string nmemonic, word code) : nmemonic(nmemonic), code(code) {}

void Opcode::operator()(State &state, word _data) { apply(state, _data); }

void opcode::MVI::apply(State &state, word _data) { state.indexRegister(_data); }

}  // namespace chip8
