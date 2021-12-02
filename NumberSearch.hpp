//berkcanozutemiz.hpp
#pragma once
#include "INumberSearch.h"
#include <map>
#include <iostream>
#include <string>
#include <queue>
namespace rasimerciyas 
{
  class NumberSearch : public INumberSearch {

    private:
      int mTargetValue;
      bool combinationFound;
      std::string mCombinationStr;
      std::map<int, bool> mNumbersMap;

    public:
      NumberSearch() :mTargetValue(0), combinationFound(false)
      {
      }

      ~NumberSearch() 
      {
      }

      // Number to reach (302)
      void SetTargetNumber(const int value) {
        mTargetValue = value;
      }

      // Accept numbers as a space separated values : “2 3 7 10 25 50”
      void SetInputNumbers(const std::string & values) 
      {
        int tempValueInt;
        std::string tempValue = "";

        for(int index = 0; index <= values.length(); index++)
        {
          // '\0' is added for the last number
          if (values[index] == ' ' || values[index] == '\0')
          {
            tempValueInt = std::atoi(tempValue.c_str());
            mNumbersMap.insert(std::pair<int, bool>(tempValueInt, false));
            tempValue = "";
            continue;
          }
          else
          {
            tempValue += values[index];
          }
        }
      }

      // Return result as a string ready to evaluate : “(((2+10)*3)*7)+50)”
      const std::string & GetSolution() {

        createSubsetAndFindCombination();

        if (!combinationFound)
        {
          // empty string
          mCombinationStr = "";
        }

        return mCombinationStr;
      }

      void createSubsetAndFindCombination()
      {
        int subsetNumber = pow(2, mNumbersMap.size());
        int bitset = 0;

        for (int i = 0; i < subsetNumber; i++)
        {
          bitset = i;
          std::map<int, bool> tempMap;
          std::map<int, bool>::iterator iter;
          for (iter = mNumbersMap.begin(); iter != mNumbersMap.end(); iter++)
          {
            if (bitset & 1)
            {
              tempMap.insert(std::pair<int, bool>(iter->first, iter->first));
            }
            bitset = bitset >> 1;
          }
          for (iter = tempMap.begin(); iter != tempMap.end(); iter++)
          {
            std::cout << iter->first << " ";
          }
          std::cout << std::endl;
        }
      }
    };
}
