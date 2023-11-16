#include <iostream>
using namespace std;

// int hello (int num);

static int hello (int num) {
    return num;
}

int main()
{
    cout << hello(5);
}