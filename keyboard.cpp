
#include "keyboard.h"

uint8_t shiftKey = 0x00;

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64)
{
    while(commandport.Read() & 0x1)
    dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

KeyboardDriver::~KeyboardDriver()
{
}

void printf(char*);

void capitalLetters(int key) {
    switch(key)
    {
        case 0x0E: printf("_"); break;
        
        case 0x10: printf("Q"); break;
        case 0x11: printf("W"); break;
        case 0x12: printf("E"); break;
        case 0x13: printf("R"); break;
        case 0x14: printf("T"); break;
        case 0x15: printf("Y"); break;
        case 0x16: printf("U"); break;
        case 0x17: printf("I"); break;
        case 0x18: printf("O"); break;
        case 0x19: printf("P"); break;
        
        case 0x1E: printf("A"); break;
        case 0x1F: printf("S"); break;
        case 0x20: printf("D"); break;
        case 0x21: printf("F"); break;
        case 0x22: printf("G"); break;
        case 0x23: printf("H"); break;
        case 0x24: printf("J"); break;
        case 0x25: printf("K"); break;
        case 0x26: printf("L"); break;
        case 0x27: printf(":"); break;
        case 0x28: printf("\""); break;
        
        case 0x2C: printf("Z"); break;
        case 0x2D: printf("X"); break;
        case 0x2E: printf("C"); break;
        case 0x2F: printf("V"); break;
        case 0x30: printf("B"); break;
        case 0x31: printf("N"); break;
        case 0x32: printf("M"); break;
        case 0x33: printf("<"); break;
        case 0x34: printf(">"); break;
        case 0x35: printf("?"); break;
        
        case 0x36: printf(""); break;
        case 0x2A: printf(""); break;
        
        default: {
            char* foo = "KEYBOARD 0x00 ";
            char* hex = "0123456789ABCDEF";
            foo[11] = hex[(key >> 4) & 0xF];
            foo[12] = hex[key & 0xF];
            printf(foo);
            break;
        }
        
        return;
    }
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    if(key < 0x80)
    {
        
      if(shiftKey == 0x01) {
            capitalLetters(key);
            shiftKey = 0x00;
            return esp;
        }
        
        else if((key == 0x36) || (key == 0x2A)) {
            if(shiftKey == 0x00) {
                shiftKey = 0x01;
            }
            
            else {
                printf("");
            }
            
            return esp;
        }
        
        else {
        switch(key)
        {
            
            case 0x02: printf("1"); break;
            case 0x03: printf("2"); break;
            case 0x04: printf("3"); break;
            case 0x05: printf("4"); break;
            case 0x06: printf("5"); break;
            case 0x07: printf("6"); break;
            case 0x08: printf("7"); break;
            case 0x09: printf("8"); break;
            case 0x0A: printf("9"); break;
            case 0x0B: printf("0"); break;
            case 0x0C: printf("-"); break;
            
            case 0x0E: printf("~"); break;

            case 0x10: printf("q"); break;
            case 0x11: printf("w"); break;
            case 0x12: printf("e"); break;
            case 0x13: printf("r"); break;
            case 0x14: printf("t"); break;
            case 0x15: printf("y"); break;
            case 0x16: printf("u"); break;
            case 0x17: printf("i"); break;
            case 0x18: printf("o"); break;
            case 0x19: printf("p"); break;
            case 0x1C: printf("\n"); break;
            
            case 0x1E: printf("a"); break;
            case 0x1F: printf("s"); break;
            case 0x20: printf("d"); break;
            case 0x21: printf("f"); break;
            case 0x22: printf("g"); break;
            case 0x23: printf("h"); break;
            case 0x24: printf("j"); break;
            case 0x25: printf("k"); break;
            case 0x26: printf("l"); break;
            case 0x27: printf(";"); break;
            case 0x28: printf("'"); break;

            case 0x2C: printf("z"); break;
            case 0x2D: printf("x"); break;
            case 0x2E: printf("c"); break;
            case 0x2F: printf("v"); break;
            case 0x30: printf("b"); break;
            case 0x31: printf("n"); break;
            case 0x32: printf("m"); break;
            case 0x33: printf(","); break;
            case 0x34: printf("."); break;
            case 0x35: printf("/"); break;

            case 0x39: printf(" "); break;
            
            case 0x45: printf(""); break;

            default:
            {
                char* foo = "KEYBOARD 0x00 ";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0xF];
                foo[12] = hex[key & 0xF];
                printf(foo);
                break;
            }
        }
    }
    
    }
    return esp;
    
}