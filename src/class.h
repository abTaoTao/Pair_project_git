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
#include "exception.h"

#define EPS 1e-13
using namespace std;

enum LineType { type_line, type_ray, type_segment };
enum Direction { dir_left, dir_right };

class Point {
private:
	double x;
	double y;
public:
	Point() {
		x = 0;
		y = 0;
	}
	Point(double _x, double _y) {
		x = _x;
		y = _y;
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
};


class HashPoint {
public:
	size_t operator()(const Point& pr) const
	{
		return hash<float>()(pr.getX()) ^ hash<float>()(pr.getY());
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
			dir = dir_right;
		}
		else {
			p2.setXY(x1, y1);
			p1.setXY(x2, y2);
			dir = dir_left;
		}
		type = _type;
	}
	//构造直线
	Line(LineType _type, long long _a, long long _b, long long _c) {
		type = _type;
		a = _a;
		b = _b;
		c = _c;
		dir = dir_right;
	}
	//0所在直线重合，1平行但是不重合，2相交
	int relation(Line l) {
		if (a * l.b == l.a * b && a * l.c == l.a * c && b * l.c == l.b * c)
			return 0;
		else if (a * l.b == l.a * b)
			return 1;
		else
			return 2;
	}
	bool isOnLine(Point p) {
		if (type == type_line) {
			return true;
		}
		else if (type == type_ray) {
			if (dir == dir_left) {
				return p < p2 || p == p2;
			}
			if (dir == dir_right) {
				return p1 < p || p1 == p;
			}
		}
		else if (type == type_segment) {
			return (p1 < p && p < p2) || (p1 == p) || (p2 == p);
		}
		return false;
	}
	vector<Point> getIntersect(Line l) {
		vector<Point> points;
		int r = relation(l);
		//printf("%d\n", r);
		if (r == 0) {
			if (type == type_segment && l.type == type_segment) {
				//printf("in getIntersect S1:%lf %lf %lf %lf\n", p1.getX(), p1.getY(), p2.getX(), p2.getY());
				//printf("in getIntersect S2:%lf %lf %lf %lf\n", l.p1.getX(), l.p1.getY(), l.p2.getX(), l.p2.getY());
				if (p1 == l.p2) {
					points.push_back(p1);
				}
				else if (p2 == l.p1) {
					points.push_back(p2);
				}
				else if (p1 < l.p2  && l.p2 < p2 || l.p1 < p2 && p2 < l.p2) {
					throw CoincideException("线段之间存在重合！");
				}
			}
			else if (type == type_segment && l.type == type_ray) {
				if ((l.dir == dir_left && p1 < l.p2) || (l.dir == dir_right && l.p1 < p2)) {
					throw CoincideException("线段和射线之间存在重合！");
				}
				else if (l.dir == dir_left && p1 == l.p2) {
					points.push_back(p1);
				}
				else if (l.dir == dir_right && l.p1 == p2) {
					points.push_back(p2);
				}
			}
			else if (type == type_ray && l.type == type_segment) {
				if ((dir == dir_left && l.p1 < p2) || (dir == dir_right && p1 < l.p2)) {
					throw CoincideException("线段和射线之间存在重合！");
				}
				else if (dir == dir_left && l.p1 == p2) {
					points.push_back(p2);
				}
				else if (dir == dir_right && p1 == l.p2) {
					points.push_back(p1);
				}
			}
			else if (type == type_ray && l.type == type_ray) {
				if (dir == dir_left && l.dir == dir_right) {
					if (l.p1 < p2) {
						throw CoincideException("射线之间存在重合！");
					}
					else if (l.p1 == p2) {
						points.push_back(p2);
					}
				}
				else if (dir == dir_right && l.dir == dir_left) {
					if (p1 < l.p2) {
						throw CoincideException("射线之间存在重合！");
					}
					else if (p1 == l.p2) {
						points.push_back(p1);
					}
				}
				else {
					throw CoincideException("射线之间存在重合！");
				}
			}
			else {
				throw CoincideException("直线与某条线重合！");
			}
		}
		else if (r == 2) {
			double down = (a * l.b - l.a * b);
			double tmpx = (double)(b * l.c - l.b * c) / down;
			double tmpy = (double)(l.a * c - a * l.c) / down;
			Point tmpp(tmpx, tmpy);
			if (isOnLine(tmpp) && l.isOnLine(tmpp)) {
			//	printf("直线与直线交点:%lf %lf\n", tmpp.getX(), tmpp.getY());
				points.push_back(tmpp);
			}
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
		double A = line.getA();
		double B = line.getB();
		double C = line.getC();
		double dis = double(A * x0 + B * y0 + C) / sqrt(A * A + B * B);
		return fabs(dis);
	}
	vector<Point> getIntersectWithLine(Line line) {
		vector<Point> intersectsWithLine;
		long long A = line.getA();
		long long B = line.getB();
		long long C = line.getC();
		double dis = getDistance(line);
		//line 的垂线line_v
		Line *line_v = new Line(type_line, B, -A, A * y0 - B * x0);
		//传入的线可能是线段或者射线，将之转化为直线求解。
		Line* line_copy = new Line(type_line, A, B, C);
		//直线与垂线的交点
		vector<Point> points = line_v->getIntersect(*line_copy);
		double X = points[0].getX();
		double Y = points[0].getY();
		//求交点
		//printf("int getLineInter:%lf %lf\n", dis, (double)r0);
		if (dis < (double)r0) {
			//printf("圆与直线的距离小于半径！");
			double times = sqrt((double)r0 * r0 - dis * dis);
			Point point1, point2;
			//求直线的单位向量方向上长度为：sqrt(半径平方-dis平方)的向量
			double first = times * B / sqrt((double)A * A + B * B);
			double second = -times * A / sqrt((double)A * A + B * B);
			point1.setXY(X - first, Y - second);
			point2.setXY(X + first, Y + second);
			if (line.isOnLine(point1))
				intersectsWithLine.push_back(point1);
			if (line.isOnLine(point2))
				intersectsWithLine.push_back(point2);
			//printf("%.22lf %.22lf %.22lf %.22lf\n", point1.getX(), point1.getY(), point2.getX(), point2.getY());
		}
		else if (fabs (dis - double(r0)) < EPS) {
			if(line.isOnLine(points[0]))
				intersectsWithLine.push_back(points[0]);
		}
		else {
			return intersectsWithLine;
		}
		return intersectsWithLine;
	}
	vector<Point> getIntersectWithCirc(Circle circ1) {
		//printf("该圆的半径：%lld\n", r0);
		long long x1 = circ1.x0;
		long long y1 = circ1.y0;
		long long r1 = circ1.r0;
		vector<Point> intersectsWithCirc;
		if (x0 == x1 && y0 == y1 && r0 == r1) {
			throw InputException("圆与圆重合！");
		}
		else {
			//圆心距离
			double d = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
			if (d <= 0 || d > (double)r1 + r0 || d < abs((double)r0 - r1)) {
				return intersectsWithCirc;
			};
			Line* line1 = new Line(type_line, 2 * x1 - 2 * x0, 2 * y1 - 2 * y0, -x1 * x1 + x0 * x0 - y1 * y1 + y0 * y0 + r1 * r1 - r0 * r0);
			return getIntersectWithLine(*line1);
		}
	}
};
class PairCore{
private:
	string input;
	string output;
	vector<Line> lines;
	vector<Circle> circles;
	unordered_set<Point, HashPoint> points;
public:
	int parser(int argc, char* argv[]);
	void text_handle() {
		int geo_num = 0;
		ifstream in_file;
		in_file.open(input);
		string str;
		if (in_file.good()) {
			getline(in_file, str);
		}
		//处理换行?如果某一行是直接输入一个换行，导致改行是空串，是否继续读？
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
				if (regex_match(str,line_pattern)) {
					//cout << str << endl;
					char type;
					int x1, y1, x2, y2;
					LineType _type;
					sscanf_s(str.c_str(), "%c %d %d %d %d", &type, sizeof(char), &x1, &y1, &x2, &y2);
					if (type == 'L')
						_type = type_line;
					else if (type == 'R')
						_type = type_ray;
					else
						_type = type_segment;
					if (x1 == x2 && y1 == y2) {
						throw InputException("输入了两个重复的交点！");
					}
					else if (abs(x1) >= 100000 || abs(y1) >= 100000 || abs(x2) >= 100000 || abs(y2) >= 100000) {
						throw InputException("坐标超出了范围，应该在(-100000,100000)！");
					}
					lines.emplace_back(_type ,x1, y1, x2, y2);	
				}
				else if (regex_match(str, circle_pattern)) {
					//cout << str << endl;
					char type;
					int x0, y0, r0;
					sscanf_s(str.c_str(), "%c %d %d %d", &type, sizeof(char), &x0, &y0, &r0);
					if (abs(x0) >= 100000 || abs(y0) >= 100000 || abs(r0) >= 100000) {
						throw InputException("坐标超出了范围，应该在(-100000,100000)！");
					}
					if (r0 <= 0) {
						throw InputException("请保证输入的圆的半径是大于0的整数");
					}
					circles.emplace_back(x0, y0, r0);
				}
				/*//处理换行?如果某一行是直接输入一个换行，导致改行是空串，是否继续读？
				else if (str == "") {
					continue;
				}*/
				else {
					throw InputException("图形的类型出错！");
				}
			}
		}
		else {
			throw InputException("请先输入一个正整数!");
		}
		if ((lines.size() + circles.size()) != geo_num) {
			throw InputException("请输入相应个数的几何图形！");
		}
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
		int i, j;
		for (i = 0; i < line_size; ++i) {
			for (j = 0; j < circ_size; ++j) {
				vector<Point> intersections = circles[j].getIntersectWithLine(lines[i]);
				for (auto point : intersections) {
					points.insert(point);
				}
			}
			for (j = i + 1; j < line_size; j++) {
				vector<Point> intersections = lines[i].getIntersect(lines[j]);
				for (auto point : intersections) {
					points.insert(point);
				}
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
	void output1() {
		//input = "input2.txt";
		//output = "output.txt";
		try {
			text_handle();
			ofstream out_file;
			out_file.open(output);
			int count = getIntersectionCount();
			cout << count;
			out_file << count;
		}
		catch (exception e) {
			cout << e.what();
		}
	}
};
