-- Social Network - Test Script
DROP DATABASE IF EXISTS db_social_network;
CREATE DATABASE IF NOT EXISTS db_social_network
  CHARACTER SET utf8 COLLATE utf8_general_ci;

USE db_social_network;

CREATE TABLE IF NOT EXISTS users(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(255) NOT NULL,
  `password` VARCHAR(255) NOT NULL,
  `last_logged` DATETIME,
  `created` DATETIME NOT NULL DEFAULT NOW(),
  `visible` BOOLEAN NOT NULL DEFAULT TRUE,
  `banned` BOOLEAN NOT NULL DEFAULT FALSE,
  PRIMARY KEY(`id`),
  UNIQUE KEY(`username`)
) AUTO_INCREMENT=1;
INSERT INTO users
  (`id`, `username`, `password`)
VALUES
(0, "jody17", "pwd"),
(0, "mad_max8", "pwd"),
(0, "Derpylordy1", "pwd"),
(0, "waka522", "pwd"),
(0, "MrM", "pwd"),
(0, "UwU_mongol", "pwd"),
(0, "xCreive", "pwd"),
(0, "Kyl3", "pwd"),
(0, "wuku787", "pwd"),
(0, "W4rl0rd", "pwd");

CREATE TABLE IF NOT EXISTS users_extended(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT UNSIGNED NOT NULL,
  `email` VARCHAR(64) NULL,
  `phone_number` VARCHAR(9) NULL,
  PRIMARY KEY(`id`),
  FOREIGN KEY(`user_id`) REFERENCES `users` (`id`)
    ON DELETE CASCADE ON UPDATE RESTRICT
) AUTO_INCREMENT=1;
INSERT INTO users_extended
  (`id`, `user_id`, `email`, `phone_number`)
VALUES
  (0, 1, "jody17@test.abcdefg", "123456709"),
  (0, 2, "mad_max8@test.abcdefg", NULL),
  (0, 3, "Derpylordy1@test.abcdefg", "123456719"),
  (0, 4, "waka522@test.abcdefg", NULL),
  (0, 5, "MrM@test.abcdefg", NULL),
  (0, 6, "UwU_mongol@test.abcdefg", "123456729"),
  (0, 7, "xCreive@test.abcdefg", NULL),
  (0, 8, "Kyl3@test.abcdefg", NULL),
  (0, 9, "wuku787@test.abcdefg", "123456739"),
  (0, 10, "W4rl0rd@test.abcdefg", NULL);

CREATE TABLE IF NOT EXISTS posts(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INT UNSIGNED NOT NULL,
  `title` VARCHAR(64) NOT NULL,
  `content` BLOB NOT NULL,
  `likes` INT UNSIGNED NOT NULL,
  `created` DATETIME NOT NULL DEFAULT NOW(),
  PRIMARY KEY(`id`),
  FOREIGN KEY(`user_id`) REFERENCES `users` (`id`)
    ON DELETE CASCADE ON UPDATE RESTRICT
);
INSERT INTO posts
  (`id`, `user_id`, `title`, `content`, `likes`)
VALUES
  (0, 1, "Title_1", "Content_1", 5),
  (0, 2, "Title_2", "Content_2", 5),
  (0, 3, "Title_3", "Content_3", 5),
  (0, 3, "Title_4", "Content_4", 5),
  (0, 3, "Title_5", "Content_5", 5),
  (0, 3, "Title_6", "Content_6", 5),
  (0, 7, "Title_7", "Content_7", 5),
  (0, 8, "Title_8", "Content_8", 5),
  (0, 8, "Title_9", "Content_9", 5),
  (0, 2, "Title_10", "Content_10", 5);

-- Print structure
SHOW TABLES;
-- DESCRIBE users;
-- DESCRIBE users_extended;
-- DESCRIBE posts;


------ Example queries
---- Check which user has the most likes
-- SELECT username, SUM(likes) AS sum_likes FROM users JOIN posts ON users.id = posts.user_id GROUP BY username ORDER BY sum_likes DESC LIMIT 1;
