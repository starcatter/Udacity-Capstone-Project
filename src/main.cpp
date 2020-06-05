//
// Created by superbob on 2020-06-02.
//


#include <iostream>

#include "app.hpp"

int main( int argc, char **argv )
{
	App app;
	try
	{
		std::cout << "Running app..." << std::endl;
		int result = app.Run();
		if ( result != 0 )
		{
			std::cout << "App terminated with exit code:" << result << std::endl;
		}
		else
		{
			std::cout << "App OK!" << std::endl;
		}
		return result;
	} catch (std::runtime_error & err)
	{
		std::cout << "App threw an exception:" << err.what() << std::endl;
		return -1;
	} catch (...)
	{
		std::cout << "App threw some exception." << std::endl;
		return -1;
	}
	
}
