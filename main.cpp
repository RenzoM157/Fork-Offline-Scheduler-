#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <algorithm>
using namespace std;


bool compare(pair<int, pair<int, pair<int,bool> > > const& a, pair<int, pair<int, pair<int,int> > > const& b)
{
    return (a.first < b.first);
}


int main()
{
    
    vector < pair<int, pair<int,int> > > vec1;
    vector < pair<int, pair<int, pair<int,bool> > > > vec2;
    int quantum, pid, exectime, priority;
    bool finished = true;
    pid = 0;
    cin >> quantum;
   
    
    while(cin >> exectime >> priority)
    {
            vec1.push_back(make_pair(priority, make_pair(exectime, pid)));
            pid++;
        
    }
    
    int difference = 0;
    
    
	for (int i = 0; i < vec1.size(); i++) 
    {
    	int k = i + 1;
    	
    	if (k != vec1.size())
        {
         
         
        	if (vec1[i].second.first > quantum)
        	{
            	difference = vec1[i].second.first - quantum;
    
            	vec2.push_back(make_pair(vec1[i].first, make_pair(quantum, make_pair(vec1[i].second.second, !finished))));
            
           		 if (vec2[i].first == vec1[k].first && (vec1[k].second.first <= quantum))
            	 {
            		vec2.push_back(make_pair(vec1[k].first, make_pair(vec1[k].second.first, make_pair(vec1[k].second.second, finished))));
            		vec2.push_back(make_pair(vec1[i].first, make_pair(difference, make_pair(vec1[i].second.second, finished))));
            	 }
         
        	}
        	else
        	{
                vec2.push_back(make_pair(vec1[k].first, make_pair(vec1[k].second.first, make_pair(vec1[k].second.second, finished))));
        	}
        
        
        	difference = 0;
   		 }
        
    }
    
	sort(vec2.begin(), vec2.end(),compare);
	
	    
    cout << endl << "Scheduling queue: " << endl;
    cout << "\t";
    
    for(int i = 0; i < vec2.size(); i++)
    {
    	if (i != vec2.size() - 1)
		{
			cout << "(" << vec2[i].second.second.first << "," << vec2[i].second.first << "," << vec2[i].first << "), ";
		}
		else
		{
			cout << "(" << vec2[i].second.second.first << "," << vec2[i].second.first << "," << vec2[i].first << ") ";
		}
	}
	

    cout << endl << endl;
    
    for(int i = 0; i < vec2.size(); i++)
    {
    	if((pid=fork())==0)
    	{
    		
    		if (!(vec2[i].second.second.second) == finished)
    		{
    			cout << "Process " << vec2[i].second.second.first << ": " << "exec time = " << vec2[i].second.first << ", priority = " << vec2[i].first << endl;
				sleep(vec2[i].second.first);
				_exit(0);	
			}
			else
			{
				cout << "Process " << vec2[i].second.second.first << ": " << "exec time = " << vec2[i].second.first << ", priority = " << vec2[i].first << endl;
				cout << "Process " << vec2[i].second.second.first << " ends." << endl;
				sleep(vec2[i].second.first);
				_exit(0);
			}
		}
		else
		{
			wait(NULL);
		}
	}
    
    return 0;
}
