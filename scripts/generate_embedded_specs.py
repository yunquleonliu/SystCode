from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
roadmap = root / "docs" / "embedded101" / "embedded_software_roadmap.md"
spec_dir = root / "docs" / "embedded101" / "embedded_specs"
index_file = root / "docs" / "embedded101" / "embedded_specs_index.md"

spec_dir.mkdir(parents=True, exist_ok=True)

lines = roadmap.read_text(encoding="utf-8").splitlines()

def slugify(text: str) -> str:
    return re.sub(r"[^a-z0-9]+", "_", text.lower()).strip("_")

module = ""
entries = []

for line in lines:
    m = re.match(r"^##\s+Module\s+\d+:\s*(.+)$", line.strip())
    if m:
        module = m.group(1).strip()
        continue

    p = re.match(r"^(\d+)\.\s+\*\*(.+?)\*\*:\s*(.+)$", line.strip())
    if not p:
        continue

    num = int(p.group(1))
    title = p.group(2).strip()
    desc = p.group(3).strip()
    sid = f"E{num:03d}"
    slug = slugify(title)
    rel = f"embedded_specs/{sid}_{slug}.md"
    path = spec_dir / f"{sid}_{slug}.md"

    extra = ""
    status = "Created"
    if num == 1:
        extra = "\n## Existing Detailed Draft\n- See [CRT0 detailed problem](../embedded_01_crt0.md).\n"
        status = "Detailed Draft + Spec"
    elif num == 44:
        extra = "\n## Existing Detailed Draft\n- See [Reentrancy Lab detailed problem](../embedded_reentrancy_lab.md).\n"
        status = "Detailed Draft + Spec"
    elif num == 103:
        extra = "\n## Existing Detailed Draft\n- See [SmartNIC Initialization detailed problem](../embedded_smartnic_init.md).\n"
        status = "Detailed Draft + Spec"

    content = f"""# {sid}: {title}

## Objective
- {desc}

## Background
- Module: {module}
- Scope: Embedded systems docs-first specification before implementation.

## Requirements
- Define a clear API contract (inputs, outputs, error codes).
- Define resource constraints (stack, heap, latency, determinism).
- Define platform assumptions (bare-metal / RTOS / SMP if applicable).

## Interfaces
- Input:
- Output:
- Error Handling:

## Reentrancy & Concurrency Notes
- Calling contexts: Task / ISR / SoftIRQ / SMP core (as applicable).
- Shared-state policy: no hidden mutable global state without explicit sync.
- Synchronization strategy: mutex / critical section / spinlock / lock-free (choose and justify).

## Acceptance Criteria
- [ ] Functional behavior matches problem statement.
- [ ] Concurrency safety documented and validated.
- [ ] Determinism/timing constraints measured and reported.

## Suggested Tests
1. Happy path correctness test.
2. Stress/preemption test with concurrent callers.
3. Fault-injection test (timeouts, invalid input, resource exhaustion).
{extra}
## Notes
- Related roadmap item: [embedded_software_roadmap.md](../embedded_software_roadmap.md)
"""

    path.write_text(content, encoding="utf-8")
    entries.append((sid, title, rel, status))

index_lines = [
    "# Embedded Problem Specs Index",
    "",
    "This is the **docs-first** tracker for Embedded Software topics. We complete specs before implementing `solution.c`.",
    "",
    "## Source of Truth",
    "- Full topic list and descriptions: [embedded_software_roadmap.md](embedded_software_roadmap.md)",
    "- Spec template: [embedded_problem_template.md](embedded_problem_template.md)",
    "",
    "## Coverage Matrix (E001-E106)",
    "| ID | Topic | Spec | Status |",
    "|---|---|---|---|",
]

for sid, title, rel, status in entries:
    index_lines.append(f"| {sid} | {title} | [{rel}]({rel}) | {status} |")

index_lines.extend([
    "",
    "## Definition of Done for Each Spec",
    "- Problem objective and system context are clear.",
    "- API/IO contracts are defined.",
    "- Reentrancy/concurrency constraints are explicit (Task/ISR/SoftIRQ/SMP).",
    "- Determinism and timing acceptance criteria are measurable.",
    "- Test plan includes stress + fault cases.",
])

index_file.write_text("\n".join(index_lines) + "\n", encoding="utf-8")

print(f"Generated {len(entries)} embedded spec files in {spec_dir}")