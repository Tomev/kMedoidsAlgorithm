#ifndef K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H

#include <string>

using namespace std;

class attributesDistanceMeasure
  {
  public:

    void setCurrentAttributeName(string attributeName)
    {
      this->currentAttributeName = attributeName;
    }

    virtual double countAttributesDistance(string firstAttributeValue, string secondAttributeValue) = 0;

  protected:

    string currentAttributeName;
};

#endif //K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H
