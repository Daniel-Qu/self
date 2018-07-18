#include <iostream>


int static_calls();
int calls();
int main(int argc, char *argv[])
{
    char key;
    while(std::cin >> key && key != 'q')
    {
        std::cout << "static_calls: " << static_calls() << std::endl;
        std::cout << "calls: " << calls() << std::endl;
    }
    return 0;
}
int static_calls()
{
    static int ansower = 0;
    if(ansower++ == 0)
        return 0;
    else
        return 1;
}
int calls()
{
    int ansower = 0;
    if(ansower++ == 0)
        return 0;
    else
        return 1;
}
