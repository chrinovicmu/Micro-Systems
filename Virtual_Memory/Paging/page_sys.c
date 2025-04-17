#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096  //4KB PAGES 
#define NUM_PAGES 1024  // totol number of pages in virtual address 
#define MAX_FRAMES 2048

struct PageTableEntry{
    unsigned int frame_number : 20; 
    unsigned int present: 1; 
    unsigned int permissons: 3; 
    unsigned int user_mode: 1;
    unsigned int accesssed: 1; 
    unsigned int dirty: 1; 
    unsigned int reserved: 7; 
};

struct PhysicalFrame{
    unsigned int allocted: 1; 
    unsigned int process_id; 
};


static struct PhysicalFrame  physical_frames[NUM_PAGES];
static struct PageTableEntry page_table[NUM_PAGES]; 


void init_page_table()
{
    int x;

    for(x = 0; x < NUM_PAGES; ++x)
    {
        page_table[x].frame_number = 0; 
        page_table[x].present = 0; 
        page_table[x].permissons = 0; 
        page_table[x].user_mode = 0; 
        page_table[x].accesssed = 0;
        page_table[x].dirty = 0; 
    }
}

void caculate_vpn(unsigned int virtual_address)
{
    unsigned int vpn;
    unsigned int pte_address;
    unsigned int offset; 
    unsigned int phys_addr; 

    vpn 
}
unsigned int translate_address(unsigned int virtual_address)
{
    unsigned int page_number = virtual_address / PAGE_SIZE; 
    unsigned int offset = virtual_address % PAGE_SIZE; 

    if(!page_table[page_number].present)
    {
        handle_page_fault(page_number);
    }

    page_table[page_number].accesssed = 1; 

    unsigned int physical_address = (page_table[page_number].frame_number * PAGE_SIZE) + offset; 

    return physical_address; 
}

void handle_page_fault(unsigned int page_number)
{
    unsigned int free_frame = find_free_frame();
    load_page_from_disk(page_number, free_frame); 


    page_table[page_number].frame_number = free_frame; 
    page_table[page_number].present = 1; 
    page_table[page_number].accesssed = 0; 
    page_table[page_number].dirty = 0; 
}

int main(int argc, char *argv[])
{
    init_page_table();
    return EXIT_SUCCESS;
}
