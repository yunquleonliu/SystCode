from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
EMB_DIR = ROOT / "docs" / "embedded101" / "embedded_specs"
SYS_DIR = ROOT / "docs" / "sys101"


def extract_title(text: str) -> str:
    m = re.search(r"^#\s+[^:]+:\s*(.+)$", text, flags=re.M)
    if m:
        return m.group(1).strip()
    m2 = re.search(r"^#\s+Problem\s+\d+:\s*(.+)$", text, flags=re.M)
    if m2:
        return m2.group(1).strip()
    m3 = re.search(r"^#\s+(.+)$", text, flags=re.M)
    return m3.group(1).strip() if m3 else "this topic"


def ensure_embedded_tutoring(path: Path) -> bool:
    text = path.read_text(encoding="utf-8")

    if "## Tutorial Walkthrough" in text:
        return False

    title = extract_title(text)

    block = f"""## Tutorial Walkthrough

### 1) Build a mental model first
- Think of **{title}** as a system behavior problem before it is a coding problem.
- Clarify what is on the critical path: latency, determinism, memory footprint, and failure boundaries.
- Identify where this feature sits in the stack (driver/RTOS/core library/protocol path).

### 2) Implement in learning layers
- Start with a minimal correct version that is easy to reason about.
- Add correctness guards and edge-case handling.
- Add context-safety constraints (Task/ISR/SMP) explicitly.
- Finally optimize hot paths only after behavior is verified.

### 3) Validate like a firmware engineer
- Functional vectors: nominal + edge + invalid input behavior.
- Concurrency vectors: preemption windows, ISR/task overlap, lock usage correctness.
- Timing vectors: worst-case path and jitter-sensitive scenarios.

### 4) Readability and maintainability rules
- Keep API contracts explicit and side effects obvious.
- Avoid hidden global mutable state unless synchronization is documented.
- Prefer compiler intrinsics/standard primitives over fragile low-level tricks when equivalent.

## Common Mistakes
- Mixing correctness logic and optimization logic too early.
- Ignoring undefined behavior or architecture-specific corner cases.
- Assuming single-context execution in code that can run in ISR or SMP environment.
- Not defining observable acceptance criteria (what success looks like in tests/metrics).

## Reader Exercises (Optional)
1. Write one failing test first, then implement the minimum fix.
2. Add one performance-oriented variant and compare behavior + complexity.
3. Add one robustness hardening check and document the tradeoff.

"""

    anchor = "## Reentrancy & Concurrency Notes\n"
    if anchor in text:
        text = text.replace(anchor, block + anchor, 1)
    else:
        text = text.rstrip() + "\n\n" + block

    path.write_text(text, encoding="utf-8")
    return True


def ensure_sys_tutoring(path: Path) -> bool:
    text = path.read_text(encoding="utf-8")

    if "## Why This Problem Matters" in text:
        return False

    title = extract_title(text)

    block = f"""
## Why This Problem Matters
- **{title}** appears in real systems as a building block for reliability, performance, or scalability.
- Mastering this problem improves your ability to reason about low-level tradeoffs under constraints.

## Step-by-Step Tutoring Guide
1. **Model first**: define invariants and expected state transitions before coding.
2. **Minimal baseline**: implement the simplest correct path.
3. **Harden edges**: handle boundary inputs, error propagation, and cleanup paths.
4. **Optimize last**: tune only after tests prove behavior.

## Common Pitfalls
- Treating happy-path correctness as enough.
- Missing ownership/lifetime rules for memory or resources.
- Ignoring concurrent access patterns and race windows.
- Over-optimizing without measurements.

## Debug & Validation Checklist
- Verify invariants after every major operation.
- Add targeted tests for boundary and stress cases.
- Inspect failure paths as carefully as success paths.
- Confirm complexity/latency assumptions with simple measurements.

## Further Practice
1. Implement a second variant with a different tradeoff (speed vs clarity).
2. Add instrumentation counters for visibility.
3. Document one production-style failure mode and mitigation.
"""

    if "## Solution Summary" in text:
        text = text.replace("## Solution Summary", block + "\n## Solution Summary", 1)
    else:
        text = text.rstrip() + "\n" + block

    path.write_text(text, encoding="utf-8")
    return True


def main() -> None:
    emb_changed = 0
    for file in sorted(EMB_DIR.glob("E*.md")):
        if ensure_embedded_tutoring(file):
            emb_changed += 1

    sys_changed = 0
    for file in sorted(SYS_DIR.glob("*.md")):
        if file.name in {"README.md", "_sidebar.md"}:
            continue
        if ensure_sys_tutoring(file):
            sys_changed += 1

    print(f"Embedded updated: {emb_changed}")
    print(f"Sys101 updated: {sys_changed}")


if __name__ == "__main__":
    main()
