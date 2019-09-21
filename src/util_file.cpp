
namespace util {
namespace file {

std::string read_total_file(const std::string& filename) {
    std::ifstream t(filename);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    return str;
}

} // namespace file
} // namespace util
