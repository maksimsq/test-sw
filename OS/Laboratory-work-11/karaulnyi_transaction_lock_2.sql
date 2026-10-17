-- Транзакція 1
BEGIN;
LOCK TABLE printer IN EXCLUSIVE MODE;
SELECT * FROM printer WHERE pr_id = 1;
UPDATE printer SET model = 'Model_2PL_1' WHERE pr_id = 1;
SELECT * FROM printer WHERE pr_id = 1;
COMMIT;

-- Транзакція 2
BEGIN;
LOCK TABLE printer IN EXCLUSIVE MODE;
SELECT * FROM printer WHERE pr_id = 1;
UPDATE printer SET model = 'Model_2PL_2' WHERE pr_id = 1;
SELECT * FROM printer WHERE pr_id = 1;
COMMIT;
