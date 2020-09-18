#include <map>
#include <vector>
#include <algorithm>
int main()
{
    std::map<int,int> a;
    std::vector<int> v(20);
    std::copy(a.begin(), a.end(), v.begin());
    return 0;
}
