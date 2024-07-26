/**
 *  File Name: matrix.cpp
 *  Assignment: ENSF 694 Summer 2024 - Lab 4 Exercise D
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 26, 2024
 */

#include "matrix.h"

Matrix::Matrix(int r, int c) : rowsM(r), colsM(c)
{
    matrixM = new double *[rowsM];
    assert(matrixM != NULL);

    for (int i = 0; i < rowsM; i++)
    {
        matrixM[i] = new double[colsM];
        assert(matrixM[i] != NULL);
    }
    sum_rowsM = new double[rowsM];
    assert(sum_rowsM != NULL);

    sum_colsM = new double[colsM];
    assert(sum_colsM != NULL);
}

Matrix::~Matrix()
{
    destroy();
}

Matrix::Matrix(const Matrix &source)
{
    copy(source);
}

Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (&rhs != this)
    {
        destroy();
        copy(rhs);
    }

    return *this;
}

double Matrix::get_sum_col(int i) const
{
    assert(i >= 0 && i < colsM);
    return sum_colsM[i];
}

double Matrix::get_sum_row(int i) const
{
    assert(i >= 0 && i < rowsM);
    return sum_rowsM[i];
}

void Matrix::sum_of_rows() const
{
    double sum;
    for (int i = 0; i < rowsM; i++)
    {
        sum = 0.0;
        for (int j = 0; j < colsM; j++)
        {
            sum += matrixM[i][j];
        }
        sum_rowsM[i] = sum;
    }
}

void Matrix::sum_of_cols() const
{
    double sum;
    for (int j = 0; j < colsM; j++)
    {
        sum = 0.0;
        for (int i = 0; i < rowsM; i++)
        {
            sum += matrixM[i][j];
        }
        sum_colsM[j] = sum;
    }
}

void Matrix::copy(const Matrix &source)
{
    if (source.matrixM == NULL)
    {
        matrixM = NULL;
        sum_rowsM = NULL;
        sum_colsM = NULL;
        rowsM = 0;
        colsM = 0;
        return;
    }

    rowsM = source.rowsM;
    colsM = source.colsM;

    sum_rowsM = new double[rowsM];
    assert(sum_rowsM != NULL);
    for (int i = 0; i < rowsM; i++)
        sum_rowsM[i] = source.sum_rowsM[i];

    sum_colsM = new double[colsM];
    assert(sum_colsM != NULL);
    for (int i = 0; i < colsM; i++)
        sum_colsM[i] = source.sum_colsM[i];

    matrixM = new double *[rowsM];
    assert(matrixM != NULL);
    for (int i = 0; i < rowsM; i++)
    {
        matrixM[i] = new double[colsM];
        assert(matrixM[i] != NULL);
        for (int j = 0; j < colsM; j++)
        {
            matrixM[i][j] = source.matrixM[i][j];
        }
    }
}

void Matrix::destroy()
{
    if (matrixM != NULL)
    {
        for (int i = 0; i < rowsM; i++)
        {
            delete[] matrixM[i];
        }
        delete[] matrixM;
    }
    delete[] sum_rowsM;
    delete[] sum_colsM;
}
