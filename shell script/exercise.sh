#!/bin/bash

# Function to perform the task using switch (case)
perform_task() {
    case $choice in
        1)
            # Compile the .c file
            gcc "$new_file" -o program && echo "Compilation successful."
            ;;
        2)
            # Compile and run the .c file
            gcc "$new_file" -o program && ./program
            ;;
        3)
            # Print the contents of the original file
            echo "Contents of the original file:"
            cat "$original_file"
            ;;
        *)
            # Print the contents of the current directory
            echo "Contents of the current directory:"
            ls
            ;;
    esac
}

# Main script
# Prompt user for the original file
echo "Enter the name of the original file containing C code:"
read original_file

# Check if the original file exists
if [ ! -f "$original_file" ]; then
    echo "Error: File '$original_file' not found."
    exit 1
fi

# Create a new .c file
echo "Enter the name of the new .c file to create (without extension):"
read new_file_name
new_file="${new_file_name}.c"

# Copy contents from the original file to the new file
cp "$original_file" "$new_file"
echo "Contents copied to '$new_file'."

# Ask the user for an action
echo "Choose an option:"
echo "1. Compile the .c file"
echo "2. Compile and run the .c file"
echo "3. Print the contents of the original file"
echo "Any other key: Print the contents of the current directory"
read choice

# Perform the task using if statement
if [ "$choice" -eq 1 ]; then
    gcc "$new_file" -o program && echo "Compilation successful."
elif [ "$choice" -eq 2 ]; then
    gcc "$new_file" -o program && ./program
elif [ "$choice" -eq 3 ]; then
    echo "Contents of the original file:"
    cat "$original_file"
else
    echo "Contents of the current directory:"
    ls
fi

# Perform the task using the switch function
echo "Performing the same task using a switch (case) statement:"
perform_task
