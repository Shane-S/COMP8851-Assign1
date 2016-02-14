#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

template <typename Object>
class Matrix
{
public:

	// Zero-arg constructor in case this should be necessary
	Matrix()
		: _array()
	{

	}

	Matrix(int rows, int cols) : _array(rows)
	{
		for (auto& thisRow : _array)
			thisRow.resize(cols);
	}

	Matrix(vector<vector<Object>> v) : _array{ v }
	{ }
	Matrix(vector<vector<Object>> && v) : _array{ std::move(v) }
	{ }

	const vector<Object> & operator[](int row) const
	{
		return _array[row];
	}

	vector<Object> & operator[](int row)
	{
		return _array[row];
	}

	int numrows() const
	{
		return _array.size();
	}

	int numcols() const
	{
		return numrows() ? _array[0].size() : 0;
	}

	// Resize the vector of rows and each row it contains
	void resize(int rows, int cols) {
		_array.resize(rows);
		for (auto& row : _array) {
			row.resize(cols);
		}
	}

private:
	vector<vector<Object>> _array;
};
#endif