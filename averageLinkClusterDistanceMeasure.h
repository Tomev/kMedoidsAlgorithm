#ifndef K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H
#define K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H

#include "clustersDistanceMeasure.h"

class averageLinkClusterDistanceMeasure : public clustersDistanceMeasure
{
public:

  averageLinkClusterDistanceMeasure(objectsDistanceMeasure *objDistanceMeasure);

  double countClustersDistance(cluster *cluster1, cluster *cluster2);

protected:

  double countSumOfClustersObjectsDistances(vector<sample*> *firstClusterObjects, vector<sample*> *secondClusterObjects);

};


#endif //K_MEDOIDALGORITHM_AVERAGELINKCLUSTERDISTANCEMEASURE_H
