#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact	_contacts[8];
		int		_nextIndex;
		int		_count;

	public:
		PhoneBook();
		bool	addContact();
		bool	searchContacts() const;
};

#endif
