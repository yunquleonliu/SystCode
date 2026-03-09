#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Mocking a 3-level page table system
// Virtual Address: [ PGD_IDX (9) | PMD_IDX (9) | PTE_IDX (9) | OFFSET (12) ]
// This covers 39 bits of address space.

#define PAGE_SHIFT 12
#define PAGE_SIZE ((uint64_t)1 << PAGE_SHIFT)
#define PTRS_PER_PTE 512

typedef struct {
    uint64_t entries[PTRS_PER_PTE]; 
} PageTable;

PageTable* create_table() {
    PageTable* table = (PageTable*)malloc(sizeof(PageTable)); 
    memset(table, 0, sizeof(PageTable));
    return table;
}

// Bit manipulation macros
// VA: 63..39 (ignored) | 38..30 PGD | 29..21 PMD | 20..12 PTE | 11..0 Offset
#define PGD_INDEX(x) (((x) >> (12 + 9 + 9)) & 0x1FF)
#define PMD_INDEX(x) (((x) >> (12 + 9)) & 0x1FF)
#define PTE_INDEX(x) (((x) >> 12) & 0x1FF)
#define OFFSET(x)    ((x) & 0xFFF)

void map_page(PageTable* pgd, uint64_t va, uint64_t pa) {
    uint64_t pgd_idx = PGD_INDEX(va);
    uint64_t pmd_idx = PMD_INDEX(va);
    uint64_t pte_idx = PTE_INDEX(va);

    if (pgd->entries[pgd_idx] == 0) {
        pgd->entries[pgd_idx] = (uint64_t)create_table() | 0x1; // Present bit
    }
    // Mask out flag bits to get pointer
    PageTable* pmd = (PageTable*)(pgd->entries[pgd_idx] & ~0xFFF);

    if (pmd->entries[pmd_idx] == 0) {
        pmd->entries[pmd_idx] = (uint64_t)create_table() | 0x1;
    }
    PageTable* pte = (PageTable*)(pmd->entries[pmd_idx] & ~0xFFF);

    pte->entries[pte_idx] = (pa & ~0xFFF) | 0x1; // Present
}

uint64_t translate(PageTable* pgd, uint64_t va) {
    uint64_t pgd_idx = PGD_INDEX(va);
    if ((pgd->entries[pgd_idx] & 0x1) == 0) return 0; // Not present
    
    PageTable* pmd = (PageTable*)(pgd->entries[pgd_idx] & ~0xFFF);
    uint64_t pmd_idx = PMD_INDEX(va);
    if ((pmd->entries[pmd_idx] & 0x1) == 0) return 0; 
    
    PageTable* pte = (PageTable*)(pmd->entries[pmd_idx] & ~0xFFF);
    uint64_t pte_idx = PTE_INDEX(va);
    
    uint64_t pte_entry = pte->entries[pte_idx];
    if (!(pte_entry & 0x1)) return 0; // Not present
    
    return (pte_entry & ~0xFFF) | OFFSET(va);
}

void solution() {
    // Wrapper for testing if needed
}

int main() {
    PageTable* pgd = create_table();
    uint64_t va = 0x123456789;
    uint64_t pa = 0xABCDE000;
    
    printf("Simulating MMU 3-level Walk...\n");
    printf("Mapping VA: 0x%lx to PA: 0x%lx\n", va, pa);
    
    map_page(pgd, va, pa);
    
    uint64_t resolved = translate(pgd, va);
    printf("Resolved:   0x%lx\n", resolved);
    
    uint64_t expected = (pa & ~0xFFF) | OFFSET(va);
    
    if (resolved == expected) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed: Expected 0x%lx\n", expected);
    }
    
    return 0;
}
