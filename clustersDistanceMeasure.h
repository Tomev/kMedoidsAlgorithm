//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H

#include "cluster.h"
#include "objectsDistanceMeasure.h"

class clustersDistanceMeasure
{
  public:

    virtual double countClustersDistance(cluster *c1, cluster *c2);

  private:

    objectsDistanceMeasure* measure;

};


#endif //K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H
