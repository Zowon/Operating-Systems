#!/bin/bash

# Ask the user to enter the name of a directory
echo "Enter the name of the directory:"
read dirname

# Check if the directory exists; if not, create it
if [ ! -d "$dirname" ]; then
    mkdir "$dirname"
    echo "Directory '$dirname' created."
else
    echo "Directory '$dirname' already exists."
fi

# Create subdirectories
mkdir -p "$dirname/Images" "$dirname/Documents" "$dirname/Others"

# Ask for the number of files to generate for each subdirectory
for subdir in "Images" "Documents" "Others"; do
    echo "Enter the number of files to generate for $subdir:"
    read num_files

    # Generate empty files with random names
    for ((i=1; i<=num_files; i++)); do
        filename=$(mktemp -u "$dirname/$subdir/fileXXXXXX.txt")
        touch "$filename"
    done
done

# Display a summary of created directories and files
echo "Summary of created directories and files:"
tree "$dirname"