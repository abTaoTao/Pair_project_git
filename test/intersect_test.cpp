#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/class.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPair
{
	TEST_CLASS(UnitTestPair)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			PairCore* paircore = new PairCore();
			//线段端点重合,且平行于y轴
			paircore->insert_line(type_segment, 1, 2, 1, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 3);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod2)
		{
			PairCore* paircore = new PairCore();
			//虽然线段有交点，但是交点不在两条线段上
			paircore->insert_line(type_segment, 1, 2, 3, 2);
			paircore->insert_line(type_segment, 1, 4, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod3)
		{
			PairCore* paircore = new PairCore();
			//交点在线段上
			paircore->insert_line(type_segment, 0, 3, 3, 3);
			paircore->insert_line(type_segment, 1, 2, 1, 9);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod4)
		{
			PairCore* paircore = new PairCore();
			//虽然延长后有交点，但是不在几何图形上
			paircore->insert_line(type_ray, 1, 2, 3, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod5)
		{
			PairCore* paircore = new PairCore();
			//交点在线段的端点上
			paircore->insert_line(type_ray, 1, 4, 3, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 119);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod6)
		{
			PairCore* paircore = new PairCore();
			//交点在线段上
			paircore->insert_line(type_ray, 1, 2, 2, 10);
			paircore->insert_line(type_segment, 1, 4, 2, 8);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod7)
		{
			PairCore* paircore = new PairCore();
			//在同一直线上但是没有交点
			paircore->insert_line(type_ray, 1, 2, 1, 9);
			paircore->insert_line(type_segment, 1, 0, 1, 1);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod8)
		{
			PairCore* paircore = new PairCore();
			//在同一直线上但是没有交点
			paircore->insert_line(type_segment, 2,3,4,3);
			paircore->insert_line(type_segment, -99999,3,1,3);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod9)
		{
			PairCore* paircore = new PairCore();
			//多种几何图形共点
			paircore->insert_line(type_segment, 0,1, 3, 3);
			paircore->insert_line(type_line,1, 1, 9, 9);
			paircore->insert_line(type_segment, 1, -1, 4, 5);
			paircore->insert_line(type_ray, 1, -3, 9, 21);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
	};
}
