#include "pch.h"
#include "CppUnitTest.h"
#include "Optional.h" // Include the header for the Optional class

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(OptionalTests)
    {
    public:
        
        TEST_METHOD(TestOptionalDefaultConstructor)
        {
            Optional<int> opt;
            Assert::IsFalse(opt.HasValue(), L"Optional should not have a value by default.");
        }

        TEST_METHOD(TestOptionalValueConstructor)
        {
            Optional<int> opt(42);
            Assert::IsTrue(opt.HasValue(), L"Optional should have a value.");
            Assert::AreEqual(42, opt.Value(), L"Optional value should be 42.");
        }

        TEST_METHOD(TestOptionalMoveConstructor)
        {
            Optional<int> opt1(42);
            Optional<int> opt2(std::move(opt1));
            Assert::IsTrue(opt2.HasValue(), L"Moved Optional should have a value.");
            Assert::AreEqual(42, opt2.Value(), L"Moved Optional value should be 42.");
            Assert::IsFalse(opt1.HasValue(), L"Original Optional should not have a value after move.");
        }

        TEST_METHOD(TestOptionalCopyConstructor)
        {
            Optional<int> opt1(42);
            Optional<int> opt2(opt1);
            Assert::IsTrue(opt2.HasValue(), L"Copied Optional should have a value.");
            Assert::AreEqual(42, opt2.Value(), L"Copied Optional value should be 42.");
        }

        TEST_METHOD(TestOptionalValueAssignment)
        {
            Optional<int> opt;
            opt = 42;
            Assert::IsTrue(opt.HasValue(), L"Optional should have a value after assignment.");
            Assert::AreEqual(42, opt.Value(), L"Optional value should be 42.");
        }

        TEST_METHOD(TestOptionalCopyAssignment)
        {
            Optional<int> opt(42);
            Optional<int> opt2;
            opt2 = opt;
            Assert::IsTrue(opt2.HasValue(), L"Optional should have a value after assignment.");
            Assert::AreEqual(42, opt2.Value(), L"Optional value should be 42.");
            Assert::IsTrue(opt2.HasValue(), L"Original opitonal should still have value after copy assignment.");
        }

		TEST_METHOD(TestOptionalMoveAssignment)
		{
			Optional<int> opt(42);
			Optional<int> opt2;
			opt2 = std::move(opt);
			Assert::IsTrue(opt2.HasValue(), L"Moved Optional should have a value.");
			Assert::AreEqual(42, opt2.Value(), L"Moved Optional value should be 42.");
			Assert::IsFalse(opt.HasValue(), L"Original Optional should not have a value after move assignment.");
		}

        TEST_METHOD(TestOptionalReset)
        {
            Optional<int> opt(42);
            opt.Reset();
            Assert::IsFalse(opt.HasValue(), L"Optional should not have a value after reset.");
        }

		TEST_METHOD(TestOptionalConversionOperator)
		{
			Optional<int> opt(42);
			int value = opt;
			Assert::AreEqual(42, value, L"Optional value should be 42.");
		}

        TEST_METHOD(TestOptionalValue)
        {
            Optional<int> opt(42);
			Assert::AreEqual(42, opt.Value(), L"Optional value should be 42.");
        }

        TEST_METHOD(TestNarrowingCoercion)
        {
            Optional<int32_t> opt(42);
            Optional<int> opt2 = opt;
            Assert::IsTrue(opt2.HasValue(), L"Optional should have a value after coercion.");
            Assert::AreEqual(42, opt2.Value(), L"Optional value should be 42 after coercion.");
        }

        TEST_METHOD(TestNarrowingCoercionR)
        {
            Optional<int> opt2 = Optional<int32_t>(42);
            Assert::IsTrue(opt2.HasValue(), L"Optional should have a value after coercion.");
            Assert::AreEqual(42, opt2.Value(), L"Optional value should be 42 after coercion.");
        }

        TEST_METHOD(TestWideningCoercionR)
        {
            Optional<int> opt2 = Optional<int>(42);
            Assert::IsTrue(opt2.HasValue(), L"Optional should have a value after coercion.");
            Assert::AreEqual(42, opt2.Value(), L"Optional value should be 42 after coercion.");
        }

    };
}
