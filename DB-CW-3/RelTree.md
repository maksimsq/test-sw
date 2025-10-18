```mermaid
graph TD
    %% Джерела (таблиці) — оформлені як овали
    Patients((Patients))
    Doctors((Doctors))
    Medical_Records((Medical_Records))
    Medical_Cards((Medical_Cards))

    %% Операції - прямокутники (будемо робити їх з пунктирною лінією і без заливки)
    S1["σ(specialization = 'Терапевт')"]
    S2["σ(record_type = 'Діагноз')"]

    %% З'єднання (по двох зв'язках, в підсумку буде з'єднання трьох таблиць)
    J1["⋈ Doctors.doctor_id = Medical_Records.doctor_id"]
    J2["⋈ Medical_Records.card_id = Medical_Cards.card_id"]
    J3["⋈ Medical_Cards.patient_id = Patients.patient_id"]

    %% Операція проекції (обрати 1 або 2 стовпці однієї таблиці, тут - з таблиці Patients)
    P["π(full_name, birth_date)"]    %% дві колонки з однієї таблиці (Patients)

    %% Потік операцій (приклад: вибірки -> з'єднання трьох таблиць -> проекція)
    Doctors --> S1
    Medical_Records --> S2

    S1 --> J1
    S2 --> J1

    J1 --> J2
    Medical_Cards --> J2

    J2 --> J3
    Patients --> J3

    J3 --> P

    %% Клас для оформлення операцій: пунктирний прямокутник без заливки
    class S1,S2,J1,J2,J3,P op;

    classDef op stroke-dasharray: 5 5, fill:none, stroke:#000, stroke-width:1;
```
