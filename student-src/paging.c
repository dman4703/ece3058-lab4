#include "paging.h"
#include "page_splitting.h"
#include "swapops.h"
#include "stats.h"

 /* The frame table pointer. You will set this up in system_init. */
fte_t *frame_table;

/*  --------------------------------- Task 2.1 --------------------------------------
    In this problem, you will initialize the frame table.

    The frame table will be located at physical address 0 in our simulated
    memory. You will first assign the frame_table global variable to point to
    this location in memory. You should zero out the frame table, in case for
    any reason physical memory is not clean.

    You should then mark the first entry in the frame table as protected. We do
    this because we do not want our free frame allocator to give out the frame
    used by the frame table.

    HINTS:
        You will need to use the following global variables:
        - mem: Simulated physical memory already allocated for you.
        - PAGE_SIZE: The size of one page.
        You will need to initialize (set) the following global variable:
        - frame_table: a pointer to the first entry of the frame table

    -----------------------------------------------------------------------------------
*/
void system_init(void) {
    // point frame_table to mem's value. not allocationg; just pointing. Two different data types require type casting (`extern fte_t *frame_table` and `uint8_t *mem` are different memory types).
    // set frame_table to hold all '0'. want to use the C function `Memset(starting point, 0, n)`. n is the num bytes to be filled, frame_table is the first frame in our memory, each frame contains PAGE_SIZE bytes.
    // Set first frame table entry's 'protected' to 1. frame_table[0] --> uint8_t protected
    
    /*
     * 1. Set the frame table pointer to point to the first frame in physical
     * memory. Zero out the memory used by the frame table.
     *
     * Address "0" in memory will be used for the frame table. This table will
     * contain n frame table entries (fte_t), where n is the number of
     * frames in memory. The frame table will be useful later if we need to
     * evict pages during page faults.
     */
    frame_table = (fte_t *)mem;
    memset(frame_table, 0, sizeof(fte_t) * NUM_FRAMES);

    /*
     * 2. Mark the first frame table entry as protected.
     *
     * The frame table contains entries for all of physical memory,
     * however, there are some frames we never want to evict.
     * We mark these special pages as "protected" to indicate this.
     */
    frame_table[0].protected = 1;

}

/*  --------------------------------- Task 2.2 --------------------------------------
    This function gets called every time a new process is created.
    You will need to allocate a new page table for the process in memory using the
    free_frame function so that the process can store its page mappings. Then, you
    will need to store the PFN of this page table in the process's PCB.

    HINTS:
        - Look at the pcb_t struct defined in pagesim.h to know what to set inside.
        - You are not guaranteed that the memory returned by the free frame allocator
        is empty - an existing frame could have been evicted for our new page table.
        - As in the previous problem, think about whether we need to mark any entries
        in the frame_table as protected after we allocate memory for our page table.
    -----------------------------------------------------------------------------------
*/
void proc_init(pcb_t *proc) {
    // Call free_frame() to get a free frame number, i
    // Zero out memory at i-th frame with memset(). Each frame contains PAGE_SIZE bytes of data; to access the start of the i-th frame in memory use mem + (i * PAGE_SIZE)
    // update process with i (saved_ptbr is set to i)
    // index into frame_table; set i-th entry as protected
    
    /*
     * 1. Call the free frame allocator (free_frame) to return a free frame for
     * this process's page table. You should zero-out the memory.
     */
    pfn_t pfn = free_frame();
    memset(mem + (pfn * PAGE_SIZE), 0, PAGE_SIZE);


    /*
     * 2. Update the process's PCB with the frame number
     * of the newly allocated page table.
     *
     * Additionally, mark the frame's frame table entry as protected. You do not
     * want your page table to be accidentally evicted.
     */
    proc->saved_ptbr = pfn;
    frame_table[pfn].protected = 1;

}

/*  --------------------------------- Task 3 --------------------------------------
    Swaps the currently running process on the CPU to another process.

    Every process has its own page table, as you allocated in proc_init. You will
    need to tell the processor to use the new process's page table.

    HINTS:
        - Look at the global variables defined in pagesim.h. You may be interested in
        the definition of pcb_t as well.
    -----------------------------------------------------------------------------------
 */
void context_switch(pcb_t *proc) {
    // set PTBR to the saved_ptbr of the new incoming process
}

/*  --------------------------------- Task 4 --------------------------------------
    Takes an input virtual address and returns the data from the corresponding
    physical memory address. The steps to do this are:

    1) Translate the virtual address into a physical address using the page table.
    2) Go into the memory and read/write the data at the translated address.

    Parameters:
        1) address     - The virtual address to be translated.
        2) rw          - 'r' if the access is a read, 'w' if a write
        3) data        - One byte of data to write to our memory, if the access is a write.
                         This byte will be NULL on read accesses.

    Return:
        The data at the address if the access is a read, or
        the data we just wrote if the access is a write.

    HINTS:
        - You will need to use the macros we defined in Problem 1 in this function.
        - You will need to access the global PTBR value. This will tell you where to
        find the page table. Be very careful when you think about what this register holds!
        - On a page fault, simply call the page_fault function defined in page_fault.c.
        You may assume that the pagefault handler allocated a page for your address
        in the page table after it returns.
        - Make sure to set the referenced bit in the frame table entry since we accessed the page.
        - Make sure to set the dirty bit in the page table entry if it's a write.
        - Make sure to update the stats variables correctly (see stats.h)
    -----------------------------------------------------------------------------------
 */
uint8_t mem_access(vaddr_t address, char rw, uint8_t data) {
    // use vpn and offset functions to split address
    // get adress of page table: Mem + PTBR * PAGE_SIZE
    // get address of the page table entry in page table: +vpn
    // check whether page fault. what bits to check in the current page table entry? use page_fault() to handle
    // in frame table, set pfn entry's 'reference' bit to 1. Frame_table[?].referenced=1
    // construct physical address
    // if rw == 'r' then increment reads inside Stats (Stats.reads)
    // if rw == 'w' then increment Stats.writes, mark dirty bit in pte, write data into physical address: memset(physical addr, data, sizeof(?))
    // return physical address's data

    /* Split the address and find the page table entry */


    /* If an entry is invalid, just page fault to allocate a page for the page table. */


    /* Set the "referenced" bit to reduce the page's likelihood of eviction */


    /*
        The physical address will be constructed like this:
        -------------------------------------
        |     PFN    |      Offset          |
        -------------------------------------
        where PFN is the value stored in the page table entry.
        We need to calculate the number of bits are in the offset.

        Create the physical address using your offset and the page
        table entry.
    */


    /* Either read or write the data to the physical address
       depending on 'rw' */
    if (rw == 'r') {

    } else {

    }
}

/*  --------------------------------- Task 7 --------------------------------------
    When a process exits, you need to free any pages previously occupied by the
    process. Otherwise, every time you closed and re-opened Microsoft Word, it
    would gradually eat more and more of your computer's usable memory.

    To free a process, you must clear the "mapped" bit on every page the process
    has mapped. If the process has swapped any pages to disk, you must call
    swap_free() using the page table entry pointer as a parameter.

    You must also clear the "protected" bits for the page table itself.
    -----------------------------------------------------------------------------------
*/
void proc_cleanup(pcb_t *proc) {
    // get page table from proc's saved_ptbr
    // i is each vpn; current pte = Page table + i
    // if current pte is valid, clear mapped bit in Frame_table[pfn]
    // if current pte > 0, swap_free(current pte)
    // free page table in the frame table. use proc's saved_ptbr to index into frame_table and clear Frame_table[...].protected

    /* Look up the process's page table */

    /* Iterate the page table and clean up each valid page */
    for (size_t i = 0; i < NUM_PAGES; i++) {

    }

    /* Free the page table itself in the frame table */

}
