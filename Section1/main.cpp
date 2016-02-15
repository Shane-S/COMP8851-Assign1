#include <iostream>
#include <vector>
#include "Rectangle.hpp"

#define NUM_RECTS (10)
#define MAX_DIM 400
#define MIN_DIM 50

using std::vector;

/**
 * Finds the maximum object using the given Comparator.
 *
 */
template<typename Object, typename Comparator>
const Object& findMax(const vector<Object>& list, Comparator& cmp) {
	if (list.size() == 1) return list[0];

	const Object* max = &list[0];
	for (auto& obj : list) {
		if (cmp(*max, obj) < 0) {
			max = &obj;
		}
	}
	return *max;
}

class RectangleAreaCmp {
public:
	int operator()(const Rectangle& lhs, const Rectangle& rhs) {
		long lhArea = lhs.getLength() * lhs.getWidth();
		long rhArea = rhs.getLength() * rhs.getWidth();
		return lhArea - rhArea;
	}
};

class RectanglePerimeterCmp {
public:
	int operator()(const Rectangle& lhs, const Rectangle& rhs) {

		long lhPerim = lhs.getLength() * 2 + lhs.getWidth() * 2;
		long rhPerim = rhs.getLength() * 2 + rhs.getWidth() * 2;
		return lhPerim - rhPerim;
	}
};

/**
 * Returns a random int in the specified range.
 * Precondition: min < max <= RAND_MAX
 */
int randInRange(int min, int max) {
	int range = max - min;
	return ((std::rand() * (range + 1)) / RAND_MAX) + min;
}

int main() {
	// Question 1.15
	// Randomly generate list of rectangles
	std::vector<Rectangle> rects{ Rectangle(20, 20), Rectangle(200, 1), Rectangle(15, 15) };

	// Find largest rectangle using area
	RectangleAreaCmp areaComp;
	const Rectangle& maxArea = findMax<Rectangle, RectangleAreaCmp>(rects, areaComp);
	std::cout << std::endl;
	std::cout << "Largest: len " << maxArea.getLength() << ", w " << maxArea.getWidth() << " (area: " << maxArea.getLength() * maxArea.getWidth() << ")" << std::endl;

	// Find largest rectangle using perimeter
	RectanglePerimeterCmp perimComp;
	const Rectangle& maxPerim = findMax<Rectangle, RectanglePerimeterCmp>(rects, perimComp);
	std::cout << std::endl;
	std::cout << "Largest: len " << maxPerim.getLength() << ", w " << maxPerim.getWidth() << " (perimeter: " << maxPerim.getLength() * 2 + maxPerim.getWidth() * 2 << ")" << std::endl;
	std::cin.get();

	// Question 1.16: See Matrix.hpp
	return 0;
}