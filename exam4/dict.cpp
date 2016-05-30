#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> orderedGroup(int arr[], int size)
{
    // Your Code Here
    std::map<int,int> count;
    std::map<int,bool> here;
    std::vector<int> order;
    std::vector<int> ret;

    for(int i = 0; i < size; i++){
	int key = arr[(unsigned int)i];
	count[key]++;
	if (count[key] == 1)
	    order.push_back(key);
    }

    for (unsigned int i = 0; i < order.size(); i++){
	int key = order[i];
	int num = count[key];
	for (int j = 0; j < num;j++)
	    ret.push_back(key);
    }
    return ret; 
}
