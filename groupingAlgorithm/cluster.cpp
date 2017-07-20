#include <c++/clocale>
#include <c++/iostream>

#include "cluster.h"

cluster::cluster(long index) : index(index)
{
  this->object = NULL;
}

cluster::cluster(long index, sample *object) : index(index), object(object)
{
  findRepresentative();
}

bool cluster::representsObject()
{
  return object != NULL;
}

std::string cluster::getClustersId()
{
  std::string id;

  if(this->representsObject()) id = "O"; // For "object"
  else id = "C"; // For "cluster"

  id +=  to_string(index);

  return id;
}

bool cluster::hasSubcluster(cluster *c)
{
  for(cluster subcluster : subclusters)
  {
    if(c->getClustersId() == subcluster.getClustersId()) return true;
    if(subcluster.hasSubcluster(c)) return true;
  }

  return false;
}

sample *cluster::getObject()
{
  if(representsObject()) return object;
  else std::cout << "Cluster doesn't represent an object. Returning nullptr.\n";

  return nullptr;
}

void cluster::getObjects(vector<sample *>* target)
{
  if(target == nullptr)
  {
    cout << "Target is a null pointer. Cannot return clusters objects.\n";
    return;
  }

  // Check if cluster is singular object
  if(this->representsObject())
  {
    target->push_back(this->getObject());
    return;
  }

  for(cluster c : subclusters) c.getObjects(target);
}

void cluster::addSubcluster(cluster subcluster)
{
  subclusters.push_back(subcluster);
}

long cluster::size()
{
  if(representsObject()) return 1;

  return subclusters.size();
}

void cluster::setRepresentative(sample *newRepresentative)
{
  representative = newRepresentative;
}

void cluster::findRepresentative()
{
  if(representsObject()) representative = object;
}

sample *cluster::getRepresentative()
{
  return representative;
}




