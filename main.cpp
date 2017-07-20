#include <iostream>
#include <c++/ctime>
#include <unordered_map>

#include "dataReader.h"
#include "dataParser.h"
#include "dataReaders/textDataReader.h"
#include "dataParsers/textDataParser.h"
#include "groupingAlgorithm/groupingAlgorithm.h"
#include "kMedoidsAlgorithm.h"
#include "numericalAttributeData.h"
#include "attributesDistanceMeasures/categorical/smdCategoricalAttributesDistanceMeasure.h"
#include "attributesDistanceMeasures/numerical/gowersNumericalAttributesDistanceMeasure.h"
#include "customObjectsDistanceMeasure.h"
#include "clusterDistanceMeasures/singleLinkClusterDistanceMeasure.h"
#include "clusterDistanceMeasures/completeLinkClusterDistanceMeasure.h"
#include "clusterDistanceMeasures/averageLinkClusterDistanceMeasure.h"
#include "clusterDistanceMeasures/centroidLinkClusterDistanceMeasure.h"

// Tests
void checkAttributesData(unordered_map<string, attributeData*> *attributesData);
void checkDistanceMeasurePerformance(vector<sample*> *samples, unordered_map<string, attributeData*> *attributesData);

using namespace std;

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  // Get source file
  ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");

  // Initialize timer
  clock_t begin = clock();

  // Generate samples and gather attributes data
  unordered_map<string, attributeData*> attributesData;

  dataReader* dr = new textDataReader(&sourceFile);
  dataParser* dp = new textDataParser(&attributesData);

  dr->gatherAttributesData(&attributesData);
  dp->setAttributesOrder(dr->getAttributesOrder());

  vector<sample*> samples;
  vector<cluster> clusters;

  for(int i = 0; i < 50; ++i)
  {
    dr->getNextRawDatum(dp->buffer);
    dp->addDatumToContainer(&samples);
    dp->parseData(samples.back());
  }

  // Group objects
  attributesDistanceMeasure* ndm = new gowersNumericalAttributesDistanceMeasure(&attributesData);
  attributesDistanceMeasure* cdm = new smdCategoricalAttributesDistanceMeasure();
  objectsDistanceMeasure* odm = new customObjectsDistanceMeasure(cdm, ndm, &attributesData);
  clustersDistanceMeasure* cludm = new completeLinkClusterDistanceMeasure(odm);
  groupingAlgorithm* a = new kMedoidsAlgorithm(10, cludm);

  a->groupObjects(&samples, &clusters);

  //Tests

  //checkAttributesData(&attributesData);
  //checkDistanceMeasurePerformance(&samples, &attributesData);

  clock_t end = clock();

  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << "Medoids found in " << elapsed_secs << " seconds.";

  return 0;
}

void checkAttributesData(unordered_map<string, attributeData*> *attributesData)
{
  cout << "Attributes number: " << attributesData->size() << endl;

  // Gather keys
  vector<string> keys;
  keys.reserve(attributesData->size());

  for(auto kv : *attributesData) keys.push_back(kv.first);

  cout << "Attributes:\n";

  for(string attributeName : keys) cout << attributeName << endl;

  numericalAttributeData *numAttribute = static_cast<numericalAttributeData*>(attributesData->at("rcdminutes"));

  cout << "Min: " << numAttribute->getMinimalValue() << ", Max: " << numAttribute->getMaximalValue() << endl;
}

void checkDistanceMeasurePerformance(vector<sample*> *samples, unordered_map<string, attributeData*> *attributesData)
{
  attributesDistanceMeasure* ndm = new gowersNumericalAttributesDistanceMeasure(attributesData);
  attributesDistanceMeasure* cdm = new smdCategoricalAttributesDistanceMeasure();

  objectsDistanceMeasure* dm = new customObjectsDistanceMeasure(cdm, ndm, attributesData);

  cout << dm->countObjectsDistance(samples->at(0), samples->at(0)) << endl;
  cout << dm->countObjectsDistance(samples->at(1), samples->at(1)) << endl;
  cout << dm->countObjectsDistance(samples->at(0), samples->at(1)) << endl;
  cout << dm->countObjectsDistance(samples->at(1), samples->at(0)) << endl;
}