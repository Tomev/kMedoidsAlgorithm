#ifndef K_MEDOIDALGORITHM_CATEGORICALATTRIBUTESDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CATEGORICALATTRIBUTESDISTANCEMEASURE_H

#include <string>

using namespace std;

class categoricalAttributesDistanceMeasure
{
  public:

    void setCurrentAttributeName(std::string attributeName)
    {
      this->currentAttributeName = attributeName;
    }

    virtual double countCategoricalAttributesDistance(string firstAttributeValue, string secondAttributeValue) = 0;

  protected:

    string currentAttributeName;
};

#endif //K_MEDOIDALGORITHM_CATEGORICALATTRIBUTESDISTANCEMEASURE_H
