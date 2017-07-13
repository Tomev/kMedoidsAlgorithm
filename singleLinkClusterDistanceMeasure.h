#ifndef K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H


#include "clustersDistanceMeasure.h"

class singleLinkClusterDistanceMeasure : public clustersDistanceMeasure
{
  public:

    singleLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

    double countClustersDistance(cluster *cluster1, cluster *cluster2);

  protected:

    double findLowestDistance(vector<sample*> firstClusterObjects, vector<sample*> secondClusterObjects);
};


#endif //K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H
