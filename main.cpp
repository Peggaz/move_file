#include <iostream>
#include <filesystem>
#include <fstream>
#include "vector"
const int MAX_FILES_IN_DIRECTORY = 10;
const std::string DIRECTORY_NAME = "/katalog";
namespace fs = std::filesystem;
void print_directory(std::string src);
void add_file(std::string src);
int count_files(std::string src);
std::vector<std::string> get_files(std::string src);
void move_files(std::string src);



int main(int argc, char *argv[]) {
    std::string directory_path = argv[1];
//    print_directory(directory_path);
//
//    add_file(directory_path);
//    print_directory(directory_path);
    int count = count_files(directory_path);
    if(count == -1){
        std::cerr << "Błąd podczas liczenia plików." << std::endl;
        return -1;
    } else if(count > MAX_FILES_IN_DIRECTORY){
        //TODO: przenoszenie plików do katalogów
        move_files(directory_path);
        return 0;
    }

    return 0;
}


void print_directory(std::string src) {
    if (!fs::is_directory(src)) {
        throw "Podana ścieżka nie jest katalogiem.";
    }
    std::cout << "Pliki w katalogu " << src << ":" << std::endl;
    for (const auto &entry : fs::directory_iterator(src)) {
        if (entry.is_regular_file()) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
}
void add_file(std::string src){
    if (!fs::is_directory(src)) {
        std::cerr << "Podana ścieżka nie jest katalogiem." << std::endl;
        return;
    }

    for (int i = 1; i <= 100; ++i) {
        std::string filename = src + "/plik" + std::to_string(i) + ".txt";
        std::ofstream file(filename);

        if (file.is_open()) {
            file.close();
        } else {
            std::cerr << "Błąd podczas tworzenia pliku: " << filename << std::endl;
        }
    }
}
int count_files(std::string src){
    if (!fs::is_directory(src)) {
        std::cerr << "Podana ścieżka nie jest katalogiem." << std::endl;
        return -1;
    }
    int count = 0;
    for (const auto &entry : fs::directory_iterator(src)) {
        if (entry.is_regular_file()) {
            count++;
        }
    }
    return count;
}
std::vector<std::string> get_files(std::string src){
    std::vector<std::string> files;
    for (const auto &entry : fs::directory_iterator(src)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }
    return files;
}

void move_files(std::string src){
    std::vector<std::string> files = get_files(src);
    std::string dest;
    int i = 0;
    for (const auto &file : files) {
        if(i % MAX_FILES_IN_DIRECTORY == 0){
            dest = src;
            dest += DIRECTORY_NAME + std::to_string(i / MAX_FILES_IN_DIRECTORY + 1);
            fs::create_directory(dest);
        }
        fs::rename(file, (dest + "/" + fs::path(file).filename().string()));
        i++;
    }
}
