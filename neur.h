#ifndef __NEUR_H__
#define __NEUR_H__

#include "layer.h"

class Neur;

class Neur {
private:
    Layer* input;
    Layer* output;
    void feedForward(Matrix& X);
    void backPropagation(Matrix& y, double learningRate);
public:
    Neur(Layer* input, Layer* output) {
        this->input = input; 
        this->output = output;
    };
    void compile(Matrix& X, Matrix& y, int epochs, int batch_size, double learningRate);
    Matrix predict(Matrix& X);
};

void Neur::feedForward(Matrix& X) {
    Layer* curLayer = this->input;
    curLayer->setA(X.transpose());
    do {
        curLayer = curLayer->getNextLayer();
        curLayer->setZ((curLayer->getW()).transpose() * (curLayer->getPrevLayer()->getA()) + (curLayer->getB()).expand(X.getShape().first, 2));
        curLayer->setA(curLayer->getZ());
        if(curLayer == this->output) break;
    } while(true);
}

void Neur::backPropagation(Matrix& y, double learningRate) {
    Layer* curLayer = this->output;
    Matrix curE;
    Matrix nextE;
    if(curLayer == this->input) return ;
    Matrix curW = curLayer->getW();
    Matrix prevA = curLayer->getPrevLayer()->getA();
    Matrix curA = curLayer->getA();
    Matrix curB = curLayer->getB();
    Matrix expB = (curB.transpose()).expand(y.getShape().first);
    curE = (curA - y.transpose()) * (1.0 / y.getShape().first);
    nextE = (curW * curE);
    curLayer->setW(curW - prevA * (prevA.transpose() * curW + expB - y) * (1.0 / y.getShape().first) * learningRate);
    curLayer->setB(curB - ((prevA.transpose() * curW + expB - y) * (1.0 / y.getShape().first) * learningRate).sum(1).transpose()); // calc_sum
    do {
        curLayer = curLayer->getPrevLayer();
        if(curLayer == this->input) break;
        curW = curLayer->getW();
        Matrix nextW = curLayer->getNextLayer()->getW();
        prevA = curLayer->getPrevLayer()->getA();
        curB = curLayer->getB();
        curE = nextE;
        nextE = (curW * curE);
        curLayer->setW(curW - prevA * curE.transpose() * learningRate);
        curLayer->setB(curB - curE.sum(2) * learningRate);
    } while(true);
}

void Neur::compile(Matrix& X, Matrix& y, int epochs, int batch_size, double learningRate) {
    for(int i = 0; i < epochs; i++) {
        this->feedForward(X);
        this->backPropagation(y, learningRate);
    }
    cout << output->getA();
}

Matrix Neur::predict(Matrix& X) {
    this->feedForward(X);
    return output->getA();
}

#endif // neur.h