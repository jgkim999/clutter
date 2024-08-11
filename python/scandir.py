from os import scandir

# Get entries in the current directory
entries = scandir(".")

# Print filename and size for each entry
for entry in entries:
    if entry.is_file():
        print(f"{entry.name:20s} {entry.stat().st_size:,} bytes")
