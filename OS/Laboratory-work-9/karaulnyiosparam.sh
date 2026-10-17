#!/bin/bash

# Перевірка наявності параметрів
if [ $# -lt 1 ]; then
    echo "для команди треба вказати параметр"
    exit 1
fi

PARAM=$1
INFO=$2

# Шлях до файлу з даними про CPU
FILE="/proc/cpuinfo"

# Пошук параметра у файлі
VALUE=$(grep -i "$PARAM" $FILE | head -n 1 | awk -F: '{print $2}' | sed 's/^[ \t]*//')

# Якщо параметр не знайдено
if [ -z "$VALUE" ]; then
    echo "параметр не знайдено"
    exit 1
fi

# Виведення значення параметра
echo "$PARAM: $VALUE"

# Якщо другий параметр — "info", вивести пояснення
if [ "$INFO" == "info" ]; then
    echo "Опис: параметр 'cpu family' показує покоління процесора (архітектурна сім'я CPU)"
fi
