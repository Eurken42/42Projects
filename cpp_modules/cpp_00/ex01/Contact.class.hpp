/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:53:38 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 14:54:38 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_CLASS_HPP 
 # define CONTACT_CLASS_HPP

#include <string> 

class Contact { 
	public: 
		Contact ( void );
		~Contact ( void );

		std::string getFirstName ( void ) const;
		std::string getLastName ( void ) const; 
		std::string getNickName ( void ) const;
		std::string getSecret ( void ) const;
		std::string getPhone ( void ) const;
		
		void setFirstName ( std::string name );
		void setLastName ( std::string name );
		void setNickName ( std::string name );
		void setSecret ( std::string secret );
		void setPhone ( std::string nb );
	private:
		std::string first_name;
		std::string phone_nb;
		std::string last_name;
		std::string nickname;
		std::string secret; 
 };
 
 #endif

