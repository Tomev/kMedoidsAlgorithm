#ifndef K_MEDOIDALGORITHM_CENTROIDLINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_CENTROIDLINKCLUSTERDISTANCEMEASURE_H

#include "../clustersDistanceMeasure.h"

class centroidLinkClusterDistanceMeasure : public clustersDistanceMeasure
{
  public:
    centroidLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

    double countClustersDistance(cluster *cluster1, cluster *cluster2);
};


#endif //K_MEDOIDALGORITHM_CENTROIDLINKCLUSTERDISTANCEMEASURE_H
