#ifndef __LAYER_H__
#define __LAYER_H__

#include "matrix.h"

enum layerType {DENSE, INPUT};

class Layer {
private:
    int nodeNum;
    Matrix W;
    Matrix b;
    Matrix z;
    Matrix a;
    bool addBias;
    Layer* nextLayer;
    Layer* prevLayer;
    layerType type;
public:
    Layer(int nodeNum, layerType type, bool addBias);
    Layer* getNextLayer() const {return this->nextLayer;};
    Layer* getPrevLayer() const {return this->prevLayer;};
    void setNextLayer(Layer* otherLayer) {this->nextLayer = otherLayer;};
    void setPrevLayer(Layer* otherLayer) {this->prevLayer = otherLayer;};
    int getNodeNum() const {return this->nodeNum;};
    void setNodeNum(int otherNodeNum) {this->nodeNum = otherNodeNum;};
    bool getAddBias() const {return this->addBias;};
    void setAddBias(bool otherAddBias) {this->addBias = otherAddBias;};
    Matrix getW() const {return this->W;};
    Matrix getB() const {return this->b;};
    Matrix getA() const {return this->a;};
    Matrix getZ() const {return this->z;};
    void setW(Matrix otherMatrix) {this->W = otherMatrix;};
    void setB(Matrix otherMatrix) {this->b = otherMatrix;};
    void setA(Matrix otherMatrix) {this->a = otherMatrix;};
    void setZ(Matrix otherMatrix) {this->z = otherMatrix;};
    layerType getType() const {return this->type;};
    static Layer* Dense(int nodeNum, bool addBias);
    static Layer* Input(int nodeNum, bool addBias);
    Layer* operator()(Layer* otherLayer);
};

Layer::Layer(int nodeNum, layerType type, bool addBias = true) {
    this->nodeNum = nodeNum;
    this->addBias = addBias;
    this->type = type;
    this->nextLayer = NULL;
    this->prevLayer = NULL;
}

Layer* Layer::Dense(int nodeNum, bool addBias = true) {
    Layer* returnLayer = new Layer(nodeNum, DENSE, addBias);
    return returnLayer;
}

Layer* Layer::Input(int nodeNum, bool addBias = true) {
    Layer* returnLayer = new Layer(nodeNum, INPUT, addBias);
    return returnLayer;
}

Layer* Layer::operator()(Layer* otherLayer) {
    otherLayer->setNextLayer(this);
    this->prevLayer = otherLayer;
    this->W = Matrix::full(otherLayer->getNodeNum(), this->nodeNum, 0.005);
    this->b = Matrix::full(this->nodeNum, 1, 0.005);
    return this;
}

ostream& operator<<(ostream& os, Layer otherLayer) {
    os << "Type: ";
    switch(otherLayer.getType()) {
        case INPUT: {
            os << "INPUT";
            break;
        }
        case DENSE: {
            os << "DENSE";
            break;
        }
    }
    os << endl;
    os << "Number of nodes: " << otherLayer.getNodeNum() << endl;
    os << "Have bias: ";
    if(otherLayer.getAddBias()) os << "true" << endl;
    else os << "false" << endl;
    if(otherLayer.getType() == INPUT) return os;
    os << "Coef matrix W: " << endl << otherLayer.getW() << endl;
    if(otherLayer.getAddBias()) os << "Bias matrix b: " << endl << otherLayer.getB() << endl;
    return os;
}

#endif // layer.h
