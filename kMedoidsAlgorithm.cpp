//
// Created by Tomev on 22.06.2017.
//

#include <iostream>
#include <algorithm>
#include <set>
#include <random>

#include "kMedoidsAlgorithm.h"

kMedoidsAlgorithm::kMedoidsAlgorithm(int numberOfMedoids) : numberOfMedoids(numberOfMedoids)
{

}

bool kMedoidsAlgorithm::canGroupingBePerformed(std::vector<sample>* objects)
{
  if(objects->size() > numberOfMedoids)
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

void kMedoidsAlgorithm::groupObjects(std::vector<sample> *objects, std::vector<cluster>* target)
{
  if(! canGroupingBePerformed(objects)) return;

  clusterObjects(objects);
  selectRandomMedoids();


}

void kMedoidsAlgorithm::clusterObjects(std::vector<sample> *objects)
{
  for(sample object : *objects) clusters.push_back(cluster(&object));
}

void kMedoidsAlgorithm::selectRandomMedoids()
{
  std::set<int> medoidsIndexes;

  // Randomize medoid indexes until required number is achieved.
  while(medoidsIndexes.size() != numberOfMedoids) medoidsIndexes.insert(rand() % clusters.size());

  // Place medoids in proper holder.
  for(int medoidsIndex : medoidsIndexes) medoids.push_back(&clusters.at(medoidsIndex));
}

