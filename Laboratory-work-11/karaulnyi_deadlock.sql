-- Транзакція 1
BEGIN;
LOCK TABLE printer IN ROW EXCLUSIVE MODE;
UPDATE printer SET model = 'Deadlock_1' WHERE pr_id = 1;

-- Очікує доступ до другого запису
UPDATE printer SET year = 2025 WHERE pr_id = 2;

COMMIT;

-- Транзакція 2
BEGIN;
LOCK TABLE printer IN ROW EXCLUSIVE MODE;
UPDATE printer SET year = 2024 WHERE pr_id = 2;

-- Очікує доступ до першого запису
UPDATE printer SET model = 'Deadlock_2' WHERE pr_id = 1;

COMMIT;
