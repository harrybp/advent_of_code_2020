#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

struct Instr {
    std::string opCode;
    int         immed;
};

struct CPU {
    int PC;
    int ACC;
};

CPU cpu;

std::vector<Instr> program;
std::vector<bool>  visited;

void readProgram(std::string filename){
    // Input file
    std::string inputText;
    std::ifstream inputFile(filename);

    // Loop through lines in file
    while (getline(inputFile, inputText)) {
        if(inputText.size() > 0){
            Instr newInstruction;
            newInstruction.opCode = inputText.substr(0,3);
            newInstruction.immed  = stoi(inputText.substr(4, inputText.size()));
            program.push_back(newInstruction);
            visited.push_back(false);
        }

    }
}

bool executeInstruction(){

    // If we have already seen this instruction then we are stuck
    if(visited[cpu.PC]){
        printf("PC = %d : ACC = %d\n", cpu.PC, cpu.ACC);
        return false;

    // Otherwise, execute the instruction
    } else {
        visited[cpu.PC] = true;
        Instr instruction = program[cpu.PC];
        switch(instruction.opCode.c_str()[0]){
            case 'n': // NOP
                cpu.PC++;
                break;
            case 'j': // JMP
                cpu.PC += instruction.immed;
                break;
            case 'a': // ACC
                cpu.ACC += instruction.immed;
                cpu.PC++;
                break;
        }
        return true;
    }
}

int main(){
    // Get bag info
    readProgram("input.txt");
    cpu.PC = 0;
    cpu.ACC = 0;

    bool notStuck = true;
    while(notStuck){
        notStuck = executeInstruction();
    }
    return 1;
}
