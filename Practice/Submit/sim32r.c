// Instruction simulator
// 名前 (Name)： ファム・ヴァン・ナム (PHAM Van Nam)　学籍番号 (ID)：1F10180008

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define LINESIZE 256 // Max #characters of one line (#bytes)
#define MEMSIZE 4096 // Memory size (#bytes)

unsigned char mem[MEMSIZE];
int regfile[16];
int pc = 0;
int cbit = 0;

char *skipspace(char *p)
{
    while( isspace(*p) )
        p++;
    return p;
}

int toxdigit(char c)
{
    if( isdigit(c) )
        return c-'0';
    else if( islower(c) )
        return c-'a'+10;
    else
        return c-'A'+10;
}

int loaddata(char *fname)
{
    FILE *fp; // File pointer
    char line[LINESIZE], *p;
    int addr;

    fp = fopen(fname, "r"); // Open file.
    if( fp == NULL ) {
        printf("%s file not opened.\n", fname);
        return -1;
    }
    while( fgets(line, LINESIZE, fp) != NULL ) {
        for( addr = 0, p = skipspace(line); isxdigit(*p); p++ )
            addr = (addr<<4)+toxdigit(*p);
        for( p = skipspace(p); isxdigit(*p) && isxdigit(*(p+1)); p = p+2 )
            mem[addr++] = (toxdigit(*p)<<4)+toxdigit(*(p+1));
    }
    fclose(fp); // Close file.
    return 0;
}

#define get1bytes(a) (mem[a])
#define get2bytes(a) ((mem[a]<<8)|mem[(a)+1])
#define get4bytes(a) ((mem[a]<<24)|(mem[(a)+1]<<16)|(mem[(a)+2]<<8)|mem[(a)+3])
#define put1bytes(a,d) (mem[a]=((d)&0xff))
#define put2bytes(a,d) ((mem[a]=(((d)>>8)&0xff)), (mem[(a)+1]=((d)&0xff))) 
#define put4bytes(a,d) ((mem[a]=(((d)>>24)&0xff)), (mem[(a)+1]=(((d)>>16)&0xff)), (mem[(a)+2]=(((d)>>8)&0xff)), (mem[(a)+3]=((d)&0xff))) 
#define sign_extend(x) (((signed) ((x)<< 8)) >> 8)

int execinstr() // Execute an instruction
{
    int icode1, icode2, nextpc, rd, rs, addr, data;
    long long int ltmp;
    char *iname;

    icode1 = get2bytes(pc);
    if( (icode1&0x8000) == 0 ) { // 16-bit instruction code
        nextpc = pc+2;
    } else { // 32-bit instruction
        icode2 = get2bytes(pc+2);
        nextpc = pc+4;
    }

    rd = (icode1>>8)&0x0f;
    rs = icode1&0x0f;
    switch( icode1&0xf0f0 ) {
    case 0x00a0: // ADD
        regfile[rd] += regfile[rs];
        iname = "ADD";
        break;
    case 0x00c0: // AND
        regfile[rd] &= regfile[rs];
        iname = "AND";
        break;
    case 0x0040: // CMP
        cbit = ((regfile[rd] < regfile[rs]) ? 1 : 0);
        iname = "CMP";
        break;
    case 0x20c0: // LD
        addr = regfile[rs];
        regfile[rd] = get4bytes(addr);
        iname = "LD";
        break;
    case 0xa0c0: // LDR
        addr = regfile[rs]+(short)icode2;
        regfile[rd] = get4bytes(addr);
        iname = "LDR";
        break;
    case 0x1060: // MUL
        ltmp = (long long int)regfile[rd]*(long long int)regfile[rs];
        regfile[rd] = (int) ltmp;
        iname = "MUL";
        break;
    case 0x1080: // MV
        regfile[rd] = regfile[rs];
        iname = "MV";
        break;
    case 0x00b0: // NOT
        regfile[rd] = ~regfile[rs];
        iname = "NOT";
        break;
    case 0x00e0: // OR
        regfile[rd] |= regfile[rs];
        iname = "OR";
        break;
    case 0x2040: // ST
        addr = regfile[rs];
        data = regfile[rd];
        put4bytes(addr,data);
        iname = "ST";
        break;
    case 0xa040: // STR
        addr = regfile[rs]+(short)icode2;
        data = regfile[rd];
        put4bytes(addr,data);
        iname = "STR";
        break;
    case 0x0020: // SUB
        regfile[rd] -= regfile[rs];
        iname = "SUB";
        break;
    case 0x00d0: // XOR
        regfile[rd] ^= regfile[rs];
        iname = "XOR";
        break;
    case 0x80a0: // ADD3
        regfile[rd]= regfile[rs] + (signed short) icode2; 
        iname = "ADD3";
        break;
    case 0x80c0: // AND3
        regfile[rd]= regfile[rs] & (unsigned short) icode2; 
        iname = "AND3";
        break;
    case 0xb000: // BEQ
        if (regfile[rd] == regfile[rs])
            nextpc= (pc &  0xfffffffc) + ((signed short) icode2 << 1);
        iname = "BEQ";
        break;
    case 0xb010: // BNE
        if ( regfile[rs] != regfile[rd])
            nextpc = ( pc  ) + ((( signed short ) icode2) << 1);
        iname = "BNE";
        break;
    case 0x0050: // CMPU
        cbit = ( ( unsigned ) regfile[rd] < ( unsigned ) regfile[rs] ) ? 1:0;
        iname = "CMPU";
        break;
    case 0x9000: // DIV
        if (icode2 == 0){
            regfile[rd] = ( signed ) regfile[rd] / ( signed ) regfile[rs];
            iname = "DIV";
        }
        break;
    case 0x9010: // DIVU
        if (icode2 == 0){
            regfile[rd] = ( unsigned ) regfile[rd] / ( unsigned ) regfile[rs];
            iname = "DIVU";
        }
        break;
    case 0x20e0: // LDPI
        addr = regfile[rs];
        regfile[rd] = get4bytes(addr);
        regfile[rs]+= 2;
        iname = "LDPI";
        break;
    case 0x2080: // LDB
        addr= regfile[rs];
        regfile[rd]= (signed char) get1bytes(addr);
        iname = "LDB";
        break;
    case 0xa080: // LDBR
        addr= regfile[rs] + (signed short) icode2;
        regfile[rd]= (signed char) get1bytes(addr);
        iname = "LDBR";
        break;
    case 0x20a0: // LDH
        addr= regfile[rs];
        regfile[rd]= (signed short)get2bytes(addr);
        iname = "LDH";
        break;
    case 0xa0a0: // LDHR
        addr= regfile[rs] + (signed short)icode2;
        regfile[rd]= (signed short)get2bytes(addr);
        iname = "LDHR";
        break;
    case 0x2090: // LDUB
        addr= regfile[rs];
        regfile[rd]= (unsigned char) get1bytes(addr);
        iname = "LDUB";
        break;
    case 0xa090: // LDUBR
        addr= regfile[rs] + (signed short) icode2;
        regfile[rd]= (unsigned char) get1bytes(addr);
        iname = "LDUBR";
        break;
    case 0x20b0: // LDUH
        addr= regfile[rs];
        regfile[rd]= (unsigned short)get2bytes(addr);
        iname = "LDUH";
        break;
    case 0xa0b0: // LDUHR
        addr= regfile[rs] + (signed short)icode2;
        regfile[rd]= (unsigned short)get2bytes(addr);
        iname = "LDUHR";
        break;
    case 0x0030: // NEG
        regfile[rd]= 0 - regfile[rs];
        iname = "NEG";
        break;
    case 0x80e0: // OR3
        regfile[rd] = regfile[rs] | ( unsigned short ) icode2;
        iname = "OR3";
        break;
    case 0x9020: // REM
        if (icode2 == 0){
            regfile[rd] = ( signed ) regfile[rd] % ( signed ) regfile[rs] ;
            iname = "REM";
        }
        break;
    case 0x9030: // REMU
        if (icode2 == 0){
            regfile[rd] = ( unsigned ) regfile[rd] % ( unsigned ) regfile[rs] ;
            iname = "REMU";
        }
        break;
    case 0x1040: // SLL
        regfile[rd] = regfile[rd] << ( regfile[rs] & 31 ) ;
        iname = "SLL";
        break;
    case 0x90c0: // SLL3
        regfile[rd] = regfile[rs] << ( icode2 & 31 ) ;
        iname = "SLL3";
        break;
    case 0x1020: // SRA
        regfile[rd] = ( signed ) regfile[rd] >> ( regfile[rs] & 31 ) ;
        iname = "SRA";
        break;
    case 0x90a0: // SRA3
        regfile[rd] = ( signed ) regfile[rs] >> ( icode2 & 31 ) ;
        iname = "SRA3";
        break;
    case 0x1000: // SRL
        regfile[rd] = ( unsigned ) regfile[rd] >> ( regfile[rs] & 31 ) ;
        iname = "SRL";
        break;
    case 0x9080: // SRL3
        regfile[rd] = ( unsigned ) regfile[rs] >> ( icode2 & 31 ) ;
        iname = "SRL3";
        break;
    case 0x2060: // STPI
        regfile[rs]+= 2;
        addr = regfile[rs];
        data = regfile[rd];
        put4bytes(addr,data);
        iname = "STPI";
        break;
    case 0x2070: // STPD
        regfile[rs]-= 2;
        addr = regfile[rs];
        data = regfile[rd];
        put4bytes(addr,data);
        iname = "STPD";
        break;
    case 0x2000: // STB
        addr = regfile[rs];
        data = regfile[rd];
        put1bytes(addr,data);
        iname = "STB";
        break;
    case 0xa000: // STBR
        addr = regfile[rs] + (signed short) icode2;
        data = regfile[rd];
        put1bytes(addr,data);
        iname = "STBR";
        break;
    case 0x2020: // STH
        addr = regfile[rs];
        data = regfile[rd];
        put2bytes(addr,data);
        iname = "STH";
        break;
    case 0xa020: // STHR
        addr = regfile[rs] + (signed short)icode2;
        data = regfile[rd];
        put2bytes(addr,data);
        iname = "STHR";
        break;
    case 0x80d0: // XOR3
        regfile[rd] = ( unsigned ) regfile[rs] ^ ( unsigned short ) icode2;
        iname = "XOR3";
        break;    
    default:
        switch( icode1&0xff00 ) {
        case 0x7c00: // BC
            if( cbit == 1 )
                nextpc = pc+((char)(icode1&0x00ff)<<1);
            iname = "BC";
            break;
        case 0xfc00: // BC24
            if( cbit == 1 )
                nextpc = pc+((((char)(icode1&0x00ff)<<16)|(unsigned short)icode2)<<1);
            iname = "BC24";
            break;
        case 0x7d00: // BNC
            if( cbit == 0 )
                nextpc = pc+((char)(icode1&0x00ff)<<1);
            iname = "BNC";
            break;
        case 0xfd00: // BNC24
            if( cbit == 0 )
                nextpc = pc+((((char)(icode1&0x00ff)<<16)|(unsigned short)icode2)<<1);
            iname = "BNC24";
            break;
        case 0x7f00: // BRA
            nextpc = pc+((char)(icode1&0x00ff)<<1);
            iname = "BRA";
            break;
        case 0xff00: // BRA24
            nextpc = pc+((((char)(icode1&0x00ff)<<16)|(unsigned short)icode2)<<1);
            iname = "BRA24";
            break;
        case 0x7e00: // BL
            regfile[14] = pc + 2;  // In the manual: + 4
            nextpc= pc + ( ( ( signed char ) icode1 & 0x0000ffff ) << 1 );
            iname = "BL";
            break;
        case 0xfe00: // BL24
            regfile[14] = pc  + 4; // In manual: + 4
            ltmp= ((icode1 & 0x00ff) << 16) + icode2; // pcdisp24
            nextpc = pc + ( sign_extend (ltmp) << 1 );        
            iname = "BL24";
            break;
        default:
            switch( icode1&0xfff0 ) {
            case 0x1ec0: // JL
                regfile[14] = pc+2;
                nextpc = regfile[rs]&0xfffffffe;
                iname = "JL";
                break;
            case 0x1fc0: // JMP
                nextpc = regfile[rs]&0xfffffffe;
                iname = "JMP";
                break;
            case 0xb080: // BEQZ
                if (regfile[rs] == 0)
                    nextpc= (pc ) + ((signed short)icode2 << 1);
                iname = "BEQZ";
                break;
            case 0xb0b0: // BGEZ
                if (regfile[rs] >= 0)
                    nextpc= (pc ) + ((signed short)icode2 << 1);
                iname = "BGEZ";
                break;
            case 0xb0d0: // BGTZ
                if ((signed) regfile[rs] > 0)
                    nextpc= (pc ) + (((signed short)icode2 ) << 1);
                iname = "BGTZ";
                break;
            case 0xb0c0: // BLEZ
                if ((signed) regfile[rs] <= 0)
                    nextpc = (pc ) + (((signed short) icode2) << 1);
                iname = "BLEZ";
                break;
            case 0xb0a0: // BLTZ
                if ((signed) regfile[rs] < 0)
                    nextpc = (pc ) + (((signed short) icode2) << 1);
                iname = "BLTZ";
                break;
            case 0xb090: // BNEZ
                if ( regfile[rs] != 0 )
                    nextpc = ( pc  ) + ( ( ( signed short ) icode2 ) << 1);
                iname = "BNEZ";
                break;    
            case 0x8040: // CMPI
                cbit = ( ( signed ) regfile[rs] < ( signed short ) icode2 ) ? 1:0;
                iname = "CMPI";
                break; 
            case 0x8050: // CMPUI
                cbit = ( ( unsigned ) regfile[rs] < ( unsigned ) ( ( signed short ) icode2 ) ) ? 1:0;
                iname = "CMPUI";
                break; 
            default:
                if( (icode1&0xf000) == 0x4000 ) { // ADDI
                    regfile[rd] += (char)(icode1&0x00ff);
                    iname = "ADDI";
                } else if( (icode1&0xf000) == 0x6000 ) { // LDI
                    regfile[rd] = (char)(icode1&0x00ff);
                    iname = "LDI";
                } else if( (icode1&0xf0ff) == 0x90f0 ) { // LDI16
                    regfile[rd] = (short)icode2;
                    iname = "LDI16";
                } else if( (icode1&0xffff) == 0x7000 ) { // NOP
                    iname = "NOP";
                } else if( (icode1&0xf000) == 0xe000 ) { // LD24
                    // Rdest = imm24 & 0x00ffffff;
                    ltmp= icode1;
                    ltmp= ltmp << 16;
                    ltmp= ltmp + icode2;
                    regfile[rd] = ltmp & 0x00ffffff;
                    iname = "LD24";
                } else if( (icode1&0xf0ff) == 0xd0c0 ) { // SETH
                    regfile[rd] = ( signed short ) icode2 << 16 ;
                    iname = "SETH";
                } else if( (icode1&0b1111000011100000) == 0b0101000001000000 ) { // SLLI
                    int imm5= icode1 & 0b0000000000011111;
                    regfile[rd] = regfile[rd] << imm5 ;
                    iname = "SLLI";
                } else if( (icode1&0b1111000011100000) == 0b0101000000100000 ) { // SRAI
                    int imm5= icode1 & 0b0000000000011111;
                    regfile[rd] = ( signed ) regfile[rd] >> imm5 ;
                    iname = "SRAI";
                } else if( (icode1&0b1111000011100000) == 0b0101000000000000 ) { // SRLI
                    int imm5= icode1 & 0b0000000000011111;
                    regfile[rd] = ( unsigned ) regfile[rd] >> ( imm5 & 31 ) ;
                    iname = "SRLI";
                } else {
                    printf("Unknown instruction: icode1 = %04x\n", icode1);
                    return -1;
                }
            }
        }
    }
    printf("PC: %04x %s\n", pc, iname);
    pc = nextpc;
    return 0;
}

int main(int ac, char **av)
{
    int i, n;

    if( ac < 2 || 3 < ac ) {
        printf("%s: file [#instructions]\n", av[0]);
        return -1;
    }

    if( loaddata(av[1]) < 0 )
        return -1;
    if( ac == 2 )
        n = 10;
    else
        n = atoi(av[2]);

    for( i = 0; regfile[13] == 0 && i < n; i++ )
        execinstr();
        
    if( regfile[13] == 1 || i >= n )
        printf("Success.\n");
    else
        printf("Fail: ERR=%04x\n", regfile[12]);
}