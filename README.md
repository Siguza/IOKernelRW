# IOKernelRW

Custom kext for kernel r/w on macOS.

If you don't know what that means, **stay away!** Dark things sleep in the abyss.

Needless to say, this will lower the security of your operating system to zero. That's the whole point. And with any luck it will also lower its stability to zero.

### Building

```
make
```

### Installation

1. Boot into recoveryOS and run:

   ```
   bputil -k
   csrutil disable
   ```
2. Reboot back into macOS and run (from within this folder):

   ```
   make install
   ```
3. Follow the OS prompts to approve the kext and reboot.

If you ever want to **undo** the above, you can just run `bputil -f` from within macOS (while connected to the internet) and reboot (unless you had previously lowered the security of your installation, in which case I trust you know how to adjust it back to how it was before).

### Usage

This creates an `IOKernelRW` service node in the IORegistry, on which an `IOKernelRWUserClient` can be opened by processes with the `com.apple.security.siguza.kernel-rw` entitlement.

The userclient exports a few external methods, all of which only take scalar inputs and provide no output (other than the return value). The following external methods exist:

| ID   | Name        | Arg 0                | Arg 1                     | Arg 2  | Arg 3                 |
| :--: | :---------- | :------------------- | :------------------------ | :----- | :-------------------- |
| 0    | `readVirt`  | source address (kVA) | destination address (uVA) | length | _N/A_                 |
| 1    | `writeVirt` | source address (uVA) | destination address (kVA) | length | _N/A_                 |
| 2    | `readPhys`  | source address (PA)  | destination address (uVA) | length | alignment<sup>1</sup> |
| 3    | `writePhys` | source address (uVA) | destination address (PA)  | length | alignment<sup>1</sup> |

<sup>1</sup> Values of 4 or 8 force all accesses to physical memory to be uncached and use the specified granularity as word size in bytes. Physical address and length must be a multiple of the chosen alignment. A value of 0 maps the physical range as cacheable instead, and puts no constraint on alignment or access granularity.

A header library with convenience wrappers exists in [`lib/iokernelrw.h`](https://github.com/Siguza/IOKernelRW/blob/master/lib/iokernelrw.h).

### Future Plans

The goal of this project is to provide capabilities that fall somewhere between what a kernel LPE would provide you and whatever primitives are useful for research and poking at hardware, with some degree of minimalism.

Things I thought about implementing:

- **Mapping memory into userspace**  
  Would remove the overhead of going through MIG and mapping/unmapping memory for each access, but is probably less powerful than direct accesses from kernel mode due to PPL constraints on what can be mapped into userspace? Would also require keeping track of `IOMemoryDescriptor` objects attached to the userclient, and that would require state management, reference counting, locking etc.
- **Kernel function calling**  
  Reasonable request. Might implement this if I ever feel like fiddling with PAC.
- **PAC signature forging**  
  Should be constructable with a kernel calling primitive.
- **Kernel base leak**  
  Should be constructable via phys read from something like CTRR lockdown registers or IORVBAR.

### License

[MIT](https://github.com/Siguza/IOKernelRW/blob/master/LICENSE).
