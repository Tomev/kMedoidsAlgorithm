//
// Created by Tomev on 22.06.2017.
//

#include <iostream>
#include <algorithm>
#include <set>

#include "kMedoidsAlgorithm.h"

kMedoidsAlgorithm::kMedoidsAlgorithm(int numberOfMedoids, clustersDistanceMeasure* clusDistanceMeasure) :
  numberOfMedoids(numberOfMedoids), clusDistanceMeasure(clusDistanceMeasure) {}

bool kMedoidsAlgorithm::canGroupingBePerformed(std::vector<sample*>* objects)
{
  if(objects->size() < numberOfMedoids)
  {
    std::cout << "Number of medoids is greater than objects number.\n";
    return false;
  }

  if(numberOfMedoids <= 0)
  {
    std::cout << "Number of medoids is lower or equal 0.\n";
    return false;
  }

  return true;
}

void kMedoidsAlgorithm::groupObjects(std::vector<sample*> *objects, std::vector<cluster>* target)
{
  if(!canGroupingBePerformed(objects)) return;

  clusterObjects(objects);
  selectRandomMedoids();

  double lowestCost = countCost(&medoids);

  cout << lowestCost;

  *target = std::vector<cluster>(medoids);
}

void kMedoidsAlgorithm::clusterObjects(std::vector<sample*> *objects)
{
  for(int clusterNumber = 0; clusterNumber < objects->size(); ++clusterNumber)
    clusters.push_back(cluster(clusterNumber+1, objects->at(clusterNumber)));
}

void kMedoidsAlgorithm::selectRandomMedoids()
{
  std::set<int> medoidsIndexes;

  // Randomize medoid indexes until required number is achieved.
  while(medoidsIndexes.size() != numberOfMedoids) medoidsIndexes.insert(rand() % clusters.size());

  // Place medoids in proper holder.

  long medoidNumber = 0;

  for(int medoidsIndex : medoidsIndexes)
    medoids.push_back(cluster(medoidNumber++, clusters.at(medoidsIndex)));
}

double kMedoidsAlgorithm::countCost(vector<cluster> *potentialMedoids)
{
  double cost = 0;

  for(cluster c : clusters)
  {
    if(!isAMedoid(&c))
    {
      int closestMedoidIndex = findClosestMedoidIndex(&c, potentialMedoids);

      cost += clusDistanceMeasure->countClustersDistance(&c, &(potentialMedoids->at(closestMedoidIndex)));
    }
  }

  return cost;
}

bool kMedoidsAlgorithm::isAMedoid(cluster *c)
{
  for(cluster medoid : medoids)
    if(c->getClustersId() == medoid.getClustersId()) return true;

  return false;
}

int kMedoidsAlgorithm::findClosestMedoidIndex(cluster *c, vector<cluster>* potentialMedoids)
{
  int closestMedoidIndex = 0;
  double minDistance = clusDistanceMeasure->countClustersDistance(&(potentialMedoids->at(0)), c), distance;

  for(int medoidIndex = 1; medoidIndex < potentialMedoids->size(); ++medoidIndex)
  {
    distance = clusDistanceMeasure->countClustersDistance(&(potentialMedoids->at(medoidIndex)), c);

    if(distance < minDistance)
    {
      minDistance = distance;
      closestMedoidIndex = medoidIndex;
    }
  }

  return closestMedoidIndex;
}


