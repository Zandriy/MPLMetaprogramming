#include <map>
#include <list>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;
void copy_list_map(list<string>& l, map<string, string>& m)
{
    copy(l.begin(), l.end(), back_inserter(m));
}

int main()
{
}
