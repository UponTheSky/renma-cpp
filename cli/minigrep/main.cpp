#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct Config {
    std::string query;
    std::string file_path;

    Config() = default;

    Config(const std::string& query, const std::string& file_path) {
        this->query = query;
        this->file_path = file_path;
    }

    static const Config build(const std::vector<const std::string>& args) {
        const Config config { args[0], args[1] };

        return config;
    }
};

void run(const Config& config) {
    std::cout << "Searching for " << config.query << std::endl;
    std::cout << "In file " << config.file_path << std::endl;

    std::ifstream ifs(config.file_path);

    if (!ifs) {
        std::cerr << "Should have been able to read the file" << std::endl; 
        throw std::runtime_error("reading file error");
    }

    std::string line_buf;
    std::ostringstream ostring_chunk;

    while (std::getline(ifs, line_buf)) {
        ostring_chunk << line_buf << std::endl;;
        line_buf.clear();
    }

    std::cout << "With text:\n" << ostring_chunk.str() << std::endl;

}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("not enough arguments");
    } 

    try {
        std::vector<const std::string> args;
        args.push_back(std::string(argv[1]));
        args.push_back(std::string(argv[2]));

        const Config config = Config::build(args);

        run(config);
    } catch(const std::invalid_argument& e) {
        std::cerr << "Problem parsing arguments: " << e.what() << std::endl; 
        return 1;
    } catch(const std::runtime_error& e) {
        std::cerr << "Application error" << e.what() << std::endl;
        return 1;
    }

    return 0;
}