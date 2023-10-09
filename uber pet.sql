CREATE TABLE IF NOT EXISTS users (
        username VARCHAR(255) PRIMARY KEY,
        password VARCHAR(255) NOT NULL
);


INSERT INTO users (username, password) VALUES ('admin', 'admin');

SELECT * FROM users;

DELETE FROM users WHERE username = 'admin';

UPDATE users
SET username = 'admin2', password = 'admin2' 
WHERE username = 'admin'


CREATE TABLE IF NOT EXISTS drivers (
	id serial not null primary key,
    name VARCHAR(255) NOT NULL,
	des_cnh varchar(10) NOT NULL,
	des_marital_status varchar(255) NOT NULL,
	des_criminal_recors TEXT,
	des_address varchar(255) NOT NULL,
	des_license_plate varchar(255) NOT NULL,
	phone1 varchar(11) NOT NULL,
	phone2 varchar(11),
	transport_id INT,
    FOREIGN KEY (transport_id) REFERENCES transports(id)
);

INSERT INTO drivers (name, des_cnh, des_marital_status, des_criminal_recors, des_address, des_license_plate, phone1, phone2)
VALUES ('Fulano', '0000000000', 'solteiro', 'Nada', 'Av. Principal','abc123', '47991385666', '47991255214');

SELECT * FROM drivers;

DELETE FROM drivers WHERE id = 1;

UPDATE drivers
SET name = 'Siclano'
WHERE id = 1;


CREATE TABLE IF NOT EXISTS clients (
	id serial not null primary key,
	des_name varchar(255) NOT NULL,
	phone1 varchar(11) NOT NULL,
	phone2 varchar(11)
)

INSERT INTO clients (des_name, phone1, phone2) VALUES ('client name', '47999998888', '47999998888');

UPDATE clients
SET des_name = 'Siclana', phone1 = '47999998777', phone2 = '47999998779'
WHERE id = 1;

select * from clients;

DELETE FROM clients WHERE id = 1;

/* TRANSPORTES */

CREATE TABLE IF NOT EXISTS transports (
	id serial not null primary key,
	des_name_pet varchar(255) NOT NULL,
	des_pet_breed varchar(255) NOT NULL,
	weight decimal(6,2) NOT NULL,
	des_payment_method varchar(255) NOT NULL,
	des_origin_adress varchar(255) NOT NULL,
	des_observation text,
	amount DECIMAL(10, 2) NOT NULL
)

INSERT INTO transports
(des_name_pet, des_pet_breed, weight, des_payment_method, des_origin_adress, des_observation, amount) 
VALUES 
('Scooby', 'Cachorro - Labrador', 200, 'PIX', 'Av. Principal, n 5', 'Ele gosta de carinho', 500);

UPDATE transports set des_name_pet = 'Scooby',  des_origin_adress = 'Av. Terceira Avenida n 100'
WHERE id = 2;

DELETE FROM transports WHERE id = 1;

select * from transports;