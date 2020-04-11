
#include "../communication/Window.hpp"

#include <unistd.h>
#include <stdlib.h>
#include <ctime>
#include <cstring>

#include "FileInput.hpp"

using namespace std;

FileInput::FileInput(string file, Window* window) :
		Input() {
	this->fileName = new char[file.length()];
	this->window = window;
	strcpy(this->fileName, file.c_str());
	this->is_open = false;
	this->file_size = 0;
	this->file_pos = 0;
}

FileInput::~FileInput() {
	delete[] fileName;
}

bool FileInput::isOpen() {
	return is_open;
}

void FileInput::open() {
	//writeBinaryFileIntType(WINDOW_SIZE / sizeof(int));

	dataSource.open(fileName, ios::binary | ios::in);

	if (dataSource) {

		dataSource.seekg(0, ios::end);
		file_size = dataSource.tellg();
		dataSource.seekg(0, ios::beg);
		is_open = true;
		cout<<file_size<<endl;
		cout<<window->capacity<<endl;

	} else {

		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		cout << "PROBLEM OPENING [" << cwd << "/" << fileName << "]" << endl;

		is_open = false;
		file_size = 0;

	}

	file_pos = 0;
}

Window* FileInput::nextWindow() {

	if (is_open) {

		if (file_pos + window->capacity < file_size) {

			dataSource.read(&window->buffer[0], window->capacity);
			window->size = window->capacity;
			file_pos += window->capacity;

		} else {

//			dataSource.read(&window->buffer[0], file_size - file_pos);
//			dataSource.close();
//			window->size = file_size - file_pos;
//			file_pos = file_size;
//			is_open = false;
			dataSource.read(&window->buffer[0], file_size - file_pos);
						//dataSource.close();
						window->size = file_size - file_pos;
						file_pos = file_size;
						while((window->size + file_size) < (window->capacity)){
							dataSource.seekg(0, ios::beg);
							dataSource.read(&window->buffer[file_pos], file_size);
							window->size = file_size + window->size;
							file_pos=file_pos+file_size;
						}
						dataSource.close();
						is_open = false;

		}
	}

	cout << window->size << " BYTES READ FROM [" << fileName << "]" << endl;
	return window;
}

void FileInput::close() {
	if (is_open) {
		dataSource.close();
		is_open = false;
	}
}

// Write a binary file with 'numberOfInts' many int values
void FileInput::writeBinaryFileIntType(int numberOfInts) {

	ofstream dataSource;
	dataSource.open(fileName, ios::binary | ios::out);

	if (dataSource) {

		srand(time(NULL));

		int len = sizeof(int);
		for (int i = 0; i < numberOfInts; i++) {
			int val = i; //rand();
			dataSource.write((char*) &val, len);
			//cout << "WRITE VALUE: " << val << endl;
		}

		cout << numberOfInts * sizeof(int) << " BYTES WRITTEN TO [" << fileName
				<< "]" << endl;

	} else {

		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		cout << "PROBLEM WRITING TO [" << cwd << "/" << fileName << "]" << endl;

	}
}

// Read a whole binary file into a window (size is adjusted if necessary)
void FileInput::readBinaryFile(Window* window) {

	ifstream dataSource;
	dataSource.open(fileName, ios::binary | ios::in);

	if (dataSource) {

		dataSource.seekg(0, ios::end);
		int size = dataSource.tellg();
		if (size > window->capacity)
			window->resize(size);
		window->size = size;
		dataSource.seekg(0, ios::beg);
		dataSource.read(&window->buffer[0], size);
		//cout << size << " BYTES READ FROM [" << fileName << "]" << endl;

	} else {

		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		cout << "PROBLEM READING FROM [" << cwd << "/" << fileName << "]"
				<< endl;

	}

	dataSource.close();
}
