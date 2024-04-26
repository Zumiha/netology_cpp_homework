INSERT INTO client (first_name, last_name, email)
VALUES ('Test', 'Tost', 'test@tost'); 

INSERT INTO phones (phone, client_id) 
VALUES ('1773', lastval()); 

INSERT INTO client (first_name, last_name, email)
VALUES ('Joe', 'Cotton', 'joe@test'); 

INSERT INTO phones (phone, client_id) 
VALUES ('5555', lastval()); 

INSERT INTO client (first_name, last_name, email)
VALUES ('Jane', 'Doe', 'jane@gov'); 

INSERT INTO phones (phone, client_id) 
VALUES ('9703', lastval()); 