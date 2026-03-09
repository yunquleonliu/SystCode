from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
docs_specs = root / "docs" / "embedded_devenv_specs"
problems_root = root / "problems" / "embedded_devenv"
problems_root.mkdir(parents=True, exist_ok=True)

spec_files = sorted(docs_specs.glob("DEV*.md"))

impl_index_lines = [
    "# Embedded DevEnv Implementations Index",
    "",
    "Auto-generated mapping between DevEnv spec docs and `solution.c` stubs.",
    "",
    "| ID | Spec | Source |",
    "|---|---|---|",
]

for spec in spec_files:
    m = re.match(r"^(DEV\d{3})_(.+)\.md$", spec.name)
    if not m:
        continue

    did = m.group(1)
    slug = m.group(2)
    title = slug.replace("_", " ").title()

    problem_dir = problems_root / f"{did}_{slug}"
    problem_dir.mkdir(parents=True, exist_ok=True)
    solution = problem_dir / "solution.c"

    if not solution.exists():
        solution.write_text(
            f'''#include <stdio.h>\n\n/*\n * {did}: {title}\n *\n * Baseline DevEnv implementation stub.\n * Expand this with platform-specific workflow/code in later phases.\n */\n\nint main(void) {{\n    printf("[{did}] {title} - baseline implementation stub\\n");\n    return 0;\n}}\n''',
            encoding="utf-8",
        )

    source_for_spec = f"../../problems/embedded_devenv/{did}_{slug}/solution.c"
    impl_index_lines.append(
        f"| {did} | [embedded_devenv_specs/{spec.name}](embedded_devenv_specs/{spec.name}) | [problems/embedded_devenv/{did}_{slug}/solution.c](../problems/embedded_devenv/{did}_{slug}/solution.c) |"
    )

    content = spec.read_text(encoding="utf-8")
    add_block = (
        f"\n## Reference Implementation\n"
        f"- C source: [{source_for_spec}]({source_for_spec})\n"
    )

    if "## Reference Implementation" in content:
        content = re.sub(
            r"\n## Reference Implementation\n(?:- .*\n)+",
            add_block,
            content,
            flags=re.MULTILINE,
        )
    else:
        content = content.rstrip() + "\n" + add_block

    spec.write_text(content, encoding="utf-8")

(root / "docs" / "embedded_devenv_impl_index.md").write_text(
    "\n".join(impl_index_lines) + "\n",
    encoding="utf-8",
)

print(f"Generated/verified {len(spec_files)} DevEnv solution.c files and updated docs links.")