.section ".text.boot"

.global _start
.extern _exception_init

_start:
    // Check processor ID is zero (executing on main core), else hang
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f
    // Not main core, hang
1:  wfe
    b       1b
2:  // Main Core

    // Clean the BSS section
    ldr     x1, =__bss_start     // Start address
    ldr     w2, =__bss_size      // Size of the section
3:  cbz     w2, kernel_entry     // Quit loop if zero
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b               // Loop if non zero


    //Execution Level
    ldr     x1, =0x30d00800
    msr     sctlr_el1, x1

    mov     x1, 0x80000000
    msr     hcr_el2, x1


    mrs     x1, CurrentEL
    and     x1, x1, #0xc
    cmp     x1, #0xc
    bne     el2
    
el3:
    mov     x1, 0x00000431
    msr     scr_el3, x1

    mov     x1, 0x000001c5
    msr     spsr_el3, x1

    adr     x1, kernel_entry
    msr     elr_el3, x1

    eret

el2:
    mov     x1, 0x000001c5
    msr     spsr_el2, x1

    adr     x1, kernel_entry
    msr     elr_el2, x1

    eret

kernel_entry: 
    ldr     x1, =_stack_top
    mov     sp, x1

    bl      _exception_init

    bl      main
    // Halt main core if it returns
    b       1b
