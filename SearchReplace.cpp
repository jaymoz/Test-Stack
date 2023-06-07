#include "SearchReplace.hpp"

SearchReplace::SearchReplace(std::string config)
{
    this->configFile.open(config);
    if (!this->configFile)
        throw std::runtime_error("Ошибка открытия конфигурационного файла");
    SearchReplace::configParser();
    
}

SearchReplace::~SearchReplace()
{
    std::cout << "Работа выполнена" << std::endl;  
}

void    SearchReplace::replaceTemplateInFile(const std::string& filePath, const std::vector<TemplateReplacement>& replacements)
{
    std::ifstream file(filePath);
    if (!file)
        throw std::runtime_error("Ошибка открытия файла");

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    for (const auto& replacement : replacements) {
        size_t pos = 0;
        while ((pos = content.find(replacement.templateStr, pos)) != std::string::npos) {
            content.replace(pos, replacement.templateStr.length(), replacement.replacementStr);
            pos += replacement.replacementStr.length();
        }
    }

    std::ofstream outputFile(filePath);
    if (!outputFile) {
        std::cerr << "Ошибка открытия файла для записи: " << filePath << std::endl;
        return;
    }

    outputFile << content;
    outputFile.close();
}

void    SearchReplace::processDirectory(const std::string& directoryPath, const std::vector<TemplateReplacement>& replacements)
{
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            processDirectory(entry.path().string(),replacements);
        } else if (entry.is_regular_file()) {
            replaceTemplateInFile(entry.path().string(), replacements);
        }
    }
}

void    SearchReplace::configParser()
{
    std::string line;

    while (std::getline(this->configFile, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        
        std::stringstream linestream(line);
        std::string key;
        std::string value;
        std::getline(linestream, key, '=');
        std::getline(linestream, value);

        if (key == "NUM_THREADS")
            this->numThreads = std::stoi(value);
        else if (key == "ROOT_DIRECTORY")
            this->rootDirectory = value;
        else
            this->replacements.push_back({key, value});
    }
    this->configFile.close();

    if (this->numThreads <= 0)
        throw std::runtime_error("Количество потоков должно быть положительным числом");
    
    if (this->rootDirectory.empty())
        throw std::runtime_error("Не указана корневая директория");
    
    if (this->replacements.empty())
        throw::std::runtime_error("Не указаны шаблоны и их замены");

}

void    SearchReplace::threadFunction(const std::string& rootDirectory, const std::vector<TemplateReplacement>& replacements, std::mutex& mutex) {
    std::lock_guard<std::mutex> lock(this->mutex);
    SearchReplace::processDirectory(rootDirectory, replacements);
}

void    SearchReplace::run()
{
    for (int i = 0; i < this->numThreads; ++i) {
        threads.emplace_back(&SearchReplace::threadFunction, this, std::ref(this->rootDirectory), std::ref(this->replacements), std::ref(this->mutex));
    }

    for (auto& thread : threads) {
        thread.join();
    } 

}