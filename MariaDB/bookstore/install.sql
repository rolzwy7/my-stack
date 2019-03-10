/*** Bookstore - example ***/

DROP DATABASE IF EXISTS db_bookstore;
CREATE DATABASE IF NOT EXISTS db_bookstore
  CHARACTER SET utf8 COLLATE utf8_general_ci;
USE db_bookstore;

/* Author */
CREATE TABLE author(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `first_name` VARCHAR(64) NOT NULL,
  `second_name` VARCHAR(64),
  `last_name` VARCHAR(64) NOT NULL,
  PRIMARY KEY(`id`)
);

/* ISBN */
CREATE TABLE isbn(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `isbn` VARCHAR(64) NOT NULL,
  PRIMARY KEY(`id`)
);

/* Book */
CREATE TABLE book(
  `id` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(64) NOT NULL,
  `author_id` INT UNSIGNED NOT NULL,
  `isbn_id` INT UNSIGNED,
  PRIMARY KEY(`id`),
  INDEX(`author_id`),
  FOREIGN KEY (`author_id`) REFERENCES `author` (`id`)
    ON DELETE CASCADE ON UPDATE RESTRICT,
  INDEX(`isbn_id`),
  FOREIGN KEY (`isbn_id`) REFERENCES `isbn` (`id`)
    ON DELETE CASCADE ON UPDATE RESTRICT
);


/*** Populating rows ***/
INSERT INTO isbn
  (`id`, `isbn`)
VALUES
  (0, '978-3-16-871590-0'),
  (0, '878-4-76-298451-5'),
  (0, '778-3-17-458410-1');

INSERT INTO author
  (`id`, `first_name`, `second_name`, `last_name`)
VALUES
  (0, 'Stephen', '', 'King'),
  (0, 'Edgar', 'Alan', 'Poe');

INSERT INTO book
  (`id`, `title`, `author_id`, `isbn_id`)
VALUES
  (0, 'Pet Semetary', 1, 2),
  (0, 'The City in the Sea', 2, NULL);

/*** Queries ***/
SELECT * FROM author;
SELECT * FROM book;
SELECT * FROM isbn;

SELECT 'INNER JOIN' as 'msg';
SELECT book.title, author.first_name, author.second_name, author.last_name, isbn.isbn FROM ((book
  INNER JOIN author ON author.id = book.author_id)
  INNER JOIN isbn ON isbn.id = book.isbn_id);

SELECT 'LEFT JOIN' as 'msg';
SELECT book.title, author.first_name, author.second_name, author.last_name, isbn.isbn FROM ((book
  INNER JOIN author ON author.id = book.author_id)
  LEFT JOIN isbn ON isbn.id = book.isbn_id);

SELECT 'RIGHT JOIN' as 'msg';
SELECT book.title, author.first_name, author.second_name, author.last_name, isbn.isbn FROM ((book
  INNER JOIN author ON author.id = book.author_id)
  RIGHT JOIN isbn ON isbn.id = book.isbn_id);
