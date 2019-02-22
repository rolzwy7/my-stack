/* users table - create example */
CREATE TABLE users(
  id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  username VARCHAR(255) NOT NULL UNIQUE,
  password VARCHAR(255) NOT NULL,
  PRIMARY KEY(id)
);

/* users table - drop example */
DROP TABLE users;

/* users table - insert example */
INSERT INTO users VALUES(0, "user01", "pwd01");

/*** DATABASE ***/
/* Create */
CREATE DATABASE mydatabase;
CREATE DATABASE mydatabase CHARACTER SET utf8 COLLATE utf8_polish_ci;
/*
utf8_general_ci
*/

/* Show */
SHOW DATABASES;
SHOW TABLES;

/* Drop */
DROP DATABASE database;

/*** DATABASE ***/
/* GET */
SELECT * FROM table;

/* DELETE */
/* PUT */
/* POST */
