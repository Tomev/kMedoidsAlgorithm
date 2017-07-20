#ifndef K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
#define K_MEDOIDALGORITHM_GROUPINGALGORITHM_H

#include <vector>
#include "cluster.h"

class groupingAlgorithm
{
  public:
    virtual void groupObjects(std::vector<sample*>* objects, std::vector<cluster>* target) = 0;

};


#endif //K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
