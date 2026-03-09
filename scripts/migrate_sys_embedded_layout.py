from pathlib import Path
import shutil
import re

root = Path(__file__).resolve().parents[1]
docs = root / "docs"
problems = root / "problems"

sys_docs = docs / "sys101"
emb_docs = docs / "embedded101"
sys_docs.mkdir(parents=True, exist_ok=True)
emb_docs.mkdir(parents=True, exist_ok=True)

sys_probs = problems / "sys101"
emb_probs = problems / "embedded101"
sys_probs.mkdir(parents=True, exist_ok=True)
emb_probs.mkdir(parents=True, exist_ok=True)

# Move sys101 docs (01..101 markdown docs)
for md in docs.glob("[0-9][0-9]_*.md"):
    shutil.move(str(md), str(sys_docs / md.name))
for md in docs.glob("100_*.md"):
    if md.exists():
        shutil.move(str(md), str(sys_docs / md.name))
for md in docs.glob("101_*.md"):
    if md.exists():
        shutil.move(str(md), str(sys_docs / md.name))

# Move embedded docs assets
embedded_items = [
    "embedded_01_crt0.md",
    "embedded_reentrancy_lab.md",
    "embedded_smartnic_init.md",
    "embedded_software_roadmap.md",
    "embedded_specs_index.md",
    "embedded_problem_template.md",
    "embedded_problem_impl_index.md",
    "embedded_devenv.md",
    "embedded_devenv_index.md",
    "embedded_devenv_impl_index.md",
    "embedded_specs",
    "embedded_devenv_specs",
]
for item in embedded_items:
    src = docs / item
    if src.exists():
        shutil.move(str(src), str(emb_docs / item))

# Move problem folders
for folder in problems.iterdir():
    if not folder.is_dir():
        continue
    name = folder.name
    if re.match(r"^\d{2}_", name) or re.match(r"^100_", name) or re.match(r"^101_", name):
        shutil.move(str(folder), str(sys_probs / name))

for name in ["embedded", "embedded_devenv", "embedded_01_crt0", "embedded_reentrancy_lab", "embedded_smartnic_init"]:
    src = problems / name
    if src.exists():
        shutil.move(str(src), str(emb_probs / name))

# Build root docs portal
(docs / "README.md").write_text(
    """# Q101 Learning Tracks

This site is split into two dedicated tracks.

## Tracks
- [System 101](sys101/README.md)
- [Embedded 101](embedded101/README.md)

## Quick Links
- [System 101 Sidebar](sys101/_sidebar.md)
- [Embedded 101 Sidebar](embedded101/_sidebar.md)
""",
    encoding="utf-8",
)

(docs / "_sidebar.md").write_text(
    """- **Home**
  - [Tracks Portal](README.md)

- **System 101**
  - [System 101 Home](sys101/README.md)

- **Embedded 101**
  - [Embedded 101 Home](embedded101/README.md)
""",
    encoding="utf-8",
)

# System README from previous combined docs README (before embedded section)
old_readme = (root / "README.md").read_text(encoding="utf-8") if (root / "README.md").exists() else ""
if "# Part II: Embedded Software & RTOS 101" in old_readme:
    sys_part = old_readme.split("# Part II: Embedded Software & RTOS 101")[0].rstrip() + "\n"
else:
    sys_part = old_readme

sys_part = sys_part.replace("(docs/", "(")
sys_part = sys_part.replace("(problems/", "(../../problems/sys101/")
(sys_docs / "README.md").write_text(sys_part, encoding="utf-8")

# Build sys sidebar from existing moved sidebar content if available
old_sidebar = (docs / "_sidebar.md").read_text(encoding="utf-8")
# keep a canonical full module sidebar in sys101
sys_sidebar_lines = []
for line in old_sidebar.splitlines():
    if "Embedded Software 101" in line or "Embedded DevEnv" in line:
        break
    sys_sidebar_lines.append(line)
if not sys_sidebar_lines:
    sys_sidebar_lines = ["- [Home](README.md)"]
(sys_docs / "_sidebar.md").write_text("\n".join(sys_sidebar_lines) + "\n", encoding="utf-8")

# Build embedded home/sidebar
(emb_docs / "README.md").write_text(
    """# Embedded 101

Dedicated Embedded track with specs, DevEnv topics, and implementations.

## Core Embedded Docs
- [Roadmap](embedded_software_roadmap.md)
- [Specs Index](embedded_specs_index.md)
- [Implementation Index](embedded_problem_impl_index.md)

## DevEnv Extension
- [DevEnv Overview](embedded_devenv.md)
- [DevEnv Topic Index](embedded_devenv_index.md)
- [DevEnv Implementation Index](embedded_devenv_impl_index.md)
""",
    encoding="utf-8",
)

(emb_docs / "_sidebar.md").write_text(
    """- [Embedded Home](README.md)
- **Core**
  - [Roadmap](embedded_software_roadmap.md)
  - [Specs Index](embedded_specs_index.md)
  - [Impl Index](embedded_problem_impl_index.md)
  - [Problem Template](embedded_problem_template.md)

- **DevEnv**
  - [DevEnv Overview](embedded_devenv.md)
  - [DevEnv Index](embedded_devenv_index.md)
  - [DevEnv Impl Index](embedded_devenv_impl_index.md)
""",
    encoding="utf-8",
)

# Rewrite embedded spec links to new problem folder location
for spec in (emb_docs / "embedded_specs").glob("E*.md"):
    content = spec.read_text(encoding="utf-8")
    content = content.replace("../../problems/embedded/", "../../problems/embedded101/embedded/")
    spec.write_text(content, encoding="utf-8")

for spec in (emb_docs / "embedded_devenv_specs").glob("DEV*.md"):
    content = spec.read_text(encoding="utf-8")
    content = content.replace("../../problems/embedded_devenv/", "../../problems/embedded101/embedded_devenv/")
    spec.write_text(content, encoding="utf-8")

# Rewrite implementation indexes link paths
impl_idx = emb_docs / "embedded_problem_impl_index.md"
if impl_idx.exists():
    content = impl_idx.read_text(encoding="utf-8")
    content = content.replace("../problems/embedded/", "../problems/embedded101/embedded/")
    impl_idx.write_text(content, encoding="utf-8")

dev_impl_idx = emb_docs / "embedded_devenv_impl_index.md"
if dev_impl_idx.exists():
    content = dev_impl_idx.read_text(encoding="utf-8")
    content = content.replace("../problems/embedded_devenv/", "../problems/embedded101/embedded_devenv/")
    dev_impl_idx.write_text(content, encoding="utf-8")

# Update generator scripts to new paths
for script_name in [
    "generate_embedded_specs.py",
    "generate_embedded_devenv_specs.py",
    "generate_embedded_problem_solutions.py",
    "generate_embedded_devenv_solutions.py",
]:
    path = root / "scripts" / script_name
    if not path.exists():
        continue
    content = path.read_text(encoding="utf-8")
    content = content.replace("root / \"docs\"", "root / \"docs\" / \"embedded101\"")
    content = content.replace("root / \"problems\" / \"embedded\"", "root / \"problems\" / \"embedded101\" / \"embedded\"")
    content = content.replace("root / \"problems\" / \"embedded_devenv\"", "root / \"problems\" / \"embedded101\" / \"embedded_devenv\"")
    path.write_text(content, encoding="utf-8")

print("Migration completed: docs/sys101 + docs/embedded101 and problems/sys101 + problems/embedded101")