#include <filesystem>

namespace fs = std::filesystem;

int countFiles(const std::string& directory) {
    int count = 0;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            count++;
        }
    }
    return count;
}
