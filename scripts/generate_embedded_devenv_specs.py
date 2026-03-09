from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
docs = root / "docs" / "embedded101"
out_dir = docs / "embedded_devenv_specs"
out_dir.mkdir(parents=True, exist_ok=True)

topics = [
    ("DEV001", "U-Boot Board Porting (ARM/Power)", "Port and configure U-Boot for a target board, including DDR init hooks, device tree handoff, and boot command flow."),
    ("DEV002", "UEFI Firmware Driver Basics (Intel)", "Create a minimal UEFI driver/application and validate PEI/DXE phase interactions and protocol discovery."),
    ("DEV003", "Slim Bootloader Integration (Intel)", "Integrate a board package with SBL stages and verify silicon init, payload handoff, and boot profile config."),
    ("DEV004", "Board Bring-up from Datasheet/Schematic", "Read IC datasheets, register maps, and board schematics to build a power-on bring-up checklist and validation plan."),
    ("DEV005", "MDIO + Ethernet PHY Bring-up", "Implement MDIO transactions to configure PHY, check link negotiation, and troubleshoot link-up issues."),
    ("DEV006", "TPM 2.0 Measured Boot Basics", "Capture boot measurements and extend PCR values with a basic measured boot flow and attestation notes."),
    ("DEV007", "NVMe Host Initialization", "Initialize an NVMe controller over PCIe, create admin queues, and run identify/read command sequence."),
    ("DEV008", "SATA AHCI Host Initialization", "Bring up AHCI controller, enumerate ports, and execute IDENTIFY command path."),
    ("DEV009", "eMMC Boot + Block I/O", "Initialize eMMC in boot mode, configure bus width/timing, and implement block read/write test path."),
    ("DEV010", "VxWorks BSP + RTOS Mapping", "Map tasks/ISRs/timers/memory model into VxWorks primitives and produce a BSP adaptation checklist."),
    ("DEV011", "Linux Driver + Device Tree", "Create a Linux platform/PCIe driver skeleton and bind resources from Device Tree/ACPI definitions."),
    ("DEV012", "Windows Driver Architecture (KMDF)", "Build a minimal KMDF driver and map I/O request lifecycle, PnP/power callbacks, and debug workflow."),
    ("DEV013", "Hardware Debug Tooling Lab", "Use oscilloscope, logic analyzer, and DMM workflows to diagnose timing/signal/power issues in driver bring-up."),
    ("DEV014", "Portable & Supportable Firmware Code", "Apply coding standards, abstraction boundaries, and static analysis to improve portability and long-term supportability."),
    ("DEV015", "Git/JIRA Defect & Regression Workflow", "Define branch, review, issue triage, and regression policy for maintaining and enhancing existing embedded software."),
]

index_lines = [
    "# Embedded DevEnv Track (JD Alignment)",
    "",
    "This track closes practical hiring-profile gaps (boot ecosystems, OS-specific workflows, HW debug, and engineering process).",
    "",
    "## Topics",
    "| ID | Topic | Spec |",
    "|---|---|---|",
]

for tid, title, objective in topics:
    slug = re.sub(r"[^a-z0-9]+", "_", title.lower()).strip("_")
    file_name = f"{tid}_{slug}.md"
    file_path = out_dir / file_name
    rel = f"embedded_devenv_specs/{file_name}"
    content = f"""# {tid}: {title}

## Objective
- {objective}

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
"""
    file_path.write_text(content, encoding="utf-8")
    index_lines.append(f"| {tid} | {title} | [{rel}]({rel}) |")

(docs / "embedded_devenv_index.md").write_text("\n".join(index_lines) + "\n", encoding="utf-8")

overview = [
    "# Embedded DevEnv",
    "",
    "A focused track to cover practical firmware ecosystems, platform-specific development, hardware debug, and team process expectations from embedded product roles.",
    "",
    "- Overview index: [embedded_devenv_index.md](embedded_devenv_index.md)",
    "- Existing Embedded roadmap: [embedded_software_roadmap.md](embedded_software_roadmap.md)",
]

(docs / "embedded_devenv.md").write_text("\n".join(overview) + "\n", encoding="utf-8")

print(f"Generated {len(topics)} Embedded DevEnv topics")