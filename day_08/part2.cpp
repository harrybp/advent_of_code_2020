#include "CPU.h"

int main(){
    CPU cpu;

    // Read program
    cpu.readProgram("input.txt");

    // Loop over program lines
    for(int i = 0; i < cpu.program.size(); i++){

        // Save the instruction, then convert jmp to nop or vice versa
        Instr saveInstruction = cpu.program[i];
        if(cpu.program[i].opCode == "nop"){
            cpu.program[i].opCode = "jmp";
        } else if(cpu.program[i].opCode == "jmp"){
            cpu.program[i].opCode = "nop";
        } else {
            continue;
        }

        // Run the program
        cpu.reset();
        cpu.run();

        // Check if the program terminated
        if(cpu.terminated){
            printf("TERMINATED: PC: %d, ACC: %d\n", cpu.PC, cpu.ACC);
            break;
        }

        // Restore changed instruction
        cpu.program[i] = saveInstruction;
    }
    return 1;
}
