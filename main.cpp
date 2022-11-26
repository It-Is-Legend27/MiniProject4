/**
 * Mini Project #4
 * CMPS 4103 101
 * Angel Badillo, Blake Gauna
 */
#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

// Used for comparing 2nd chance pages in the find_if function
struct comp
{
	comp(unsigned int const &s) : _s(s) {}

	bool operator()(pair<unsigned int, bool> const &p)
	{
		return (p.first == _s);
	}

	unsigned int _s;
};

int main()
{
	// Seed for rand function
	srand(time(0));

	int randomNumber, pageFaultsFIFO = 0, pageFaults2nd = 0;
	
	// Queues for storing pages
	deque<unsigned int> pagesFIFO;
	deque<pair<unsigned int, bool>> pages2nd;

	//6 1's that we will & with the first 6 bits of the
	//address to get the first 6 bits
	unsigned int page_mask = 0x3F;

	//Initial loading in of the first 10 pages, as well as
	//incrementing the page fault count for both algorithms.
	for (int i = 0; i < 10; i++)
	{
		randomNumber = rand() % 4096;
		unsigned int pageNum = page_mask & (randomNumber >> 6);

		pagesFIFO.push_back(pageNum);
		pages2nd.push_back(pair<unsigned int, bool>(pageNum, true));

		pageFaultsFIFO++;
		pageFaults2nd++;
	}

	//Generating 9,990 random addresses (first 10 in queue already)
	for (int i = 0; i < 9990; i++)
	{
		randomNumber = rand() % 4096;
		//6 bit page number 
		unsigned int pageNum = page_mask & (randomNumber >> 6);
		
		// Check if page is already in the FIFO queue
		deque<unsigned int>::iterator foundPageFIFO = find(pagesFIFO.begin(), pagesFIFO.end(), pageNum);

		//Check if page is already in the second chance queue
		deque<pair<unsigned int, bool>>::iterator foundPage2nd = find_if(pages2nd.begin(), pages2nd.end(), comp(pageNum));

		//If find() returns the last element, which means that the page # wasn't found,
		//then we know we have a page fault, and we run the FIFO operation
		if (foundPageFIFO == pagesFIFO.end())
		{
			pageFaultsFIFO++;
			pagesFIFO.pop_front();
			pagesFIFO.push_back(pageNum);
		}

		//If find() returns the last element, which means that the page # wasn't found,
		//then we know we have a page fault, and we run the 2nd chance operation
		if (foundPage2nd == pages2nd.end())
		{
			pageFaults2nd++;
			pair<unsigned int, bool> temp = *(pages2nd.begin());
			//Start at the beginning of the deque, if the ref bit is 1, then we 
			//will send the page to the back with the ref bit set to 0.
			while (temp.second)
			{
				temp.second = false;
				pages2nd.pop_front();
				pages2nd.push_back(temp);
				temp = *(pages2nd.begin());
			}
			//When we find a page in the queue where the ref bit is 0, then
			//we just pop the front, send the page to the back, and set the
			//ref bit to 1.
			pages2nd.pop_front();
			pages2nd.push_back(pair<unsigned int, bool>(pageNum, true));
		}
		//If the page # is already in the queue, we set the ref bit to true.
		else
		{
			foundPage2nd->second = true;
		}
	}

	cout << "Total page faults (FIFO): " << pageFaultsFIFO << '\n';
	cout << "Total page faults (2nd chance): " << pageFaults2nd << "\n\n";
	return 0;
}