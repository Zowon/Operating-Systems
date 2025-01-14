#!/bin/usr
#!/bin/bash
# Question: Write a shell script that performs addition, subtraction, multiplication, division, and remainder based on the first argument.
# Usage: ./com.sh <operation> <num1> <num2>

operation=$1
num1=$2
num2=$3

if [[ "$operation" == "add" ]]; then
  echo "$num1 + $num2 = $((num1 + num2))"
elif [[ "$operation" == "sub" ]]; then
  echo "$num1 - $num2 = $((num1 - num2))"
elif [[ "$operation" == "mul" ]]; then
  echo "$num1 * $num2 = $((num1 * num2))"
elif [[ "$operation" == "div" ]]; then
  echo "$num1 / $num2 = $((num1 / num2))"
elif [[ "$operation" == "rem" ]]; then
  echo "$num1 % $num2 = $((num1 % num2))"
else
  echo "Invalid operation. Use add, sub, mul, div, or rem."
fi

# Simpler Syntax: $((expression))
# I prefer $((expression)) because it's concise, easy to read, and supports all arithmetic operations.