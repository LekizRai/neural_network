#include "neur.h"

void print(Layer* output) {cout << output << endl;};

int main() {
    // double a[6][3] =  {{0, 0, 0},
    //                     {1, 1, 1},
    //                     {8, 4, 2},
    //                     {27, 9, 3},
    //                     {64, 16, 4},
    //                     {125, 25, 5}};
    // Matrix X = Matrix::linspace(0, 5, 6).transpose();
    // Matrix y = (X & X & X) + (X & X) * 2 + X;
    // X = Matrix(a, 6, 3);
    // Layer* input = Layer::Input(3);
    // Layer* x = (*Layer::Dense(5))(input);
    // x = (*Layer::Dense(2))(x);
    // Layer* output = (*Layer::Dense(1))(x);
    // Neur model(input, output);
    // cout << y.transpose();
    // model.compile(X, y, 500, 1, 0.0001);
    // model.compile(X, y, 20000, 1, 0.0001);
    double a[1][4] = {1, 0, 0, 1};
    double b[1][4] = {0, 1, 0, 1};
    Matrix X(a, 1, 4);
    Matrix Y(b, 1, 4);
    cout << X.transpose() * Y - Y.transpose() * X;
}