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
			//�߶�֮������غϣ�
			paircore->insert_line(type_segment, 1, 2, 1, 4);
			paircore->insert_line(type_segment, 1, 3, 1, 5);
			Assert::AreEqual(paircore->output1(), -1);
		}
		TEST_METHOD(TestMethodE2)
		{
			PairCore* paircore = new PairCore(TEST);
			//�߶κ�����֮������غϣ�
			paircore->insert_line(type_segment, 1, 2, 1, 4);
			paircore->insert_line(type_ray, 1, 3, 1, 7);
			Assert::AreEqual(paircore->output1(), -2);
		}
		TEST_METHOD(TestMethodE3)
		{
			PairCore* paircore = new PairCore(TEST);
			//����֮������غϣ�
			paircore->insert_line(type_ray, 1, 2, 1, -1);
			paircore->insert_line(type_ray, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -3);
		}
		TEST_METHOD(TestMethodE4)
		{
			PairCore* paircore = new PairCore(TEST);
			//ֱ�ߺ��߶δ����غϣ�
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_segment, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE5)
		{
			PairCore* paircore = new PairCore(TEST);
			//ֱ�ߺ����ߴ����غϣ�
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_ray, 1, 0, 1, 7);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE6)
		{
			PairCore* paircore = new PairCore(TEST);
			//ֱ��֮������غϣ�
			paircore->insert_line(type_line, 1, 2, 1, 8);
			paircore->insert_line(type_line, 1, 0, 1, -1);
			Assert::AreEqual(paircore->output1(), -4);
		}
		TEST_METHOD(TestMethodE7)
		{
			PairCore* paircore = new PairCore(TEST);
			//Բ��Բ�����غϣ�
			paircore->insert_circle(5, 6, 3);
			paircore->insert_circle(5, 6, 3);
			Assert::AreEqual(paircore->output1(), -5);
		}
		TEST_METHOD(TestMethodE8)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//�����������ظ��Ľ���
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error6.txt");
			Assert::AreEqual(paircore->output1(), -6);
		}
		TEST_METHOD(TestMethodE9)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//���곬����Χ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error7.txt");
			Assert::AreEqual(paircore->output1(), -7);
		}
		TEST_METHOD(TestMethodE10)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//���곬����Χ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error8.txt");
			Assert::AreEqual(paircore->output1(), -8);
		}
		TEST_METHOD(TestMethodE11)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//ͼ�����Ͳ���ȷ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error9.txt");
			Assert::AreEqual(paircore->output1(), -9);
		}
		TEST_METHOD(TestMethodE12)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//ͼ�����Ͳ���ȷ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error10.txt");
			Assert::AreEqual(paircore->output1(), -10);
		}
		TEST_METHOD(TestMethodE13)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//ͼ�����Ͳ���ȷ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error11.txt");
			Assert::AreEqual(paircore->output1(), -11);
		}
		TEST_METHOD(TestMethodE14)
		{
			PairCore* paircore = new PairCore(TEST_INPUT_ERROR);
			//ͼ�����Ͳ���ȷ
			paircore->setInput("D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\error12.txt");
			Assert::AreEqual(paircore->output1(), -12);
		}
	};
}
