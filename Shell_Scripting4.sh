//calculation
#!/bin/bash
echo "Enter first number:"
read a
echo "Enter second number:"
read b
echo "Enter operator (+ - * /):"
read op

case $op in
  +) res=$((a + b));;
  -) res=$((a - b));;
  \*) res=$((a * b));;
  /) res=$((a / b));;
  *) echo "Invalid operator"; exit 1;;
esac
echo "Result: $res"
