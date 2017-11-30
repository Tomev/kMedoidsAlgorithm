#ifndef K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H

#include "../clustersDistanceMeasure.h"

class singleLinkClusterDistanceMeasure : public clustersDistanceMeasure
{
  public:

    singleLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

    double countClustersDistance(cluster *cluster1, cluster *cluster2);

  protected:

    double findLowestDistance(std::vector<std::shared_ptr<sample>> *firstClusterObjects,
                              std::vector<std::shared_ptr<sample>> *secondClusterObjects);
};


#endif //K_MEDOIDALGORITHM_SINGLELINKCLUSTERDISTANCEMEASURE_H
