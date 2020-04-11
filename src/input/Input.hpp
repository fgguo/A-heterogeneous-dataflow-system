

#ifndef INPUT_INPUT_HPP_
#define INPUT_INPUT_HPP_

#include "../communication/Window.hpp"
#include "../communication/Message.hpp"

class Input {

public:

	Input();

	virtual ~Input();

	virtual void open() = 0;

	virtual Window* nextWindow() = 0;

	virtual bool isOpen() = 0;

	virtual void close() = 0;

};

#endif /* INPUT_INPUT_HPP_ */
