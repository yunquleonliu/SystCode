# Problem 41: Minimal KVM Hypervisor

## Description
Use /dev/kvm API to boot a tiny 16-bit real-mode kernel.

## Learning Objectives
- **Concepts**: ioctl API, CPU State, Real Mode vs Protected Mode

## Implementation Guide
1. **Understand Layout**: Review how this component works in a real system.
2. **Define Structures**: Create the `struct` needed.
3. **Core Logic**: Implement the algorithm.
4. **Edge Cases**: Handle memory boundaries, overflows, or concurrency.

## Testing Strategy
- Verify fundamental correctness.
- Test boundary conditions.
- (If applicable) Performance benchmark.

## Pseudocode Hint
```text
// Add high-level logic here
```

## Solution Summary
The minimal KVM hypervisor uses `/dev/kvm` ioctls to create a VM, set up guest memory, initialize CPU state (registers, segment descriptors) for 16-bit real mode, and execute the guest kernel. It handles VM exits to emulate I/O operations, demonstrating the core virtualization cycle of running guest code and handling traps.

**[View Solution Code](https://github.com/yunquleonliu/SystCode/blob/main/problems/41_minimal_kvm/solution.c)**
