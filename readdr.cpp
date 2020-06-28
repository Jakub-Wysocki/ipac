/*
 * readdr.cpp
 *
 *  Created on: 14 maj 2020
 *      Author: Jakub Wysocki
 */

#include <iostream>
#include <fstream>
#include "readdr.hpp"
#include <stdio.h>


unsigned int ip_addr::convert_submask(unsigned int mask)
{
    if(mask > 32)
        return 0; //im not sure about it


    if(mask >= 32)
        return 1;

    unsigned int full_mask = 0xFFFFFFFF;

    return full_mask << (32-mask);
}
int ip_addr::load_address(unsigned int address)
{
    this->address = address;

    return 0;
}
unsigned int ip_addr::get_address()
{
    return address;
}
int ip_addr::load_submask(unsigned int submask)
{
    short_submask = submask; //short value of mask is stored

    this->submask = convert_submask(submask); //change short form to decimal form
    return 0;
}
unsigned int ip_addr::network_address()
{
    return address&submask;
}
unsigned int ip_addr::broadcast_address()
{
    unsigned int negative_submask = ~submask;
    return network_address()+negative_submask;
}
unsigned int ip_addr::first_host()
{
    return network_address()+1;
}
unsigned int ip_addr::last_host()
{
    return broadcast_address()-1;
}
unsigned int ip_addr::host_amount()
{
    return (1 << (32 - short_submask)) - 2;
}

int manage_ip_address::load_address_data(unsigned int* bytes, unsigned int mask, ip_addr* cptr)
{
	if(bytes == NULL || cptr == NULL)
		return 1;

	if(validate(bytes, mask) != 0)
		return 2;

	cptr->load_address(printable_to_decimal(bytes));
	cptr->load_submask(mask);

	return 0;
}
unsigned int manage_ip_address::printable_to_decimal(unsigned int* ptr)
{

    unsigned int dec = 0x00000000;

    dec |= (*(ptr+3) << 24) | (*(ptr+2) << 16) | (*(ptr+1) << 8) | (*(ptr+0) << 0 );

    return dec;
}
std::string manage_ip_address::print_network_address(ip_addr* cptr)
{
		unsigned int bytes[4];
		std::string result;

		unsigned int decimal = cptr->network_address();
	    decimal_to_printable(bytes, decimal);

	    result += "Network address: " + std::to_string(*(bytes+3))+"."+std::to_string(*(bytes+2))+"."+std::to_string(*(bytes+1))+"."+std::to_string(*(bytes+0))+ "\n";
	    return result;
}
std::string manage_ip_address::print_broadcast_address(ip_addr* cptr)
{
		unsigned int bytes[4];
		std::string result;

		unsigned int decimal = cptr->broadcast_address();
		decimal_to_printable(bytes, decimal);

		result += "Broadcast address: " + std::to_string(*(bytes+3))+"."+std::to_string(*(bytes+2))+"."+std::to_string(*(bytes+1))+"."+std::to_string(*(bytes+0))+ "\n";
		return result;

}
std::string manage_ip_address::print_address_range(ip_addr* cptr)
{
		unsigned int bytes[4];
		std::string result;

		unsigned int decimal = cptr->first_host();
		decimal_to_printable(bytes, decimal);

		result += "Address range: " + std::to_string(*(bytes+3))+"."+std::to_string(*(bytes+2))+"."+std::to_string(*(bytes+1))+"."+std::to_string(*(bytes+0))+ " - ";

	    decimal = cptr->last_host();
	    decimal_to_printable(bytes, decimal);

	    result += std::to_string(*(bytes+3))+"."+std::to_string(*(bytes+2))+"."+std::to_string(*(bytes+1))+"."+std::to_string(*(bytes+0)) + "\n";
	    return result;


}
std::string manage_ip_address::print_host_amount(ip_addr* cptr)
{
	std::string result = "Host amount: " + std::to_string(cptr->host_amount()) + "\n";

	return result;

}
int manage_ip_address::decimal_to_printable(unsigned int * ptr, unsigned int decimal)
{
    if(ptr == NULL)
        return 1;

    *(ptr+0) = decimal & 0xFF;
    *(ptr+1) = (decimal >> 8) & 0xFF;
    *(ptr+2) = (decimal >> 16) & 0xFF;
    *(ptr+3) = (decimal >> 24) & 0xFF;

    return 0;
}
std::string manage_ip_address::print_all_data(ip_addr* cptr)
{
	std::string result;

	result += print_network_address(cptr) + print_broadcast_address(cptr) + print_host_amount(cptr) + print_address_range(cptr);

	return result;

}
void manage_ip_address::print_on_screen(ip_addr* cptr)
{
	std::cout << print_all_data(cptr);
}
int manage_ip_address::print_to_file(std::string filename,  ip_addr* cptr)
{
	  std::fstream fptr;

	    fptr.open(filename, std::ios::app);

	    if(fptr.good() == true)
	        fptr << print_all_data(cptr) + "------------------------------\n";
	    else
	    	return 1;

	    fptr.close();

	    return 0;

}
int manage_ip_address::validate(unsigned int* bytes, unsigned int mask)
{
	if(*(bytes+0) >= 256 || *(bytes+1) >= 256 || *(bytes+2) >= 256 || *(bytes+3) >= 256)
		return 1;

	if(mask > 32)
		return 1;

	return 0;
}






