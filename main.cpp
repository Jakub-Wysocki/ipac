/*
 * main.cpp
 *
 *  Created on: 14 maj 2020
 *      Author: Jakub Wysocki
 */

#include <iostream>
#include <stdio.h>
#include "readdr.hpp"



// I could use regex to check if address is in proper format, although I know it works only in C++11(and further) and it is decreasing performance, instead I used sscanf which works well.
int main()
{
	ip_addr address_object;
    manage_ip_address address_object_manager;
    unsigned int sub_mask;
    unsigned int bytes[4];
    char input[15];

    std::cout << "Hello, type your IPv4 address: ";

    for(int i = 0;;i++)
    {
    		if(i >= 1)
    		{
    			std::cin.ignore();

    			char c;
    			std::cout << "Do you want to check next address? Y/N ";
    			c = std::cin.get();

    			//here could be clear console command but I don't know which system you'll be using checking this code

    			if(c != 'Y' && c != 'y')
    				break;
    			else
    				std::cout << "Please, type new address:  ";


    		}

    		// I could use regex to check if address is in proper format, although I know it works only in C++11(and further) and it is decreasing performance, instead I used sscanf which works well.
    		std::cin >> input;
    		if(sscanf(input, "%u.%u.%u.%u/%2u", (bytes+3),(bytes+2),(bytes+1),(bytes+0), &sub_mask) != 5)
    		{
    			std::cout << "Incorrect input format\n";
    			continue;
    		}


			if(address_object_manager.load_address_data(bytes, sub_mask, &address_object) != 0)
			{
				std::cout << "Incorrect input data\n";
				continue;
			}

			address_object_manager.print_on_screen(&address_object);

			if(address_object_manager.print_to_file("log.txt", &address_object) != 0)
					std::cout << "File save error!\n";

    }

    std::cout << "Thank you for using!";

    return 0;

}
