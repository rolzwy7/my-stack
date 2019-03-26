/* Social Network - Test Script */
DROP DATABASE IF EXISTS db_social_network;
CREATE DATABASE IF NOT EXISTS db_social_network
  CHARACTER SET utf8 COLLATE utf8_general_ci;
USE mydb;

CREATE TABLE IF NOT EXISTS users(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(255) NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `last_logged_in_at` DATETIME,
  `created_at` DATETIME NOT NULL DEFAULT NOW(),
  `visible` BOOLEAN NOT NULL DEFAULT TRUE,
  `banned` BOOLEAN NOT NULL DEFAULT FALSE,
  PRIMARY KEY(`id`),
  UNIQUE KEY(`username`)
);

INSERT INTO users
  (id, username, password)
VALUES
(0, "user_01", "pwd"),
(0, "user_02", "pwd"),
(0, "user_03", "pwd"),
(0, "user_04", "pwd"),
(0, "user_05", "pwd"),
(0, "user_06", "pwd"),
(0, "user_07", "pwd"),
(0, "user_08", "pwd"),
(0, "user_09", "pwd"),
(0, "user_10", "pwd");


/* Print structure */
SHOW TABLES;
DESCRIBE users;
