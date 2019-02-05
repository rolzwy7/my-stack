class TestClass():

    def __init__(self):
        self.list_values = list(map(lambda x: "iter element: %s" % x, [1,2,3,4,5]))
        self.dict_values = {}

    def __iter__(self):
        return iter(self.list_values)

    def __reversed__(self):
        return reversed(self.list_values)

    def __setitem__(self, key, value):
        self.dict_values[key] = value

    def __getitem__(self, key):
        return self.dict_values[key]

    def __delitem__(self, key):
        print("[*] Item removed from dict_values")
        del self.dict_values[key]

    def __call__(self, a, b, c):
        print("Calling:", a, b, c)

    def __str__(self):
        return "[__str__]"

    def __format__(self, format_spec):
        return str(self)

test_object = TestClass()

print("__iter__ example")
for _ in test_object:
    print(_)
print("")


print("__reversed__ example")
for _ in reversed(test_object):
    print(_)
print("")


print("__setitem__ example")
test_object["key01"] = "value01"
print("")

print("__getitem__ example")
print(test_object["key01"])
print("")

print("__delitem__ example")
del test_object["key01"]
print("")

test_object(1,2,3)

print("__format__ + __str__ example: {a}".format(a=test_object))
