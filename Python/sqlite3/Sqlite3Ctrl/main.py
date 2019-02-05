from Sqlite3Ctrl.ctrl import Sqlite3 as DB
from Sqlite3Ctrl.schema import Schema

# Sqlite
DB.connect("ms.db")
db = DB()

table_targets = Schema("targets"  , auto_primary_key=True, autoincrement=True)
table_targets.add_field("name", datatype="text")
table_targets.add_field("surname", datatype="text")
table_targets.add_field("second_name", datatype="text")
table_targets.lock()
if not db.table_exists(table_targets.table_name):
    db.sql(table_targets.get_creation_query(), commit=True)

sql, vals = table_targets.get_insert_query(
    id=None,
    name="John",
    surname="Doe",
    second_name="George"
)
db.cursor.execute(sql, vals)
db.link.commit()
for row in db.sql('SELECT * FROM targets'):
    print(row)
