//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_DATAPARSER_H
#define RESERVOIRALGORITHM_DATAPARSER_H

#include <vector>

#include "groupingAlgorithm/sample.h"

using namespace std;

class dataParser
{
  public:

    virtual void parseData(void *target) = 0;
    virtual int addDatumToContainer(vector<sample*> *container) = 0;
    virtual void writeDatumOnPosition(vector<sample*> *container, int position) = 0;
    virtual void setAttributesOrder(vector<string> *attributesOrder) = 0;

    void *buffer;

  protected:

    vector<string> *attributesOrder;
};


#endif //RESERVOIRALGORITHM_DATAPARSER_H
