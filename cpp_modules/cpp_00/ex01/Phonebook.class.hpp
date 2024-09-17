/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:00:51 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 14:54:46 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.class.hpp"

class Phonebook {
	public:
		Phonebook(void);
		~Phonebook(void);
		Contact	getContact(int i);
		void	setContact(int i, int i2);
		void	search_contact(Phonebook pb);
		void	add_contact(Phonebook *pb);
	private:
		int		count;
		Contact contact[8];
};

#endif
