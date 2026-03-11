from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
EMB_SPECS_DIR = ROOT / "docs" / "embedded101" / "embedded_specs"


def update_reference_links(spec_file: Path) -> bool:
    """Update GitHub blob URLs to raw content URLs for better web navigation."""
    spec_text = spec_file.read_text(encoding='utf-8')
    
    # Pattern: https://github.com/yunquleonliu/SystCode/blob/main/problems/embedded101/...
    # Change to: https://raw.githubusercontent.com/yunquleonliu/SystCode/main/problems/embedded101/...
    old_pattern = r'https://github\.com/yunquleonliu/SystCode/blob/main/'
    new_url = 'https://raw.githubusercontent.com/yunquleonliu/SystCode/main/'
    
    new_text = re.sub(old_pattern, new_url, spec_text)
    
    if new_text != spec_text:
        spec_file.write_text(new_text, encoding='utf-8')
        return True
    return False


def main():
    specs = sorted(EMB_SPECS_DIR.glob('E*.md'))
    updated = 0
    
    for spec_file in specs:
        if update_reference_links(spec_file):
            updated += 1
    
    print(f"Updated {updated}/{len(specs)} reference links to raw GitHub URLs")


if __name__ == "__main__":
    main()
