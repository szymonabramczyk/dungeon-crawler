#include <gtest/gtest.h>
#include <filesystem>

std::filesystem::path build_path;

// Main function
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::filesystem::path cwd( std::filesystem::canonical( argv[0] ) );
    build_path = cwd.parent_path().parent_path();
    std::cout << build_path << std::endl;
    return RUN_ALL_TESTS();
}
