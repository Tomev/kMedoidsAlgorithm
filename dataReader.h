//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_DATAREADER_H
#define RESERVOIRALGORITHM_DATAREADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "attributeData.h"


using namespace std;

class dataReader
{
  public:

    virtual void getNextRawDatum(void *target) = 0;
    virtual void gatherAttributesData(unordered_map<string, unordered_map<string, attributeData*>> *attributesData) = 0;
    virtual bool hasMoreData() = 0;

    virtual vector<string>* getAttributesOrder() = 0;
};


#endif //RESERVOIRALGORITHM_DATAREADER_H
