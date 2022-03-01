// ----------------- Histogram.h ---------------

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <memory>

#include "HistogramBase.h"


/*
HistogramBase-luokan default constructor = delete esti kaikkien constructorien käyttämisen lapsiluokassa, joten poistettu constructori vasta lapsiluokassa.
m_log oli private, joten siihen ei ollut pääsyä lapsiluokasta. Muokattu private -> protected
*/


namespace Hist{

  class Histogram : HistogramBase {
  public:
    
    //delete default constructor
    Histogram() = delete;

    //delete copy constructor because we can't copy unique_pointer without destroying it
    Histogram(Histogram&) = delete;

    

    //since we need ponter to Logger object for this to work
    Histogram(std::unique_ptr<Logger> p){
      this->m_log = std::move(p);
    };
   
    ~Histogram() {};


    //If value is already in our histogram, we increase its occurence by one, otherwise we add new 
    //key to our data and put its value to 1
    //we also update our Min and Max values if needed
    void add(EInteger value){
      this->m_Data[value]++;

      //if value is smaller than smallest saved value in histogram we update m_MinValue:
      if(value < this->m_MinValue) this->m_MinValue = value;
      //if value is larger than our saved highest value we update m_MaxValue;
      if(value > this->m_MaxValue) this->m_MaxValue = value;

      //if added value changes our highest frequency -> update m_MostFrequency pair
      if(m_Data[value] > this->m_MostFrequency.second){
        this->m_MostFrequency.first = value;
        this->m_MostFrequency.second = this->m_Data[value];
      }
    };

    // Return the value that occurrs most often in the data set (I.e. there exists no other value that occurs more often than the return value)
    EInteger getMode() const {
      return this->m_MostFrequency.first;
    };

    // Return the smallest value in the data set
    EInteger getMinValue() const {
      return static_cast<EInteger>(this->m_MinValue);
    };

    // Return the largest value in the data set
    EInteger getMaxValue() const {
      return static_cast<EInteger>(this->m_MaxValue);
    };


  private:
    //These store our smallest and highest number in histogram
    //IF we dont allow negative numbers in EInteger we could use unsigned
    //if we need larger numbers than integer, we could also use long or unsingned long
    int m_MinValue{ INT_MAX };
    int m_MaxValue{ 0 };
 

    //int m_MostFrequency;
    //key and frequency stored here for easier access
    std::pair<EInteger, int> m_MostFrequency;

    //Actual histogram is here. EInteger is the key and int is frequency
    //use unordered map, because we only need fast lookup times
    std::unordered_map<EInteger, int> m_Data;



    //if we need to update our min and max values manually
    //we have to iterate whole unordered_map to get the correct values.
    //usually we update our values while adding new ones to histogram
    void updateMaxValue(){
      int maxSoFar = 0;

      for(auto i: this->m_Data){
        maxSoFar = std::max(maxSoFar, (int)i.first); 
      }

      this->m_MaxValue = maxSoFar;
    };

    void updateMinValue(){
      int minSoFar = INT_MAX;
      
      for(auto i: this->m_Data){
        minSoFar = std::min(minSoFar, (int)i.first); 
      }

      this->m_MinValue = minSoFar;
    };
    

    //if we have to manually update highest frequency. Usually we check this while we add new values to histogram
    //find key that has most frequency from dataset
    void updateMostFrequency(){
      std::pair<EInteger, int> mostFrequencySoFar;
      
      for(auto i: this->m_Data){
        
        //lets do this the good old way
        if (mostFrequencySoFar.second < i.second) {
          mostFrequencySoFar.second = i.second;
          mostFrequencySoFar.first = i.first;
        }
      }

      this->m_MostFrequency = mostFrequencySoFar;
    };
  };
}

#endif