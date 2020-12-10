#include "CPU.h"

CPU::CPU(): PC(0), ACC(0), stalled(false), terminated(false){
}

void CPU::readProgram(std::string filename){
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

void CPU::reset(){
    terminated = false;
    stalled = false;
    PC = 0;
    ACC = 0;
    for(int i = 0; i < visited.size(); i++){
        visited[i] = false;
    }
}

void CPU::step(){
    visited[PC] = true;
    Instr instruction = program[PC];
    switch(instruction.opCode.c_str()[0]){
        case 'n': // NOP
            PC++;
            break;
        case 'j': // JMP
            PC += instruction.immed;
            break;
        case 'a': // ACC
            ACC += instruction.immed;
            PC++;
            break;
    }
    stalled = visited[PC];
    terminated = PC >= program.size();
}

void CPU::run(){
    while(!stalled && !terminated){
        step();
    }
}
