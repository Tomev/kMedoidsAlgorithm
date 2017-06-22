//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
#define K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H

#include "groupingAlgorithm.h"

class kMedoidsAlgorithm : public groupingAlgorithm
{
  public:

    kMedoidsAlgorithm(int numberOfMedoids);
    void groupObjects(std::vector<sample>* objects, std::vector<cluster>* target);

  private:

    int numberOfMedoids = 1;

    std::vector<cluster> clusters;
    std::vector<cluster*> medoids;

    bool canGroupingBePerformed(std::vector<sample>* objects);
    void clusterObjects(std::vector<sample> *objects);
    void selectRandomMedoids();
};


#endif //K_MEDOIDALGORITHM_KMEDOIDSALGORITHM_H
