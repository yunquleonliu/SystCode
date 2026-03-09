# DEV006: TPM 2.0 Measured Boot Basics

## Objective
- Capture boot measurements and extend PCR values with a basic measured boot flow and attestation notes.

## Why It Matters
- Aligns with real embedded product development and maintenance expectations.

## Requirements
- Define platform assumptions (Intel/ARM/Power, RTOS/OS, board constraints).
- Define interfaces, expected artifacts, and pass/fail criteria.
- Document debug and validation steps.

## Deliverables
- Design notes and architecture decisions.
- Implementation checklist and verification evidence.
- Review notes (design/code/test).

## Test & Validation
1. Functional validation path.
2. Failure-mode and troubleshooting path.
3. Regression and maintainability checks.

## Tooling & Process
- Git workflow, code review expectations, and issue tracking references.
- Scripts/log capture format for repeatable validation.

## Reference Implementation
- C source: [../../problems/embedded_devenv/DEV006_tpm_2_0_measured_boot_basics/solution.c](../../problems/embedded_devenv/DEV006_tpm_2_0_measured_boot_basics/solution.c)
