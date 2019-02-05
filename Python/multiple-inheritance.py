class A():
    def __init__(self, a):
        self.a = a

class B(A):
    def __init__(self, b, **kwords):
        super(B, self).__init__(**kwords)
        self.b = b

    def meth_B(self):
        print("Method B:", self.b)

class C(A):
    def __init__(self, c, **kwords):
        super(C, self).__init__(**kwords)
        self.c = c

class D(B, C):
    def __init__(self, a, b, c, d):
        super(D, self).__init__(a=a, b=b, c=c)


        if super(D, self).meth_B == self.meth_B:
            print("super(D, self).meth_B == self.meth_B")

        self.d = d

for e in D.__mro__:
    print(e)

obj = D(1,2,3,4)

print(obj.a, obj.b, obj.c, obj.d)
