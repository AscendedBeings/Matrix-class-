#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

#define accurate_threshold 0.0000001	//Set threshold
#define element_width 15				//Set width for show matrix element

template <typename T>
class Matrix
{
private:
	T **data;		//record matrix data
	int raws;		//matrix raws
	int cols;		//matrix cols
		
	void remove_raw(int parameter);
	void remove_col(int parameter);
public:
	Matrix();
	Matrix(int r, int c, T default_value = 0);
	Matrix(int r, int c, T **array);
	~Matrix();
	void inilization(int r, int c, T **array);
	double det(const Matrix &parameter);		//calcurate det of square matrix
	Matrix<T> & transpose();	
	Matrix<T> & adjugate();
	Matrix<T> & inverse();

	Matrix<T> & operator =(const Matrix<T> &parameter);
	Matrix<T> & operator +(const Matrix<T> &parameter);
	Matrix<T> & operator -(const Matrix<T> &parameter);
	Matrix<T> & operator *(const Matrix<T> &parameter);

	Matrix<T> & operator +(const double &parameter);
	Matrix<T> & operator -(const double &parameter);
	Matrix<T> & operator *(const double &parameter);

	bool operator ==(const Matrix<T> &parameter);
	bool operator !=(const Matrix<T> &parameter);

	void show_matrix(bool approximate = true);
	//show the matrix in the screen, when parameter is true: the element value of matrix will be zero when the
	//element less than threshold; when parameter is false, will show the accurate value.
};

template <typename T>
inline void Matrix<T>::remove_raw(int parameter)
{
	if (parameter<1 || parameter>raws)
	{
		cout << "out of size" << endl;
	}
	else
	{
		T **temp;
		temp = new T*[raws - 1];
		for (int i = 0; i < raws - 1; i++)
		{
			temp[i] = new T[cols];
		}
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (i < parameter - 1)
				{
					temp[i][j] = data[i][j];
				}
				else if (i == parameter - 1)
				{
					continue;
				}
				else
				{
					temp[i - 1][j] = data[i][j];
				}
			}
		}
		delete[] data;
		inilization(raws - 1, cols, temp);
	}
}

template <typename T>
inline void Matrix<T>::remove_col(int parameter)
{
	if (parameter<1 || parameter>cols)
	{
		cout << "out of size" << endl;
	}
	else
	{
		T **temp;
		temp = new T*[raws];
		for (int i = 0; i < raws; i++)
		{
			temp[i] = new T[cols - 1];
		}
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (j < parameter - 1)
				{
					temp[i][j] = data[i][j];
				}
				else if (j == parameter - 1)
				{
					continue;
				}
				else
				{
					temp[i][j - 1] = data[i][j];
				}
			}
		}
		delete[] data;
		inilization(raws, cols - 1, temp);
	}
}

template <typename T>
Matrix<T>::Matrix()
{
	raws = 2;
	cols = 2;
	data = new T*[raws];
	for (int i = 0; i < raws; i++)
	{
		data[i] = new T[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = 0;
		}
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	raws = 0;
	cols = 0;
	delete[] data;
}

template <typename T>
Matrix<T>::Matrix(int r, int c, T default_value)
{
	raws = r;
	cols = c;
	data = new T*[raws];
	for (int i = 0; i < raws; i++)
	{
		data[i] = new T[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = default_value;
		}
	}
}

template <typename T>
Matrix<T>::Matrix(int r, int c, T **array)
{
	raws = r;
	cols = c;
	data = new T*[raws];
	for (int i = 0; i < raws; i++)
	{
		data[i] = new T[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = array[i][j];
		}
	}
}

template <typename T>
void Matrix<T>::inilization(int r, int c, T **array)
{
	raws = r;
	cols = c;
	data = new T*[raws];
	for (int i = 0; i < raws; i++)
	{
		data[i] = new T[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = array[i][j];
		}
	}
}

template <typename T>
Matrix<T> & Matrix<T>::transpose()
{
	static Matrix<T> temp(cols, raws);
	temp.data = new T*[temp.raws];
	for (int i = 0; i < temp.raws; i++)
	{
		temp.data[i] = new T[temp.cols];
	}
	for (int i = 0; i < temp.raws; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{
			temp.data[i][j] = data[j][i];
		}
	}
	return temp;
}


template <typename T>
Matrix<T> & Matrix<T>::adjugate()
{
	static Matrix<T> result;
	if (result.data != nullptr)
	{
		delete[] result.data;
	}
	result.raws = raws;
	result.cols = cols;
	result.data = new T*[raws];
	for (int i = 0; i < result.raws; i++)
	{
		result.data[i] = new T[result.cols];
	}
	int sub_size = raws * cols;
	Matrix<T> temp(raws,cols,data);
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp = Matrix<T>(raws, cols, data);
			temp.remove_raw(i + 1);
			temp.remove_col(j + 1);
			if ((i + j + 2) % 2 == 0)
			{
				result.data[j][i] = result.det(temp);
			}
			else
			{
				result.data[j][i] = -result.det(temp);
			}
		}
	}
	return result;
}

template <typename T>
Matrix<T> & Matrix<T>::inverse()
{
	static Matrix<T> temp(raws, cols);
	if (raws != cols)
	{
		cout << "Not a square matrix!" << endl;
	}
	else
	{
		Matrix<T> temp_matrix(raws, cols, data);
		double D = temp_matrix.det(temp_matrix);
		if (D == 0)
		{
			cout << "This square matrix det is zero, inverse matrix not exist!" << endl;
		}
		else
		{
			temp = adjugate();
			temp = temp * (1 / D);
		}	
	}
	return temp;
}

template <typename T>
double Matrix<T>::det(const Matrix &parameter)
{
	if (parameter.cols != parameter.raws)
	{
		cout << "This matrix have not det value!" << endl;
		return DBL_MAX;
	}
	else
	{
		double sum = 0;
		if (parameter.raws > 2)
		{
			Matrix<T> *temp = new Matrix<T>[parameter.raws];
			T *V_temp = new T[parameter.raws];
			for (int i = 0; i < parameter.raws; i++)
			{
				temp[i] = parameter;
				V_temp[i] = parameter.data[i][0];
				temp[i].remove_raw(i + 1);
				temp[i].remove_col(1);
			}
			for (int i = 0; i < parameter.raws; i++)
			{
				if (i % 2 == 0)
				{
					sum += V_temp[i] * det(temp[i]);
				}
				else
				{
					sum -= V_temp[i] * det(temp[i]);
				}
			}
			return sum;
		}
		else if(parameter.raws == 2)
		{
			sum = parameter.data[0][0] * parameter.data[1][1] - parameter.data[0][1] * parameter.data[1][0];
			return sum;
		}
		else
		{
			sum = parameter.data[0][0];
			return sum;
		}
	}
	
}

template <typename T>
Matrix<T> & Matrix<T>::operator =(const Matrix<T> &parameter)
{
	if (data != nullptr)
	{
		delete[] data;
	}
	raws = parameter.raws;
	cols = parameter.cols;
	data = new T*[raws];
	for (int i = 0; i < raws; i++)
	{
		data[i] = new T[cols];
	}
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			data[i][j] = parameter.data[i][j];
		}
	}
	return *this;
}

template <typename T>
Matrix<T> & Matrix<T>::operator +(const Matrix<T> &parameter)
{
	if (raws != parameter.raws || cols != parameter.cols)
	{
		cout << "Matrix size not match!" << endl;
		return *this;
	}
	else
	{
		static Matrix<T> temp;
		if (temp.data != nullptr)
		{
			delete[] temp.data;
		}
		temp.raws = parameter.raws;
		temp.cols = parameter.cols;
		temp.data = new T*[temp.raws];
		for (int i = 0; i < temp.raws; i++)
		{
			temp.data[i] = new T[temp.cols];
		}
		for (int i = 0; i < temp.raws; i++)
		{
			for (int j = 0; j < temp.cols; j++)
			{
				temp.data[i][j] = data[i][j] + parameter.data[i][j];
			}
		}
		return temp;
	}
}

template <typename T>
Matrix<T> & Matrix<T>::operator -(const Matrix<T> &parameter)
{

	if (raws != parameter.raws || cols != parameter.cols)
	{
		cout << "Matrix size not match!" << endl;
		return *this;
	}
	else
	{
		static Matrix<T> temp;
		if (temp.data != nullptr)
		{
			delete[] temp.data;
		}
		temp.raws = parameter.raws;
		temp.cols = parameter.cols;
		temp.data = new T*[temp.raws];
		for (int i = 0; i < temp.raws; i++)
		{
			temp.data[i] = new T[temp.cols];
		}
		for (int i = 0; i < temp.raws; i++)
		{
			for (int j = 0; j < temp.cols; j++)
			{
				temp.data[i][j] = data[i][j] - parameter.data[i][j];
			}
		}
		return temp;
	}
}

template <typename T>
Matrix<T> & Matrix<T>::operator *(const Matrix<T> &parameter)
{

	if (cols != parameter.raws)
	{
		cout << "Matrix size not match!" << endl;
		return *this;
	}
	else
	{
		static Matrix<T> temp;
		if (temp.data != nullptr)
		{
			delete[] temp.data;
		}
		temp.raws = raws;
		temp.cols = parameter.cols;
		temp.data = new T*[temp.raws];
		for (int i = 0; i < temp.raws; i++)
		{
			temp.data[i] = new T[temp.cols];
		}
		for (int i = 0; i < temp.raws; i++)
		{
			for (int j = 0; j < temp.cols; j++)
			{
				T sum = 0;
				for (int k = 0; k < cols; k++)
				{
					sum += data[i][k] * parameter.data[k][j];
				}
				temp.data[i][j] = sum;
			}
		}
		return temp;
	}
}

template <typename T>
Matrix<T> & Matrix<T>::operator +(const double &parameter)
{
	static Matrix<T> temp;
	if (temp.data != nullptr)
	{
		delete[] temp.data;
	}
	temp.raws = raws;
	temp.cols = cols;
	temp.data = new T*[temp.raws];
	for (int i = 0; i < temp.raws; i++)
	{
		temp.data[i] = new T[temp.cols];
	}
	for (int i = 0; i < temp.raws; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{
			temp.data[i][j] = data[i][j] + parameter;
		}
	}
	return temp;
}

template <typename T>
Matrix<T> & Matrix<T>::operator -(const double &parameter)
{
	static Matrix<T> temp;
	if (temp.data != nullptr)
	{
		delete[] temp.data;
	}
	temp.raws = raws;
	temp.cols = cols;
	temp.data = new T*[temp.raws];
	for (int i = 0; i < temp.raws; i++)
	{
		temp.data[i] = new T[temp.cols];
	}
	for (int i = 0; i < temp.raws; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{
			temp.data[i][j] = data[i][j] - parameter;
		}
	}
	return temp;
}

template <typename T>
Matrix<T> & Matrix<T>::operator *(const double &parameter)
{
	static Matrix<T> temp;
	if (temp.data != nullptr)
	{
		delete[] temp.data;
	}
	temp.raws = raws;
	temp.cols = cols;
	temp.data = new T*[temp.raws];
	for (int i = 0; i < temp.raws; i++)
	{
		temp.data[i] = new T[temp.cols];
	}
	for (int i = 0; i < temp.raws; i++)
	{
		for (int j = 0; j < temp.cols; j++)
		{
			temp.data[i][j] = data[i][j] * parameter;
		}
	}
	return temp;
}


template <typename T>
bool Matrix<T>::operator ==(const Matrix<T> &parameter)
{
	if (raws != parameter.raws || cols != parameter.cols)
	{
		return false;
	}
	else
	{
		int check_count = 0;
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (data[i][j] == parameter.data[i][j])
				{
					check_count++;
				}
			}
		}
		if (check_count == raws * cols)
			return true;
		else
			return false;
	}
}

template <typename T>
bool Matrix<T>::operator !=(const Matrix<T> &parameter)
{
	if (raws != parameter.raws || cols != parameter.cols)
	{
		return true;
	}
	else
	{
		int check_count = 0;
		for (int i = 0; i < raws; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (data[i][j] != parameter.data[i][j])
				{
					return true;
				}
				else
					check_count++;
			}
		}
		if (check_count == raws * cols)
			return false;
		else
			return true;
	}
}

template <typename T>
void Matrix<T>::show_matrix(bool approximate)
{
	cout << endl;
	for (int i = 0; i < raws; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (approximate)
			{
				if (data[i][j] < accurate_threshold)
				{
					cout << setw(element_width) << 0;
				}
				else
				{
					cout << setw(element_width) << data[i][j];
				}	
			}
			else
			{
				cout << setw(element_width) << data[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}
