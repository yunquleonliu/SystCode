from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
docs_specs = root / "docs" / "embedded_specs"
problems_root = root / "problems" / "embedded"
problems_root.mkdir(parents=True, exist_ok=True)

spec_files = sorted(docs_specs.glob("E*.md"))

impl_index_lines = [
    "# Embedded Problem Implementations Index",
    "",
    "Auto-generated mapping between embedded spec docs and `solution.c` stubs.",
    "",
    "| ID | Spec | Source |",
    "|---|---|---|",
]

for spec in spec_files:
    m = re.match(r"^(E\d{3})_(.+)\.md$", spec.name)
    if not m:
        continue

    eid = m.group(1)
    slug = m.group(2)
    title = slug.replace("_", " ").title()

    problem_dir = problems_root / f"{eid}_{slug}"
    problem_dir.mkdir(parents=True, exist_ok=True)
    solution = problem_dir / "solution.c"

    if not solution.exists():
        solution.write_text(
            f'''#include <stdio.h>\n\n/*\n * {eid}: {title}\n *\n * This is a baseline reference stub generated from docs-first planning.\n * Expand this file with full algorithm/driver logic in implementation phases.\n */\n\nint main(void) {{\n    printf("[{eid}] {title} - baseline implementation stub\\n");\n    return 0;\n}}\n''',
            encoding="utf-8",
        )

    relative_source_for_spec = f"../../problems/embedded/{eid}_{slug}/solution.c"
    relative_spec_from_docs = f"embedded_specs/{spec.name}"

    impl_index_lines.append(
        f"| {eid} | [{spec.name}]({relative_spec_from_docs}) | [problems/embedded/{eid}_{slug}/solution.c](../problems/embedded/{eid}_{slug}/solution.c) |"
    )

    content = spec.read_text(encoding="utf-8")
    marker = "## Reference Implementation"
    add_block = (
        f"\n## Reference Implementation\n"
        f"- C source: [{relative_source_for_spec}]({relative_source_for_spec})\n"
    )

    if marker in content:
        content = re.sub(
            r"\n## Reference Implementation\n(?:- .*\n)+",
            add_block,
            content,
            flags=re.MULTILINE,
        )
    else:
        content = content.rstrip() + "\n" + add_block

    spec.write_text(content, encoding="utf-8")

(root / "docs" / "embedded_problem_impl_index.md").write_text(
    "\n".join(impl_index_lines) + "\n",
    encoding="utf-8",
)

print(f"Generated/verified {len(spec_files)} embedded solution.c files and updated docs links.")