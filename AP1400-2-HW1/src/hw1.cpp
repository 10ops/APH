#include "hw1.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace algebra
{
Matrix create_Matrix(std::size_t n, std::size_t m) {
	Matrix obj(n);
	for (std::size_t i = 0; i < obj.size(); i++) {
		obj[i].resize(m);
	}

	return obj;
}

Matrix Matrix_set_val(std::size_t n, std::size_t m, double value) {
	Matrix obj = create_Matrix(n, m);

	for (std::size_t i = 0; i < obj.size(); i++) {
		for (std::size_t j = 0; j < obj[i].size(); j++) {
			obj[i][j] = value;
		}
	}
	return obj;
}


/*
 * Function: zeros
 * create a 'n x m' matrix with all elements equal to zero
 */
Matrix zeros(std::size_t n, std::size_t m) {
	return Matrix_set_val(n, m, 0);
}


/* 
 * Function: ones
 * create a 'n x m' matrix with all elements equal to one
 */
Matrix ones(std::size_t n, std::size_t m) {
	return Matrix_set_val(n, m, 1);
}


/*
 * Function: random
 * create a 'n x m' matrix with all elements a random number between 'min' and 'max'
 */
Matrix random(std::size_t n, std::size_t m, double min, double max) {
	if (max < min) {
		throw std::logic_error("wrong input, max must greater than min");
	}
	int offset = max - min;
	Matrix obj = create_Matrix(n, m);
	
	if (offset != 0) {
		for (std::size_t i = 0; i < obj.size(); i++) {
			for (std::size_t j = 0; j < obj[i].size(); j++) {
				obj[i][j] = rand()%offset + min;
			}
		}
	} else {
		obj = Matrix_set_val(n, m, min);
	}
	
	return obj;
}


/*
 * Function: show
 * display the matrix in a beautiful way
 */
void show(const Matrix& matrix) {
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			std::cout << std::right << std::setw(5) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


/*
 * Function: multiply (scalar number)
 * it multiply the matrix into the constant scalar 'c'
 */
Matrix multiply(const Matrix &matrix, double c) {
	Matrix obj = create_Matrix(matrix.size(), matrix[0].size());

	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			obj[i][j] = matrix[i][j] * c;
		}
	}

	return obj;
}


/*
 * Function: multiply (matrix)
 * it multiplies the 'matrix1' into 'matrix2'
 */
Matrix multiply(const Matrix &matrix1, const Matrix &matrix2) {
/* 
	if (matrix1.size() == 0 || matrix2.size() == 0 ||
			matrix1[0].size() == 0 || matrix2[0].size() == 0) {
		throw std::logic_error("Empty Matrix");
	}
*/
	if (matrix1.size() == 0 || matrix2.size() == 0) {
		Matrix emp = create_Matrix(0, 0);
		return emp;
	}
	if (matrix1.size() != 0 && matrix1[0].size() != matrix2.size()) {
		throw std::logic_error("Error");
	}

	Matrix obj = zeros(matrix1.size(), matrix2[0].size());
	for (std::size_t i = 0; i < matrix1.size(); i++) {
		for (std::size_t j = 0; j < matrix2[0].size(); j++) {
			for (std::size_t k = 0; k < matrix1[i].size(); k++) {
				obj[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	
	return obj;
}


/*
 * Function: sum (scalar number)
 * adds the constant number 'c' to every element of 'matrix'
 */
Matrix sum(const Matrix &matrix, double c) {
	Matrix obj = matrix;
	if (obj.size() == 0) {
		return obj;
	}

	for (std::size_t i = 0; i < obj.size(); i++) {
		for (std::size_t j = 0; j < obj[i].size(); j++) {
			obj[i][j] += c;
		}
	}

	return obj;
}


/*
 * Function: sum (matrix)
 * adds 2 matrixces to each other
 */
Matrix sum(const Matrix &matrix1, const Matrix &matrix2) {
	if (matrix1.size() == 0 && matrix2.size() == 0) {
		Matrix m2 = matrix2;
		return m2;
	}
	if (matrix1.size() == 0 || matrix2.size() == 0) {
		throw std::logic_error("Error");
	}
	if (matrix1.size() != matrix2.size() && matrix1[0].size() != matrix2[0].size()) {
		throw std::logic_error("Error");
	}

	Matrix obj = create_Matrix(matrix1.size(), matrix1[0].size());
	for (std::size_t i = 0; i < matrix1.size(); i++) {
		for (std::size_t j = 0; j < matrix1[i].size(); j++) {
			obj[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	
	return obj;
}


/*
 * Function: transpose
 * generate the transpose matrix of the input 'matrix'
 */
Matrix transpose(const Matrix &matrix) {
	int n, m;
	if (matrix.size() == 0) { // throw a logic error 	throw std::logic_error("Error");
		n = 0;
		m = 0;
	} else {
		n = matrix.size();
		m = matrix[0].size();
	}

	Matrix obj = create_Matrix(m, n);
	for (std::size_t i = 0; i < n; i++) {
		for (std::size_t j = 0; j < m; j++) {
			obj[j][i] = matrix[i][j];
		}
	}

	return obj;
}


/*
 * Function: minor
 * create the minor of the input 'matrix' with respect to nth row and mth column
 */
Matrix minor(const Matrix &matrix, std::size_t n, std::size_t m) {
	if (n >= matrix.size() || m >= matrix[0].size()) { // throw a logic error 
		throw std::logic_error("Error");
	}

	Matrix obj = create_Matrix(matrix.size()-1, matrix[0].size()-1);
	
	for (std::size_t i = 0; i < n; i++) {
		for (std::size_t j = 0; j < m; j++) {
			obj[i][j] = matrix[i][j];
		} 

		for (std::size_t j = m+1; j < matrix[i].size(); j++) {
			obj[i][j-1] = matrix[i][j];
		}
	}

	for (std::size_t i = n+1; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < m; j++) {
			obj[i-1][j] = matrix[i][j];
		} 
		for (std::size_t j = m+1; j < matrix[i].size(); j++) {
			obj[i-1][j-1] = matrix[i][j];
		}
	}

	return obj;
}


/*
 * Function: determinant
 * calculates the determinant of the input 'matrix'
 */
double determinant(const Matrix &matrix) {
	if (matrix.size() == 0) {
		return 1;
	}
	if (matrix.size() != matrix[0].size()) {
		// throw a logic error
		throw std::logic_error("Error");
	}
	if (matrix.size() == 1) {
		return matrix[0][0];
	}
	else {
		std::vector<double> midVal(matrix.size());
		double result = 0;
		for (std::size_t i = 0; i < matrix.size(); i++) {
			Matrix mid = minor(matrix, 0, i);
			midVal[i] = determinant(mid);
			if (i % 2 == 1) {
				midVal[i] *= -1;
			}
		}
		for (std::size_t i = 0; i < matrix.size(); i++) {
			result += matrix[0][i] * midVal[i];
		}
		return result;
	}
}


/*
 * Function: inverse
 * generate the matrix's inverse
 */
Matrix inverse(const Matrix &matrix) {
	if (matrix.size() == 0) {
		Matrix m = matrix;
		return m;
	}
	double det = determinant(matrix);
	if (det == 0.0) {
		// throw a logic error
		throw std::logic_error("Error");
	}
	
	Matrix obj = create_Matrix(matrix.size(), matrix[0].size());
	
	// calculate inverse matrix algorithm
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			obj[j][i] = determinant(minor(matrix, i, j)) * (1 / det);
		}
	}

	return obj;
}


/*
 * Function: concatenate
 * concatenate matrix1 and matrix2 along the specified axis
 * (axis=0: on top of each other | axis=1: alongside each other)
 */
Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis) {
	// Implement
	Matrix obj;
	if (axis == 0) {
		if (matrix1[0].size() != matrix2[0].size()) {
			throw std::logic_error("Error");
		}
		obj = create_Matrix(matrix1.size() + matrix2.size(), matrix1[0].size());
		for (std::size_t i = 0; i < matrix1[0].size(); i++) {
			for (std::size_t j = 0; j < matrix1.size(); j++) {
				obj[j][i] = matrix1[j][i];
			}
			for (std::size_t j = 0; j < matrix2.size(); j++) {
				obj[j + matrix1.size()][i] = matrix2[j][i];
			}
		}
	}
	else if (axis == 1) {
		if (matrix1.size() != matrix2.size()) {
			throw std::logic_error("Error");
		}
		obj = create_Matrix(matrix1.size(), matrix1[0].size() + matrix2[0].size());
		for (std::size_t i = 0; i < matrix1.size(); i++) {
			for (std::size_t j = 0; j < matrix1[i].size(); j++) {
				obj[i][j] = matrix1[i][j];
			}
			for (std::size_t j = 0; j < matrix2[i].size(); j++) {
				obj[i][j + matrix1[i].size()] = matrix2[i][j];
			}
		}
	}
	else {
		throw std::logic_error("Error");
	}

	return obj;
}


/*
 * Function: ero_swap
 * swapping two rows
 */
Matrix ero_swap(const Matrix &matrix, size_t r1, size_t r2) {
	if (r1 >= matrix.size() || r2 >= matrix.size()) {
		throw std::logic_error("Error");
	}

	Matrix obj = create_Matrix(matrix.size(), matrix[0].size());
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			obj[i][j] = matrix[i][j];
		}
	}
	for (std::size_t j = 0; j < matrix[0].size(); j++) {
		double val = obj[r1][j];
		obj[r1][j] = obj[r2][j];
		obj[r2][j] = val;
	}
	return obj;
}


/*
 * Function: ero_multiply
 * multiplies every element in rth row with constant number c
 */
Matrix ero_multiply(const Matrix &matrix, size_t r, double c) {

	Matrix obj = create_Matrix(matrix.size(), matrix[0].size());
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			obj[i][j] = matrix[i][j];
			if (i == r) { 
				obj[i][j] *= c;
			}
		}
	}

	return obj;
}


/*
 * Function: ero_sum
 * adds r1th x c row into r2th row
 */
Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2) {

	Matrix obj = create_Matrix(matrix.size(), matrix[0].size());
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix[i].size(); j++) {
			obj[i][j] = matrix[i][j];
			if (i == r2) {
				obj[i][j] += matrix[r1][j] * c;
			}
		}
	}

	return obj;
}


/*
 * Function: upper_triangular
 * calculate the upper triangular form of the matrix using the ERO operations
 */
Matrix upper_triangular(const Matrix &matrix) {
	if (matrix.size() == 0) {
		Matrix m = matrix;
		return m;
	}
	if (matrix.size() != matrix[0].size()) {
		throw std::logic_error("Error");
	}
	
	// copy matrix
	Matrix obj = create_Matrix(matrix.size(), matrix.size());
	for (std::size_t i = 0; i < matrix.size(); i++) {
		for (std::size_t j = 0; j < matrix.size(); j++) {
			obj[i][j] = matrix[i][j];
		}
	}

	// calculate
	for (std::size_t i = 0; i < matrix.size(); i++) {
		std::size_t r = i + 1;
		// main diagonal is not zero
		while (r < matrix.size() && obj[i][i] == 0.0) {
			obj = ero_swap(obj, 0, r);
			r++;
		}
		for (std::size_t j = r; j < matrix.size(); j++) {
			obj = ero_sum(obj, i, (-1) * obj[j][i]/obj[i][i], j);
		}
	}
	
	return obj;
}

}





