
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

  //make our Histogram first and move unique pointer p to it
  Hist::Histogram first(std::move(p));

  //our random Einteger generator for testdata
  Hist::RandomEintegerGenerator randomEInteger;

  //generate 1000 pseudo random value for Histogram
  for (int i = 0; i < 1000; i++) {
    first.add(randomEInteger());
  }
  
  //print basic data from histogram
  std::cout << "Histogram first: max value: " << first.getMaxValue() << "\n";
  std::cout << "Histograms first: min value: " << first.getMinValue() << "\n";
  std::cout << "Value that first: has most occurence in Histogram: " << first.getMode() << "\n\n";


  //test our move constructor
  Hist::Histogram second(std::move(first));

  //print basic data from histogram
  std::cout << "Histograms first: max value: " << first.getMaxValue() << "\n";
  std::cout << "Histograms first: min value: " << first.getMinValue() << "\n";
  std::cout << "Value that first: has most occurence in Histogram: " << first.getMode() << "\n\n";

  //print basic data from histogram
  std::cout << "Histograms second: max value: " << second.getMaxValue() << "\n";
  std::cout << "Histograms second: min value: " << second.getMinValue() << "\n";
  std::cout << "Value that second: has most occurence in Histogram: " << second.getMode() << std::endl;

  return 0;
}
