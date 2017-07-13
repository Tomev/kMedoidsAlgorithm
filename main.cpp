#include <iostream>
#include <c++/ctime>
#include <unordered_map>

#include "dataReader.h"
#include "dataParser.h"
#include "textDataReader.h"
#include "textDataParser.h"
#include "groupingAlgorithm.h"
#include "kMedoidsAlgorithm.h"

// Tests
void checkAttributesData(unordered_map<string, attributeData*> *attributesData);

using namespace std;

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");

  // Generate samples and gather attributes data

  unordered_map<string, attributeData*> attributesData;

  dataReader* dr = new textDataReader(&sourceFile);
  dataParser* dp = new textDataParser(&attributesData);

  dr->gatherAttributesData(&attributesData);
  dp->setAttributesOrder(dr->getAttributesOrder());

  string line;
  vector<sample*> samples;
  vector<cluster> clusters;

  for(int i = 0; i < 1000; ++i)
  {
    dr->getNextRawDatum(dp->buffer);
    dp->addDatumToContainer(&samples);
    dp->parseData(samples.back());
  }

  // Group objects

  groupingAlgorithm* a = new kMedoidsAlgorithm(10);

  a->groupObjects(&samples, &clusters);

  //Tests

  //checkAttributesData(&attributesData);

  cout << "Clusters size: " <<  clusters.size() << endl;

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
}