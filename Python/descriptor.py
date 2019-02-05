class TestClass(object):

    def __init__(self, name="Variable", value=11):
        self.name = name
        self.value = value

    def __str__(self):
        return "{} {}".format(self.name, self.value)

    def __get__(self, obj, objtype):
        print("Getting:", self.name, "| type:", objtype)
        return self.value

    def __set__(self, obj, value):
        print("Setting:", self.name, "to", value)
        obj.y = 666
        self.value = value

class MyClass(object):

    x = TestClass("'X' Variable", 21) # need to be class variable

    def test(self):
        self.x

    y = 5

test_obj = MyClass()

print("[*] Get")
print(test_obj.x)

print("\n[*] Set")
test_obj.x = 10

print("\n[*] object can be modified through 'obj' in __set__ and __get__", test_obj.y)
print("y = ", test_obj.y)

print("\n[*] Use in own method")
test_obj.test()
