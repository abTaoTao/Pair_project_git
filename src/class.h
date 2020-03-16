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
/*struct equals {
	bool operator()( const Point&a,  const Point&b) const
	{
		return fabs(a.getX() - b.getX()) < EPS && fabs(a.getY() - b.getY()) < EPS;
	}
};*/

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
		a = y2 - y1;
		b = x1 - x2;
		c = x2 * y1 - x1 * y2;
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
};
class PairCore{
private:
	string input;
	string output;
	vector<Line> lines;
	unordered_set<Point, HashPoint> points;
public:
	int parser(int argc, char* argv[]);
	void text_handle() {
		ifstream in_file;
		in_file.open(input);
		string str;
		if (in_file.good()) {
			getline(in_file, str);
		}
		regex num_pattern("[1-9][0-9]*");
		regex line_pattern("(L|R|S) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0)");
		//cout << regex_match("L -1 -2 -3 2", line_pattern) << endl;
		//cout << regex_match("L -1 -2 -3 0", line_pattern) << endl;
		regex circle_pattern("(C) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0) ((-?[1-9][0-9]*)|0)");
		if (regex_match(str, num_pattern)) {
			while (in_file.good()) {
				getline(in_file, str);
				//cout << str << endl;
				if (regex_match(str,line_pattern)) {
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

				}
				else {
					throw InputException("图形的类型出错！");
				}

			}
			//cout << lines.size() << endl;
		}
		else {
			throw InputException("请先输入一个正整数");
		}
	}
	void insert_line(LineType _type, int x1, int y1, int x2, int y2) {
		lines.emplace_back(_type, x1, y1, x2, y2);
	}
	int getIntersectionCount() {
		auto end = lines.end();
		//int count = 0;
		for (auto it1 = lines.begin(); it1 != end - 1; it1++) {
			for (auto it2 = it1 + 1; it2 != end; it2++) {
				//count++;
				vector<Point> intersections = it1->getIntersect(*it2);
				for (auto it3 : intersections) {
					points.insert(it3);
				}
			}
		}
		///printf("%d\n", count);
		return points.size();
	}
	void output1() {
		input = "input9.txt";
		output = "output.txt";
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
