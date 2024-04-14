SELECT advertising_id, amount, created_at, status
FROM advertising
--WHERE  status = 'Активно' AND (created_at BETWEEN '2022-01-01' AND '2023-01-01') 
where extract(year from created_at) = 2022 and status = 'Активно' 
ORDER BY amount DESC
LIMIT 5