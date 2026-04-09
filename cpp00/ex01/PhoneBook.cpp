#include "PhoneBook.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
	int	getStoredIndex(int count, int nextIndex, int displayIndex)
	{
		if (count < 8)
			return displayIndex;
		return (nextIndex + displayIndex) % 8;
	}

	bool	readNonEmptyField(const std::string &prompt, std::string &value)
	{
	while (true)
	{
		std::cout << prompt << std::endl;
		if (!std::getline(std::cin, value))
		{
			return false;
		}
			if (!value.empty())
				return true;
			std::cout << "Field cannot be empty." << std::endl;
		}
	}

	std::string	formatColumn(const std::string &value)
	{
		if (value.length() <= 10)
			return value;
		return value.substr(0, 9) + ".";
	}

	bool	parseIndex(const std::string &input, int &index)
	{
		std::istringstream	stream(input);
		char				extra;

		if (!(stream >> index))
			return false;
		if (stream >> extra)
			return false;
		return true;
	}

	void	printContactDetails(const Contact &contact)
	{
		std::cout << "First name: " << contact.getFirstName() << std::endl;
		std::cout << "Last name: " << contact.getLastName() << std::endl;
		std::cout << "Nickname: " << contact.getNickname() << std::endl;
		std::cout << "Phone number: " << contact.getPhoneNumber() << std::endl;
		std::cout << "Darkest secret: " << contact.getDarkestSecret() << std::endl;
	}
}

PhoneBook::PhoneBook() : _nextIndex(0), _count(0)
{
}

bool	PhoneBook::addContact()
{
	std::string	firstName;
	std::string	lastName;
	std::string	nickname;
	std::string	phoneNumber;
	std::string	darkestSecret;

	if (!readNonEmptyField("First name: ", firstName)
		|| !readNonEmptyField("Last name: ", lastName)
		|| !readNonEmptyField("Nickname: ", nickname)
		|| !readNonEmptyField("Phone number: ", phoneNumber)
		|| !readNonEmptyField("Darkest secret: ", darkestSecret))
		return false;
	_contacts[_nextIndex].setFields(firstName, lastName, nickname,
		phoneNumber, darkestSecret);
	_nextIndex = (_nextIndex + 1) % 8;
	if (_count < 8)
		++_count;
	std::cout << "Contact saved." << std::endl;
	return true;
}

bool	PhoneBook::searchContacts() const
{
	std::string	input;
	int			index;

	if (_count == 0)
	{
		std::cout << "PhoneBook is empty." << std::endl;
		return true;
	}
	std::cout << std::setw(10) << "Index" << '|'
		<< std::setw(10) << "First name" << '|'
		<< std::setw(10) << "Last name" << '|'
		<< std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < _count; ++i)
	{
		int	storedIndex;

		storedIndex = getStoredIndex(_count, _nextIndex, i);
		std::cout << std::setw(10) << i << '|'
			<< std::setw(10) << formatColumn(_contacts[storedIndex].getFirstName()) << '|'
			<< std::setw(10) << formatColumn(_contacts[storedIndex].getLastName()) << '|'
			<< std::setw(10) << formatColumn(_contacts[storedIndex].getNickname())
			<< std::endl;
	}
	std::cout << "Index to display:" << std::endl;
	if (!std::getline(std::cin, input))
	{
		return false;
	}
	if (!parseIndex(input, index) || index < 0 || index >= _count)
	{
		std::cout << "Invalid index." << std::endl;
		return true;
	}
	printContactDetails(_contacts[getStoredIndex(_count, _nextIndex, index)]);
	return true;
}
