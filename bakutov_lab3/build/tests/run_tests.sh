#!/bin/bash

base_name="test"

num_files=20

for ((i = 1; i <= num_files; i++)); do
    input_file="${base_name}${i}.txt"
    echo "Running with input file: $input_file"
    ./../a.out < "$input_file"
done
