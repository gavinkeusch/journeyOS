#include "paging.h"

void paging_init()
{
    unsigned int curr_page_frame = 0;
    page_directory = kalloc(4 * 1024);

    for (int curr_pde = 0; curr_pde < PDE_NUM; curr_pde++) {
        unsigned int* pagetable = kalloc(4 * PTE_NUM);

        for (int curr_pte = 0; curr_pte < PTE_NUM; curr_pte++, curr_page_frame++)
            pagetable[curr_pte] = create_page_entry(curr_page_frame * 4096, 1, 0, 0, 1, 1, 0, 0, 0);

        page_directory[curr_pde] = create_page_entry(pagetable, 1, 0, 0, 1, 1, 0 ,0, 0);
    }

    load_page_directory();
    enable_paging();
}

int create_page_entry(int base_address, char present, char writable, char privilege_level,
    char cache_enabled, char write_through_cache, char accessed, char page_size, char dirty)
{
    int entry = 0;

    entry |= present;
    entry |= writable << 1;
    entry |= privilege_level << 2;
    entry |= write_through_cache << 3;
    entry |= cache_enabled << 4;
    entry |= accessed << 5;
    entry |= dirty << 6;
    entry |= page_size << 7;

    return base_address | entry;
}