#pragma once

class Rectangle {
public:

	/**
	 * Creates a new Rectangle with the specified dimensions.
	 *
	 * @param length: The length of the rectangle.
	 * @param width: The width of the rectangle.
	 */
	Rectangle(const int length, const int width)
		: _length(length), _width(width) {

	}

	inline int getLength() const { return _length; }
	inline int getWidth() const { return _width; }

private:
	int _length;
	int _width;
};