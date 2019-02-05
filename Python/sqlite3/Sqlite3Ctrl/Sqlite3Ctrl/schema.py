from .ctrl import Sqlite3
import pprint as pp

class Schema():

    _DEBUG = False

    schema = {
        "primary_key_added" : False,
        "primary_key_for" : "",
        "datatypes" : [
            "INTEGER",
            "REAL",
            "BLOB",
            "TEXT",
            "CHAR",
        ],
        "dtmap" : {
            "INTEGER": int,
            "REAL": float,
            "BLOB": str,
            "TEXT": str,
            "CHAR": str
        },
        "fields" : [],
        "creation_query" : "",
    }

    default_primary_key_name = "id"
    lock_schema = False

    def __str__(self):
        return "[ class Table() ]"

    def __init__(self, name, auto_primary_key=True, autoincrement=False, debug=False):
        self._DEBUG = debug
        self.table_name = name
        if auto_primary_key:
            self.add_field(
                self.default_primary_key_name,
                datatype="INTEGER", null=False,
                primary_key=True,
                autoincrement=autoincrement
                )
            self.schema["primary_key_added"] = True
            self.schema["primary_key_for"] = self.default_primary_key_name

    def lock(self):
        self.lock_schema = True

    def add_field(self, name, datatype="text", lenght=0, null=True, primary_key=False, autoincrement=False):
        if self.lock_schema:
            print("[*] Adding new fields has been locked")
            return False
        assert(isinstance(name, str));
        assert(isinstance(datatype, str));
        assert(isinstance(lenght, int) and lenght >= 0);
        assert(isinstance(null, bool));
        assert(isinstance(primary_key, bool));

        if autoincrement:
            assert( (primary_key == True) and (datatype.upper()=="INTEGER") )
        if datatype.upper() not in self.schema["datatypes"]:
            raise Exception(
                "Invalid datatype: {datatype} for '{name}' field".format(
                    datatype=datatype.lower(),
                    name=name
                )
            )
        if primary_key and self.schema["primary_key_added"]:
            raise Exception(
                "(while adding '{name}' field) Primary key already added for field: {field}".format(
                    name=name,
                    field=self.schema["primary_key_for"]
                )
            )
        if datatype.upper() == "CHAR" and lenght==0:
            raise Exception(
                "(while adding '{name}' field) CHAR datatype needs lenght specified".format(
                    name=name
                )
            )

        field = {}
        field["name"] = name
        field["datatype"] = datatype
        field["null"] = null
        field["primary_key"] = primary_key
        field["lenght"] = lenght
        field["autoincrement"] = autoincrement
        self.schema["fields"].append(field)
        if self._DEBUG:
            print("[+] Added field:", name)
            pp.pprint(field)

    def get_creation_query(self, upper=True):
        query = "CREATE TABLE {table_name}({parsed_fields});"
        tmp_fields = []
        for field in self.schema["fields"]:
            b_name = field["name"]
            if field["lenght"] == 0:
                b_datatype = field["datatype"]
            else:
                b_datatype = "%s(%s)" % (field["datatype"], field["lenght"])
            b_null = "not null" if not field["null"] else ""
            b_pkey = "primary key" if field["primary_key"] else ""
            b_autoinc = "autoincrement" if field["autoincrement"] else ""
            if upper:
                b_datatype = b_datatype.upper()
                b_pkey     = b_pkey.upper()
                b_null     = b_null.upper()
                b_autoinc  = b_autoinc.upper()
            tmp_fields.append(" ".join([b_name, b_datatype, b_pkey, b_autoinc, b_null]))
        if self._DEBUG: pp.pprint(tmp_fields);
        ret = query.format(table_name=self.table_name, parsed_fields=", ".join(tmp_fields))
        if self._DEBUG: pp.pprint(ret);
        return ret

    def get_insert_query(self, **kwargs):
        # Check if all field has been set
        for field in self.schema["fields"]:
            if field["name"] not in kwargs.keys():
                raise Exception("Field '{field}' wasn't provided".format(field=field["name"]))
        # Check types of kwargs
        for field in self.schema["fields"]:
            field_type = self.schema["dtmap"][field["datatype"].upper()]
            kwargs_value = kwargs[field["name"]]
            # Check type
            if not isinstance(kwargs_value, field_type) and not field["autoincrement"]:
                raise Exception("'{field}' isn't an instance of {instance}".format(
                    field=field["name"],
                    instance=field_type
                ))
            if field["primary_key"] and field["autoincrement"]:
                if kwargs[field["name"]] != None:
                    raise Exception(
                        "Autoincrement field {field} needs to be INTEGER".format(
                            field=field["name"]
                        )
                    )
        # Build query
        insert_values = []
        for field in self.schema["fields"]:
            kwargs_value = kwargs[field["name"]]
            if field["autoincrement"]:
                insert_values.append(None)
                continue
            insert_values.append(kwargs_value)


        values = tuple(insert_values)
        query = "INSERT INTO {table_name} VALUES ({insert_values})".format(
            table_name=self.table_name,
            insert_values=", ".join(["?"]*len(insert_values))
        )
        # print("debug:", query)
        # print("debug:", values)

        return query, values
