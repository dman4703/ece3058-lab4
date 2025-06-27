#pragma once

#include "paging.h"

/*  --------------------------------- Task 1: Page Splitting --------------------------------------
    Split the virtual address into VPN and offset.
    These macros will be used whenever you get a memory address from the CPU and need
    to translate it.

    HINT: Examine the global defines in pagesim.h, which will be
    necessary in implementing these functions.

    HINT: While these values will be powers of two, allowing you to use bit-wise
    arithmetic, consider using modulus division and integer division for
    an elegant solution.
    -----------------------------------------------------------------------------------
 */

// two possible ways to implement
/*
    Solution 1: Bit shifting and masking
    Page num = addr >> OFFSET_LEN
    Offset = addr & bitmask for VPN part
*/
/*
    Solution 2: Division and Modulus
    Page num = addr >> OFFSET_LEN = addr / 2^(OFFSET_LEN) = addr / page size
    Offset: same rule applies, but using modulus instead of division
*/

/* Get the virtual page number from a virtual address. */
static inline vpn_t vaddr_vpn(vaddr_t addr) {
    return addr / PAGE_SIZE; // use integer division to get vpn
}

/* Get the offset into the page from a virtual address. */
static inline uint16_t vaddr_offset(vaddr_t addr) {
    return addr % PAGE_SIZE; // offset is remainder of the address within the page
}
