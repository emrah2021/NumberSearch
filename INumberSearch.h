#include <string>
namespace rasimerciyas
{
  class INumberSearch {
    protected:
      virtual ~INumberSearch() {}
      virtual void SetTargetNumber(const int value) = 0;
      virtual void SetInputNumbers(const std::string & values) = 0;
      virtual const std::string & GetSolution() = 0;
  };
}
