
/*
 * FileInput.hpp
 *
 *  Created on: Nov 27, 2017
 *      Author: amal.tawakuli, martin.theobald
 */

#ifndef INPUT_FILEINPUT_HPP_
#define INPUT_FILEINPUT_HPP_

#include <string>
#include <fstream>
#include <iostream>

#include "Input.hpp"

using namespace std;

class FileInput: public Input {

public:

	char* fileName;

	Window* window;

	FileInput(string fileName, Window* window);

	~FileInput();

	bool isOpen();

	void open();

	Window* nextWindow();

	void close();

private:

	void readBinaryFile(Window* window);

	void writeBinaryFileIntType(int numberOfInts);

	ifstream dataSource;

	bool is_open;

	int file_pos, file_size;

};

#endif /* INPUT_FILEINPUT_HPP_ */
