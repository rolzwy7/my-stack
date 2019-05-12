-- Bartosz Nowakowski IV sem Teleinformatyka
/*
Isolation level	Dirty reads		Lost updates	Non-repeatable reads	Phantoms
Read Uncommitted	may occur		may occur		may occur				may occur
Read Committed		don't occur		may occur		may occur				may occur
Repeatable Read	don't occur		don't occur		don't occur				may occur
Serializable		don't occur		don't occur		don't occur				don't occur

*/

-- SET SESSION TRANSACTION ISOLATION LEVEL 
-- {READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE} 
-- select @@tx_isolation (default: REPEATABLE READ)

/*
	SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED
*/

-- Part 1
begin;
	begin;
	update students set student_name='XX' where student_id=1;
-- (A)
select * from students;
	rollback;
rollback;

-- Part 2
begin;
	begin;
select * from students;
	-- (B)
	update students set student_name='XX2' where student_id=1;
-- (C)
select * from students;
	commit;
-- (D)
select * from students;
rollback; 

-- Part 3
begin;
begin;
select * from students;
-- (E)
select * from students;
-- (F)
update students set student_name='ZZ1' where student_id=1;
-- (G)
update students set student_name='ZZ2' where student_id=1;
rollback;
rollback; 


-- Sprawozdanie:
/*
READ UNCOMMITTED
 - A - Zmiana imienia studenta o id=1 na 'XX'
 		 jest widoczna dla obu klientów. (Dirty read)
 - B - Wyświetlona została lista studentów.
 - C - Zmiana imienia studenta o id=1 na 'XX2'
 		 jest widoczna dla obu klientów. (Dirty read)
 - D - Drugi użytkownik zcommit'ował zmiany.
   	 Pierwszemu użytkownikowi wyświetla się
   	 zmodyfikowany rekod o id=1 i student_name=XX2
 - E -
 - F -
 - G -
READ COMMITTED
 - A - Zmiana imienia studenta o id=1 na 'XX'
 		jest widoczna tylko dla klienta przeprowadzajacego 
 		transakcje.
 - B - Wyświetlona została lista studentów.
 - C - Modyfikacja rekordu nie została odnotowana przez pierwszego użytkownika.
 - D - Po zcommit'owaniu zmiana rekordu id=1 jest widoczna dla pierwszego użytkownika.
 - E -
 - F -
 - G -
REPEATABLE READ
 - A - Zmiana imienia studenta o id=1 na 'XX'
 		jest widoczna tylko dla klienta przeprowadzajacego 
 		transakcje.
 - B -
 - C -
 - D -
 - E -
 - F -
 - G -
SERIALIZABLE
 - A - Zmiana imienia studenta o id=1 na 'XX'
 		jest widoczna tylko dla klienta przeprowadzajacego 
 		transakcje.
 - B -
 - C -
 - D -
 - E -
 - F -
 - G -
*/