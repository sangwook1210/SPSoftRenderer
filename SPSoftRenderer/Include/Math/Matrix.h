#pragma once

#include <stdexcept>
#include <initializer_list>

#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

// 열벡터 사용
template<size_t Rows,size_t Cols>
struct Matrix
{
	float values[Rows][Cols] = {};

#pragma region 생성자
	Matrix() 
	{
		Clear();
	}

	Matrix(const float* input, const size_t size, bool isRowMajor = true)
	{
		if (size != Rows * Cols)
		{
			throw std::invalid_argument("Matrix size mismatch");
		}

		size_t index = 0;

		// 행의 순서대로 입력이 들어올 경우
		if (isRowMajor)
		{
			for (size_t r = 0; r < Rows; r++)
			{
				for (size_t c = 0; c < Cols; c++)
				{
					values[r][c] = input[index];
					index++;
				}
			}
		}
		// 열의 순서대로 입력이 들어올 경우
		else
		{
			for (size_t c = 0; c < Cols; c++)
			{
				for (size_t r = 0; r < Rows; r++)
				{
					values[r][c] = input[index];
					index++;
				}
			}
		}

	}
	Matrix(const std::initializer_list<float> input,  bool isRowMajor = true)
	{
		if (input.size() != Rows * Cols)
		{
			throw std::invalid_argument("Matrix size mismatch");
		}

		auto* it = input.begin();

		// 행의 순서대로 입력이 들어올 경우
		if (isRowMajor)
		{
			for (size_t r = 0; r < Rows; r++)
			{
				for (size_t c = 0; c < Cols; c++)
				{
					values[r][c] = *it;
					++it;
				}
			}
		}
		// 열의 순서대로 입력이 들어올 경우
		else
		{
			for (size_t c = 0; c < Cols; c++)
			{
				for (size_t r = 0; r < Rows; r++)
				{
					values[r][c] = *it;
					++it;
				}
			}
		}
	}

	Matrix(Vector2 a, Vector2 b)
	{
		static_assert(Rows == 2 && Cols == 2);

		values[0][0] = a.x;
		values[1][0] = a.y;

		values[0][1] = b.x;
		values[1][1] = b.y;
	}
	Matrix(Vector3 a, Vector3 b, Vector3 c)
	{
		static_assert(Rows == 3 && Cols == 3);

		values[0][0] = a.x;
		values[1][0] = a.y;
		values[2][0] = a.z;

		values[0][1] = b.x;
		values[1][1] = b.y;
		values[2][1] = b.z;

		values[0][2] = c.x;
		values[1][2] = c.y;
		values[2][2] = c.z;
	}
	Matrix(Vector4 a, Vector4 b, Vector4 c, Vector4 d)
	{
		static_assert(Rows == 4 && Cols == 4);

		values[0][0] = a.x;
		values[1][0] = a.y;
		values[2][0] = a.z;
		values[3][0] = a.w;

		values[0][1] = b.x;
		values[1][1] = b.y;
		values[2][1] = b.z;
		values[3][1] = b.w;

		values[0][2] = c.x;
		values[1][2] = c.y;
		values[2][2] = c.z;
		values[3][2] = c.w;

		values[0][3] = d.x;
		values[1][3] = d.y;
		values[2][3] = d.z;
		values[3][3] = d.w;
	}

	Matrix(Vector2 colVec)
	{
		static_assert(Rows <= 4 && Rows >= 2 && Cols == 1);

		for (size_t r = 0; r < Rows; r++)
		{
			values[r][0] = r == 0 ? colVec.x :
				r == 1 ? colVec.y :
				1.0f;
		}
	}
	Matrix(Vector3 colVec)
	{
		static_assert(Rows <= 4 && Rows >= 3 && Cols == 1);

		for (size_t r = 0; r < Rows; r++)
		{
			values[r][0] = r == 0 ? colVec.x :
				r == 1 ? colVec.y :
				r == 2 ? colVec.z :
				1.0f;
		}
	}
	Matrix(Vector4 colVec)
	{
		static_assert(Rows == 4 && Cols == 1);

		values[0][0] = colVec.x;
		values[1][0] = colVec.y;
		values[2][0] = colVec.z;
		values[3][0] = colVec.w;
	}
#pragma endregion

#pragma region 연산
	
	// 행렬곱
	template<size_t Rows_r, size_t Cols_r>
	Matrix<Rows, Cols_r> operator*(const Matrix<Rows_r, Cols_r>& right) const
	{
		static_assert(Cols == Rows_r);

		float results[Rows * Cols_r] = {};

		for (size_t r = 0; r < Rows; r++)
		{
			for (size_t c = 0; c < Cols_r; c++)
			{
				float value = 0;
				for (int i = 0; i < Cols; i++) {

					value += values[r][i] * right.values[i][c];
				}

				results[r * Cols_r + c] = value;
			}
		}

		return Matrix<Rows, Cols_r>(results, sizeof(results) / sizeof(results[0]));
	}// 행렬합
	template<size_t Rows_r, size_t Cols_r>
	Matrix<Rows, Cols> operator+(const Matrix<Rows_r, Cols_r>& right) const
	{
		static_assert((Rows == Rows_r) && (Cols == Cols_r));

		float results[Rows * Cols] = {};

		for (size_t r = 0; r < Rows; r++)
		{
			for (size_t c = 0; c < Cols; c++)
			{
				results[r * Cols + c] = values[r][c] + right.values[r][c];
			}
		}

		return Matrix<Rows, Cols>(results, sizeof(results) / sizeof(results[0]));
	}


	// 스칼라곱
	Matrix<Rows, Cols>& Scale(float scalar)
	{
		for (int r = 0; r < Rows; r++)
		{
			for (int c = 0; c < Cols; c++)
			{
				values[r][c] *=scalar;
			}
		}

		return *this;
	}
	Matrix<Rows, Cols> Scaled(float scalar)
	{
		Matrix<Rows, Cols> scaled;

		for (int r = 0; r < Rows; r++)
		{
			for (int c = 0; c < Cols; c++)
			{
				scaled.values[r][c] = values[r][c] * scalar;
			}
		}

		return scaled;
	}

	// 자신을 전치
	// 단, 정방행렬만
	Matrix<Cols, Rows>& Transpose()
	{
		static_assert(Rows == Cols);

		for (size_t r = 0; r < Rows; r++)
		{
			for (size_t c = r + 1; c < Cols; c++)
			{
				std::swap(values[r][c], values[c][r]);
			}
		}

		return *this;
	}

	// 전치시킨 행렬 반환
	Matrix<Cols, Rows> Transposed()
	{
		Matrix<Cols, Rows> transposed;
		
		for (size_t r = 0; r < Rows; r++)
		{
			for (size_t c = 0; c < Cols; c++)
			{
				transposed.values[c][r] = values[r][c];
			}
		}

		return transposed;
	}


	// 행렬식
	float Determinant()
	{
		static_assert(Rows == Cols);
		
		if constexpr (Cols == 1)
		{
			return values[0][0];
		}

		else if constexpr (Cols == 2)
		{
			return values[0][0] * values[1][1]
				- values[0][1] * values[1][0];
		}

		else
		{
			float determinant = 0;

			for (size_t subMatrixIdx = 0; subMatrixIdx < Cols; subMatrixIdx++)
			{
				float subValues[(Rows - 1) * (Cols - 1)] = {};
				size_t subValueIdx = 0;

				for (size_t r = 0; r < Rows; r++)
				{
					for (size_t c = 0; c < Cols; c++)
					{
						if (r == 0 || c == subMatrixIdx)
							continue;

						subValues[subValueIdx++] = values[r][c];
					}
				}

				determinant += (subMatrixIdx % 2 == 0 ? 1.0f : -1.0f) * values[0][subMatrixIdx]
					* Matrix<Rows - 1, Cols - 1>(subValues, sizeof(subValues) / sizeof(subValues[0])).Determinant();
			}

			return determinant;
		}
	}

#pragma endregion


	void Clear(float value = 0.0f)
	{
		for (size_t r = 0; r < Rows; r++)
		{
			for (size_t c = 0; c < Cols; c++)
			{
				values[r][c] = value;
			}
		}
	}
};

using Matrix2x2 = Matrix<2, 2>;
using Matrix3x3 = Matrix<3, 3>;
using Matrix4x4 = Matrix<4, 4>;

using Matrix2x1 = Matrix<2, 1>;
using Matrix3x1 = Matrix<3, 1>;
using Matrix4x1 = Matrix<4, 1>;

template<size_t Rows, size_t Cols>
std::ostream& operator<<(std::ostream& os, const Matrix<Rows, Cols>& matrix)
{
	os << "\n";

	// os << "Row: " << Rows << "Col: " << Cols << "\n";

	for (size_t r = 0; r < Rows; r++)
	{
		for (size_t c = 0; c < Cols; c++)
		{
			os << matrix.values[r][c] << " ";
		}
		os << "\n";
	}

	return os;
}