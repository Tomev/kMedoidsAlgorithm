#ifndef RESERVOIRALGORITHM_DATAREADER_H
#define RESERVOIRALGORITHM_DATAREADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "attributeData.h"

class dataReader
{
  public:

    virtual void getNextRawDatum(void *target) = 0;
    virtual void gatherAttributesData(std::unordered_map<std::string, attributeData*> *attributesData) = 0;
    virtual bool hasMoreData() = 0;

    virtual std::vector<std::string>* getAttributesOrder() = 0;
};


#endif //RESERVOIRALGORITHM_DATAREADER_H
