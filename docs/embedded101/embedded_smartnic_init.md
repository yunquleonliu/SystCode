# Problem: SmartNIC Initialization (Mailbox)

## Description

Modern high-performance NICs (Network Interface Cards) and accelerators use a **Mailbox Interface** (also called Admin Queue) to communicate control commands between the host Driver and the device Firmware.

This challenge simulates initializing a hypothetical "SuperNIC" via its PCI BAR0 memory-mapped registers.

The initialization sequence requires:
1.  **Reset**: Check the device status register.
2.  **Version Check**: Read the firmware version.
3.  **Mailbox Setup**: Allocate a specialized ring buffer in host memory for Admin Commands.
4.  **Handshake**: Send an `INIT_DRIVER` command via the mailbox and wait for `COMPLETION`.

## Requirements

1.  **Simulated PCI Read/Write**: Implement `pci_read_32` and `pci_write_32` to access the `g_virtual_device_bar0` array.
2.  **Command Structure**: Define a 64-byte `AdminCommand` struct (Opcode, Flags, Address, etc.).
3.  **Doorbell Logic**: Write the "tail" index to the hardware register to trigger processing.
4.  **Completion Polling**: Poll the `AdminCompletion` ring for the `status` bit flip (Ownership bit).

## Hint

*   The NIC is a separate entity (simulated here by a thread or just function calls).
*   Communication is asynchronous: You write a command, ring the doorbell, and *poll* for a result.
*   Endianness matters (Simulated as little-endian host, little-endian device).