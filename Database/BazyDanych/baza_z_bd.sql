DROP DATABASE IF EXISTS bazy_danych;
CREATE DATABASE IF NOT EXISTS bazy_danych CHARACTER SET utf8 COLLATE utf8_polish_ci;
USE bazy_danych;

CREATE TABLE IF NOT EXISTS zespoly(
  `nrz` int not null,
  `nazwa` varchar(64),
  `kierownik` int not null);
CREATE TABLE IF NOT EXISTS pracownicy(
  `nrp` int not null,
  `nazwisko` varchar(64),
  `adres` varchar(64),
  `nrz` int not null);
CREATE TABLE IF NOT EXISTS tematy(
  `nrt` int not null,
  `nazwa` varchar(64),
  `kierownik` int not null);
CREATE TABLE IF NOT EXISTS wyplaty(
  `nrp` int not null,
  `nrt` int not null,
  `kwota` int not null);

INSERT INTO zespoly VALUES
  (1, "Zespol Analiz", 2),
  (2, "Zespol Wdrozen", 1);
INSERT INTO pracownicy VALUES
  (1, "Jan Lipowski", "Ruda Slaska, ul. Teatralna 7", 2),
  (2, "Adam Grabski", "Zabrze, ul. Wolnosci 333", 1),
  (3, "Jakub Jaworek", "Gliwice, ul. Zwyciestwa 44", 1);
INSERT INTO tematy VALUES
  (1, "Projekt zasilacza", 2),
  (2, "Projekt przetwornika", 1),
  (3, "Projekt reaktora", 2);
INSERT INTO wyplaty VALUES
  (2, 2, 300),
  (3, 3, 150),
  (1, 1, 150),
  (3, 2, 200),
  (1, 3, 200);

select * from zespoly; select * from pracownicy; select * from tematy; select * from wyplaty;

select 'Przykład: wyszukać nazwy zespołów, których pracownicy otrzymali wypłaty w ramach tematu o nazwie "Projekt przetwornika"' as '';

select nazwa from zespoly where nrz in (
  select nrz from pracownicy where nrp in (
    select nrp from wyplaty where nrt in (
      select nrt from tematy where nazwa = 'Projekt przetwornika'
    )
  )
);
