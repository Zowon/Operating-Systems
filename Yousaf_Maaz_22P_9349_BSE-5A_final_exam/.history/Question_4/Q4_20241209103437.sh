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
    # names=$((RANDOM % 101)) # Generate random value between 0-100
     touch $results_dir/Logs$file_name="result_$i.txt"

    # #Sort the files based on value
    # # if [ $names -gt 90 ]; then
    #     mv "$results_dir/$file_name" "$results_dir/Logs/"
    # # elif [ $names -ge 50 ]; then
    #     mv "$results_dir/$file_name" "$results_dir/Backups/"
    
    #     mv "$results_dir/$file_name" "$results_dir/Reports/"
    # # fi

done

# Display a summary
echo "Summary is here"
echo "logs file : $(ls -1 $results_dir/Logs | wc -l)"
echo "backups file: $(ls -1 $results_dir/Backups | wc -l)"
echo "Reports: $(ls -1 $results_dir/Reports | wc -l)"
