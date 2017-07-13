//
// Created by Tomev on 29.05.2017.
//

#ifndef RESERVOIRALGORITHM_TEXTDATAPARSER_H
#define RESERVOIRALGORITHM_TEXTDATAPARSER_H

/*
 * Parsing from .arff files to sample.
 */

#include <string>
#include <vector>
#include <c++/iostream>
#include <unordered_map>

#include "dataParser.h"
#include "textDataSample.h"
#include "attributeData.h"

using namespace std;

class textDataParser : public dataParser
{

  public:

    textDataParser(unordered_map<string, attributeData*> *attributesData);

    void parseData(void *target);
    int addDatumToContainer(std::vector<sample*> *container);
    void writeDatumOnPosition(std::vector<sample*> *container, int position);

    void setAttributesOrder(vector<string> *attributesOrder);

  protected:

    vector<string> *attributesOrder;
    unordered_map<string, attributeData*>* attributesData;

};


#endif //RESERVOIRALGORITHM_TEXTDATAPARSER_H
