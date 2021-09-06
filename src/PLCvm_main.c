/*
 *  PLCvm_main.c
 *
 * Copyright 2021 Emiliano Gonzalez LU3VEA (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/PLCvm *
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "PLCvm_config.h"
#include "PLCvm.h"
#include "PLCvm_assembler.h"
#include "PLCvm_disassembler.h"

///////////////////////////////// memory functions //////////////////////////////////
uint8_t plcvm_mem_put(uint16_t addr, uint16_t value, vm_t* vm) {
    vm->RAM[addr] = value;
    return RC_OK;
}

uint16_t plcvm_mem_get(uint16_t addr, vm_t* vm) {
    return vm->RAM[addr];
}

/////////////////////////////////////////////////////////////////////////////////////
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    uint8_t result;
    vm_t *vm = PLCvm_init(RAM_SIZE, RS_SIZE, DS_SIZE, REG_SIZE);

#ifdef DEBUG
    DBG_PRINT("START...\n");
#endif
    if (argc == 1) {
        printf("\nUse: SM1 [-d|-a] file.in [file.out] [basewords] [ramSize]\n");
        exit(1);
    } else if (!strcmp(argv[1], "-d")) { // disassembler
        int add;
        for (add = 0; add < RAM_SIZE; add++) {
            uint16_t word = plcvm_mem_get(add, vm);
            printf("%04x %s\n", add, plcvm_disassembly(word));
        }
    } else if (!strcmp(argv[1], "-a")) { // assembler
        plcvm_assembleFile(argv[2], argv[3]);
    } else {                        // run program
        printf("--RUN\n\n");
#ifdef DEBUG
        DBG_PRINT("LOAD...\n");
#endif
        FILE *RAM;
        int addr = 0x0000;
        if (argc == 2) {
            printf("load(2): %s\n", argv[1]);
            RAM = fopen(argv[1], "r");
        } else {
            printf("load: %s\n", argv[1]);
            RAM = fopen(argv[2], "r");
        }
#ifdef DEBUG
        if (RAM == NULL)
            DBG_PRINT("...Can't load file!\n");
#endif
        uint16_t data;
        while (fread(&data, sizeof(uint16_t), 1, RAM) == 1) {
            vm->RAM[addr++] = data;
        }
        fclose(RAM);

        while (1) {
            uint16_t word = plcvm_mem_get(vm->pc, vm);
            result = PLCvm_step(word, vm);
#ifdef DEBUG
            DBG_PRINT("step:%d\n", step_counter++);
#endif
            // TODO: Implement external functions for input/output
            //if ((vm->status & ST_SNDTN) && (vm->n_ext == 0)) {
            //    printf("%c", (char) vm->t_ext);
            //    vm->status &= ~ST_SNDTN;
            //}

            if (result != RC_OK) {
                printf("\nEXCEPTION: %d\n", result);
                exit(1);
            }
        }
    }
}
