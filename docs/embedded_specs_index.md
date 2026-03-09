# Embedded Problem Specs Index

This is the **docs-first** tracker for Embedded Software topics. We will complete specs before implementing `solution.c`.

## Source of Truth
- Full topic list and descriptions: [embedded_software_roadmap.md](embedded_software_roadmap.md)
- Spec template: [embedded_problem_template.md](embedded_problem_template.md)

## Current Drafted Specs
| ID | Topic | Spec |
|---|---|---|
| E001 | C Runtime Initialization (CRT0) | [embedded_01_crt0.md](embedded_01_crt0.md) |
| E044 | Reentrancy Lab (The Gauntlet) | [embedded_reentrancy_lab.md](embedded_reentrancy_lab.md) |
| E103 | SmartNIC Initialization (Mailbox) | [embedded_smartnic_init.md](embedded_smartnic_init.md) |

## Planned Spec Batches
| Batch | Scope | Status |
|---|---|---|
| B1 | E001-E010 Bare Metal Essentials | In progress |
| B2 | E011-E025 Peripheral Drivers | Planned |
| B3 | E026-E045 RTOS Kernel + Reentrancy | In progress |
| B4 | E046-E055 Advanced Real-Time Scheduling | Planned |
| B5 | E056-E065 Memory & Storage | Planned |
| B6 | E066-E080 Communication Protocols | Planned |
| B7 | E081-E090 Bootloader & Security | Planned |
| B8 | E091-E101 DSP + Testing & DevOps | Planned |
| B9 | E102-E106 SmartNIC / IB High Performance I/O | In progress |

## Definition of Done for Each Spec
- Problem objective and system context are clear.
- API/IO contracts are defined.
- Reentrancy/concurrency constraints are explicit (Task/ISR/SoftIRQ/SMP).
- Determinism and timing acceptance criteria are measurable.
- Test plan includes stress + fault cases.

## Next Docs-Only Work
1. Create `docs/embedded_specs/E0xx_*.md` files in batch order.
2. Cross-link each spec from this index.
3. Start implementation only after spec review.
