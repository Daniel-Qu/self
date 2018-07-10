#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

int main(int argc, char *argv[])
{
    std::vector<std::string> words;
    std::string word;
    std::string temp;
    int quantity = 1;
    int count = 0;
    std::vector<int> quantitys;
    while(std::cin >> word)
    {
        if(temp == word)
        {
            ++quantity;
        }
        else
        {
            if(word == "#")
            {
                quantitys[count - 1] = quantity;
                std::cout << "Done!" << std::endl;
                break;
            }
            ++count;
            words.push_back(word);
            if(quantity == 1)
            {
                quantitys.push_back(quantity);
            }
            else
            {
                quantitys[count - 2] = quantity;
                quantity = 1;
                quantitys.push_back(quantity);
            }
        }
        temp = word;
        std::cout << "word: " << word << std::endl;
    }
    std::getchar();
    std::cout << "words.size(): " << words.size() << std::endl;
    std::cout << "quantitys.size(): " << quantitys.size() << std::endl;
    for(decltype(words.size()) i = 0; i != words.size(); i++)
    {
        std::cout << words[i] << ": " << quantitys[i] << std::endl;
    }
    auto quantity_max_position = std::max_element(quantitys.begin(), quantitys.end());
    std::cout << "the most frequent: " << words[int(quantity_max_position - quantitys.begin())] << std::endl;
    // std::cout << "word: " << word << std::endl;
    // std::string sentence;
    // while(std::getline(std::cin, sentence))
    // {
    //     if(sentence.empty())
    //         break;
    // }
    return 0;
}

