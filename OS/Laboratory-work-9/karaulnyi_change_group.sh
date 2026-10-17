#!/bin/bash

# 1. Введення назви поточної групи
read -p "Введіть назву поточної групи: " OLD_GROUP
read -p "Введіть нову назву групи: " NEW_GROUP

# 2. Перевірка, чи існує стара група
if ! grep -q "^$OLD_GROUP:" /etc/group; then
    echo "Помилка! Група '$OLD_GROUP' не існує!"
    exit 1
fi

# 3. Перевірка, чи вже існує нова група
if grep -q "^$NEW_GROUP:" /etc/group; then
    echo "Помилка! Група '$NEW_GROUP' вже існує!"
    exit 1
fi

# 4. Перевірка обмежень
if [ ${#NEW_GROUP} -gt 16 ]; then
    echo "Помилка! Назва групи перевищує 16 символів!"
    exit 1
fi

if echo "$NEW_GROUP" | grep -q '[0-9]\{14,\}'; then
    echo "Помилка! Назва містить більше ніж 13 цифр підряд!"
    exit 1
fi

# 5. Зміна назви групи
echo "Змінюємо назву групи."
sudo groupmod "$OLD_GROUP" -n "$NEW_GROUP"
echo "Групу '$OLD_GROUP' перейменовано на '$NEW_GROUP'!"
