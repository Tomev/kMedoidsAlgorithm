#include <iostream>
#include <c++/ctime>

#include "dataReader.h"
#include "dataParser.h"
#include "textDataReader.h"
#include "textDataParser.h"
#include "groupingAlgorithm.h"
#include "kMedoidsAlgorithm.h"

int main()
{
  // Initialize time-dependent random seed
  srand (time(NULL));

  std::ifstream sourceFile("D:\\Dysk Google\\Data Streams\\sensor.arff");

  dataReader* dr = new textDataReader(&sourceFile);
  dataParser* dp = new textDataParser();

  dr->gatherAttributesData(NULL);

  std::string line;
  std::vector<sample*> samples;
  std::vector<cluster> clusters;

  for(int i = 0; i < 1000; ++i)
  {
    dr->getNextRawDatum(dp->buffer);
    dp->addDatumToContainer(&samples);
    dp->parseData(samples.back());
  }

  groupingAlgorithm* a = new kMedoidsAlgorithm(10);

  a->groupObjects(&samples, &clusters);

  std::cout << "Clusters size: " <<  clusters.size() << std::endl;

  return 0;
}