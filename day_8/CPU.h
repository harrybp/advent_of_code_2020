#ifndef _CPU_INCLUDE
#define _CPU_INCLUDE

#include <vector>
#include <fstream>

struct Instr {
    std::string opCode;
    int         immed;
};

class CPU {
    public:
        CPU();

        bool terminated;
        bool stalled;

        void run();
        void step();
        void readProgram(std::string filename);
        void reset();

        int PC;
        int ACC;

        std::vector<Instr> program;
        std::vector<bool>  visited;
};

#endif
