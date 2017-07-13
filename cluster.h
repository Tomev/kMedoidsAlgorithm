//
// Created by Tomev on 22.06.2017.
//

#ifndef K_MEDOIDALGORITHM_CLUSTER_H
#define K_MEDOIDALGORITHM_CLUSTER_H

#include <c++/vector>
#include <string>

#include "sample.h"

class cluster
{
  public:

    cluster(long index);
    cluster(long index, sample* object);
    cluster(long index, cluster c);

    bool representsObject();
    std::string getClustersId();

    sample* getObject();
    void getObjects(vector<sample*>* target);

    void addSubcluster(cluster subcluster);

    bool hasSubcluster(cluster* c);

  private:

    int index;
    sample* object;
    sample* representative;

    std::vector<cluster> subclusters;
};


#endif //K_MEDOIDALGORITHM_CLUSTER_H
