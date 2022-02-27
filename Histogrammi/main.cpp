
#include <iostream>
#include <memory>

#include "Histogram.h"
#include "HistogramBase.h"
#include "log.h"
#include "RandomEintegerGenerator.h"



int main()
{
  //pointer to Logger object
  std::unique_ptr<Logger> p = std::make_unique<Logger>();

  //make our Histogram hist
  Hist::Histogram hist(std::move(p));

  //our random Einteger generator for testdata
  Hist::RandomEintegerGenerator randomEInteger;

  //generate 1000 pseudo random value for Histogram
  for (int i = 0; i < 1000; i++) {
    hist.add(randomEInteger());
  }
  
  //print basic data from histogram
  std::cout << "Histograms max value: " << hist.getMaxValue() << std::endl;
  std::cout << "Histograms min value: " << hist.getMinValue() << std::endl;
  std::cout << "Value that has most occurence in Histogram: " << hist.getMode() << std::endl;
  return 0;
}
