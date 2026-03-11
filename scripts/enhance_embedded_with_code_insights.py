from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
EMB_SPECS_DIR = ROOT / "docs" / "embedded101" / "embedded_specs"
EMB_PROBLEMS_DIR = ROOT / "problems" / "embedded101"


def extract_key_functions(c_code: str) -> list:
    """Extract function signatures and key patterns from C code."""
    lines = c_code.split('\n')
    functions = []
    in_comment = False
    for i, line in enumerate(lines):
        if '/*' in line:
            in_comment = True
        if '*/' in line:
            in_comment = False
            continue
        if in_comment:
            continue
        # Extract function definitions (simple heuristic)
        if re.match(r'^\s*(static\s+)?[a-zA-Z_][\w\s\*]+\([^)]*\)\s*\{', line):
            # Get context: previous line (if comment) + this line
            func_sig = line.strip()
            if i > 0 and lines[i-1].strip().startswith('//'):
                comment = lines[i-1].strip()
                functions.append((comment, func_sig))
            else:
                functions.append(("", func_sig))
    return functions


def extract_test_logic(c_code: str) -> str:
    """Extract main function test logic."""
    # Find the main function body
    match = re.search(r'int\s+main\s*\([^)]*\)\s*\{(.*?)\n\}', c_code, re.DOTALL)
    if match:
        body = match.group(1)
        # Clean up and extract key lines
        lines = body.split('\n')
        key_lines = []
        for line in lines:
            stripped = line.strip()
            if stripped and not stripped.startswith('//'):
                # Filter out variable declarations, keep key logic
                if any(kw in stripped for kw in ['=', 'ok', 'printf', 'for', 'if', 'return']):
                    key_lines.append(stripped)
        return '\n'.join(key_lines[:10])  # First 10 key lines
    return ""


def get_code_snippet_summary(solution_file: Path) -> str:
    """Generate a summary of the code at a high level."""
    if not solution_file.exists():
        return ""
    
    code = solution_file.read_text(encoding='utf-8')
    
    # Extract includes
    includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', code)
    
    # Extract key functions
    functions = extract_key_functions(code)
    
    # Extract main logic
    main_logic = extract_test_logic(code)
    
    # Build summary
    summary = "### Code Structure\n\n"
    
    if includes:
        summary += f"**Dependencies**: {', '.join(set(includes))}\n\n"
    
    if functions:
        summary += "**Key Functions**:\n"
        for comment, sig in functions[:5]:  # Top 5 functions
            if comment:
                summary += f"- {comment}\n  ```c\n  {sig}\n  ```\n"
            else:
                summary += f"- ```c\n  {sig}\n  ```\n"
    
    if main_logic:
        summary += f"\n**Test Logic**:\n```c\n{main_logic}\n```\n"
    
    return summary


def enhance_spec_with_code_insights(spec_file: Path) -> bool:
    """Add code insights section to a spec file."""
    spec_text = spec_file.read_text(encoding='utf-8')
    
    # Check if already has implementation overview
    if "## Implementation Overview" in spec_text or "## Code Insights" in spec_text:
        return False
    
    # Extract E number from filename
    match = re.match(r'E(\d+)', spec_file.name)
    if not match:
        return False
    
    e_num = match.group(1)
    
    # Find corresponding problem folder
    # E001 -> E001_*, E005 -> E005_*, etc.
    problem_folders = list(EMB_PROBLEMS_DIR.glob(f'E{e_num:0>3}_*'))
    if not problem_folders:
        problem_folders = list(EMB_PROBLEMS_DIR.glob(f'E{e_num}_*'))
    
    if not problem_folders:
        return False
    
    solution_file = problem_folders[0] / "solution.c"
    if not solution_file.exists():
        return False
    
    # Get code insights
    code_summary = get_code_snippet_summary(solution_file)
    if not code_summary:
        return False
    
    # Insert before "## Reference Implementation" or at end
    if "## Reference Implementation" in spec_text:
        insertion_point = spec_text.find("## Reference Implementation")
        reference_section = spec_text[insertion_point:]
        spec_text = spec_text[:insertion_point]
    else:
        reference_section = ""
    
    # Build implementation overview section
    overview_section = f"""## Implementation Overview

{code_summary}

"""
    
    # Append overview and reference
    new_spec = spec_text + overview_section + reference_section
    
    # Update reference link to be relative markdown-friendly
    # From: https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/.../solution.c
    # To: [../../problems/embedded101/.../solution.c](../../problems/embedded101/.../solution.c)
    # Keep it as-is for now, or convert to relative
    
    spec_file.write_text(new_spec, encoding='utf-8')
    return True


def main():
    specs = sorted(EMB_SPECS_DIR.glob('E*.md'))
    enhanced = 0
    
    for spec_file in specs:
        if enhance_spec_with_code_insights(spec_file):
            enhanced += 1
            print(f"Enhanced: {spec_file.name}")
    
    print(f"\nTotal enhanced: {enhanced}/{len(specs)}")


if __name__ == "__main__":
    main()
