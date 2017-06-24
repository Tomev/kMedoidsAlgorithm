//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm.h"
#include "objectsDistanceMeasure.h"

class kMedoidsAlgorithm : public groupingAlgorithm
{
  public:

    kMedoidsAlgorithm(int numberOfMedoids);
    void groupObjects(std::vector<sample*>* objects, std::vector<cluster>* target);

  private:

    int numberOfMedoids = 1;

    objectsDistanceMeasure* distanceMeasure;

    std::vector<cluster> clusters;
    std::vector<cluster> medoids;

    bool canGroupingBePerformed(std::vector<sample*>* objects);
    void clusterObjects(std::vector<sample*> *objects);
    void selectRandomMedoids();
    void assignObjectsToClusters();
      bool isAMedoid(cluster* c);
      int findClosestMedoidIndex(cluster *c);
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
