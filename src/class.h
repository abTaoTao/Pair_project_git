#pragma once
#include <cmath>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <regex>
#include <unordered_map>
#include<iostream>
#include<fstream>
#include <map>
#include "exception.h"

#define EPS 1e-10
#define GUI 1
#define COMMAND 2
#define TEST 3
#define TEST_INPUT_ERROR 4
using namespace std;

enum class LineType { type_line, type_ray, type_segment };
enum class Direction { dir_left, dir_right };

class Point {
private:
	double x;
	double y;
	int error_flag;
public:
	Point() {
		x = 0;
		y = 0;
		error_flag = 0;
	}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
		error_flag = 0;
	}
	void SetError() {
		error_flag = 1;
	}
	bool operator==(const Point& p) const {
		return (fabs(x - p.x) < EPS && fabs(y - p.y) < EPS);
	}

	bool operator<(const Point& p) const {
		if (fabs(x - p.x) > EPS) {
			return x < p.x;
		}
		if (fabs(y - p.y) > EPS) {
			return y < p.y;
		}
		return false;
	}

	bool operator>(const Point& p) const {
		if (fabs(x - p.x) > EPS) {
			return x > p.x;
		}
		if (fabs(y - p.y) > EPS) {
			return y > p.y;
		}
		return false;
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	void setXY(double _x, double _y) {
		x = _x;
		y = _y;
	}
	int getErrorFlag() {
		return error_flag;
	}
};

class HashPoint {
public:
	size_t operator()(const Point& pr) const
	{
		return hash<float>()((float)pr.getX()) ^ hash<float>()((float)pr.getY());
	}
};

class Line {
private:
	LineType type;
	Point p1;
	Point p2;
	Direction dir;
	long long a;
	long long b;
	long long c;
public:
	Line(LineType _type, int x1, int y1, int x2, int y2) {
		a = (long long)y2 - y1;
		b = (long long)x1 - x2;
		c = (long long)x2 * y1 - (long long)x1 * y2;
		Point tmp1 = Point(x1, y1);
		Point tmp2 = Point(x2, y2);
		if (tmp1 < tmp2) {
			p1.setXY(x1, y1);
			p2.setXY(x2, y2);
			dir = Direction::dir_right;
		}
		else {
			p2.setXY(x1, y1);
			p1.setXY(x2, y2);
			dir = Direction::dir_left;
		}
		type = _type;
	}
	//����ֱ��
	Line(LineType _type, long long _a, long long _b, long long _c) {
		type = _type;
		a = _a;
		b = _b;
		c = _c;
		dir = Direction::dir_right;
	}
	//0����ֱ���غϣ�1ƽ�е��ǲ��غϣ�2�ཻ
	int relation(Line l) {
		if (a * l.b == l.a * b && a * l.c == l.a * c && b * l.c == l.b * c)
			return 0;
		else if (a * l.b == l.a * b)
			return 1;
		else
			return 2;
	}
	bool isOnLine(Point p) {
		if (type == LineType::type_line) {
			return true;
		}
		else if (type == LineType::type_ray) {
			if (dir == Direction::dir_left) {
				return p < p2 || p == p2;
			}
			if (dir == Direction::dir_right) {
				return p1 < p || p1 == p;
			}
		}
		else if (type == LineType::type_segment) {
			return (p1 < p && p < p2) || (p1 == p) || (p2 == p);
		}
		return false;
	}
	Point getIntersect(Line l) {
		Point points;
		int r = relation(l);
		//printf("%d\n", r);
		if (r == 0) {
			if (type == LineType::type_segment && l.type == LineType::type_segment) {
				//printf("in getIntersect S1:%lf %lf %lf %lf\n", p1.getX(), p1.getY(), p2.getX(), p2.getY());
				//printf("in getIntersect S2:%lf %lf %lf %lf\n", l.p1.getX(), l.p1.getY(), l.p2.getX(), l.p2.getY());
				if (p1 == l.p2) {
					//points.push_back(p1);
					points.setXY(p1.getX(), p1.getY());

				}
				else if (p2 == l.p1) {
					//points.push_back(p2);
					points.setXY(p2.getX(), p2.getY());
				}
				else if (p1 < l.p2 && l.p2 < p2 || l.p1 < p2 && p2 < l.p2) {
					throw CoincideException("�߶�֮������غϣ�");
				}
				else {
					points.SetError();
				}
			}
			else if (type == LineType::type_segment && l.type == LineType::type_ray) {
				if ((l.dir == Direction::dir_left && p1 < l.p2) || (l.dir == Direction::dir_right && l.p1 < p2)) {
					throw CoincideException("�߶κ�����֮������غϣ�");
				}
				else if (l.dir == Direction::dir_left && p1 == l.p2) {
					//points.push_back(p1);
					points.setXY(p1.getX(), p1.getY());
				}
				else if (l.dir == Direction::dir_right && l.p1 == p2) {
					//points.push_back(p2);
					points.setXY(p2.getX(), p2.getY());
				}
				else {
					points.SetError();
				}
			}
			else if (type == LineType::type_ray && l.type == LineType::type_segment) {
				if ((dir == Direction::dir_left && l.p1 < p2) || (dir == Direction::dir_right && p1 < l.p2)) {
					throw CoincideException("�߶κ�����֮������غϣ�");
				}
				else if (dir == Direction::dir_left && l.p1 == p2) {
					//points.push_back(p2);
					points.setXY(p2.getX(), p2.getY());
				}
				else if (dir == Direction::dir_right && p1 == l.p2) {
					//points.push_back(p1);
					points.setXY(p1.getX(), p1.getY());
				}
				else {
					points.SetError();
				}
			}
			else if (type == LineType::type_ray && l.type == LineType::type_ray) {
				if (dir == Direction::dir_left && l.dir == Direction::dir_right) {
					if (l.p1 < p2) {
						throw CoincideException("����֮������غϣ�");
					}
					else if (l.p1 == p2) {
						//points.push_back(p2);
						points.setXY(p2.getX(), p2.getY());
					}
					else {
						points.SetError();
					}
				}
				else if (dir == Direction::dir_right && l.dir == Direction::dir_left) {
					if (p1 < l.p2) {
						throw CoincideException("����֮������غϣ�");
					}
					else if (p1 == l.p2) {
						//points.push_back(p1);
						points.setXY(p1.getX(), p1.getY());
					}
					else {
						points.SetError();
					}
				}
				else {
					throw CoincideException("����֮������غϣ�");
				}
			}
			else {
				throw CoincideException("ֱ����ĳ�����غϣ�");
			}
		}
		else if (r == 2) {
			double down = ((double)a * l.b - (double)l.a * b);
			double tmpx = (double)(b * l.c - l.b * c) / down;
			double tmpy = (double)(l.a * c - a * l.c) / down;
			Point tmpp(tmpx, tmpy);
			if (isOnLine(tmpp) && l.isOnLine(tmpp)) {
				//printf("ֱ����ֱ�߽���:%lf %lf\n", tmpp.getX(), tmpp.getY());
				points.setXY(tmpp.getX(), tmpp.getY());
			}
			else {
				points.SetError();
			}
		}
		else {
			//û�н���
			points.SetError();
		}
		return points;
	}
	LineType getLineType() {
		return type;
	}
	Direction getDirection() {
		return dir;
	}
	long long getA() {
		return a;
	}
	long long getB() {
		return b;
	}
	long long getC() {
		return c;
	}
};
class Circle {
private:
	long long x0;
	long long y0;
	long long r0;
public:
	Circle(int _x0, int _y0, int _r0) {
		x0 = _x0;
		y0 = _y0;
		r0 = _r0;
	}
	double getDistance(Line line) {
		long long A = line.getA();
		long long B = line.getB();
		long long C = line.getC();
		double dis = (A * x0 + B * y0 + C) / sqrt(A * A + B * B);
		return fabs(dis);
	}
	vector<Point> getIntersectWithLine(Line line) {
		vector<Point> intersectsWithLine;
		long long A = line.getA();
		long long B = line.getB();
		long long C = line.getC();
		double dis = getDistance(line);
		//line �Ĵ���line_v
		Line* line_v = new Line(LineType::type_line, B, -A, A * y0 - B * x0);
		//������߿������߶λ������ߣ���֮ת��Ϊֱ����⡣
		Line* line_copy = new Line(LineType::type_line, A, B, C);
		//ֱ���봹�ߵĽ���,�ض��н���
		Point points = line_v->getIntersect(*line_copy);
		double X = points.getX();
		double Y = points.getY();
		//�󽻵�
		//printf("int getLineInter:%lf %lf\n", dis, (double)r0);
		if (fabs(dis - double(r0)) >= EPS && dis < double(r0)) {
			//printf("Բ��ֱ�ߵľ���С�ڰ뾶��");
			double times = sqrt(r0 * r0 - dis * dis);
			Point point1, point2;
			//��ֱ�ߵĵ�λ���������ϳ���Ϊ��sqrt(�뾶ƽ��-disƽ��)������
			double first = times * B / sqrt(A * A + B * B);
			double second = -times * A / sqrt(A * A + B * B);
			point1.setXY(X - first, Y - second);
			point2.setXY(X + first, Y + second);
			if (line.isOnLine(point1))
				intersectsWithLine.push_back(point1);
			if (line.isOnLine(point2))
				intersectsWithLine.push_back(point2);
			//printf("%.22lf %.22lf %.22lf %.22lf\n", point1.getX(), point1.getY(), point2.getX(), point2.getY());
		}
		else if (fabs(dis - double(r0)) < EPS) {
			if (line.isOnLine(points))
				intersectsWithLine.push_back(points);
		}
		else {
			return intersectsWithLine;
		}
		return intersectsWithLine;
	}
	vector<Point> getIntersectWithCirc(Circle circ1) {
		//printf("��Բ�İ뾶��%lld\n", r0);
		long long x1 = circ1.x0;
		long long y1 = circ1.y0;
		long long r1 = circ1.r0;
		vector<Point> intersectsWithCirc;
		if (x0 == x1 && y0 == y1 && r0 == r1) {
			throw InputException("Բ��Բ�غϣ�");
		}
		else {
			//Բ�ľ���
			double d = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
			if (d <= 0 || d > (double)r1 + r0 || d < abs((double)r0 - r1)) {
				return intersectsWithCirc;
			};
			Line* line1 = new Line(LineType::type_line, 2 * x1 - 2 * x0, 2 * y1 - 2 * y0, -x1 * x1 + x0 * x0 - y1 * y1 + y0 * y0 + r1 * r1 - r0 * r0);
			return getIntersectWithLine(*line1);
		}
	}
};
class PairCore {
private:
	string input;
	string output;
	vector<Line> lines;
	vector<Circle> circles;
	unordered_set<Point, HashPoint> points;
	map<string, int> exc2;
	int mode = 1;

public:
	PairCore(int _mode) {
		if (_mode == GUI) {
			input = "lines.pair";
			output = "points.pair";
		}
		mode = _mode;
		exc2.insert(pair<string, int>("�߶�֮������غϣ�", -1));
		exc2.insert(pair<string, int>("�߶κ�����֮������غϣ�", -2));
		exc2.insert(pair<string, int>("����֮������غϣ�", -3));
		exc2.insert(pair<string, int>("ֱ����ĳ�����غϣ�", -4));
		exc2.insert(pair<string, int>("Բ��Բ�غϣ�", -5));
		exc2.insert(pair<string, int>("�����������ظ��Ľ��㣡", -6));
		exc2.insert(pair<string, int>("���곬���˷�Χ��Ӧ����(-100000,100000)��", -7));
		exc2.insert(pair<string, int>("�뱣֤�����Բ�İ뾶�Ǵ���0������", -8));
		exc2.insert(pair<string, int>("ͼ�ε����ͳ���", -9));
		exc2.insert(pair<string, int>("��������һ����������", -10));
		exc2.insert(pair<string, int>("��������Ӧ�����ļ���ͼ�Σ�", -11));
		exc2.insert(pair<string, int>("����Ļ��з���", -12));
		exc2.insert(pair<string, int>("�����в�������", -13));
	}
	int parser(int argc, char* argv[]);
	void text_handle() {
		int geo_num = 0;
		ifstream in_file;
		in_file.open(input);
		string str;
		if (in_file.good()) {
			getline(in_file, str);
		}
		//������?���ĳһ����ֱ������һ�����У����¸����ǿմ����Ƿ��������
		/*while (str == "" && in_file.good()) {
			getline(in_file, str);
		}*/
		regex num_pattern("[1-9][0-9]*");
		regex line_pattern("(L|R|S) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0)");
		//cout << regex_match("L -1 -2 -3 2", line_pattern) << endl;
		//cout << regex_match("R 2 5 -1 2", line_pattern) << endl;
		regex circle_pattern("(C) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0)");
		if (regex_match(str, num_pattern)) {
			sscanf_s(str.c_str(), "%d", &geo_num);
			while (in_file.good()) {
				getline(in_file, str);
				//cout << str << endl;
				if (regex_match(str, line_pattern)) {
					//cout << str << endl;
					char type;
					int x1, y1, x2, y2;
					LineType _type;
					sscanf_s(str.c_str(), "%c %d %d %d %d", &type, sizeof(char), &x1, &y1, &x2, &y2);
					if (type == 'L')
						_type = LineType::type_line;
					else if (type == 'R')
						_type = LineType::type_ray;
					else
						_type = LineType::type_segment;
					if (x1 == x2 && y1 == y2) {
						throw InputException("�����������ظ��Ľ��㣡");
					}
					else if (abs(x1) >= 100000 || abs(y1) >= 100000 || abs(x2) >= 100000 || abs(y2) >= 100000) {
						throw InputException("���곬���˷�Χ��Ӧ����(-100000,100000)��");
					}
					lines.emplace_back(_type, x1, y1, x2, y2);
				}
				else if (regex_match(str, circle_pattern)) {
					//cout << str << endl;
					char type;
					int x0, y0, r0;
					sscanf_s(str.c_str(), "%c %d %d %d", &type, sizeof(char), &x0, &y0, &r0);
					if (abs(x0) >= 100000 || abs(y0) >= 100000 || abs(r0) >= 100000) {
						throw InputException("���곬���˷�Χ��Ӧ����(-100000,100000)��");
					}
					if (r0 <= 0) {
						throw InputException("�뱣֤�����Բ�İ뾶�Ǵ���0������");
					}
					circles.emplace_back(x0, y0, r0);
				}
				//������?���ĳһ����ֱ������һ�����У����¸����ǿմ����Ƿ��������
				else if (str == "") {
					if (in_file.good()) {
						throw InputException("����Ļ��з���");
					}
				}
				else {
					throw InputException("ͼ�ε����ͳ���");
				}
			}
		}
		else {
			throw InputException("��������һ����������");
		}
		if ((lines.size() + circles.size()) != geo_num) {
			throw InputException("��������Ӧ�����ļ���ͼ�Σ�");
		}
	}
	void setInput(string _input) {
		input = _input;
	}
	void insert_line(LineType _type, int x1, int y1, int x2, int y2) {
		lines.emplace_back(_type, x1, y1, x2, y2);
	}
	void insert_circle(int x0, int y0, int r0) {
		circles.emplace_back(x0, y0, r0);
	}
	int getIntersectionCount() {
		int line_size = lines.size();
		int circ_size = circles.size();
		vector<Point> intersections;
		int i, j;
		for (i = 0; i < line_size; ++i) {
			for (j = 0; j < circ_size; ++j) {
				intersections = circles[j].getIntersectWithLine(lines[i]);
				for (auto point : intersections) {
					points.insert(point);
				}
			}
			for (j = i + 1; j < line_size; j++) {
				Point point = lines[i].getIntersect(lines[j]);
				if (!point.getErrorFlag())
					points.insert(point);
			}
		}
		for (i = 0; i < circ_size; ++i) {
			for (j = i + 1; j < circ_size; j++) {
				vector<Point> intersections = circles[i].getIntersectWithCirc(circles[j]);
				for (auto point : intersections) {
					points.insert(point);
				}
			}
		}
		return points.size();
	}
	int output1() {
		//input = "D:\\ѧϰ����\\������\\��\\�����Ŀ\\intersect\\input.txt";
	  // output = "output.txt";
		if (mode == TEST) {
			try {
				int count = getIntersectionCount();
				return count;
			}
			catch (exception e) {
				return exc2[e.what()];
			}
		}
		else if (mode == TEST_INPUT_ERROR) {
			try {
				text_handle();
				int count = getIntersectionCount();
				return count;
			}
			catch (exception e) {
				return exc2[e.what()];
			}
		}
		else {
			try {
				text_handle();
				ofstream out_file;
				out_file.open(output);
				int count = getIntersectionCount();
				//cout << count;
				out_file << count;
				return count;
			}
			catch (exception e) {
				//cout << e.what()<<endl;
				//cout << exc2[e.what()];
				return exc2[e.what()];

			}
		}
	}
	int getError(string str) {
		return exc2[str];
	}
};

// for GUI
int gui_solve();

//for command
int command_solve();
