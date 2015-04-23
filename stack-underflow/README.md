When getting a page fault for accessing data that is under the current `sp` (_stack pointer_) value, the kernel uses an access cushion[1]. If the page fault address is beyond that cushion, the process gets an access violation exception (i.e. `SIGSEGV`, i.e. _Segmentation Fault_).

The `stack-underflow.c` program checks this. If the page fault address is within that cushion (i.e. the underflow offset is `UNDERFLOW_ALMOST_FAULT`) the process will be OK. On the other hand, if the page fault address is outside that cushio (i.e. the underflow offset is `UNDERFLOW_WILL_FAULT`) the process will crash.

I don't know why I need to add an extra small offset to the value shown in the kernel[1] in order to make it crash.

[1] http://lxr.free-electrons.com/source/arch/x86/mm/fault.c?v=3.13#L1171
