//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
#define K_MEDOIDALGORITHM_GROUPINGALGORITHM_H

#include <vector>
#include "cluster.h"

class groupingAlgorithm
{
  public:
    virtual void groupObjects(std::vector<sample>* objects, std::vector<cluster>* target) = 0;

  protected:

};


#endif //K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
