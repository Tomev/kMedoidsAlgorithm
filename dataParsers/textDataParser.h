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

#include "../dataParser.h"
#include "../dataSamples/textDataSample.h"
#include "../attributeData.h"

class textDataParser : public dataParser
{

  public:

    textDataParser(std::unordered_map<std::string, attributeData*> *attributesData);

    void parseData(void *target);
    int addDatumToContainer(std::vector<sample*> *container);
    void writeDatumOnPosition(std::vector<sample*> *container, int position);

    void setAttributesOrder(std::vector<std::string> *attributesOrder);

  protected:

    std::vector<std::string> *attributesOrder;
    std::unordered_map<std::string, attributeData*>* attributesData;

    void updateAttributesData(textDataSample *newSample);

};


#endif //RESERVOIRALGORITHM_TEXTDATAPARSER_H
