#include <cmath>
using namespace std;
#include <vector>
using namespace std;

vector<int> buildMinHeap(vector<int> partialMinHeap)
{
    // Your code here
    for (unsigned int i = (partialMinHeap.size()-1)/2; i > 0; i--){
	unsigned int l = i * 2;
	unsigned int r = i * 2 + 1;
	unsigned int maxpri;
	if (r < partialMinHeap.size())
	    maxpri = l;
	else{
	    if (partialMinHeap[l] < partialMinHeap[r])
		maxpri = l;
	    else
		maxpri = r;
	}
	partialMinHeap[i] = partialMinHeap[maxpri] - 1;
    }
    return partialMinHeap;
}
