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

#include "TrackedValue.h"
#include "Optional.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(TrackedValueTests)
	{
	public:
		TEST_METHOD(TestTrackedValueDefaultConstructor)
		{
			TrackedValue<int> trackedValue;
			Assert::AreEqual(0, trackedValue.Get(), L"TrackedValue should be 0 by default.");
		}

		TEST_METHOD(TestTrackedValueValueConstructor)
		{
			TrackedValue<int> trackedValue(42);
			Assert::AreEqual(42, trackedValue.Get(), L"TrackedValue should be 42.");
		}

		TEST_METHOD(TestTrackedValueCopyConstructor)
		{
			TrackedValue<int> trackedValue1(42);
			TrackedValue<int> trackedValue2(trackedValue1);
			Assert::AreEqual(42, trackedValue2.Get(), L"Copied TrackedValue should be 42.");
			Assert::AreEqual(42, trackedValue1.Get(), L"Original TrackedValue should still be 42 after copy.");
		}

		TEST_METHOD(TestTrackedValueValueAssignment)
		{
			TrackedValue<int> trackedValue;
			trackedValue = 42;
			Assert::AreEqual(42, trackedValue.Get(), L"TrackedValue should be 42 after assignment.");
		}

		TEST_METHOD(TestTrackedValueCopyAssignment)
		{
			TrackedValue<int> trackedValue1(42);
			TrackedValue<int> trackedValue2;
			trackedValue2 = trackedValue1;
			Assert::AreEqual(42, trackedValue2.Get(), L"TrackedValue should be 42 after assignment.");
			Assert::AreEqual(42, trackedValue1.Get(), L"Original TrackedValue should still be 42 after copy assignment.");
		}

		TEST_METHOD(TestSetNoChange)
		{
			TrackedValue<int> trackedValue(42);
			Assert::IsFalse(trackedValue.Set(42), L"Set should return false when the value doesn't change.");
			Assert::AreEqual(42, trackedValue.Get(), L"TrackedValue should still be 42.");
		}

		TEST_METHOD(TestSetChange)
		{
			TrackedValue<int> trackedValue(42);
			Assert::IsTrue(trackedValue.Set(43), L"Set should return true when the value changes.");
			Assert::AreEqual(43, trackedValue.Get(), L"TrackedValue should be 43.");
		}

		TEST_METHOD(TestTrackedOptionalSetFirstValue)
		{
			TrackedValue<Optional<int>> trackedValue;
			Assert::IsTrue(trackedValue.Set(42));
			Assert::AreEqual(42, trackedValue.Get().Value(), L"TrackedValue should be 42.");
		}

		TEST_METHOD(TestTrackedOptionalSetSameValue)
		{
			TrackedValue<Optional<int>> trackedValue(42);
			Assert::IsFalse(trackedValue.Set(42));
			Assert::AreEqual(42, trackedValue.Get().Value(), L"TrackedValue should be 42.");
		}

		TEST_METHOD(TestTrackedOptionalSetDifferentValue)
		{
			TrackedValue<Optional<int>> trackedValue(42);
			Assert::IsTrue(trackedValue.Set(43));
			Assert::AreEqual(43, trackedValue.Get().Value(), L"TrackedValue should be 43.");
		}
	};
}


