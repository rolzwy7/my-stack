DELIMITER //
CREATE FUNCTION PageCount ( value INT )
RETURNS varchar(10) DETERMINISTIC
BEGIN
   DECLARE level varchar(20);
   IF value < 500 THEN
      SET level = 'Low';
   ELSEIF value >= 500 AND value <= 4000 THEN
      SET level = 'Medium';
   ELSE
      SET level = 'High';
   END IF;
   RETURN level;
END;
//
DELIMITER ;
