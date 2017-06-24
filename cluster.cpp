//
// Created by Tomev on 22.06.2017.
//

#include <c++/clocale>
#include <c++/iostream>

#include "cluster.h"

cluster::cluster(long index) : index(index)
{
  this->object = NULL;
}

cluster::cluster(long index, sample *object) : index(index), object(object)
{

}

cluster::cluster(long index, cluster c) : index(index)
{
  subclusters.push_back(c);
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

  id += index;

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

void cluster::addSubcluster(cluster subcluster)
{
  subclusters.push_back(subcluster);
}


