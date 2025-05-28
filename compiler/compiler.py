#!/usr/bin/python3

from instructions import get_instr, registers
import re

f = open("example.xx", "r")

data = f.read().replace("\n","").split(";")
data_signs = {}

bytestr = []

def parse_instr(s):
    print(f"parsing {s}")
    match = re.match(r'^[^\s]+', s)
    if match:
        in_str = match.group()
        instrbyte = get_instr(in_str)
        if instrbyte[1] != 0:
            bytestr.append(instrbyte[0])
        else:
            print(f"unrecognized instruction {in_str[1]}")
            return False
        
        s = s[len(in_str):].replace(" ", "")
        if instrbyte[1] == 2:
            s = s.split(",")#todo : 1 or 2 args
            if s[0] not in registers:
                return False
            bytestr.append(registers[s[0]])
            argument2 = s[1]
            if argument2 in registers:
                bytestr.append(registers[argument2])
            elif argument2.startswith("0x"):
                if int(argument2[2:], 16) > (1 << 15):
                    print("literal larger than 16bit")
                    return False
                hexval = format(int(argument2[2:],16),"04x")
                upperb = int(hexval[:2],16)
                lowerb = int(hexval[2:],16)
                bytestr.append(lowerb)
                bytestr.append(upperb)

            else:
                hexval = format(int(argument2), '04x')
                upperb = int(hexval[:2], 16)
                lowerb = int(hexval[2:], 16)
                bytestr.append(lowerb)
                bytestr.append(upperb)

        elif instrbyte[1] == 1:
            if s in registers:
                bytestr.append(registers[s])
            elif s.startswith("0x"):
                hexval = format(int(s[2:],16), "04x")
                upperb = int(hexval[:2], 16)
                lowerb = int(hexval[2:], 16)
                bytestr.append(lowerb)
                bytestr.append(upperb)
            else:
                hexval = format(int(s[2:]), '04x')
                upperb = int(hexval[:2], 16)
                lowerb = int(hexval[2:], 16)
                bytestr.append(lowerb)
                bytestr.append(upperb)
        elif instrbyte[1] == 3:
            relativeval = len(bytestr) - int(data_signs[s]) + 2#+2b for lower
            print(f"relative :{relativeval}")
            hexval = format(relativeval, '04x')
            upperb = int(hexval[:2], 16)
            lowerb = int(hexval[2:], 16)
            bytestr.append(lowerb)
            bytestr.append(upperb)
        else:
            print("error not enough arguments")
            return False
        return True
    else:
        print("error parsing instruction")
        return False

data.pop(-1)
for x in data:
    if ":" in x:
        z = x.split(":")
        #data[ data.index(x)] = z[1]
        data_signs[z[0]] = len(bytestr)
        print(f"resolving {z[0]}")
        if ( parse_instr(z[1]) == False ):
            print("Comp eror")
            break

    else:
        if ( parse_instr(x) == False ):
            print("Comp eror")
            break
bytedata = bytearray(bytestr)
bin = open("x.bin","wb+")
bin.write(bytedata)
