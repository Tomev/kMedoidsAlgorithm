//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm.h"
#include "objectsDistanceMeasure.h"
#include "clustersDistanceMeasure.h"

class kMedoidsAlgorithm : public groupingAlgorithm
{
  public:

    kMedoidsAlgorithm(int numberOfMedoids, clustersDistanceMeasure* clusDistanceMeasure);
    void groupObjects(std::vector<sample*>* objects, std::vector<cluster>* target);

  protected:

    int numberOfMedoids = 1;

    clustersDistanceMeasure* clusDistanceMeasure;

    std::vector<cluster> clusters;
    std::vector<cluster> medoids;

    bool canGroupingBePerformed(std::vector<sample*>* objects);
    void clusterObjects(std::vector<sample*> *objects);
    void selectRandomMedoids();
    double countCost(vector<cluster> *potentialMedoids);
      bool isAMedoid(cluster* c);
      int findClosestMedoidIndex(cluster *c, vector<cluster>* potentialMedoids);
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
