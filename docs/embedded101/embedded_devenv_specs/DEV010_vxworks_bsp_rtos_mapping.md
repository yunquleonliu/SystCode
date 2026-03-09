# DEV010: VxWorks BSP + RTOS Mapping

## Objective
- Map tasks/ISRs/timers/memory model into VxWorks primitives and produce a BSP adaptation checklist.

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
- C source: [../../problems/embedded101/embedded_devenv/DEV010_vxworks_bsp_rtos_mapping/solution.c](https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/embedded_devenv/DEV010_vxworks_bsp_rtos_mapping/solution.c)
