#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/class.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#define type_segment LineType::type_segment
#define type_ray  LineType::type_ray
#define type_line LineType::type_line
namespace UnitTestPair
{
	TEST_CLASS(UnitTestPair)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段端点重合,且平行于y轴
			paircore->insert_line(type_segment, 1, 2, 1, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 3);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod2)
		{
			PairCore* paircore = new PairCore(TEST);
			//虽然线段有交点，但是交点不在两条线段上
			paircore->insert_line(type_segment, 1, 2, 3, 2);
			paircore->insert_line(type_segment, 1, 4, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod3)
		{
			PairCore* paircore = new PairCore(TEST);
			//交点在线段上
			paircore->insert_line(type_segment, 0, 3, 3, 3);
			paircore->insert_line(type_segment, 1, 2, 1, 9);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod4)
		{
			PairCore* paircore = new PairCore(TEST);
			//虽然延长后有交点，但是不在几何图形上
			paircore->insert_line(type_ray, 1, 2, 3, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod5)
		{
			PairCore* paircore = new PairCore(TEST);
			//交点在线段的端点上
			paircore->insert_line(type_ray, 1, 4, 3, 3);
			paircore->insert_line(type_segment, 1, 4, 1, 119);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod6)
		{
			PairCore* paircore = new PairCore(TEST);
			//交点在线段上
			paircore->insert_line(type_ray, 1, 2, 2, 10);
			paircore->insert_line(type_segment, 1, 4, 2, 8);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod7)
		{
			PairCore* paircore = new PairCore(TEST);
			//在同一直线上但是没有交点
			paircore->insert_line(type_ray, 1, 2, 1, 9);
			paircore->insert_line(type_segment, 1, 0, 1, 1);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod8)
		{
			PairCore* paircore = new PairCore(TEST);
			//在同一直线上但是没有交点
			paircore->insert_line(type_segment, 2,3,4,3);
			paircore->insert_line(type_segment, -99999,3,1,3);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod9)
		{
			PairCore* paircore = new PairCore(TEST);
			//多种几何图形共点
			paircore->insert_line(type_segment, 0,1, 3, 3);
			paircore->insert_line(type_line,1, 1, 9, 9);
			paircore->insert_line(type_segment, 1, -1, 4, 5);
			paircore->insert_line(type_ray, 1, -3, 9, 21);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}

		//test for circle
		TEST_METHOD(TestMethod10)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆与线段所在直线有交点但是不在线段上
			paircore->insert_circle(1,2,3);
			paircore->insert_line(type_segment, 1,2, 1, 0);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod111)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆与线段所在直线有交点但是其中一个交点不在线段上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, 1, 2, 1, -3);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod11)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆与线段所在直线有交点且都在线段端点上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, 1, -1, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 2);
		}
		TEST_METHOD(TestMethod12)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆与线段所在直线有交点且都在线段上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, 1, -7, 1, 9);
			Assert::AreEqual(paircore->getIntersectionCount(), 2);
		}
		TEST_METHOD(TestMethod13)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段与圆相切，但是切点不在线段上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, -1, 5, 0, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod14)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段与圆相切，切点在线段端点上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, -1, 5, 1, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod15)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段与圆相切，切点在线段上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, -1, 5, 2, 5);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod155)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段与圆相离
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_segment, -1, 5, 2, 18);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod16)
		{
			PairCore* paircore = new PairCore(TEST);
			//射线所在直线与圆相交，交点不在射线上
			paircore->insert_circle(1, 2, 2);
			paircore->insert_line(type_ray, 0, 0, -1, -2);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod17)
		{
			PairCore* paircore = new PairCore(TEST);
			//射线所在直线与圆相交，只有一个交点在射线(端点)上，另一个不在射线上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_ray, 1,-1, -1, -9);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod18)
		{
			PairCore* paircore = new PairCore(TEST);
			//射线所在直线与圆相交，只有一个交点在射线(端点)上，另一个在射线上
			paircore->insert_circle(1, 2, 3);
			paircore->insert_line(type_ray, 1, -1, -1, 1);
			Assert::AreEqual(paircore->getIntersectionCount(), 2);
		}
		TEST_METHOD(TestMethod19)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆相交
			paircore->insert_circle(1, 2, 3);
			paircore->insert_circle(1, 4, 2);
			Assert::AreEqual(paircore->getIntersectionCount(), 2);
		}
		TEST_METHOD(TestMethod20)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆相切-外切
			paircore->insert_circle(1, 2, 3);
			paircore->insert_circle(1, 6, 1);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod21)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆相切-内切
			paircore->insert_circle(1, 2, 3);
			paircore->insert_circle(1, 4, 1);
			Assert::AreEqual(paircore->getIntersectionCount(), 1);
		}
		TEST_METHOD(TestMethod22)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆相离
			paircore->insert_circle(1, 2, 3);
			paircore->insert_circle(2, 99, 2);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}
		TEST_METHOD(TestMethod23)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆内含
			paircore->insert_circle(1, 2, 3);
			paircore->insert_circle(1, 2, 9);
			Assert::AreEqual(paircore->getIntersectionCount(), 0);
		}

		TEST_METHOD(TestMethod24)
		{
			PairCore* paircore = new PairCore(TEST);
			//综合测试-样例
			paircore->insert_circle(3, 3, 3);
			paircore->insert_line(type_segment, 2, 4, 3, 2);
			paircore->insert_line(type_line, -1, 4, 5, 2);
			paircore->insert_line(type_ray, 2, 5, -1, 2);
			Assert::AreEqual(paircore->getIntersectionCount(), 5);
		}
		TEST_METHOD(TestMethod25)
		{
			PairCore* paircore = new PairCore(TEST);
			//综合测试-边界测试
			paircore->insert_circle(99998, 99998, 1);
			paircore->insert_line(type_segment, 99999,99999,99999,99998);//1
			paircore->insert_line(type_line, -99999,99999,-99998,99999);//2
			paircore->insert_line(type_ray, 99999,99999,99998,99998);//3(1个点重复)
			Assert::AreEqual(paircore->getIntersectionCount(), 5);
		}
		//test interface gui
		/*
		TEST_METHOD(TestMethod27_GUI)
		{
			//PairCore* paircore = new PairCore(GUI);
			//Assert::AreEqual(paircore->output1() ,6);
			Assert::AreEqual(gui_solve(), 6);
		}
		//test interface command
		TEST_METHOD(TestMethod28_Command)
		{
			Assert::AreEqual(command_solve(), 6);
		}
		*/
	};
}
