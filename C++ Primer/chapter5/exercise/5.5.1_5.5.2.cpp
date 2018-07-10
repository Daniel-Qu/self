#include<iostream>
#include<string>
#include<vector>
#include<cctype>

int main(int argc, char *argv[])
{
    std::string word;
    std::string temp;
    while(std::cin >> word && word != "#")
    {
        if(temp == word && std::isupper(word[0]))
        {
            std::cout << word << std::endl;
            break;
        }
        else
        {
            temp = word;
            continue;
        }
    }
    // std::getchar();
    if(word == "#")
    {
        std::cout << "No repeat!" << std::endl;
    }
    return 0;
}
