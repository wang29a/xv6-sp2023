> Looking at the backtrace output, which function called syscall? 

usertrap()

> What is the value of p->trapframe->a7 and what does that value represent? (Hint: look user/initcode.S, the first user program xv6 starts.) 

0x7 

sys_exec SYSCALLID

> What was the previous mode that the CPU was in? 

> Write down the assembly instruction the kernel is panicing at. Which register corresponds to the variable num? 

> Why does the kernel crash? Hint: look at figure 3-3 in the text; is address 0 mapped in the kernel address space? Is that confirmed by the value in scause above? (See description of scause in RISC-V privileged instructions) 

> What is the name of the binary that was running when the kernel paniced? What is its process id (pid)? 

initcode 1