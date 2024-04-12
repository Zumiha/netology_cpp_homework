CREATE TABLE IF NOT EXISTS department (
	id serial PRIMARY KEY ,
	department_name varchar(60) NOT null
);

CREATE TABLE IF NOT EXISTS employee (
	id serial PRIMARY KEY ,
	employee_name varchar(60) NOT null,
	department_id int references department(id),
	dephead_id int references employee(id)
);

