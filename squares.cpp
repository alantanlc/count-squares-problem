#include <iostream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

class Point {
public:
	int x, y;

	Point() {}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

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
		string isParallel = ((this->getGradient() - l.getGradient() < numeric_limits<double>::epsilon())) ? "true" : "false";
		cout << "isParallel(): gradients = (" << this->getGradient() << ", " << l.getGradient() << "), parallel = " << isParallel << "\n";

		return (this->getGradient() - l.getGradient() < numeric_limits<double>::epsilon());
	}

	// Computes gradient of this line
	double getGradient() {
		if(this->p2.x - this->p1.x > numeric_limits<double>::epsilon()) {
			// cout << (double) (this->p2.y - this->p1.y) / (double) (this->p2.x - this->p1.x);
			return (double) (this->p2.y - this->p1.y) / (double) (this->p2.x - this->p1.x);
		}

		return numeric_limits<double>::max();
	}
};

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
		if(this->isPerpendicular(p) && this->hasSamePerpendicularDistanceBetweenLines(p)) {
			return true;
		}

		return false;
	}

	// Checks if this pair of parallel lines and given pair of parallel lines
	// are perpendicular
	bool isPerpendicular(ParallelLines p) {
		// If lines are perpendicular, then gradient g1 * g2 equals -1
		return (this->l1.getGradient() * p.l1.getGradient() + 1.0) > numeric_limits<double>::epsilon();
	}

	// Checks if the 2 sets of parallel lines has same perpendicular distance between their lines l1 and l2.
	bool hasSamePerpendicularDistanceBetweenLines(ParallelLines p) {
		// For each pair of parallel lines, compute perpendicular distance between lines l1 and l2.
		// Check if the perpendicular distances are the same for the two pairs of parallel lines.
		return (this->getPerpendicularDistance() - p.getPerpendicularDistance()) < numeric_limits<double>::epsilon();
	}

	// Compute perpendicular distance between lines l1 and l2
	double getPerpendicularDistance() {
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
	Point p1 { 0, 0 };
	Point p2 { 0, 1 };

	Point p3 { 1, 0 };
	Point p4 { 1, 1 };

	Point p5 { 0, 0 };
	Point p6 { 1, 0 };

	Point p7 { 0, 1 };
	Point p8 { 1, 1 };

	Line l1 { p1, p2 };
	Line l2 { p3, p4 };

	Line l3 { p5, p6 };
	Line l4 { p7, p8 };

	vector<Line> lines { l1, l2, l3, l4 };

	cout << "Find parallel lines: \n";
	vector<ParallelLines> parallelLines = findParallelLines(lines);
	cout << "\n";

	cout << "Parallel lines: \n";
	for(auto &i : parallelLines) {
		i.toString();
	}
	cout << "\n";

	int numOfSquares = findSquares(parallelLines);
	cout << "Number of squares: " << numOfSquares;

	return 0;
}