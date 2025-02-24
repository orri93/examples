import unittest

# https://www.dataquest.io/blog/unit-tests-python/

# >>>python -m unittest -v
# >>>python -m unittest -v tests.test
# >>>python -m unittest -v tests.test.TestCalculations.test_diff

class TestStringMethods(unittest.TestCase):

  def test_upper(self):
    self.assertEqual('foo'.upper(), 'FOO')

  def test_isupper(self):
    self.assertTrue('FOO'.isupper())
    self.assertFalse('Foo'.isupper())

  def test_split(self):
    s = 'hello world'
    self.assertEqual(s.split(), ['hello', 'world'])
    # check that s.split fails when the separator is not a string
    with self.assertRaises(TypeError):
      s.split(2)

if __name__ == '__main__':
  unittest.main()
