# DEV011: Linux Driver + Device Tree

## Objective
- Create a Linux platform/PCIe driver skeleton and bind resources from Device Tree/ACPI definitions.

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
- C source: [../../problems/embedded101/embedded_devenv/DEV011_linux_driver_device_tree/solution.c](../../problems/embedded101/embedded_devenv/DEV011_linux_driver_device_tree/solution.c)
