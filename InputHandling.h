//EC327 PA4 Error Handling Class 

#ifndef INVALIDINPUT_H
#define INVALIDINPUT_H

class InvalidInput
{
	public:
	InvalidInput (const char* in_ptr): msg_ptr (in_ptr) { }
	const char* const msg_ptr;
	
	private:
	InvalidInput();
	// no default construction
};

#endif