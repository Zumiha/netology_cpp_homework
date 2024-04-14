SELECT user_id, first_name, last_name
FROM users
WHERE first_name like '%Вер%' AND last_name like '%хор%'
ORDER BY user_id