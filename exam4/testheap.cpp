#include <cmath>
using namespace std;
#include <vector>
using namespace std;
#include <iostream>
using namespace std;

vector<int> buildMinHeap(vector<int> partialMinHeap)
{
    // Your code here
    for (unsigned int i = (partialMinHeap.size()-1)/2; i > 0; i--){
cout << "i : " << i << endl;
	unsigned int l = i * 2;
	unsigned int r = i * 2 + 1;
	unsigned int maxpri;
	if (r >= partialMinHeap.size()) // wrong
	    maxpri = l;
	else{
	    if (partialMinHeap[l] < partialMinHeap[r])
		maxpri = l;
	    else
		maxpri = r;
	}
cout << "maxpri : " << maxpri << endl;
	partialMinHeap[i] = partialMinHeap[maxpri] - 1;
    }
    return partialMinHeap;
}

int main(){
    std::vector<int> v;
    v.push_back(-1);
    v.push_back(299);
    v.push_back(300);    v.push_back(299);
    for (unsigned int i = 0; i < v.size();i++)
        std:: cout << v[i] << " ";
    cout<<endl;
 
   vector<int> v2 = buildMinHeap(v);
   for (unsigned int i = 0; i < v2.size();i++)
        std:: cout << v2[i] << " ";
    cout<<endl;
}

