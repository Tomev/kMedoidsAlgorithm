#ifndef K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H

#include "cluster.h"
#include "objectsDistanceMeasure.h"

class clustersDistanceMeasure
{
  public:

    virtual double countClustersDistance(cluster *cluster1, cluster *cluster2) = 0;

  protected:

    objectsDistanceMeasure* objDistanceMeasure;

};


#endif //K_MEDOIDALGORITHM_CLUSTERSDISTANCEMEASURE_H
