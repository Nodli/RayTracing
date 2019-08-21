#ifndef H_PPM
#define H_PPM

#include <fstream>
#include <vector>

// sizeX is the number of columns
// sizeY is the number of rows
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
// data starts from the top-left of the image and ends at bottom-right of the image
void writeP3(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);
bool writeP3(const char* const filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);

// sizeX returns the number of columns
// sizeY returns the number of rows
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
// data starts from the top-left of the image and ends at bottom-right of the image
bool readP3(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);
bool readP3(const char* const filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);

// sizeX is the number of columns
// sizeY is the number of rows
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
// data starts from the top-left of the image and ends at bottom-right of the image
void writeP6(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);
bool writeP6(const char* const filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);

// sizeX returns the number of columns
// sizeY returns the number of rows
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
// data starts from the top-left of the image and ends at bottom-right of the image
bool readP6(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);
bool readP6(const char* const filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);

#endif
