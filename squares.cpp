#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <cmath>

using namespace std;

// A Point (aka coordinate) is defined as a pair of doubles (x, y)
class Point {
public:
	double x, y;

	Point() {}

	Point(double x, double y) {
		this->x = x;
		this->y = y;
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
		string isParallel = 
			(abs(this->getGradient() - l.getGradient()) < numeric_limits<double>::epsilon()) ? "true" : "false";
		cout << "isParallel(): gradients = (" << this->getGradient() 
			<< ", " << l.getGradient() << "), parallel = " << isParallel << "\n";

		return (abs(this->getGradient() - l.getGradient()) < numeric_limits<double>::epsilon());
	}

	// Checks if this line is vertical
	bool isVertical() {
		return abs(this->getGradient() - numeric_limits<double>::max()) < numeric_limits<double>::epsilon();
	}

	// Checks if this line is horizontal
	bool isHorizontal() {
		return abs(this->getGradient()) < numeric_limits<double>::epsilon();
	}

	// Computes gradient of this line
	double getGradient() {
		// gradient = (y2 - y1) / (x2 - x1);
		if(abs(this->p2.x - this->p1.x) > numeric_limits<double>::epsilon()) {
			return (double) (this->p2.y - this->p1.y) / (double) (this->p2.x - this->p1.x);
		}

		// if x2 - x1 equals zero, return "infinity"
		return numeric_limits<double>::max();
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
		return this->isPerpendicular(p) && this->hasSamePerpendicularDistanceBetweenLines(p);
	}

	// Checks if this pair of parallel lines and given pair of parallel lines
	// are perpendicular
	bool isPerpendicular(ParallelLines p) {
		// If lines are perpendicular, then gradient g1 * g2 equals -1
		// or if one Line l1 is vertical while the other is horizontal, vice versa
		return abs(this->l1.getGradient() * p.l1.getGradient() + 1.0) < numeric_limits<double>::epsilon()
			|| this->l1.isVertical() && p.l1.isHorizontal()
			|| this->l1.isHorizontal() && p.l1.isVertical();
	}

	// Checks if the 2 sets of parallel lines has same perpendicular distance between their lines l1 and l2.
	bool hasSamePerpendicularDistanceBetweenLines(ParallelLines p) {
		// For each pair of parallel lines, compute perpendicular distance between lines l1 and l2.
		// Check if the perpendicular distances are the same for the two pairs of parallel lines.
		return abs(this->getPerpendicularDistance() - p.getPerpendicularDistance()) < numeric_limits<double>::epsilon();
	}

	// Compute perpendicular distance between lines l1 and l2
	double getPerpendicularDistance() {
		// HELP!
		// Need to compute perpendicular distance between this->l1 and this->l2
		// ...

		return 0;
	}

	toString() {
		cout << "[(";
		cout << l1.p1.x << ", " << l1.p1.y << "), (" << l1.p2.x << ", " << l1.p2.y;
		cout << ")], [(";
		cout << l2.p1.x << ", " << l2.p1.y << "), (" << l2.p2.x << ", " << l2.p2.y;
		cout << ")]";
		cout << endl;
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

// Find all squares given a vector of parallel lines
int findSquares(vector<ParallelLines> parallelLines) {
	int count = 0;

	// Time complexity: O(n^2)
	for(int i = 0; i < parallelLines.size(); ++i) {
		for (int j = i+1; j < parallelLines.size(); ++j) {
			if(parallelLines[i].isSquare(parallelLines[j])) {
				count++;
			}
		}
	}

	return count;
}

int main(int argc, char** argv) {
	// Initialize points
	Point p1 { 0.0, 0.0 };
	Point p2 { 0.0, 1.0 };
	Point p3 { 1.0, 0.0 };
	Point p4 { 1.0, 1.0 };

	Point p5 { 0.0, 0.0 };
	Point p6 { 1.0, 0.0 };
	Point p7 { 0.0, 1.0 };
	Point p8 { 1.0, 1.0 };

	Point p9  { 0.0, 1.0 };
	Point p10 { 1.0, 0.0 };
	Point p11 { -1.0, 0.0 };
	Point p12 { 0.0, -1.0 };

	Point p13 { -1.0, 0.0 };
	Point p14 { 0.0, 1.0 };
	Point p15 { 0.0, -1.0 };
	Point p16 { 1.0, 0.0 };

	// Lines l1 and l2 are parallel lines p1
	Line l1 { p1, p2 };
	Line l2 { p3, p4 };

	// Lines l3 and l4 are parallel lines p2
	Line l3 { p5, p6 };
	Line l4 { p7, p8 };

	// Lines l5 and l6 are parallel lines p3
	Line l5 { p9, p10 };
	Line l6 { p11, p12 };

	// Lines l7 and l8 are parallel lines p4
	Line l7 { p13, p14 };
	Line l8 { p15, p16 };

	// Initialize lines
	// Parallel lines p1 and p2 form a square
	// Parallel lines p3 and p4 form a square
	vector<Line> lines { l1, l2, l3, l4, l5, l6, l7, l8 };

	// Find all pairs of parallel lines
	cout << "Find parallel lines: \n";
	vector<ParallelLines> parallelLines = findParallelLines(lines);
	cout << "\n";

	// Print details of parallel lines
	cout << "Parallel lines: \n";
	for(auto &i : parallelLines) {
		i.toString();
	}
	cout << "\n";

	// Find all possible squares given a set of parallel lines
	int numOfSquares = findSquares(parallelLines);
	cout << "Number of squares: " << numOfSquares;

	return 0;
}