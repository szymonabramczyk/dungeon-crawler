#include <gtest/gtest.h>
#include <filesystem>

std::filesystem::path buildPath;

// Main function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::filesystem::path cwd( std::filesystem::canonical( argv[0] ) );
    buildPath = cwd.parent_path().parent_path();
    std::cout << buildPath << std::endl;
    return RUN_ALL_TESTS();
}
