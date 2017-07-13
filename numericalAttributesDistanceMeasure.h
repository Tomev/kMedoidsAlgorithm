#ifndef K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H

#include "string"

using namespace std;

class numericalAttributesDistanceMeasure
{
  public:

    void setCurrentAttributeName(std::string attributeName)
    {
      this->currentAttributeName = attributeName;
    }

    virtual double countNumericalAttributesDistance(double firstAttributeValue, double secondAttributeValue) = 0;

  protected:

    string currentAttributeName;
};

#endif //K_MEDOIDALGORITHM_NUMERICALATTRIBUTESDISTANCEMEASURE_H
