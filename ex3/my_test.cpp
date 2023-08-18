//
// Created by itay on 27/05/2022.
//

#include "Original_Queue.h"
#include <vector>

bool isNotEven(int n)
{
    return n % 2 != 0;
}

void plusOne(int& n)
{
    n = n + 1;
}

int main()
{
    int length = 0;
//    Queue<int> queue;
//    Queue<std::vector<char>> queue;
//    std::vector<char> v1 = {'A', 'B'};
//    std::vector<char> v2 = {'C', 'D', 'E'};
//    queue.pushBack(v1);
//    queue.pushBack(v2);
//    queue.pushBack(1);
//    queue.pushBack(2);
//    queue.pushBack(5);
//    queue.pushBack(3);
//    queue.pushBack(32);
//    queue.pushBack(34);
//    queue.pushBack(43);
//    queue.pushBack(22);
//    queue.pushBack(6);
//    int ans = queue.front();
//    std::cout << ans << std::endl;
//    queue.popFront();
//    ans = queue.front();
//    std::cout << ans << std::endl;
//    length = queue.size();
//    std::cout << length << std::endl;
//    int num;
//    for (int i : queue)
//    {
//        num = i;
//        std::cout << num << ",";
//    }
//    std::cout << std::endl << "After filter" << std::endl;
//    const Queue<int> queue2 = filter(queue, isNotEven);
//    for (int j : queue2)
//    {
//        num = j;
//        std::cout << num << ",";
//    }
//    transform(queue, plusOne);
//    std::cout << std::endl << "After transform" << std::endl;
//    for (int k : queue)
//    {
//        num = k;
//        std::cout << num << ",";
//    }

    Queue<std::vector<char>> q;
    std::vector<char> v1 = {'O', 'A'};
    q.pushBack(v1);
    q.pushBack(v1);
    q.front()[0] = 'D';
    std::cout << q.front()[0] << std::endl;
    q.popFront();
    std::cout << q.front()[0];
    return 0;
}
