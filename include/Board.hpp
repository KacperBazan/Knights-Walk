#pragma once
#include "Knight.hpp"

using vec2_t = std::array<int, 2>;

class Board
{
private:
	int m_cols{};	 // Number of collumns.
	int m_rows{};	 // Number of rows.
	bool** m_grid{}; // Multi-dimensional array that will hold bools.

public:
	Board(int cols = 8, int rows = 8);

	/* Returns the stepped/not stepped state of the board at that position. */
	bool& operator()(vec2_t pos);

	/* Sets the stepped/not stepped state of the board at that position. */
	void setState(vec2_t pos, bool b);

	const int cols() const { return m_cols; } // Return number of collumns.
	const int rows() const { return m_rows; } // Return number of rows.

	~Board();
};