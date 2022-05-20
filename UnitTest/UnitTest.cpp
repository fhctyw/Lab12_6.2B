#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_6.2B\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Elem* first = nullptr, * last = nullptr;
			for (size_t i = 0; i < 10; i++)
				enqueue(first, last, i);
			int i = 0;
			remove(first, last, i, 0);
			i = 0;
			remove(first, last, i, 0);
			Assert::AreEqual(8, count(first));
		}
	};
}
