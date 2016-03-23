// Mat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
#define Matrix Mat
class Matrix
{
	public:
		Matrix();
		Matrix(int _n, int _m);
		Matrix(int **mass, int _n, int _m);
		Matrix(const Matrix & x);
		~Matrix();

		Matrix operator +(const Matrix&);
		Matrix operator *(const Matrix&);
		double* operator [](int);

		static Matrix &scan(char* path);
		void write() const;
		int getLinesNumber() const;
		int getColumnsNumber() const;
	private:
		double **matrix;
		int lines;
		int columns;
};

Matrix::Matrix(const Matrix & x) : matrix(new double *[x.lines]), columns(x.columns), lines(x.lines) {
	for (int i = 0; i < lines; i++) {
		matrix[i] = new double[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = x.matrix[i][j];
		}
	}
}

Matrix::Matrix()
{
	lines = 0;
	columns = 0;
	matrix = nullptr;
}

Mat::~Mat()
{
	for (int i = 0; i < lines; i++)
		delete[] matrix[i];
	delete[] matrix;
} 

Mat::Mat(int _lines, int _columns)
{
	lines = _lines;
	columns = _columns;
	matrix = new double*[lines];
	for (int i = 0; i < lines; i++)
		matrix[i] = new double[columns];
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			matrix[i][j] = 0;
}

Mat::Mat(int **mass, int _lines, int _columns)
{
	lines = _lines;
	columns = _columns;
	matrix = new double*[lines];
	for (int i = 0; i < lines; i++)
		matrix[i] = new double[columns];
	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			matrix[i][j] = mass[i][j];
}

double* Mat::operator[](int index) 
{
	return this->matrix[index];
}

int Matrix::getLinesNumber() const
{
	return lines;
}

int Matrix::getColumnsNumber() const
{
	return columns;
}

Matrix &Matrix::scan(char* path)
{
	ifstream stream;
	stream.open(path);

	if (stream.fail())
	{
		cout << "Incorrect filename";
		return Matrix();
	}

	int lines, columns;

	stream >> lines >> columns;
	int **mass = new int*[lines];
	for (int i = 0; i < lines; i++)
	{
		mass[i] = new int[columns];
		for (int j = 0; j < columns; j++)
			stream >> mass[i][j];
	}

	Matrix *temp = new Matrix(mass, lines, columns);
	stream.close();
	return *temp;
}

void Matrix::write() const
{
	if (this->matrix == nullptr || this->lines == 0 || this->columns == 0) {
		cout << "Empty matrix\n";
	}
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			cout.width(4);
			cout << this->matrix[i][j];
		}
		cout << endl;
	}
}

Matrix Mat::operator +(const Matrix &M1)
{
	Matrix temp(this->lines, this->columns); 

	for (int i = 0; i < lines; i++)
		for (int j = 0; j < columns; j++)
			temp.matrix[i][j] = this->matrix[i][j] + this->matrix[i][j];
	return temp;
}

Matrix Mat::operator *(const Matrix &M1) 
{
		Matrix temp(this->lines, this->columns);

		for (int row = 0; row < this->lines; row++)
			for (int col = 0; col < this->columns; col++)
				for (int inner = 0; inner < this->lines; inner++)
					temp.matrix[row][col] += this->matrix[row][inner] * this ->matrix[inner][col];

		return temp;
}

int main()
{
	int i,j;
	char* path = new char[256];
	int** test = new int*[5];
	for (int i = 0; i < 5; i++) {
		test[i] = new int[5];
		for (int j = 0; j < 5; j++) {
			test[i][j] = rand() % 10;
		}
	}
	//cout<< ("Enter the path to file: \n");
	//cin>> path;
	//Matrix M1;
	//M1 = M1.scan(path);
	//cout<<("Your Matrix:\n");
	//M1.write();
	Mat M1(test, 5, 5);
	cout << ("Lines:\n");
	cout << M1.getLinesNumber();
	cout << ("Columns:\n");
	cout << M1.getColumnsNumber();
	cout << ("M1+M1=\n");
	(M1+M1).write();
	cout << ("M1*M1=\n");
	(M1*M1).write();
	M1.~Matrix();
	return 0;
}

