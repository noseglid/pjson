#include "pjson.hpp"
#include <iostream>
#include <fstream>
#include <exception>

std::string
file_get_contents(const char *file)
{
  std::ifstream ifs(file);
  if (!ifs.good())
    throw std::exception();

  return std::string(
    (std::istreambuf_iterator<char>(ifs)),
    (std::istreambuf_iterator<char>())
  );
}

void
usage(char *argv[])
{
  std::cout
    << "JSON minifier." << std::endl << std::endl
    << "Each input file will produce a new output file." << std::endl
    << "The new file will have the extension 'min' appended." << std::endl << std::endl
    << "Usage: " << argv[0] << "[file1 [file2 ... ]" << std::endl;
}

int
main(int argc, char *argv[])
{
  if (1 == argc || 0 == strcmp("--help", argv[1]) || 0 == strcmp("-h", argv[1])) {
    usage(argv);
    exit(EXIT_FAILURE);
  }

  bool failed = false;
  std::cout << std::endl;
  while (--argc > 0) {
    std::cout << "Minifaction of file: " << argv[argc] << std::endl;

    std::string json;
    try {
      json = file_get_contents(argv[argc]);
    } catch (const std::exception& e) {
      std::cout << "[!] Could not read file." << std::endl;
      std::cout << "Continuing..." << std::endl << std::endl;
      failed = true;
      continue;
    }

    std::string outfile(argv[argc]);
    outfile += ".min";
    std::ofstream file(outfile.c_str());
    if (!file) {
      std::cout << "[!] Could not open file for writing: " << outfile << std::endl;
      std::cout << "Continuing..." << std::endl << std::endl;
      continue;
    }

    file << Json::Value::minify(json);
    file.close();

    std::cout << "Complete." << std::endl << std::endl;
  }

  std::cout << "Minification process complete." << std::endl;
  if (failed) {
    std::cout << "[!] However, there were some files that failed." << std::endl;
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
