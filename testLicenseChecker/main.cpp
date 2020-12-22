#include <UnitTest++/UnitTest++.h>
#include <../LicenseChecker/LicenseChecker.cpp>

SUITE(LicenseCheckerOne)
{
	TEST(TrueSerialNumbers) {
		LicenseChecker ch("1", "ABCD12345");
		CHECK(true);
	}
	TEST(SerialNumbersNull) {
		CHECK_THROW(LicenseChecker ch("0", "ABCD12345"), checker_error);
	}
	TEST(EmptyString) {
		CHECK_THROW(LicenseChecker ch("", "ABCD12345"), checker_error);
	}
	TEST(UppercaseLatin) {
		CHECK_THROW(LicenseChecker ch("ABC", "ABCD12345"), checker_error);
	}
	TEST(LowercaseLatin) {
		CHECK_THROW(LicenseChecker ch("abc", "ABCD12345"), checker_error);
	}
	TEST(UppercaseCyrillic) {
		CHECK_THROW(LicenseChecker ch("АБВ", "ABCD12345"), checker_error);
	}
	TEST(LowercaseCyrillic) {
		CHECK_THROW(LicenseChecker ch("абв", "ABCD12345"), checker_error);
	}
	TEST(NegativeNumber) {
		CHECK_THROW(LicenseChecker ch("-5", "ABCD12345"), checker_error);
	}
	TEST(NotInteger) {
		CHECK_THROW(LicenseChecker ch("0,3", "ABCD12345"), checker_error);
	}
	TEST(Symbols) {
		CHECK_THROW(LicenseChecker ch("!.!.!", "ABCD12345"), checker_error);
	}
}

SUITE(LicenseCheckerTwo)
{
	TEST(TrueLicenseKey) {
		LicenseChecker ch("1", "ABCD12345");
		CHECK(true);
	}
	TEST(LessThan9) {
		CHECK_THROW(LicenseChecker ch("1", "ABCD1"), checker_error);
	}
	TEST(MoreThan9) {
		CHECK_THROW(LicenseChecker ch("1", "ABCD1234567"), checker_error);
	}
	TEST(LowercaseLatin) {
		CHECK_THROW(LicenseChecker ch("1", "abcd12345"), checker_error);
	}
	TEST(LowercaseCyrillic) {
		CHECK_THROW(LicenseChecker ch("1", "абвг12345"), checker_error);
	}
	TEST(UppercaseCyrillic) {
		CHECK_THROW(LicenseChecker ch("1", "АБВГ12345"), checker_error);
	}
	TEST(EmptyString) {
		CHECK_THROW(LicenseChecker ch("1", ""), checker_error);
	}
	TEST(Symbols) {
		CHECK_THROW(LicenseChecker ch("1", "АБВГ!!345"), checker_error);
	}
}

int main(int argc, char **argv) {
	return UnitTest::RunAllTests();
}