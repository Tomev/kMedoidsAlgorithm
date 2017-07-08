//
// Created by Tomev on 07.07.2017.
//

#ifndef K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H

#include "string"

class numericalAttributesDistanceMeasure
{
  public:

    void setCurrentAttributeName(std::string attributeName)
    {
      this->currentAttributeName = attributeName;
    }

    virtual double countNumericalAttributesDistance(double firstAttributeValue, double secondAttributeValue) = 0;

  protected:

    std::string currentAttributeName;
};

#endif //K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H
