#include <filesystem>
#include <string>
#include <iostream>
#include <utility>

std::pair<std::string, std::string> split_dir(std::string path)
{
    int index = path.rfind('/');
    std::string prefix = "../data/";
    int dot_index = path.find('.', index);
    std::cout << path << "\n";
    if (dot_index != std::string::npos)
    {
        // file
        // 0 1 2 3 4
        // a / a . b
        // index = 1
        // substr: (index+1, string.size() - (index+1))
        std::cout << "File name: " << path.substr(index + 1, path.size() - (index + 1)) << '\n';
    }
    else
    {
        // directory
    }
    return std::make_pair("hi", "hi");
}
int main()
{

    // using directory_iterator = std::filesystem::directory_iterator;

    using directory_iterator = std::filesystem::recursive_directory_iterator;
    std::string myPath = "data";
    for (const auto &dirEntry : directory_iterator(myPath))
    {
        std::cout << "path: " << dirEntry.path().string() << std::endl;
        std::cout << "\tparent path: " << dirEntry.path().parent_path() << std::endl;
        std::cout << "\tstem: " << dirEntry.path().stem() << std::endl;
        std::cout << "\textension: " << dirEntry.path().extension() << std::endl;
        std::cout << "\tfilename: " << dirEntry.path().filename() << std::endl;
        // std::cout << "file: " <<
    }
    // split_dir(std::string(dirEntry));
}