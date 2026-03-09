#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Use standard elf.h if available, otherwise define needed parts
#ifdef __linux__
#include <elf.h>
#else
// Minimal definitions for ELF64
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint64_t Elf64_Xword;

#define EI_NIDENT 16

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

#define ELFMAG      "\177ELF"
#define SELFMAG     4
#define EI_CLASS    4
#define ELFCLASS64  2
#define EI_DATA     5
#define ELFDATA2LSB 1
#define EV_CURRENT  1
#define ET_EXEC     2
#define EM_X86_64   62
#endif

// Function to parse buffer and return entry point
uint64_t get_elf_entry_point(const char* buffer, size_t size) {
    if (size < sizeof(Elf64_Ehdr)) return 0;
    
    // Check magic
    if (memcmp(buffer, ELFMAG, SELFMAG) != 0) {
        printf("Error: Not an ELF file\n");
        return 0;
    }
    
    // Assumption: 64-bit Little Endian for this exercise
    if (buffer[EI_CLASS] != ELFCLASS64) {
        printf("Error: Not 64-bit ELF\n");
        return 0;
    }

    const Elf64_Ehdr* hdr = (const Elf64_Ehdr*)buffer;
    return hdr->e_entry;
}

void solution() {}

int main() {
    Elf64_Ehdr mock_hdr;
    memset(&mock_hdr, 0, sizeof(mock_hdr));
    
    // Fill specific fields
    memcpy(mock_hdr.e_ident, ELFMAG, SELFMAG);
    mock_hdr.e_ident[EI_CLASS] = ELFCLASS64;
    mock_hdr.e_ident[EI_DATA] = ELFDATA2LSB;
    mock_hdr.e_entry = 0x401000; // Standard Linux entry
    
    printf("Parsing Mock ELF Header...\n");
    uint64_t entry = get_elf_entry_point((const char*)&mock_hdr, sizeof(mock_hdr));
    
    printf("Entry Point: 0x%lx\n", entry);
    
    if (entry == 0x401000) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }
    return 0;
}
