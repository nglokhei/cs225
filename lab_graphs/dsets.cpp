/* Your code here! */

#include "dsets.h"

void DisjointSets :: addelements (int num){
    for (int i = 0; i < num; i++)
	s.push_back(-1);
}

int DisjointSets::find (int elem) {
    if (s[elem] < 0) 
	return elem;
    
    s[elem] = find(s[elem]);
    return s[elem];
}

void DisjointSets :: setunion (int a, int b){
    int s1 = find(a);
    int s2 = find(b);
    
    if (s1 == s2)
	return;

    int newsize = s[s1] + s[s2];
    if (s[s1] <= s[s2]){
	s[s2] = s1;
	s[s1] = newsize;
    }
    else {
	s[s1] = s2;
	s[s2] = newsize;
    }
}



