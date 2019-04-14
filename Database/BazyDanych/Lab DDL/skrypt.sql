USE labbdx;

CREATE TABLE IF NOT EXISTS zesp1(
  `nr_zesp` smallint(6),
  `nazwa_zesp` char(30),
  `nr_prac_kz` int(11),
  `nr_inst` smallint(6),
  primary key(`nr_zesp`)
)ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS prac1(
  `nr_prac` int(11),
  `plec` char (1) not null,
  `data_ur` datetime,
  `nazwisko` char (15),
  `nr_zesp` smallint (6),
  primary key(`nr_prac`)
)ENGINE=InnoDB;

CREATE INDEX `nr_zesp_index` ON `prac1`(`nr_zesp`);
describe zespoly;
describe zesp1;

describe pracownicy;
describe prac1;

INSERT INTO `zesp1`(`nr_zesp`, `nazwa_zesp`, `nr_prac_kz`, `nr_inst`)
SELECT `NR_ZESP`, `NAZWA_ZESP`, `NR_PRAC_KZ`, `NR_INST`
FROM `zespoly`;

INSERT INTO `prac1`(`nr_prac`, `plec`, `data_ur`, `nazwisko`, `nr_zesp`)
SELECT `NR_PRAC`, `PLEC`, `DATA_UR`, `NAZWISKO`, `NR_ZESP`
FROM `pracownicy`;

ALTER TABLE zesp1 ADD CONSTRAINT
  FOREIGN KEY(`nr_prac_kz`)
  REFERENCES `prac1`(`nr_prac`)
  ON DELETE RESTRICT;


ALTER TABLE prac1 ADD CONSTRAINT
  FOREIGN KEY(`nr_zesp`)
  REFERENCES `zesp1`(`nr_zesp`)
  ON DELETE SET NULL;

/* Testy */
/* -- nie da sie
  -- delete from prac1 where nr_prac=37;
*/
/* -- wszedzie ustawilo null w pracownikach gdzie nr_zesp=4
  -- delete from zesp1 where nr_zesp=4;
*/
/* -- duplikat primery key
  insert into `prac1`
    (`nr_prac`, `plec`, `data_ur`, `nazwisko`, `nr_zesp`)
    values (1, 'M', null, null, null);
*/
/* -- plec cannot be null
  insert into `prac1`
    (`nr_prac`, `plec`, `data_ur`, `nazwisko`, `nr_zesp`)
    values (100, null, null, null, null);
*/
/* -- nie da się, domyślnie od update jest restrict
  update zesp1 set nr_prac_kz=99 where nr_prac_kz=1;
*/
/* -- nie da się, domyślnie od update jest restrict
  update prac1 set nr_prac=99 where nr_prac=25;
*/
