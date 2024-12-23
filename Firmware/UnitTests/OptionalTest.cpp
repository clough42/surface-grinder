// Copyright (c) 2024 James Clough (Clough42, LLC)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "pch.h"
#include "CppUnitTest.h"
#include "Optional.h" // Include the header for the Optional class

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
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

        TEST_METHOD(TestConvertAssign1)
        {
            Optional<int32_t> opt((int32_t)42);
            int16_t value = opt;
            Assert::AreEqual((int16_t)42, value, L"Optional value should be 42.");
        }

        TEST_METHOD(TestConvertAssign2)
        {
            Optional<int16_t> opt((int16_t)42);
            int32_t value = opt;
            Assert::AreEqual(42, value, L"Optional value should be 42.");
        }

        TEST_METHOD(TestConvertAssign3)
        {
            Optional<int32_t> opt((int32_t)42);
			opt = (int16_t)43;
            Assert::AreEqual(opt.Value(), 43, L"Optional value should be 42.");
        }

        TEST_METHOD(TestConvertAssign4)
        {
            Optional<int16_t> opt((int16_t)42);
            opt = (int32_t)43;
            Assert::AreEqual(opt.Value(), (int16_t)43, L"Optional value should be 42.");
        }

        TEST_METHOD(TestOrValueNotSet)
		{
			Optional<int> opt;
			int value = opt.ValueOr(43);
			Assert::AreEqual(43, value, L"Should return default value when not set");
		}

        TEST_METHOD(TestOrValueSet)
        {
            Optional<int> opt(42);
            int value = opt.ValueOr(43);
            Assert::AreEqual(42, value, L"Should return value when set");
        }

    };
}
