#!/bin/bash

# Part 1: Perform Arithmetic Operations
echo "Enter the first number:"
read num1
echo "Enter the second number:"
read num2

# Addition
sum=$((num1 + num2))
echo "Addition of $num1 and $num2 is: $sum"

# Subtraction
diff=$((num1 - num2))
echo "Subtraction of $num1 and $num2 is: $diff"

# Multiplication
prod=$((num1 * num2))
echo "Multiplication of $num1 and $num2 is: $prod"

# Division (check if the divisor is zero)
if [ $num2 -ne 0 ]; then
    div=$((num1 / num2))
    echo "Division of $num1 by $num2 is: $div"
else
    echo "Division by zero is not allowed."
fi

# Part 2: File Operations
echo "Enter the filename to work with:"
read filename

# Check if the file exists
if [ -e "$filename" ]; then
    echo "File '$filename' exists."
    
    # Ask the user if they want to overwrite or append
    echo "Choose an option:"
    echo "1 - Overwrite the file"
    echo "2 - Append to the file"
    echo "3 - View the current contents of the file"
    read choice

    case $choice in
        1)
            echo "Enter text to overwrite the file:"
            read file_content
            echo "$file_content" > "$filename"
            echo "File has been overwritten."
            ;;
        2)
            echo "Enter text to append to the file:"
            read file_content
            echo "$file_content" >> "$filename"
            echo "Content has been appended to the file."
            ;;
        3)
            echo "Displaying contents of '$filename':"
            cat "$filename"
            ;;
        *)
            echo "Invalid option. Exiting."
            ;;
    esac
else
    echo "File '$filename' does not exist."
fi

