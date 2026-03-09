# Embedded Problem Specs Index

This is the **docs-first** tracker for Embedded Software topics. We complete specs before implementing `solution.c`.

## Source of Truth
- Full topic list and descriptions: [embedded_software_roadmap.md](embedded_software_roadmap.md)
- Spec template: [embedded_problem_template.md](embedded_problem_template.md)
- Embedded DevEnv track: [embedded_devenv_index.md](embedded_devenv_index.md)

## Coverage Matrix (E001-E106)
| ID | Topic | Spec | Status |
|---|---|---|---|
| E001 | C Runtime Initialization (CRT0) | [embedded_specs/E001_c_runtime_initialization_crt0.md](embedded_specs/E001_c_runtime_initialization_crt0.md) | Detailed Draft + Spec |
| E002 | Linker Script Basics | [embedded_specs/E002_linker_script_basics.md](embedded_specs/E002_linker_script_basics.md) | Created |
| E003 | Memory Map Layout | [embedded_specs/E003_memory_map_layout.md](embedded_specs/E003_memory_map_layout.md) | Created |
| E004 | Register Bit Manipulation | [embedded_specs/E004_register_bit_manipulation.md](embedded_specs/E004_register_bit_manipulation.md) | Created |
| E005 | Inline Assembly & Intrinsics | [embedded_specs/E005_inline_assembly_intrinsics.md](embedded_specs/E005_inline_assembly_intrinsics.md) | Created |
| E006 | Stack Paint | [embedded_specs/E006_stack_paint.md](embedded_specs/E006_stack_paint.md) | Created |
| E007 | Endianness Handling | [embedded_specs/E007_endianness_handling.md](embedded_specs/E007_endianness_handling.md) | Created |
| E008 | Unaligned Access Handling | [embedded_specs/E008_unaligned_access_handling.md](embedded_specs/E008_unaligned_access_handling.md) | Created |
| E009 | Function Call Conventions (ABI) | [embedded_specs/E009_function_call_conventions_abi.md](embedded_specs/E009_function_call_conventions_abi.md) | Created |
| E010 | Vector Table Setup | [embedded_specs/E010_vector_table_setup.md](embedded_specs/E010_vector_table_setup.md) | Created |
| E011 | GPIO Driver | [embedded_specs/E011_gpio_driver.md](embedded_specs/E011_gpio_driver.md) | Created |
| E012 | UART Polling Driver | [embedded_specs/E012_uart_polling_driver.md](embedded_specs/E012_uart_polling_driver.md) | Created |
| E013 | UART Interrupt-Based Ring Buffer | [embedded_specs/E013_uart_interrupt_based_ring_buffer.md](embedded_specs/E013_uart_interrupt_based_ring_buffer.md) | Created |
| E014 | Simple Timer/Counter | [embedded_specs/E014_simple_timer_counter.md](embedded_specs/E014_simple_timer_counter.md) | Created |
| E015 | PWM Generation | [embedded_specs/E015_pwm_generation.md](embedded_specs/E015_pwm_generation.md) | Created |
| E016 | Watchdog Timer (WDT) | [embedded_specs/E016_watchdog_timer_wdt.md](embedded_specs/E016_watchdog_timer_wdt.md) | Created |
| E017 | I2C Bit-Banging | [embedded_specs/E017_i2c_bit_banging.md](embedded_specs/E017_i2c_bit_banging.md) | Created |
| E018 | I2C Hardware Master | [embedded_specs/E018_i2c_hardware_master.md](embedded_specs/E018_i2c_hardware_master.md) | Created |
| E019 | SPI Master Polling | [embedded_specs/E019_spi_master_polling.md](embedded_specs/E019_spi_master_polling.md) | Created |
| E020 | ADC Single Conversion | [embedded_specs/E020_adc_single_conversion.md](embedded_specs/E020_adc_single_conversion.md) | Created |
| E021 | ADC DMA Transfer | [embedded_specs/E021_adc_dma_transfer.md](embedded_specs/E021_adc_dma_transfer.md) | Created |
| E022 | Debounce Logic | [embedded_specs/E022_debounce_logic.md](embedded_specs/E022_debounce_logic.md) | Created |
| E023 | Rotary Encoder Decoder | [embedded_specs/E023_rotary_encoder_decoder.md](embedded_specs/E023_rotary_encoder_decoder.md) | Created |
| E024 | Keypad Scanner | [embedded_specs/E024_keypad_scanner.md](embedded_specs/E024_keypad_scanner.md) | Created |
| E025 | LCD/OLED Driver | [embedded_specs/E025_lcd_oled_driver.md](embedded_specs/E025_lcd_oled_driver.md) | Created |
| E026 | Cooperative Scheduler | [embedded_specs/E026_cooperative_scheduler.md](embedded_specs/E026_cooperative_scheduler.md) | Created |
| E027 | Round-Robin Time Slicing | [embedded_specs/E027_round_robin_time_slicing.md](embedded_specs/E027_round_robin_time_slicing.md) | Created |
| E028 | Task Control Block (TCB) | [embedded_specs/E028_task_control_block_tcb.md](embedded_specs/E028_task_control_block_tcb.md) | Created |
| E029 | Context Switch (Assembly) | [embedded_specs/E029_context_switch_assembly.md](embedded_specs/E029_context_switch_assembly.md) | Created |
| E030 | Priority-Based Scheduling | [embedded_specs/E030_priority_based_scheduling.md](embedded_specs/E030_priority_based_scheduling.md) | Created |
| E031 | Idle Task | [embedded_specs/E031_idle_task.md](embedded_specs/E031_idle_task.md) | Created |
| E032 | Semaphore (Binary) | [embedded_specs/E032_semaphore_binary.md](embedded_specs/E032_semaphore_binary.md) | Created |
| E033 | Counting Semaphore | [embedded_specs/E033_counting_semaphore.md](embedded_specs/E033_counting_semaphore.md) | Created |
| E034 | Mutex with Priority Inheritance | [embedded_specs/E034_mutex_with_priority_inheritance.md](embedded_specs/E034_mutex_with_priority_inheritance.md) | Created |
| E035 | Message Queue | [embedded_specs/E035_message_queue.md](embedded_specs/E035_message_queue.md) | Created |
| E036 | Event Flags/Groups | [embedded_specs/E036_event_flags_groups.md](embedded_specs/E036_event_flags_groups.md) | Created |
| E037 | Software Timers | [embedded_specs/E037_software_timers.md](embedded_specs/E037_software_timers.md) | Created |
| E038 | Memory Pool (Fixed Block) | [embedded_specs/E038_memory_pool_fixed_block.md](embedded_specs/E038_memory_pool_fixed_block.md) | Created |
| E039 | Worker/Bottom-Half threads | [embedded_specs/E039_worker_bottom_half_threads.md](embedded_specs/E039_worker_bottom_half_threads.md) | Created |
| E040 | Tickless Idle | [embedded_specs/E040_tickless_idle.md](embedded_specs/E040_tickless_idle.md) | Created |
| E041 | Deadlock Detection | [embedded_specs/E041_deadlock_detection.md](embedded_specs/E041_deadlock_detection.md) | Created |
| E042 | Stack Overflow Check | [embedded_specs/E042_stack_overflow_check.md](embedded_specs/E042_stack_overflow_check.md) | Created |
| E043 | CPU Load Monitor | [embedded_specs/E043_cpu_load_monitor.md](embedded_specs/E043_cpu_load_monitor.md) | Created |
| E044 | Reentrancy Lab (The Gauntlet) | [embedded_specs/E044_reentrancy_lab_the_gauntlet.md](embedded_specs/E044_reentrancy_lab_the_gauntlet.md) | Detailed Draft + Spec |
| E045 | Critical Sections | [embedded_specs/E045_critical_sections.md](embedded_specs/E045_critical_sections.md) | Created |
| E046 | Reader-Writer Lock (RTOS) | [embedded_specs/E046_reader_writer_lock_rtos.md](embedded_specs/E046_reader_writer_lock_rtos.md) | Created |
| E047 | Condition Variables | [embedded_specs/E047_condition_variables.md](embedded_specs/E047_condition_variables.md) | Created |
| E048 | Barrier Synchronization | [embedded_specs/E048_barrier_synchronization.md](embedded_specs/E048_barrier_synchronization.md) | Created |
| E049 | Rate Monotonic Scheduling (RMS) | [embedded_specs/E049_rate_monotonic_scheduling_rms.md](embedded_specs/E049_rate_monotonic_scheduling_rms.md) | Created |
| E050 | Earliest Deadline First (EDF) | [embedded_specs/E050_earliest_deadline_first_edf.md](embedded_specs/E050_earliest_deadline_first_edf.md) | Created |
| E051 | Dual-Core Spinlock | [embedded_specs/E051_dual_core_spinlock.md](embedded_specs/E051_dual_core_spinlock.md) | Created |
| E052 | Inter-Processor Communication (IPC) | [embedded_specs/E052_inter_processor_communication_ipc.md](embedded_specs/E052_inter_processor_communication_ipc.md) | Created |
| E053 | Interrupt Latency Measurement | [embedded_specs/E053_interrupt_latency_measurement.md](embedded_specs/E053_interrupt_latency_measurement.md) | Created |
| E054 | Jitter Analysis | [embedded_specs/E054_jitter_analysis.md](embedded_specs/E054_jitter_analysis.md) | Created |
| E055 | Priority Ceiling Protocol | [embedded_specs/E055_priority_ceiling_protocol.md](embedded_specs/E055_priority_ceiling_protocol.md) | Created |
| E056 | Flash Driver | [embedded_specs/E056_flash_driver.md](embedded_specs/E056_flash_driver.md) | Created |
| E057 | EEPROM Emulation | [embedded_specs/E057_eeprom_emulation.md](embedded_specs/E057_eeprom_emulation.md) | Created |
| E058 | Circular Log/Journal | [embedded_specs/E058_circular_log_journal.md](embedded_specs/E058_circular_log_journal.md) | Created |
| E059 | CRC32 Checksum | [embedded_specs/E059_crc32_checksum.md](embedded_specs/E059_crc32_checksum.md) | Created |
| E060 | LittleFS/FatFS Porting | [embedded_specs/E060_littlefs_fatfs_porting.md](embedded_specs/E060_littlefs_fatfs_porting.md) | Created |
| E061 | Memory Protection Unit (MPU) | [embedded_specs/E061_memory_protection_unit_mpu.md](embedded_specs/E061_memory_protection_unit_mpu.md) | Created |
| E062 | Cache Coherency | [embedded_specs/E062_cache_coherency.md](embedded_specs/E062_cache_coherency.md) | Created |
| E063 | Scatter-Gather DMA | [embedded_specs/E063_scatter_gather_dma.md](embedded_specs/E063_scatter_gather_dma.md) | Created |
| E064 | Heap Fragmentation Analysis | [embedded_specs/E064_heap_fragmentation_analysis.md](embedded_specs/E064_heap_fragmentation_analysis.md) | Created |
| E065 | NAND Bad Block Management | [embedded_specs/E065_nand_bad_block_management.md](embedded_specs/E065_nand_bad_block_management.md) | Created |
| E066 | UART Command Shell (CLI) | [embedded_specs/E066_uart_command_shell_cli.md](embedded_specs/E066_uart_command_shell_cli.md) | Created |
| E067 | XMODEM/YMODEM Protocol | [embedded_specs/E067_xmodem_ymodem_protocol.md](embedded_specs/E067_xmodem_ymodem_protocol.md) | Created |
| E068 | Modbus RTU Slave | [embedded_specs/E068_modbus_rtu_slave.md](embedded_specs/E068_modbus_rtu_slave.md) | Created |
| E069 | CAN Bus Filter | [embedded_specs/E069_can_bus_filter.md](embedded_specs/E069_can_bus_filter.md) | Created |
| E070 | CAN-FD Payload | [embedded_specs/E070_can_fd_payload.md](embedded_specs/E070_can_fd_payload.md) | Created |
| E071 | Ethernet Frame Builder | [embedded_specs/E071_ethernet_frame_builder.md](embedded_specs/E071_ethernet_frame_builder.md) | Created |
| E072 | ARP Request/Reply | [embedded_specs/E072_arp_request_reply.md](embedded_specs/E072_arp_request_reply.md) | Created |
| E073 | IP/ICMP Stack | [embedded_specs/E073_ip_icmp_stack.md](embedded_specs/E073_ip_icmp_stack.md) | Created |
| E074 | UDP Socket primitive | [embedded_specs/E074_udp_socket_primitive.md](embedded_specs/E074_udp_socket_primitive.md) | Created |
| E075 | TCP State Machine (Simplified) | [embedded_specs/E075_tcp_state_machine_simplified.md](embedded_specs/E075_tcp_state_machine_simplified.md) | Created |
| E076 | MQTT Packet Serializer | [embedded_specs/E076_mqtt_packet_serializer.md](embedded_specs/E076_mqtt_packet_serializer.md) | Created |
| E077 | CoAP Message | [embedded_specs/E077_coap_message.md](embedded_specs/E077_coap_message.md) | Created |
| E078 | USB HID Mouse | [embedded_specs/E078_usb_hid_mouse.md](embedded_specs/E078_usb_hid_mouse.md) | Created |
| E079 | USB CDC-ACM | [embedded_specs/E079_usb_cdc_acm.md](embedded_specs/E079_usb_cdc_acm.md) | Created |
| E080 | Bluetooth LE Beacon | [embedded_specs/E080_bluetooth_le_beacon.md](embedded_specs/E080_bluetooth_le_beacon.md) | Created |
| E081 | Simple Bootloader | [embedded_specs/E081_simple_bootloader.md](embedded_specs/E081_simple_bootloader.md) | Created |
| E082 | Firmware Image Header | [embedded_specs/E082_firmware_image_header.md](embedded_specs/E082_firmware_image_header.md) | Created |
| E083 | Memory Remapping/Aliasing | [embedded_specs/E083_memory_remapping_aliasing.md](embedded_specs/E083_memory_remapping_aliasing.md) | Created |
| E084 | Firmware Update (Over-the-Air/UART) | [embedded_specs/E084_firmware_update_over_the_air_uart.md](embedded_specs/E084_firmware_update_over_the_air_uart.md) | Created |
| E085 | Dual-Bank Boot | [embedded_specs/E085_dual_bank_boot.md](embedded_specs/E085_dual_bank_boot.md) | Created |
| E086 | Secure Boot Chain (Concept) | [embedded_specs/E086_secure_boot_chain_concept.md](embedded_specs/E086_secure_boot_chain_concept.md) | Created |
| E087 | Root of Trust | [embedded_specs/E087_root_of_trust.md](embedded_specs/E087_root_of_trust.md) | Created |
| E088 | Encrypted Storage | [embedded_specs/E088_encrypted_storage.md](embedded_specs/E088_encrypted_storage.md) | Created |
| E089 | True Random Number Generator (TRNG) | [embedded_specs/E089_true_random_number_generator_trng.md](embedded_specs/E089_true_random_number_generator_trng.md) | Created |
| E090 | Anti-Tamper | [embedded_specs/E090_anti_tamper.md](embedded_specs/E090_anti_tamper.md) | Created |
| E091 | Fixed-Point Arithmetic | [embedded_specs/E091_fixed_point_arithmetic.md](embedded_specs/E091_fixed_point_arithmetic.md) | Created |
| E092 | PID Controller | [embedded_specs/E092_pid_controller.md](embedded_specs/E092_pid_controller.md) | Created |
| E093 | Digital Filter (FIR/IIR) | [embedded_specs/E093_digital_filter_fir_iir.md](embedded_specs/E093_digital_filter_fir_iir.md) | Created |
| E094 | FFT (Fast Fourier Transform) | [embedded_specs/E094_fft_fast_fourier_transform.md](embedded_specs/E094_fft_fast_fourier_transform.md) | Created |
| E095 | Sensor Fusion (Complementary Filter) | [embedded_specs/E095_sensor_fusion_complementary_filter.md](embedded_specs/E095_sensor_fusion_complementary_filter.md) | Created |
| E096 | Semihosting | [embedded_specs/E096_semihosting.md](embedded_specs/E096_semihosting.md) | Created |
| E097 | Fault Injection Hook | [embedded_specs/E097_fault_injection_hook.md](embedded_specs/E097_fault_injection_hook.md) | Created |
| E098 | Unit Testing (Unity/CppUTest) | [embedded_specs/E098_unit_testing_unity_cpputest.md](embedded_specs/E098_unit_testing_unity_cpputest.md) | Created |
| E099 | Code Coverage (GCOV) | [embedded_specs/E099_code_coverage_gcov.md](embedded_specs/E099_code_coverage_gcov.md) | Created |
| E100 | CI/CD Pipeline Script | [embedded_specs/E100_ci_cd_pipeline_script.md](embedded_specs/E100_ci_cd_pipeline_script.md) | Created |
| E101 | System Trace (SWV/ETM) | [embedded_specs/E101_system_trace_swv_etm.md](embedded_specs/E101_system_trace_swv_etm.md) | Created |
| E102 | PCIe Enumeration & BAR Mapping | [embedded_specs/E102_pcie_enumeration_bar_mapping.md](embedded_specs/E102_pcie_enumeration_bar_mapping.md) | Created |
| E103 | SmartNIC Initialization (Mailbox) | [embedded_specs/E103_smartnic_initialization_mailbox.md](embedded_specs/E103_smartnic_initialization_mailbox.md) | Detailed Draft + Spec |
| E104 | Ring Doorbell Mechanism | [embedded_specs/E104_ring_doorbell_mechanism.md](embedded_specs/E104_ring_doorbell_mechanism.md) | Created |
| E105 | Scatter-Gather Descriptor Chain | [embedded_specs/E105_scatter_gather_descriptor_chain.md](embedded_specs/E105_scatter_gather_descriptor_chain.md) | Created |
| E106 | Interrupt Moderation (NAPI) | [embedded_specs/E106_interrupt_moderation_napi.md](embedded_specs/E106_interrupt_moderation_napi.md) | Created |

## Definition of Done for Each Spec
- Problem objective and system context are clear.
- API/IO contracts are defined.
- Reentrancy/concurrency constraints are explicit (Task/ISR/SoftIRQ/SMP).
- Determinism and timing acceptance criteria are measurable.
- Test plan includes stress + fault cases.

## JD Alignment Extension
- Practical firmware ecosystem and tooling topics are tracked in [embedded_devenv.md](embedded_devenv.md) and [embedded_devenv_index.md](embedded_devenv_index.md).
