#include "INumberSearch.h"
#include <map>
#include <iostream>
#include <string>
#include <queue>
namespace rasimerciyas
{

#define OPERATION_NUMBER 4

  class NumberSearch : public INumberSearch {

  private:
    int mTargetValue;
    bool combinationFound;
    std::string mCombinationStr;
    std::map<int, bool> mNumbersMap;

    enum Operations
    {
      INIT = 0,
      ADDITION,
      SUBTRACTION,
      MULTIPLICATION,
      DIVISION
    };

    // create subset with bitset method from the original set
    // for the set of 6 elements, there are 2^6 = 64 subsets
    // for every subset tries to find the combination which calculates the target number
    void createSubsetAndFindCombination()
    {
      double subsetNumber = pow(2, mNumbersMap.size());
      int bitset{ 0 };

      for (int i = 0; i < subsetNumber; i++)
      {
        bitset = i;
        std::map<int, bool> tempMap;
        std::map<int, bool>::iterator iter;
        for (iter = mNumbersMap.begin(); iter != mNumbersMap.end(); iter++)
        {
          if (bitset & 1)
          {
            tempMap.insert(std::pair<int, bool>(iter->first, iter->second));
          }
          bitset = bitset >> 0x1;
        }

        findCombination(tempMap, 0, INIT, mCombinationStr);
        
        /*
        for (iter = tempMap.begin(); iter != tempMap.end(); iter++)
        {
          std::cout << iter->first << " ";
        }
        std::cout << std::endl;
        */

        if (combinationFound)
          break;
      }
    }
    
    // find combination with trying the permutation of subset
    // all operations are taken into account
    void findCombination(std::map<int, bool> subset, int result, Operations operation, std::string combination)
    {
      if (combinationFound)
        return;

      if (subset.size() == 0)
        return;

      std::map<int, bool>::iterator iter;

      for (iter = subset.begin(); iter != subset.end(); iter++)
      {
        int tempResult = 0;

        // do arithmetic operation
        doOperation(iter, result, operation, &tempResult, combination);
        result = tempResult;

        // reached to target value
        if (result == mTargetValue)
        {
          combinationFound = true;
          mCombinationStr = combination;
          return;
        }

        // recursion with except first item
        std::map<int, bool> tempSubset = subset;
        tempSubset.erase(iter->first);

        if (tempSubset.size() != 0)
        {
          // do all operations
          for (int i = 1; i <= OPERATION_NUMBER; i++)
            findCombination(tempSubset, result, (Operations)i, combination);
        }
      } // end of for loop
    }

    // devision check
    bool controlDivision(int left, int right)
    {
      // division with zero
      if (right == 0)
        return false;
      // dvision result less than 1
      else if (left < right)
        return false;
      // devision result is floating
      else if (left % right != 0)
        return false;
      else
        return true;
    }

    void doOperation(std::map<int, bool>::iterator& iter, int left, Operations op, int* result, std::string& comb)
    {
      std::string strValue = std::to_string(iter->first);

      if (iter->second == true)
      {
        int find = comb.find(strValue);
        if (std::string::npos == find)
        {
          iter->second = false;
        }
      }
      if (iter->second == false)
      {
        iter->second = true;

        switch (op)
        {
          case ADDITION:
          {
            *result = left + iter->first;
            comb = '(' + comb + "+" + std::to_string(iter->first) + ")";
            break;
          }
          case SUBTRACTION:
          {
            *result = left - iter->first;
            comb = '(' + comb + "-" + std::to_string(iter->first) + ")";
            break;
          }
          case MULTIPLICATION:
          {
            *result = left * iter->first;
            comb = '(' + comb + "*" + std::to_string(iter->first) + ")";
            break;
          }
          case DIVISION:
          {
            // division control
            bool divisable = controlDivision(left, iter->first);
            if (divisable)
            {
              *result = left / iter->first;
              comb = '(' + comb + "/" + std::to_string(iter->first) + ")";
            }
            break;
          }
          default:
          {
            *result = iter->first;
            comb = std::to_string(iter->first);
            break;
          }
        }
      }
    }

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

      for (unsigned int index = 0; index <= values.length(); index++)
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
    const std::string & GetSolution() 
    {
      // control for the max number which is obtained from elements of the set
      std::map<int, bool>::iterator iter;
      int tempResult = 1;
      for (iter = mNumbersMap.begin(); iter != mNumbersMap.end(); iter++)
      {
        tempResult *= iter->first;
      }

      // no need to find combination
      if ((mTargetValue>INT32_MAX) || (mTargetValue > tempResult))
        combinationFound = false;
      else
        createSubsetAndFindCombination();

      if (!combinationFound)
      {
        // empty string
        mCombinationStr = "";
      }

      return mCombinationStr;
    }

  }; // end of class
} // namespace rasimerciyas
