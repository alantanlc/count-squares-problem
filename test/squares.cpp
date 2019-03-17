#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <cmath>

using namespace std;

const double MAX = numeric_limits<double>::max();
const double EPSILON = numeric_limits<double>::epsilon();
const bool IS_PRINT_LOGS = false;

// A Point (aka coordinate) is defined as a pair of doubles (x, y)
class Point {
public:
	double x, y;

	Point() {}

	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double getEuclideanDistance(Point p) {
		return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
	}

	bool isValid() {
		return !abs(this->x - MAX) < EPSILON
			&& !abs(this->y - MAX) < EPSILON;
	}

	void toString() {
		cout << "(" << x << ", " << y << ") ";
	}
};

// A Line is defined as a pair of Points (p1, p2)
class Line {
public:
	Point p1, p2;

	Line() {}

	Line(Point p1, Point p2) {
		this->p1 = p1;
		this->p2 = p2;
	}

	// Checks if this line and given line are parallel using gradient
	bool isParallel(Line l) {
		return (abs(this->getGradient() - l.getGradient()) < EPSILON);
	}

	// Checks if this line and given line are perpendicular using gradient
	// If lines are perpendicular, then gradient g1 * g2 equals -1
	// or if one Line l1 is vertical while the other is horizontal, vice versa
	bool isPerpendicular(Line l) {
		return this->isVertical() && l.isHorizontal()
			|| this->isHorizontal() && l.isVertical()
			|| abs(this->getGradient() * l.getGradient() + 1.0) < EPSILON;
	}

	// Checks if this line is vertical
	bool isVertical() {
		return abs(this->getGradient() - MAX) < EPSILON;
	}

	// Checks if this line is horizontal
	bool isHorizontal() {
		return abs(this->getGradient()) < EPSILON;
	}

	// Computes gradient of this line
	// gradient = (y2 - y1) / (x2 - x1). if x2 - x1 equals zero, return MAX.
	double getGradient() {
		if(abs(this->p2.x - this->p1.x) > EPSILON) {
			return (double) (this->p2.y - this->p1.y) / (double) (this->p2.x - this->p1.x);
		}

		return MAX;
	}

	// Computes y-axis intersection of this line
	// c = y - mx
	double getC() {
		if(this->isVertical()) {
			return MAX;
		} else if(this->isHorizontal()) {
			return this->p1.y;
		}

		return this->p1.y - this->getGradient() * this->p1.x;
	}

	// Computes intersection point (x, y) of this line and given line
	// x = (c2 - c1) / (m1 - m2)
	// y = m1 * x + c1
	Point getIntersectionPoint(Line l) {
		double x = MAX;
		double y = MAX;

		if(this->isVertical() && l.isHorizontal()) {
			x = this->p1.x;
			y = l.p1.y;
		} else if (this->isHorizontal() && l.isVertical()) {
			x = l.p1.x;
			y = this->p1.y;
		} else if (!this->isParallel(l)) {
			x = (double) (l.getC() - this->getC()) / (double) (this->getGradient() - l.getGradient());
			y = this->getGradient() * x + this->getC();
		}

		return Point{x, y};
	}
};

// Stores a pair of lines that are parallel, i.e. gradients of both lines are the same
class ParallelLines {
public:
	Line l1;
	Line l2;

	ParallelLines() {}

	ParallelLines(Line l1, Line l2) {
		this->l1 = l1;
		this->l2 = l2;
	}

	// Checks if this pair of parallel lines and given pair of parallel lines
	// forms a square between intersection points
	bool isSquare(ParallelLines p) {
		// Find the 4 intersection points if exist
		Point p1 = this->l1.getIntersectionPoint(p.l1);
		Point p2 = this->l1.getIntersectionPoint(p.l2);
		Point p3 = this->l2.getIntersectionPoint(p.l1);
		Point p4 = this->l2.getIntersectionPoint(p.l2);

		if(IS_PRINT_LOGS) {
			cout << "Intersection points: " << endl;
			p1.toString();
			p2.toString();
			p3.toString();
			p4.toString();
			cout << "\n";

			cout << "Euclidean distances: [";
			cout << p1.getEuclideanDistance(p2) << ", ";
			cout << p1.getEuclideanDistance(p3) << ", ";
			cout << p1.getEuclideanDistance(p4);
			cout << "]\n";
		}

		if(!p1.isValid() && !p2.isValid() && !p3.isValid() && !p4.isValid()) {
			return false;
		}

		return this->l1.isPerpendicular(p.l1)
			&& (abs(p1.getEuclideanDistance(p2) - p1.getEuclideanDistance(p3)) < EPSILON
			|| abs(p1.getEuclideanDistance(p2) - p1.getEuclideanDistance(p4)) < EPSILON);
	}

	void toString() {
		cout << "Lines: [(";
		cout << l1.p1.x << ", " << l1.p1.y << "), (" << l1.p2.x << ", " << l1.p2.y;
		cout << ")], [(";
		cout << l2.p1.x << ", " << l2.p1.y << "), (" << l2.p2.x << ", " << l2.p2.y;
		cout << ")]";
		cout << ", gradients = (" << l1.getGradient() 
			<< ", " << l2.getGradient() << ")" << "\n";
	}
};

// Finds all pairs of parallel lines given a vector of lines
vector<ParallelLines> findParallelLines(vector<Line> lines) {
	vector<ParallelLines> p;

	// Time complexity: O(n^2)
	for (int i = 0; i < lines.size(); ++i) {
		for (int j = i+1; j < lines.size(); ++j) {
			if(lines[i].isParallel(lines[j])) {
				p.push_back(ParallelLines{lines[i], lines[j]});
			}
		}
	}

	return p;
}

int countSquares(vector<Line> lines) {
	// Find all pairs of parallel lines given vector of lines
	vector<ParallelLines> parallelLines = findParallelLines(lines);

	if(IS_PRINT_LOGS) {
		// Print parallel lines
		cout << "\nParallel lines: \n";
		for(auto &i : parallelLines) {
			i.toString();
		}
		cout << "\n";
	}

	// Time complexity: O(n^2)
	int count = 0;
	for(int i = 0; i < parallelLines.size(); ++i) {
		for (int j = i+1; j < parallelLines.size(); ++j) {
			if(parallelLines[i].isSquare(parallelLines[j])) {
				count++;
				if(IS_PRINT_LOGS) {
					cout << "is a square!\n";
				}
			}
			if(IS_PRINT_LOGS) {
				cout << "\n";
			}
		}
	}

	return count;
}

// int main(int argc, char** argv) {
	// // Initialize points
	// Point p1 { 0.0, 0.0 };
	// Point p2 { 0.0, 1.0 };

	// Point p3 { 1.0, 0.0 };
	// Point p4 { 1.0, 1.0 };

	// Point p5 { 0.0, 0.0 };
	// Point p6 { 1.0, 0.0 };

	// Point p7 { 0.0, 1.0 };
	// Point p8 { 1.0, 1.0 };

	// Point p9  { 0.0, 1.0 };
	// Point p10 { 1.0, 0.0 };

	// Point p11 { -1.0, 0.0 };
	// Point p12 { 0.0, -1.0 };

	// Point p13 { -1.0, 0.0 };
	// Point p14 { 0.0, 1.0 };

	// Point p15 { 0.0, -1.0 };
	// Point p16 { 1.0, 0.0 };

	// Point p17 { 0.5, -2.0 };
	// Point p18 { 0.5, 2.0 };

	// Point p19 { -2.0, 0.5 };
	// Point p20 { 2.0, 0.5 };

	// // Lines l1 and l2 are parallel lines p1
	// Line l1 { p1, p2 };
	// Line l2 { p3, p4 };

	// // Lines l3 and l4 are parallel lines p2
	// Line l3 { p5, p6 };
	// Line l4 { p7, p8 };

	// // Lines l5 and l6 are parallel lines p3
	// Line l5 { p9, p10 };
	// Line l6 { p11, p12 };

	// Lines l7 and l8 are parallel lines p4
	// Line l7 { p13, p14 };
	// Line l8 { p15, p16 };

	// Line l9 { p17, p18 };
	// Line l10 { p19, p20 };

	// // Parallel lines p1 and p2 form a square
	// // Parallel lines p3 and p4 form a square
	// vector<Line> lines1 { l1, l2, l3, l4, l5, l6, l7, l8 };
	// vector<Line> lines2 { l1, l2, l3, l4, l9, l10 };

	// cout << "Total number of squares for lines1: " << countSquares(lines1) << "\n";
	// cout << "Total number of squares for lines2: " << countSquares(lines2) << "\n";

	// return 0;
// }
