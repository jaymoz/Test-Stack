#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <thread>
#include <mutex>
#include <functional>


struct TemplateReplacement {
    std::string templateStr;
    std::string replacementStr;
};

class SearchReplace
{
    private:
        std::vector<std::thread>            threads;
        std::mutex                          mutex;
        std::string                         rootDirectory;
        std::vector<TemplateReplacement>    replacements;
        int                                 numThreads;
        std::ifstream                       configFile;

    public:
        SearchReplace(std::string config);
        ~SearchReplace();

        void    replaceTemplateInFile(const std::string& filePath, const std::vector<TemplateReplacement>& replacements);
        void    processDirectory(const std::string& directoryPath, const std::vector<TemplateReplacement>& replacements);
        void    configParser();
        void    run();
        void    threadFunction(const std::string& rootDirectory, const std::vector<TemplateReplacement>& replacements, std::mutex& mutex);


};
