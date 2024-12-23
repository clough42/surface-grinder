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

#include "Limiter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utility
{
	TEST_CLASS(LimiterTests)
	{
	public:
		TEST_METHOD(TestForward)
		{
			Limiter<int> limiter(10, 20);
			Assert::AreEqual(10, limiter.Clamp(5), L"5 should be limited to 10.");
			Assert::AreEqual(10, limiter.Clamp(10), L"10 should be within the limits.");
			Assert::AreEqual(15, limiter.Clamp(15), L"15 should be within the limits.");
			Assert::AreEqual(20, limiter.Clamp(20), L"20 should be within the limits.");
			Assert::AreEqual(20, limiter.Clamp(25), L"25 should be limited to 20.");
		}

		TEST_METHOD(TestReverse)
		{
			Limiter<int> limiter(20, 10);
			Assert::AreEqual(10, limiter.Clamp(5), L"5 should be limited to 10.");
			Assert::AreEqual(10, limiter.Clamp(10), L"10 should be within the limits.");
			Assert::AreEqual(15, limiter.Clamp(15), L"15 should be within the limits.");
			Assert::AreEqual(20, limiter.Clamp(20), L"20 should be within the limits.");
			Assert::AreEqual(20, limiter.Clamp(25), L"25 should be limited to 20.");
		}

		TEST_METHOD(TestNegative)
		{
			Limiter<int> limiter(-10, -20);
			Assert::AreEqual(-10, limiter.Clamp(-5), L"-5 should be limited to -10.");
			Assert::AreEqual(-10, limiter.Clamp(-10), L"-10 should be within the limits.");
			Assert::AreEqual(-15, limiter.Clamp(-15), L"-15 should be within the limits.");
			Assert::AreEqual(-20, limiter.Clamp(-20), L"-20 should be within the limits.");
			Assert::AreEqual(-20, limiter.Clamp(-25), L"-25 should be limited to -20.");
		}

		TEST_METHOD(TestSpanZero)
		{
			Limiter<int> limiter(-10, 10);
			Assert::AreEqual(-10, limiter.Clamp(-15), L"-15 should be limited to -10.");
			Assert::AreEqual(-10, limiter.Clamp(-10), L"-10 should be within the limits.");
			Assert::AreEqual(-1, limiter.Clamp(-1), L"-1 should be within the limits.");
			Assert::AreEqual(0, limiter.Clamp(0), L"0 should be within the limits.");
			Assert::AreEqual(1, limiter.Clamp(1), L"1 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(10), L"10 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(15), L"15 should be limited to 10.");
		}

		TEST_METHOD(TestSpanZeroReverse)
		{
			Limiter<int> limiter(10, -10);
			Assert::AreEqual(-10, limiter.Clamp(-15), L"-15 should be limited to -10.");
			Assert::AreEqual(-10, limiter.Clamp(-10), L"-10 should be within the limits.");
			Assert::AreEqual(-1, limiter.Clamp(-1), L"-1 should be within the limits.");
			Assert::AreEqual(0, limiter.Clamp(0), L"0 should be within the limits.");
			Assert::AreEqual(1, limiter.Clamp(1), L"1 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(10), L"10 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(15), L"15 should be limited to 10.");
		}

		TEST_METHOD(ZeroUp)
		{
			Limiter<int> limiter(0, 10);
			Assert::AreEqual(0, limiter.Clamp(-5), L"-5 should be limited to 0.");
			Assert::AreEqual(0, limiter.Clamp(0), L"0 should be within the limits.");
			Assert::AreEqual(5, limiter.Clamp(5), L"5 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(10), L"10 should be within the limits.");
			Assert::AreEqual(10, limiter.Clamp(15), L"15 should be limited to 10.");
		}
		TEST_METHOD(ZeroDown)
		{
			Limiter<int> limiter(0, -10);
			Assert::AreEqual(0, limiter.Clamp(5), L"5 should be limited to 0.");
			Assert::AreEqual(0, limiter.Clamp(0), L"0 should be within the limits.");
			Assert::AreEqual(-5, limiter.Clamp(-5), L"15 should be within the limits.");
			Assert::AreEqual(-10, limiter.Clamp(-10), L"-10 should be within the limits.");
			Assert::AreEqual(-10, limiter.Clamp(-15), L"-15 should be limited to -10.");
		}
		
	};
}


