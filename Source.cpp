#include <iostream>
#include <bitset>
#include <queue>
#include <vector>

using namespace std;

void showq(queue<int> gq)
{
	queue<int> g = gq;
	while (!g.empty()) {
		cout << '\t' << g.front();
		g.pop();
	}
	cout << '\n';
}

int main() {
	srand(time(0));
	int randomNumber;
	vector<int> pages;
	int pageFaults = 0;

	queue<int> que;
	unsigned int page_mask = 0x3F;
	for (int i = 0; i < 10; i++) {
		randomNumber = rand() % 4096;

		unsigned int pageNum = page_mask & (randomNumber >> 6);

		if (que.size() > 10) {
			for (int i = 0; i < pages.size(); i++) {
				if (pageNum == pages[i]) {
					return;
				}
				else
				{

				}
			}
			que.pop();
			que.push(pageNum);

		}
		else
		{
			que.push(pageNum);
			pages.push_back(pageNum)
		}
	}

	
	return 0;
}
//cout << hex << pageNum << endl; //first 6 bits in hex
//cout << hex << page << endl; //last 6 bits in hex
//cout << randomNumber << endl;
//cout << hex << randomNumber << endl;