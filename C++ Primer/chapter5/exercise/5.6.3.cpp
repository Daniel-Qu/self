#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
    float divisor;
    float dividend;
    float quotient;

    std::cout << "Please input dividend and divisor: " << std::endl;

    while(std::cin >> dividend >> divisor)
    {
        try
        {
            if(divisor == 0)
                throw std::overflow_error("Divisor is zero!");
            quotient = dividend / divisor;
            std::cout << "quotient: " << quotient <<std::endl;
        }
        catch(std::overflow_error error)
        {
            std::cerr << error.what()
                      << "\nTry Again? Enter y or n" << std::endl;
            char c;
            std::cin >> c;
            if(!std::cin || c == 'n')
            {
                std::cout << "Procedure Exit!" << std::endl;
                break;
            }
        }

        std::cout << "Please input dividend and divisor: " << std::endl;
    }


    return 0;
}
