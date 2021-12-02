#include <iostream>
#include "NumberSearch.hpp"

using namespace rasimerciyas;

int main()
{
  std::cout << "Hello World!\n";

  NumberSearch ins;

  ins.SetTargetNumber(302);
  ins.SetInputNumbers("2 3 7 10 25 50");
  std::string result = ins.GetSolution();

  return 0;
}
