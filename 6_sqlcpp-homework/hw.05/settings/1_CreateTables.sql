CREATE TABLE IF NOT EXISTS client (
id SERIAL PRIMARY KEY NOT null,
first_name VARCHAR(60) NOT null,
last_name VARCHAR(60) NOT null, 
email VARCHAR(255) UNIQUE NOT null);

CREATE TABLE IF NOT EXISTS phones (
id SERIAL PRIMARY KEY NOT null, 
phone VARCHAR(60) unique, 
client_id INT NOT NULL REFERENCES client(id));
