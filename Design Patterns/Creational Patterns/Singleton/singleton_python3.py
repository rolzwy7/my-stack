"""
    A way to define class with which object can be initialized only once
"""


class DBConnection():
    __instance = None

    @staticmethod
    def getInstance():
        if DBConnection.__instance:
            return DBConnection.__instance
        else:
            return DBConnection()

    def __init__(self):
        if DBConnection.__instance is None:
            DBConnection.__instance = self
        else:
            raise Exception("DBConnection class is singleton")


instance_1 = DBConnection()
try:
    instance_2 = DBConnection()
except Exception as e:
    print(e)

instance_3 = instance_1.getInstance()

print(instance_1)
print(instance_3)
