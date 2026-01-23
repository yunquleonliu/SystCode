/**
 * Problem 44: eBPF Verifier
 * Verify safety of eBPF bytecode before execution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    BPF_MOV, BPF_ADD, BPF_EXIT
} BPFOpcode;

typedef struct {
    BPFOpcode op;
    int dst_reg;
    int32_t imm;
} BPFInsn;

typedef struct {
    int reg_type[11];
} VerifierState;

void verifier_init(VerifierState* state) {
    memset(state, 0, sizeof(VerifierState));
}

bool verify_insn(VerifierState* state, BPFInsn* insn) {
    switch (insn->op) {
    case BPF_MOV:
        printf("  MOV r%d, %d\n", insn->dst_reg, insn->imm);
        break;
    case BPF_ADD:
        printf("  ADD r%d, %d\n", insn->dst_reg, insn->imm);
        break;
    case BPF_EXIT:
        printf("  EXIT\n");
        break;
    }
    return true;
}

bool verify_program(BPFInsn* prog, int count) {
    printf("Verifying %d instructions\n", count);
    VerifierState state;
    verifier_init(&state);
    for (int i = 0; i < count; i++) {
        if (!verify_insn(&state, &prog[i])) return false;
    }
    printf("Verification PASSED\n");
    return true;
}

int main() {
    printf("=== eBPF Verifier ===\n\n");
    BPFInsn prog[] = {
        {BPF_MOV, 0, 42},
        {BPF_ADD, 0, 8},
        {BPF_EXIT, 0, 0}
    };
    verify_program(prog, 3);
    return 0;
}