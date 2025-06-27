#include "paging.h"
#include "stats.h"

/* The stats. See the definition in stats.h. */
stats_t stats;

/*  --------------------------------- Task 8 --------------------------------------
    Calculate any remaining statistics to print out.

    You will need to include code to increment many of these stats in
    the functions you have written for other parts of the project.

    Use this function to calculate any remaining stats, such as the
    average access time (AAT).

    You may find the #defines in the stats.h file useful.
    -----------------------------------------------------------------------------------
*/
void compute_stats() {
    // Stats.access = reads + writes
    // Stats.aat = total operation time / stat.accesses
    // total operation time = (memory-level time * memory-level accesses) + (disk-level read time * disk-read accesses) + (disk-level write time * disk-write accesses)
}
