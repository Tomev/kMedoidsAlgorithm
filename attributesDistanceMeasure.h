#ifndef K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H

#include <string>

class attributesDistanceMeasure
  {
  public:

    void setCurrentAttributeName(std::string attributeName)
    {
      this->currentAttributeName = attributeName;
    }

    virtual double countAttributesDistance(std::string firstAttributeValue,
                                           std::string secondAttributeValue) = 0;

  protected:

    std::string currentAttributeName;
};

#endif //K_MEDOIDALGORITHM_ATTRIBUTESDISTANCEMEASURE_H
