# compare_lines.py

file_a_path = "parseaddr.gen"  # file with lines to check
file_b_path = "test.out"  # file to search in

# Read both files
with open(file_a_path, "r", encoding="utf-8") as f:
    lines_a = [line.strip() for line in f]

with open(file_b_path, "r", encoding="utf-8") as f:
    lines_b = [line.strip() for line in f]

# Turn lines of file B into a set for fast lookup
lines_b_set = set(lines_b)

# Check each line from file A
for line in lines_a:
    if line not in lines_b_set:
        print(f"❌ Missing: {line}")