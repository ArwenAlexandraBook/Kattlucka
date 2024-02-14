import unittest

from catflap import addApprovedCat, processCatChip, isApproved, isFlapOpen

class TestCatFlap(unittest.TestCase):
    def test_add_approved_cat(self):
        addApprovedCat("CAT12345")
        self.assertTrue(isApproved("CAT12345"))

        def test_process_cat_chip(self):
            processCatChip("CAT12345")
            self.assertTrue(isFlapOpen())

if __name__ == '__main__':
    unittest.main()            