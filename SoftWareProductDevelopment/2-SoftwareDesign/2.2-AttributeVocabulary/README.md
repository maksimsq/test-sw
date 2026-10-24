### 2.2-AttributeVocabulary
### Словник атрибутів об’єктів

| Об’єкт | Атрибут | Короткий опис | Тип | Обмеження |
|---|---|---|---|---|
| **Camera** | resolution | Роздільна здатність відеопотоку камери | String | Не може бути пустим, формат (напр., "1920x1080") |
| **Camera** | frameRate | Частота кадрів відеопотоку | Integer | > 0, зазвичай 30 або 60 FPS |
| **ArUcoMarker** | markerId | Унікальний ідентифікатор маркера в сітці | Integer | >= 0 |
| **ArUcoMarker** | size | Фізичний розмір сторони маркера (мм) | Float | > 0.0 |
| **SliderController** | currentValue | Поточне обчислене значення положення повзунка | Float | Від 0.0 до 100.0 |
| **SliderController** | state | Поточний стан трекінгу (активний / втрачений) | String | Значення: "ACTIVE", "LOST" |
| **Calibration** | minValue | Нижня межа робочого діапазону слайдера | Float | >= 0.0 |
| **Calibration** | maxValue | Верхня межа робочого діапазону слайдера | Float | > minValue |
| **Calibration** | calibrationDate | Дата та час проведення калібрування | Date | Формат YYYY-MM-DD |
| **SystemConfig** | configName | Назва активного профілю конфігурації | String | Унікальна назва, не порожня |
| **SystemConfig** | status | Статус готовності системи до роботи | String | Значення: "READY", "UNSYNCHRONIZED" |
