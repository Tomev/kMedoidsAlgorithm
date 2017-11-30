#ifndef K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H

#include "../clustersDistanceMeasure.h"

class averageLinkClusterDistanceMeasure : public clustersDistanceMeasure
{
public:

  averageLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

  double countClustersDistance(cluster *cluster1, cluster *cluster2);

protected:

  double countSumOfClustersObjectsDistances(std::vector<std::shared_ptr<sample> > *firstClusterObjects,
                                            std::vector<std::shared_ptr<sample> > *secondClusterObjects);

};


#endif //K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H
