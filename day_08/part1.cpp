#include "CPU.h"

int main(){
    CPU cpu;
    cpu.readProgram("input.txt");
    cpu.reset();
    cpu.run();
    printf("%s with ACC: %d\n", cpu.stalled? "STALLED" : "TERMINATED", cpu.ACC);
    return 1;
}
