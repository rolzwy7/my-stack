SELECT * FROM <table_name> INTO OUTFILE 'outfile_name.dump';

LOAD DATA INFILE 'outfile_name.dump' INTO TABLE <table_name>;
