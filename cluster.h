//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_CLUSTER_H
#define K_MEDOIDALGORITHM_CLUSTER_H

#include <c++/vector>
#include "sample.h"

class cluster
{
  public:
    cluster(int index);
    cluster(int index, sample* object);

    bool representsObject();
    long getClustersIndex();

  private:
    int index;
    sample* object;
    sample* representative;

    std::vector<cluster> subclusters;
};


#endif //K_MEDOIDALGORITHM_CLUSTER_H
