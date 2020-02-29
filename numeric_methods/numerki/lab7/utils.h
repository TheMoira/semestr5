#pragma once
#include <cmath>
#include <vector>
#include <iostream>

template<typename T>
class Matrix
{
    int size;
    int rows;
    int cols;
    T** matrix;

    public:

    //constructor with argments: number of rows, number of columns
    Matrix(int r, int c);

    Matrix(const Matrix& m1);

    //prefill matrix with one value
    Matrix(int r, int c, T value);
    ~Matrix();

    //operator [] overload - returns reference to vector 
    T* operator[](int row);
    void print_matrix() const;

    void add_row(T* row);
    // void insert(int i, int j);
    void resize(int new_rows, int new_cols);
    

    int get_rows() const {return rows;}
    int get_cols() const {return cols;}

};


template<typename T>
Matrix<T>::Matrix(int r, int c, T value)
{
    Matrix<T>(r,c);

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            matrix[i][j] = value;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix& m1)
{
    Matrix<T>(m1.get_rows(), m1.get_cols());

    for(int i=0; i<m1.get_rows(); i++)
    {
        for(int j=0; j<m1.get_cols(); j++)
        {
            matrix[i][j] = m1[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    size = r*c;

    matrix = new T*[rows];
    for(int i=0; i<rows; i++)
    {
        matrix[i] = new T[cols];
    }
}


template<typename T>
Matrix<T>::~Matrix()
{
    for(int i=0; i<rows; i++)
    {
        delete [] matrix[i];
    }
}

template<typename T>
T* Matrix<T>::operator[](int row)
{
    return matrix[row];
}

template<typename T>
void Matrix<T>::print_matrix() const
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            std::cout<<matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename T>
void Matrix<T>::add_row(T* row)
{
    Matrix<T> temp = Matrix<T>(*this);

    rows++;
    matrix = new T*[rows];

    for(int i=0; i<rows; i++)
    {
        matrix[i] = new T[cols];
        for(int j=0; j<cols; j++)
        {
            if(i<rows-1) matrix[i][j] = temp[i][j];
            else matrix[i][j] = row[j];
        }
    }

}