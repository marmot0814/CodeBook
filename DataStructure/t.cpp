#include <iostream>
#include <queue>
using namespace std;
int main(){
    priority_queue<int, vector<int>, greater<int> > pq;
    pq.push(8);
    pq.push(4);
    cout << pq.top() << '\n';

}
