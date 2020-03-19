#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/class.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestPair
{
	TEST_CLASS(UnitTestPair)
	{
	public:

		TEST_METHOD(TestMethodE1)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段之间存在重合！
			paircore->insert_line(type_segment, 1, 2, 1, 4);
			paircore->insert_line(type_segment, 1, 3, 1, 5);
			Assert::AreEqual(paircore->output1(), -1);
		}
		TEST_METHOD(TestMethodE2)
		{
			PairCore* paircore = new PairCore(TEST);
			//线段和射线之间存在重合！
			paircore->insert_line(type_segment, 1, 2, 1, 4);
			paircore->insert_line(type_ray, 1, 3, 1, 7);
			Assert::AreEqual(paircore->output1(), -2);
		}
		TEST_METHOD(TestMethodE3)
		{
			PairCore* paircore = new PairCore(TEST);
			//射线之间存在重合！
			paircore->insert_line(type_ray, 1, 2, 1, -1);
			paircore->insert_line(type_ray, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -3);
		}
		TEST_METHOD(TestMethodE4)
		{
			PairCore* paircore = new PairCore(TEST);
			//直线和线段存在重合！
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_segment, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE5)
		{
			PairCore* paircore = new PairCore(TEST);
			//直线和射线存在重合！
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_ray, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE6)
		{
			PairCore* paircore = new PairCore(TEST);
			//直线之间存在重合！
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_line, 1, 0, 1, -1);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE7)
		{
			PairCore* paircore = new PairCore(TEST);
			//圆和圆存在重合！
			paircore->insert_circle(5, 6, 3);
			paircore->insert_circle(5, 6, 3);
			Assert::AreEqual(paircore->output1(), -5);
		}
		TEST_METHOD(TestMethodE8)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//输入了两个重复的交点
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error6.txt");
			Assert::AreEqual(paircore->output1(), -6);
		}
		TEST_METHOD(TestMethodE9)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//坐标超出范围
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error7.txt");
			Assert::AreEqual(paircore->output1(), -7);
		}
		TEST_METHOD(TestMethodE10)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//坐标超出范围
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error8.txt");
			Assert::AreEqual(paircore->output1(), -8);
		}
		TEST_METHOD(TestMethodE11)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//图形类型不正确
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error9.txt");
			Assert::AreEqual(paircore->output1(), -9);
		}
		TEST_METHOD(TestMethodE12)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//图形类型不正确
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error10.txt");
			Assert::AreEqual(paircore->output1(), -10);
		}
		TEST_METHOD(TestMethodE13)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//图形类型不正确
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error11.txt");
			Assert::AreEqual(paircore->output1(), -11);
		}
		TEST_METHOD(TestMethodE14)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//图形类型不正确
			paircore->setInput("D:\\学习资料\\大三下\\软工\\结队项目\\intersect\\error12.txt");
			Assert::AreEqual(paircore->output1(), -12);
		}
	};
}
