#!/bin/bash

# Створюємо тимчасовий файл, до якого будемо створювати жорсткі посилання
touch source_file.txt

# Генерація 42 (30+n, де n=12) жорстких зв’язків
for ((i=1; i<=42; i++)); do
    random_number=$RANDOM
    ln source_file.txt hlink_$random_number
done

echo "Створено 42 (30+n, де n=12) жорсткі зв’язки на файл source_file.txt"
