#include "ppm.h"

#include <string>

void writeP3(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data){

	constexpr int max_value = 255;

	file << "P3 " << (int)(sizeX) << ' ' << (int)(sizeY) << ' ' << max_value << std::endl;

	for(unsigned int y = 0; y != sizeY; ++y){
		for(unsigned int x = 0; x != sizeX; ++x){
			file << (int)data[y * 3 * sizeX + 3 * x]
				<< ' ' << (int)data[y * 3 * sizeX + 3 * x + 1]
				<< ' ' << (int)data[y * 3 * sizeX + 3 * x + 2];

			// no space at the end of a line
			if(x != sizeX - 1){
				file << ' ';
			}
		}

		file << std::endl;
	}
}

bool writeP3(const char* const filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data){

	std::ofstream file(filename);

	if(!file.is_open()){
		return false;
	}

	writeP3(file, sizeX, sizeY, data);

	return true;
}

bool readP3(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data){

	bool status = true;

	std::string format_buffer;
	file >> format_buffer;

	status &= (format_buffer == "P3");

	file >> sizeX;
	file >> sizeY;

	int max_value;
	file >> max_value;

	status &= (max_value == 255);

	file.get(); // skipping EOL

	data.resize(sizeX * sizeY * 3);
	for(unsigned int value = 0; value != sizeX * sizeY * 3; ++value){
		int value_buffer; // buffer to make the conversion to int
		file >> value_buffer;

		data[value] = value_buffer;
	}

	return status;
}

bool readP3(const char* const filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data){

	std::ifstream file(filename);

	if(!file.is_open()){
		return false;
	}

	return readP3(file, sizeX, sizeY, data);
}

void writeP6(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data){

	constexpr int max_value = 255;

	file << "P6 " << (int)sizeX << ' ' << (int)sizeY << ' ' << (int)max_value << std::endl;

	file.write((char*)data, 3 * sizeX * sizeY);
}

bool writeP6(const std::string& filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data){

	std::ofstream file(filename);

	if(!file.is_open()){
		return false;
	}

	writeP6(file, sizeX, sizeY, data);

	return true;
}

// TODO : Avoid using std::string for the format_buffer
bool readP6(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data){

	bool status = true;

	std::string format_buffer;
	file >> format_buffer;

	status &= (format_buffer == "P6");

	file >> sizeX;
	file >> sizeY;

	int max_value;
	file >> max_value; // max value

	status &= (max_value == 255);

	file.get(); // skipping EOL

	data.resize(sizeX * sizeY * 3);
	file.read((char*)data.data(), 3 * sizeX * sizeY);

	return status;
}

bool readP6(const char* const filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data){

	std::ifstream file(filename);

	if(!file.is_open()){
		return false;
	}

	return readP6(file, sizeX, sizeY, data);
}
