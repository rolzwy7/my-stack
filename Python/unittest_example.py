import unittest
#https://docs.python.org/3/library/unittest.html

class TestCase_01(unittest.TestCase):

    def setUp(self):
        print("Set up: TestCase_01")

    def tearDown(self):
        print("Tear down: TestCase_02")

    # def test_(self):
    def test_is_array(self):
        a = [1,2,3]
        self.assertIsInstance(a, list)

class TestCase_02(unittest.TestCase):

    def setUp(self):
        print("Set up: TestCase_02")

    def tearDown(self):
        print("Tear down: TestCase_02")

    @unittest.skipIf(5 == 5, "Skipped because: 5==5")
    def test_is_in(self):
        a = [1, 2, 3, 77, 5, 1]
        self.assertIn(77, a)

class TestCase_03(unittest.TestCase):

    def setUp(self):
        print("Set up: TestCase_03")

    def tearDown(self):
        print("Tear down: TestCase_03")

    def test_assert_false(self):
        a, b = 5, 4
        self.assertFalse(b == a)

class TestCase_04(unittest.TestCase):

    def setUp(self):
        print("Set up: TestCase_04")

    def tearDown(self):
        print("Tear down: TestCase_04")

    def test_iter_assert_equal(self):
        for i in range(6):
            with self.subTest(i=i):
                self.assertEqual(i % 2, 0, "Iterator: %s" % i)


if __name__ == "__main__":
    unittest.main()
