import sqlite3

class Sqlite3():
    _DEBUG = False
    link, cursor = None, None

    def __init__(self):
        self.version        = sqlite3.version
        self.sqlite_version = sqlite3.sqlite_version

    def __str__(self, debug=False):
        self._DEBUG = debug
        ret = """
        Module version: {version}
        SQLite library: {sqlite_version}
        """.format(
            version = self.version,
            sqlite_version = self.sqlite_version
        )
        return ret

    def sql(self, sql, commit=False):
        try:
            result = self.cursor.execute(sql)
        except sqlite3.OperationalError as e:
            if self._DEBUG: print("[sql] OperationalError:", e);
            return False
        if commit: self.link.commit()
        return self.cursor

    def table_exists(self, table_name):
        sql = "select * from {table_name};".format(table_name=table_name)
        try:
            self.cursor.execute(sql)
            return True
        except Exception as e:
            if self._DEBUG: print("table_exists - supressed error");
            return False

    @staticmethod
    def connect(database_path=None, uri=False, timeout=5):
        if not database_path: database_path = ":memory:";
        if not Sqlite3.link:
            print("[*] Connected to database:", database_path)
            Sqlite3.link = sqlite3.connect(database_path, uri=uri, timeout=timeout)
            Sqlite3.cursor = Sqlite3.link.cursor()
