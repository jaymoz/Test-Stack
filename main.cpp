#include "SearchReplace.hpp"


int main(int argc, char *argv[])
{
    try
    {
        SearchReplace data("config.txt");
        data.run();

    } catch(const std::runtime_error &e)
    {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}