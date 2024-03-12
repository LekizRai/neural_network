#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "main.h"

class Matrix;

class Matrix {
private:
    vector<vector<double>> arr;
    int numRow;
    int numCol;
public:
    Matrix();
    Matrix(auto &arr, int numRow, int numCol);
    Matrix(vector<vector<double>> &arr);
    ~Matrix();
    vector<vector<double>> getMatrix() const;
    pair<int, int> getShape() const;
    void print() const;
    void reshape(int numRow, int numCol);
    Matrix transpose();
    Matrix expand(int num, int axis);
    Matrix sum(int axis);
    static Matrix linspace(int lowerBound, int upperBound, int numNum);
    static Matrix full(int numRow, int numCol, double val);
    static Matrix unit(int edgeSize);
    static Matrix randInt(int numRow, int numCol, int lowerBound, int upperBound);
    vector<double>& operator[](int index);
    Matrix operator+(Matrix otherMatrix);
    Matrix operator-(Matrix otherMatrix);
    Matrix operator*(double factor);
    Matrix operator*(Matrix otherMatrix);
    Matrix operator^(int exp);
    Matrix operator&(Matrix otherMatrix);
};

// ostream& operator<<(ostream& os, Matrix &otherMatrix) {
//     vector<vector<double>> arr = otherMatrix.getMatrix();
//     int numRow = (int)(arr.size());
//     int numCol = (int)(arr[0].size());
//     os << "Shape: " << "(" << numRow << ", " << numCol << ")" << endl;
//     os << "[";
//     for(int i = 0; i < numRow; i++) {
//         if(i == 0) os << "[";
//         else os << " [";
//         for(int j = 0; j < numCol; j++) {
//             os << setw(8) << setprecision(6) << arr[i][j];
//             if(j == numCol - 1) continue;
//             else os << ", ";
//         }
//         os << "]";
//         if(i == numRow - 1) continue;
//         else os << endl;
//     }
//     os << "]" << endl;
//     return os;
// }

ostream& operator<<(ostream& os, Matrix otherMatrix) {
    vector<vector<double>> arr = otherMatrix.getMatrix();
    int numRow = (int)(arr.size());
    int numCol = (int)(arr[0].size());
    os << "Shape: " << "(" << numRow << ", " << numCol << ")" << endl;
    os << "[";
    for(int i = 0; i < numRow; i++) {
        if(i == 0) os << "[";
        else os << " [";
        for(int j = 0; j < numCol; j++) {
            os << setw(8) << setprecision(6) << arr[i][j];
            if(j == numCol - 1) continue;
            else os << ", ";
        }
        os << "]";
        if(i == numRow - 1) continue;
        else os << endl;
    }
    os << "]" << endl;
    return os;
}

Matrix::Matrix() {
    this->arr = vector<vector<double>> (0, vector<double> (0, 0));
    this->numRow = 0;
    this->numCol = 0;
}

Matrix::Matrix(auto &arr, int numRow, int numCol) {
    this->numRow = numRow;
    this->numCol = numCol;
    this->arr = vector<vector<double>> (this->numRow, vector<double> (this->numCol, 0));
    for(int i = 0; i < this->numRow; i++) {
        for(int j = 0; j < this->numCol; j++) {
            (this->arr)[i][j] = arr[i][j];
        }
    }
}

Matrix::Matrix(vector<vector<double>> &arr) {
    this->arr = arr;
    this->numRow = (int)(arr.size());
    this->numCol = (int)(arr[0].size());
}

Matrix::~Matrix() {
    //
}

vector<vector<double>> Matrix::getMatrix() const {
    return this->arr;
}

pair<int, int> Matrix::getShape() const {
    return pair<int, int> (this->numRow, this->numCol);
}

void Matrix::print() const {
    cout << "Shape: " << "(" << this->numRow << ", " << this->numCol << ")" << endl;
    cout << "[";
    for(int i = 0; i < this->numRow; i++) {
        if(i == 0) cout << "[";
        else cout << " [";
        for(int j = 0; j < this->numCol; j++) {
            cout << setw(8) << setprecision(6) << (this->arr)[i][j];
            if(j == this->numCol - 1) continue;
            else cout << ", ";
        }
        cout << "]";
        if(i == this->numRow - 1) continue;
        else cout << endl;
    }
    cout << "]" << endl;
}

void Matrix::reshape(int numRow, int numCol) {
    if(numRow * numCol != this->numRow * this->numCol) {
        cout << "Error: The size is not compatible for reshaping" << endl;
        abort();
    }
    vector<vector<double>> resultMatrix(numRow, vector<double> (numCol, 0));
    int row_id = 0;
    int col_id = 0;
    for(int i = 0; i < this->numRow; i++) {
        for(int j = 0; j < this->numCol; j++) {
            resultMatrix[row_id][col_id] = (this->arr)[i][j];
            if(col_id + 1 >= numCol) {
                row_id += 1;
                col_id = 0;
            }
            else col_id += 1;
        }
    }
    this->arr = resultMatrix;
    this->numRow = numRow;
    this->numCol = numCol;
}

Matrix Matrix::transpose() {
    vector<vector<double>> resultMatrix(this->numCol, vector<double> (this->numRow, 0));
    for(int i = 0; i < this->numRow; i++) {
        for(int j = 0; j < this->numCol; j++) {
            resultMatrix[j][i] = (this->arr)[i][j];
        }
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::expand(int num, int axis = 1) {
    if(axis == 1) {
        if((int)((this->arr).size()) == 1) {
            vector<double> duplicate = (this->arr)[0];
            vector<vector<double>> returnMatrix(num, vector<double> ((int)((this->arr)[0].size()), 1));
            for(int i = 0; i < num; i++) {
                returnMatrix[i] = duplicate;
            }
            return Matrix(returnMatrix);
        }
        else {
            cout << "The shape is not compatible for expanding" << endl;
            abort();
        }
    }
    else if(axis == 2) {
        if((int)((this->arr)[0].size()) == 1) {
            vector<vector<double>> returnMatrix((int)((this->arr).size()), vector<double> (num, 1));
            for(int i = 0; i < (int)((this->arr).size()); i++) {
                for(int j = 0; j < num; j++) {
                    returnMatrix[i][j] =  (this->arr)[i][0];
                }
            }
            return Matrix(returnMatrix);
        }
        else {
            cout << "The shape is not compatible for expanding" << endl;
            abort();
        }
    }
    else {
        cout << "No more than 2 axises 1 and 2" << endl;
        abort();
    }
}

Matrix Matrix::sum(int axis = 1) {
    if(axis == 1) {
        vector<vector<double>> returnMatrix(1, vector<double> ((int)((this->arr)[0].size()), 0));
        for(int j = 0; j < (int)((this->arr)[0].size()); j++) {
            for(int i = 0; i < (int)((this->arr).size()); i++) {
                returnMatrix[0][j] += (this->arr)[i][j];
            }
        }
        return Matrix(returnMatrix);
    }
    else if(axis == 2) {
        vector<vector<double>> returnMatrix((int)((this->arr).size()), vector<double> (1, 0));
        for(int i = 0; i < (int)((this->arr).size()); i++) {
            for(int j = 0; j < (int)((this->arr)[0].size()); j++) {
                returnMatrix[i][0] += (this->arr)[i][j];
            }
        }
        return Matrix(returnMatrix);
    }
    else {
        cout << "No more than 2 axises 1 and 2" << endl;
        abort();
    }
}

Matrix Matrix::linspace(int lowerBound, int upperBound, int numNum) {
    vector<vector<double>> resultMatrix(1, vector<double> (numNum, 0));
    double gap = (double)(upperBound - lowerBound) / (double)(numNum - 1);
    double cum_sum = lowerBound;
    for(int i = 0; i < numNum; i++) {
        resultMatrix[0][i] = cum_sum;
        cum_sum += gap;
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::full(int numRow, int numCol, double val) {
    vector<vector<double>> resultMatrix(numRow, vector<double> (numCol, val));
    return Matrix(resultMatrix);
}

Matrix Matrix::unit(int edgeSize) {
    vector<vector<double>> resultMatrix(edgeSize, vector<double> (edgeSize, 0));
    for(int i = 0; i < edgeSize; i++) resultMatrix[i][i] = 1;
    return Matrix(resultMatrix);
}

Matrix Matrix::randInt(int numRow, int numCol, int lowerBound, int upperBound) {
    srand(time(NULL));
    vector<vector<double>> returnMatrix(numRow, vector<double> (numCol, 0));
    for(int i = 0; i < numRow; i++) {
        for(int j = 0; j < numCol; j++) {
            returnMatrix[i][j] = rand() % (upperBound - lowerBound + 1) + lowerBound;
        }
    }
    return Matrix(returnMatrix);
}

vector<double>& Matrix::operator[](int index) {
    return (this->arr)[index];
}

Matrix Matrix::operator+(Matrix otherMatrix) {
    vector<vector<double>> resultMatrix = otherMatrix.getMatrix();
    if(int((this->arr).size()) != int(resultMatrix.size())) {
        cout << "The two matrixes' sizes are not the same" << endl;
        abort();
    }
    if(int((this->arr)[0].size()) != int(resultMatrix[0].size())) {
        cout << "The two matrixes' sizes are not the same" << endl;
        abort();
    }
    for(int i = 0; i < int(resultMatrix.size()); i++) {
        for(int j = 0; j < int(resultMatrix[0].size()); j++) {
            resultMatrix[i][j] += (this->arr)[i][j];
        }
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::operator-(Matrix otherMatrix) {
    vector<vector<double>> resultMatrix = otherMatrix.getMatrix();
    if(int((this->arr).size()) != int(resultMatrix.size())) {
        cout << "The two matrixes' sizes are not the same" << endl;
        abort();
    }
    if(int((this->arr)[0].size()) != int(resultMatrix[0].size())) {
        cout << "The two matrixes' sizes are not the same" << endl;
        abort();
    }
    for(int i = 0; i < int(resultMatrix.size()); i++) {
        for(int j = 0; j < int(resultMatrix[0].size()); j++) {
            resultMatrix[i][j] = (this->arr)[i][j] - resultMatrix[i][j];
        }
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::operator*(double factor) {
    vector<vector<double>> resultMatrix = this->arr;
    for(int i = 0; i < int(resultMatrix.size()); i++) {
        for(int j = 0; j < int(resultMatrix[0].size()); j++) {
            resultMatrix[i][j] *= factor;
        }
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::operator*(Matrix otherMatrix) {
    vector<vector<double>> matrix = otherMatrix.getMatrix();
    if((int)((this->arr)[0].size()) != (int)(matrix.size())) {
        cout << "The two matrixes' sizes are not compatible for multipling" << endl;
        abort();
    }
    vector<vector<double>> resultMatrix((int)(this->arr).size(), vector<double> ((int)(matrix[0].size()), 0));
    for(int i = 0; i < (int)(this->arr).size(); i++) {
        for(int j = 0; j < (int)(matrix[0].size()); j++) {
            for(int k = 0; k < (int)((this->arr)[0].size()); k++) {
                resultMatrix[i][j] += (this->arr)[i][k] * matrix[k][j];
            }
        }
    }
    return Matrix(resultMatrix);
}

Matrix Matrix::operator^(int exp) {
    if(this->numRow != this->numCol) {
        cout << "The matrix is not square for exponent" << endl;
        abort();
    }
    Matrix resultMatrix = Matrix::unit(this->numRow);
    Matrix base = *this;
    while(exp) {
        if(exp & 1) resultMatrix = resultMatrix * base;
        exp >>= 1;
        if(exp) base = base * base;
    }
    return resultMatrix;
}

Matrix Matrix::operator&(Matrix otherMatrix) {
    if(this->getShape() != otherMatrix.getShape()) {
        cout << "The two matrixes' shapes are not the same for elementwise multipling" << endl;
        abort();
    }
    vector<vector<double>> returnMatrix = otherMatrix.getMatrix();
    for(int i = 0; i < (int)((this->arr).size()); i++) {
        for(int j = 0; j < (int)((this->arr)[0].size()); j++) {
            returnMatrix[i][j] *= (this->arr)[i][j];
        }
    }
    return Matrix(returnMatrix);
}

#endif // __MATRIX_H__