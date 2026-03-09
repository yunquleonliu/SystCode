from pathlib import Path

root = Path(__file__).resolve().parents[1]
sys_docs = root / "docs" / "sys101"

module_ranges = [
    ("Module 1: Memory", 1, 5),
    ("Module 2: Concurrency", 6, 10),
    ("Module 3: OS Internals", 11, 15),
    ("Module 4: Networking", 16, 20),
    ("Module 5: Distributed", 21, 25),
    ("Module 6: Advanced OS", 26, 30),
    ("Module 7: Compiler & Runtime", 31, 40),
    ("Module 8: Kernel & Virtualization", 41, 50),
    ("Module 9: Drivers & Hardware", 51, 60),
    ("Module 10: HPC & Optimization", 61, 70),
    ("Module 11: Databases & Storage", 71, 80),
    ("Module 12: Networked Systems", 81, 90),
    ("Module 13: AI Infrastructure", 91, 100),
    ("Module 14: Capstone", 101, 101),
]

files = sorted(sys_docs.glob("*.md"))
index = {}
for file_path in files:
    stem = file_path.stem
    prefix = stem.split("_", 1)[0]
    if prefix.isdigit():
        index[int(prefix)] = file_path.name

lines = ["- [System 101 Home](README.md)", ""]
for title, start, end in module_ranges:
    lines.append(f"- **{title}**")
    for number in range(start, end + 1):
        file_name = index.get(number)
        if file_name:
            lines.append(f"  - [{number:02d} {file_name.replace('.md', '').split('_', 1)[1].replace('_', ' ').title()}]({file_name})")
    lines.append("")

(sys_docs / "_sidebar.md").write_text("\n".join(lines), encoding="utf-8")
print("Generated docs/sys101/_sidebar.md")