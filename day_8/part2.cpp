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
    bool stalled;
    bool terminated;
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

void checkStall(){
    cpu.stalled = visited[cpu.PC];
}

void checkTerminated(){
    cpu.terminated = cpu.PC >= program.size();
}

void executeInstruction(){
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
    checkStall();
    checkTerminated();
}

void reset(){
    cpu.terminated = false;
    cpu.stalled = false;
    cpu.PC = 0;
    cpu.ACC = 0;
    for(int i = 0; i < visited.size(); i++){
        visited[i] = false;
    }
}

int main(){
    // Read program
    readProgram("input.txt");

    // Loop over program lines
    for(int i = 0; i < program.size(); i++){

        // Save the instruction, then convert jmp to nop or vice versa
        Instr saveInstruction = program[i];
        if(program[i].opCode == "nop"){
            program[i].opCode = "jmp";
        } else if(program[i].opCode == "jmp"){
            program[i].opCode = "nop";
        } else {
            continue;
        }

        // Run the program
        reset();
        while(!cpu.stalled && !cpu.terminated){
            executeInstruction();
        }

        // Check if the program terminated
        if(cpu.terminated){
            printf("TERMINATED: PC: %d, ACC: %d\n", cpu.PC, cpu.ACC);
            break;
        }

        // Restore changed instruction
        program[i] = saveInstruction;
    }
    return 1;
}
