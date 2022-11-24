#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

struct comp
{
    comp(unsigned int const& s) : _s(s) { }

    bool operator () (pair<unsigned int, bool> const& p)
    {
        return (p.first == _s);
    }

    unsigned int _s;
};

bool isPageFaultFIFO(deque<unsigned int> q, unsigned pageNum)
{
	return find(q.begin(), q.end(), pageNum) == q.end();
}

bool isPageFault2nd(deque<pair<unsigned int, bool>> q, unsigned pageNum)
{
	return find_if(q.begin(), q.end(), comp(pageNum)) == q.end();
}

int main()
{
	srand(time(0));
	int randomNumber;
	deque<unsigned int> pages;
	deque<pair<unsigned int, bool>> second;
	int pageFaults = 0;
	int pageFaults2 = 0;
	
	unsigned int page_mask = 0x3F;

	for (int i = 0; i < 30; i++)
	{
		randomNumber = rand() % 4096;
		unsigned int pageNum = page_mask & (randomNumber >> 6);

		if(isPageFaultFIFO(pages, pageNum))
		{
			pageFaults++;

			if(pages.size() > 10)
				pages.pop_front();

			pages.push_back(pageNum);
		}


		if(isPageFault2nd(second, pageNum))
		{
			pageFaults2++;

			// TODO: Make this work
			if(second.size() > 10)
			{
				pair<unsigned int, bool> temp = *(second.begin());
			}
			second.push_back(pair<unsigned int, bool>(pageNum, true));
		}
		  
	}
	
	for (int i = 0; i < pages.size(); i++)
	{
		cout << pages[i] << endl;
	}

	cout << endl << "Total page faults: " << pageFaults << endl;

	return 0;
}
// cout << hex << pageNum << endl; //first 6 bits in hex
// cout << hex << page << endl; //last 6 bits in hex
// cout << randomNumber << endl;
// cout << hex << randomNumber << endl;