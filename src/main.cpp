#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " input_file.txt\n";
		return -1;
	}
	file_path = argv[1];
	// TODO Read file

	return 0;
}
