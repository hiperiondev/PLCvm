/*
 * PLCvm_assembler.h
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

#ifndef __PLCVM_ASSEMBLER_H__
#define __PLCVM_ASSEMBLER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "jwHash.h"
#include "PLCvm.h"
#include "PLCvm_assdis_common.h"

/////////////////////////////////////////////////////////////////////////////////////
const uint8_t VMFLAGS_POS[] = {
        ALU_F_T2N,
        ALU_F_T2R,
        ALU_F_N2T,
        ALU_F_R2P
};
const uint8_t VMFLAGS_CODE[] = {
        0x80,
        0x40,
        0x20,
        0x10
};
 char stringResult[512];

 int macroIndex = 0;
char macroName[40] = "";
 int addr = -1;
 int isStr = 0;
 int asmPrecedent = 0;
bool isAlu = false;
bool isCall = false;

jwHashTable   *equ = NULL;
jwHashTable  *word = NULL;
jwHashTable *label = NULL;
jwHashTable *macro = NULL;

/////////////////////////////////////////////////////////////////////////////////////
     int plcvm_assembleFile(char* fileIn, char* fileOut);
uint16_t plcvm_assembleLine(char* line, bool pass);

/////////////////////////////////////////////////////////////////////////////////////
int opCmp(char *op, char *value){
    return strcmp(strlwr(op), value);
}

int doHere(char *item1, char *item2) {
    int offsetHere = 0;
    char *ptr;
    if (strcmp(item1, "+") == 0) {
        int res = (int) strtol(item2, &ptr, 10);
        if (item2 == ptr) {
            printf("ASSEMBLER ERROR: $HERE$ offset not number\n");
            exit(1);
        }
        offsetHere += res;
    }
    if (strcmp(item1, "-") == 0) {
        int res = (int) strtol(item2, &ptr, 10);
        if (item2 == ptr) {
            printf("ASSEMBLER ERROR: $HERE$ offset not number\n");
            exit(1);
        }
        offsetHere -= res;
    }
    return (addr + offsetHere);
}

int directives(char* line, char* fileOut, bool pass) {
    char lineSplited[40][80], str[60] = "";
     int words = getWords(line, lineSplited);
    char *hresult;

    // search macro and insert
    if (get_str_by_str(macro, lineSplited[0], &hresult) != HASHNOTFOUND) {
        char macroArgs[40][80];
        char macroLine[40][80];
         int macroArgsCnt = words - 1;

        int cnt = 0;
        while(cnt < macroArgsCnt){
            strcpy(macroArgs[cnt], lineSplited[cnt]);
            cnt++;
        }
        macroIndex = 1;
        strcpy(macroName, lineSplited[0]);
        printf("[ %s\n", macroName);
        while (1) {
            sprintf(str, "%d#_%s", macroIndex++, macroName);
            if (get_str_by_str(macro, str, &hresult) == HASHNOTFOUND)
                break;

            // substitute macro arguments
            words = getWords(hresult, macroLine) - 1;
            strcpy(hresult,"");
            cnt = 0;
            while(cnt <= words){
                if (macroLine[cnt][0] == '$') {
                    int res = macroLine[cnt][1] - '0';
                    strcpy(macroLine[cnt], macroArgs[res]);
                }
                sprintf(hresult, "%s ",macroLine[cnt]);
                cnt++;
            }

            plcvm_assembleLine(hresult, pass);
        }
        printf("]\n");
        macroIndex = 0;
        return 0;
    } // macro

    if (opCmp(lineSplited[0], ".comment") == 0) {
        if (pass)
            printf("%s\n", line);
        return 0;
    }
    if (opCmp(lineSplited[0], ".equ") == 0) {
        if (opCmp(lineSplited[2], "$here$") == 0) {
            sprintf(lineSplited[2], "%04x", doHere(lineSplited[3],lineSplited[4]));
        }
        if (pass) {
            add_str_by_str(equ, lineSplited[1], lineSplited[2]);
            get_str_by_str(equ, lineSplited[1], &hresult);
            printf(".equ %s %s\n", lineSplited[1], hresult);
        }
        return 0;
    }
    if (opCmp(lineSplited[0], ".macro") == 0) {
        if (macroIndex) {
            printf("ASSEMBLER ERROR: macro inside macro\n");
            exit(1);
        }
        macroIndex = 1;
            strcpy(macroName, lineSplited[1]);
            add_str_by_str(macro, macroName, macroName);
            get_str_by_str(macro, macroName, &hresult);
            printf(".macro %s \n", hresult);
        return 0;
    }
    if (opCmp(lineSplited[0], ".endm") == 0) {
        printf(".endm\n");
        macroIndex = 0;
        return 0;
    }
    /* TODO add .include
    if (opCmp(lineSplited[0], ".include") == 0) {
        printf(".include %s\n", lineSplited[1]);
        plcvm_assembleFile(lineSplited[1], fileOut);
        printf(".endinclude\n");
        return 0;
    }
    */
    if (opCmp(lineSplited[0], ".word") == 0) {
        int ptr = 2;
        while (ptr <= words) {
            strcat(str, lineSplited[ptr]);
            strcat(str, " ");
            ptr++;
        }
        get_str_by_str(word, lineSplited[1], &hresult);
        add_str_by_str(word, lineSplited[1], str);
        get_str_by_str(word, lineSplited[1], &hresult);
        printf(".word %s (%s)\n", lineSplited[1], hresult);
        return 0;
    }
    if (opCmp(lineSplited[0], ".label") == 0) {
        sprintf(str, "%04x", addr + 1);
        if (pass)
            add_str_by_str(label, lineSplited[1], str);
        get_str_by_str(label, lineSplited[1], &hresult);
        printf(".label %s (%s)\n", lineSplited[1], hresult);
        return 0;
    }
    if (opCmp(lineSplited[0], ".org") == 0) {
        char *ptr;
        int value;
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            printf("     ^_ (%04x)\n", value);
        } else {
            value = (int) strtol(lineSplited[1], &ptr, 10);
            if (lineSplited[1] == ptr) {
                perror("Error: value not decimal integer");
                return RC_ERROR;
            }
        }
        addr = value;
        return 0;
    }

    if (macroIndex) {
        sprintf(str, "%d#_%s", macroIndex++, macroName);
        add_str_by_str(macro, str, line);
    }

    return 1;
}

//////////////////////////////////////////////////////////////
uint16_t plcvm_assembleLine(char* line, bool pass) {
      int words, value, w;
     char *hresult = NULL;
     char lineSplited[40][80], str[40];
      int len = 0;
     char *ptr;

    isStr = 0;

    words = getWords(line, lineSplited);
    value = (int) strtol(lineSplited[1], &ptr, 16);

    addr++;
    if (!pass) {
        printf("    %04x %s\n", addr, line);
    }

    get_str_by_str(word, lineSplited[0], &hresult);
    if (hresult != NULL) {
        words = getWords(hresult, lineSplited);
    } else {
        get_str_by_str(equ, lineSplited[1], &hresult);
        if (hresult == NULL)
            get_str_by_str(label, lineSplited[1], &hresult);

        if (hresult != NULL) {
            value = (int) strtol(hresult, NULL, 16);
            if (!pass) printf("               ^_ (%04x)\n", value);
        }
    }

    if (opCmp(lineSplited[0], "lit") == 0) {
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            if (!pass) printf("             ^_ (%04x)\n", value);
        }
        if (value < 32768)
            return (0x8000 | value);
        printf("ASSEMBLER ERROR: lit too long\n");
        exit(1);
    }

    if (opCmp(lineSplited[0], "jmp") == 0) {
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            if (!pass) printf("             ^_ (%04x)\n", value);
        }
        if (value < 8192)
            return (0x0000 | value);
        printf("ASSEMBLER ERROR: jmp too long\n");
        exit(1);
    }
    if (opCmp(lineSplited[0], "jmz") == 0) {
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            if (!pass) printf("             ^_ (%04x)\n", value);
        }
        if (value < 8192)
            return (0x2000 | value);
        printf("ASSEMBLER ERROR: jmz too long\n");
        exit(1);
    }
    if (opCmp(lineSplited[0], "cll") == 0) {
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            if (!pass) printf("             ^_ (%04x)\n", value);
        }
        if (value < 8192)
            return (0x4000 | value);
        printf("ASSEMBLER ERROR: cll too long\n");
        exit(1);
    }

    if (opCmp(lineSplited[0], "lod") == 0) {
        if (value < 0x100) {
            return (OP_ALU | (ALU_OP_ALULOD << 8) | value);
        }
        printf("ASSEMBLER ERROR: lod off range\n");
        exit(1);
    }

    if (opCmp(lineSplited[0], "str") == 0) {
        if (value < 0x100) {
            return (OP_ALU | (ALU_OP_ALUSTR << 8) | value);
        }
        printf("ASSEMBLER ERROR: str off range\n");
        exit(1);
    }

    if (opCmp(lineSplited[0], ".data") == 0) {
        if (opCmp(lineSplited[1], "$here$") == 0) {
            value = doHere(lineSplited[2], lineSplited[3]);
            if (!pass) printf("       ^_ (%04x)\n", value);
        }
        if (value < 65536) {
            return value;
        }
        printf("ASSEMBLER ERROR: .data too long\n");
        exit(1);
    }
    if (opCmp(lineSplited[0], ".string") == 0) {
        --addr;
        strcpy(str,line+8);
        trim(str);
        len = strlen(str);

        bool pad = false;
        if ((len % 2) == 0) {
            strcat(str, "\0");
            len++;
            pad = true;
        }
        strcpy(stringResult, "");
        char tmpStr[20], tmpStr2[20];
        strcpy(tmpStr2, "");
        int cnt = 0;
        while (cnt <= len) {
            sprintf(tmpStr, "%02x%02x", str[cnt], str[cnt + 1]);
            cnt += 2;
            isStr++;
            strcat(stringResult, tmpStr);
            strcat(stringResult, "\n");
            strcat(tmpStr2, tmpStr);
            strcat(tmpStr2," ");
        }
        trim(tmpStr2);
        if (!pass) printf("                 ^_ (%s) %s\n", tmpStr2, pad ? "padded" : "");
        return 0;
    }

    value = 0xffff;
    int op_alu_ext = 0;

    // ALU standard
    for (int w = 0; w < 32; w++) {
        strcpy(str, ALU[w]);
        removePrefix(str);

        if (opCmp(str, lineSplited[0]) == 0) {
            value = w << 8;
            break;
        }
    }

    // ALU EXT 1
    if (value == 0xffff) {
        for (int w = 0; w < 32; w++) {
            strcpy(str, ALU_EX1[w]);
            removePrefix(str);

            if (opCmp(str, lineSplited[0]) == 0) {
                value = w << 8;
                op_alu_ext = 1;
                break;
            }
        }
    }

    // ALU EXT 2
    if (value == 0xffff) {
        for (int w = 0; w < 32; w++) {
            strcpy(str, ALU_EX2[w]);
            removePrefix(str);

            if (opCmp(str, lineSplited[0]) == 0) {
                value = w << 8;
                op_alu_ext = 2;
                break;
            }
        }
    }

    // ALU EXT 3
    if (value == 0xffff) {
        for (int w = 0; w < 32; w++) {
            strcpy(str, ALU_EX3[w]);
            removePrefix(str);

            if (opCmp(str, lineSplited[0]) == 0) {
                value = w << 8;
                op_alu_ext = 3;
                break;
            }
        }
    }

    if (value == 0xffff) {
        printf("ASSEMBLER ERROR: unknown mnemonic\n");
        exit(1);
    }
    if (!pass)
        printf("         ^_ %s\n", hresult);
    value |= 0x6000;

    int pos = 1, fl = 0;
    while (pos < words) {
        for (w = 0; w < 4; w++) {
            strcpy(str, VMFLAGS[VMFLAGS_POS[w]]);
            removePrefix(str);
            if (opCmp(str, lineSplited[pos]) == 0) {
                value |= VMFLAGS_CODE[w];
                fl = 1;
                break;
            }
        }
        pos++;
        for (w = 0; w < 6; w++) {
            strcpy(str, DELTA[w]);
            removePrefix(str);
            if (opCmp(str, lineSplited[pos]) == 0) {
                value |= DELTA_CODE[w];
                fl = 1;
                break;
            }
        }
        if (fl == 0) {
            printf("ASSEMBLER ERROR: unknown mnemonic\n");
            exit(1);
        }
        pos++;
        fl = 0;
    }

    switch (op_alu_ext) {
    case 1:
        value &= 0xFFFC;
        value |= 0x03;
        break;
    case 2:
        value &= 0xFFF3;
        value |= 0x0C;
        break;
    case 3:
        value &= 0xFFF0;
        value |= 0x0F;
    }

    return value;
}

void assemblePass(bool pass, FILE *fIn, FILE *fOut, char *fileOut) {
    int asmResult;
   char buf[80];

    while (fgets(buf, sizeof(buf), fIn) != NULL) {
        buf[strlen(buf) - 1] = '\0';
        trim(buf);
        if (strcmp(buf, "") != 0) {
            if (directives(buf, fileOut, false) && !macroIndex) {
                asmResult = plcvm_assembleLine(buf, false);
                if (isStr > 0) {
                    addr += isStr;
                    if (pass)
                        fprintf(fOut, stringResult);
                } else {
                    // (r2p r-1)|CALL/JMP optimization //
                    if ((asmResult & OP_ALU) == OP_ALU) {
                        if ((asmResult == 0x6018) && (isAlu)
                                && !(asmPrecedent & 0x1C)) {
                            if (pass)
                                fprintf(fOut, "%04x\n", asmPrecedent | ALU_F_R2P);
                            isAlu = false;
                            printf("            ^_  compress R2P\n");
                            addr--;
                            continue;
                        }
                        if ((asmResult == 0x6018) && isCall) {
                            if (pass)
                                fprintf(fOut, "%04x\n", asmPrecedent);
                            isCall = false;
                            printf("            ^_  compress CALL/JMP\n");
                            addr--;
                            continue;
                        }
                        if (asmResult == 0x6018) {
                            if (isAlu && pass)
                                fprintf(fOut, "%04x\n", asmPrecedent);
                            if (pass)
                                fprintf(fOut, "%04x\n", asmResult);
                            isAlu = false;
                            continue;
                        }
                        asmPrecedent = asmResult;
                        isAlu = true;
                        continue;
                    }

                    if ((asmResult & OP_CLL) == OP_CLL) {
                        asmPrecedent = ARG_OP(asmResult);
                        isCall = true;
                        continue;
                    }
                    //////////////////////////////////

                    isAlu = false;
                    isCall = false;
                    if (pass)
                        fprintf(fOut, "%04x\n", asmResult);
                }
            }
        }
    }
}

int plcvm_assembleFile(char* fileIn, char* fileOut) {
    FILE *fIn;
    FILE *fOut;

    if (equ == NULL) {
          equ = create_hash(100);
        label = create_hash(100);
        remove(fileOut);
    }
    macro = create_hash(1000);
     word = create_hash(100);

    if ((fIn = fopen(fileIn, "r")) == NULL) {
        perror("Error: can't open source-file");
        return 1;
    }

    if ((fOut = fopen(fileOut, "a")) == NULL) {
        perror("Error: can't open destination-file");
        return 1;
    }

    printf ("\n\n -- First pass --\n\n");
    assemblePass(false, fIn, fOut, fileOut);

    addr = -1;
    rewind(fIn);

    printf ("\n\n -- Second pass --\n\n");
    assemblePass(true, fIn, fOut, fileOut);

    fclose(fIn);
    fclose(fOut);

    return 0;
}

#endif
