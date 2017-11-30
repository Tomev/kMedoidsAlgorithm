#ifndef K_MEDOIDALGORITHM_NUMERICALATTRIBUTEDATA_H
#define K_MEDOIDALGORITHM_NUMERICALATTRIBUTEDATA_H

#include "attributeData.h"

class numericalAttributeData : public attributeData
{
  public:

    numericalAttributeData(std::string name);

    std::string getName();
    std::string getType();

    double getMaximalValue();
    double getMinimalValue();
    double getMinMaxDifference();

    void setMaximalValue(double newMaximalValue);
    void setMinimalValue(double newMinimalValue);

    bool hasAttributeOccurred();
    void attributeOccured();

  protected:

    std::string name;

    bool occurred = false;

    double maximalValue;
    double minimalValue;

};


#endif //K_MEDOIDALGORITHM_NUMERICALATTRIBUTEDATA_H
