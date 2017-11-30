#ifndef K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
#define K_MEDOIDALGORITHM_GROUPINGALGORITHM_H

#include <vector>
#include "cluster.h"

class groupingAlgorithm
{
  public:
    virtual void groupObjects(std::vector<std::shared_ptr<sample>>* objects, std::vector<std::shared_ptr<cluster>>* target) = 0;
    virtual void groupClusters(std::vector<std::shared_ptr<cluster>>* clusters, std::vector<std::shared_ptr<cluster>>* target) = 0;
};


#endif //K_MEDOIDALGORITHM_GROUPINGALGORITHM_H
