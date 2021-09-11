# PLCvm
Virtual Machine for IEC 61131-3 ( work in process... )

*TODO:*
* complete functions
* implement persist/retain
* test
* optional compilation by functions groups

Functions implemented:
```diff
+: Completed
*: Incompleted
-: Still not implemented

* VARCVR: CREATE_VARIABLE
* VARSVR: SET_VARIABLE
+ NUMABS: ABS
+ NUMSQR: SQRT
+ NUMLON: LN
+ NUMLOG: LOG
+ NUMSIN: SIN
+ NUMCOS: COS
+ NUMTAN: TAN
+ NUMASN: ASIN
+ NUMACS: ACOS
+ NUMATN: ATAN
+ ATHADD: ADD
+ ATHMUL: MUL
+ ATHSUB: SUB
+ ATHDIV: DIV
+ ATHMOD: MOD
+ ATHEXP: EXPT
+ ATHMOV: MOVE
+ BITSHL: SHL
+ BITSHR: SHR
+ BITROR: ROR
+ BITROL: ROL
+ CMPAND: AND
+ CMPORF: OR
+ CMPXOR: XOR
+ CMPNOT: NOT
+ SELMAX: MAX
+ SELMIN: MIN
- ENCTBI: TO_BIG_ENDIAN
- ENCTLI: TO_LITTLE_ENDIAN
* CNVTOT: CONVERT_TO_TYPE
+ SELMUX: MUX
+ CMPGRT: GT
+ CMPGEQ: GE
+ CMPEQU: EQ
+ CMPLES: LE
+ CMPLTH: LT
+ CMPNEQ: NE
+ STRLEN: LEN
+ STRLFT: LEFT
+ STRRGH: RIGHT
+ STRMID: MID
+ STRCNC: CONCAT
+ STRINS: INSERT
+ STRDEL: DELETE
+ STRRPL: REPLACE
- STRFND: FIND
- TIMADD: ADD
- TIMSUM: SUB
- TIMMUL: MUL
- TIMDIV: DIV
- TIMCNC: CONCAT
- ENMSEL: SEL
- ENMMUX: MUX
- ENMEQU: EQ
- ENMNEQ: NE
```
