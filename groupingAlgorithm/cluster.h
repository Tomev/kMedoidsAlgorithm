#ifndef K_MEDOIDALGORITHM_CLUSTER_H
#define K_MEDOIDALGORITHM_CLUSTER_H

#include <c++/vector>
#include <string>
#include <memory>

#include "sample.h"

class cluster
{
  public:

    cluster(long index);
    cluster(long index, std::shared_ptr<sample> object);

    bool representsObject();
    std::string getClustersId();

    std::shared_ptr<sample> getObject();
    void getObjects(std::vector<std::shared_ptr<sample>> *target);
    void getSubclusters(std::vector<std::shared_ptr<cluster>> *target);

    void addSubcluster(std::shared_ptr<cluster> subcluster);

    bool hasSubcluster(std::shared_ptr<cluster> c);

    long size();

    void setWeight(double weight);
    double getWeight();

    cluster *getMedoid();
    void setMedoid(std::shared_ptr<cluster> newMedoid);

    void setRepresentative(sample *newRepresentative);
    void findRepresentative();
    sample* getRepresentative();

  protected:

    long index;
    double weight = 0;

    std::shared_ptr<sample> object;
    sample* representative;
    std::shared_ptr<cluster> medoid;

    std::vector<std::shared_ptr<cluster>> subclusters;


};


#endif //K_MEDOIDALGORITHM_CLUSTER_H
