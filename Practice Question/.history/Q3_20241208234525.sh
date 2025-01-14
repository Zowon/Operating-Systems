



#!/bin/bash

# Prompt user for the results directory
read -p "Enter the directory name for competition results: " results_dir

# Check if the directory exists; if not, create it
if [ ! -d "$results_dir" ]; then
    echo "Directory does not exist. Creating $results_dir..."
    mkdir -p "$results_dir"
fi

# Create subdirectories
mkdir -p "$results_dir/Winners"
mkdir -p "$results_dir/Participants"
mkdir -p "$results_dir/Disqualified"

# Ask for the number of result files
read -p "How many result files do you want to create? " num_files

# Generate result files with random scores
for ((i = 1; i <= num_files; i++)); do
    score=$((RANDOM % 101)) # Generate random score between 0-100
    file_name="result_$i.txt"
    echo "Score: $score" > "$results_dir/$file_name"
    
    # Sort the files based on score
    if [ $score -gt 90 ]; then
        mv "$results_dir/$file_name" "$results_dir/Winners/"
    elif [ $score -ge 50 ]; then
        mv "$results_dir/$file_name" "$results_dir/Participants/"
    else
        mv "$results_dir/$file_name" "$results_dir/Disqualified/"
    fi
done

# Display a summary
echo "Results sorted:"
echo "Winners: $(ls -1 $results_dir/Winners | wc -l)"
echo "Participants: $(ls -1 $results_dir/Participants | wc -l)"
echo "Disqualified: $(ls -1 $results_dir/Disqualified | wc -l)"
