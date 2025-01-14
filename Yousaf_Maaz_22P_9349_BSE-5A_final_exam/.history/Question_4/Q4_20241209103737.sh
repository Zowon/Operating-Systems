#!/bin/bash

read -p "Enter the directory name : " results_dir

if [ ! -d "$results_dir" ]; then
    echo "Directory does not exist. Creating $results_dir..."
    mkdir -p "$results_dir"
fi

mkdir -p "$results_dir/Logs"
mkdir -p "$results_dir/Backups"
mkdir -p "$results_dir/Reports"

read -p "How many files do you want to create? " num_files

for ((i = 1; i <= num_files; i++)); do

    touch $results_dir/Logs/="result_$i.txt"
    touch $results_dir/Backups/="result_$i.txt"
    touch $results_dir/Reports/="result_$i.txt"

done

# Display a summary
echo "Summary is here"
echo "logs file : $(ls -1 $results_dir/Logs )"
echo "backups file: $(ls -1 $results_dir/Backups )"
echo "Reports: $(ls -1 $results_dir/Reports | wc -l)"
