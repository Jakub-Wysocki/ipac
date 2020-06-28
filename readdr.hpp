/*
 * readdr.hpp
 *
 *  Created on: 14 maj 2020
 *      Author: Jakub Wysocki
 */

/*
 * During writing this program I decided to adopt concept where the calculated addresses are not stored. That way the program saves some operating memory but works slower.
 * Choice between those concepts depends on application, which I don't know.
 */

#ifndef READDR_HPP_
#define READDR_HPP_

#include <string>

class ip_addr
{
private:
    unsigned int address;
    unsigned int submask;
    short short_submask;


    friend class manage_ip_address;

    int load_address(unsigned int);
    int load_submask(unsigned int);
    unsigned int convert_submask(unsigned int);
public:


    unsigned int get_address();
    unsigned int network_address(); //return network address
    unsigned int broadcast_address(); //return broadcast address
    unsigned int first_host(); //return first host address
    unsigned int host_amount();
    unsigned int last_host();
};
class manage_ip_address
{
private:
	int decimal_to_printable(unsigned int*, unsigned int);
	unsigned int printable_to_decimal(unsigned int*);

public:

	int load_address_data(unsigned int*, unsigned int,ip_addr*);

	std::string print_network_address(ip_addr* cptr);
	std::string print_broadcast_address(ip_addr* cptr);
	std::string print_address_range(ip_addr* cptr);
	std::string print_host_amount(ip_addr* cptr);

	std::string print_all_data(ip_addr* cptr);

	void print_on_screen(ip_addr* cptr);
	int print_to_file(std::string filename, ip_addr* cptr);

	int validate(unsigned int*, unsigned int);

};

#endif /* READDR_HPP_ */



