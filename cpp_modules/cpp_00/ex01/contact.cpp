/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorreia <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:06:42 by scorreia          #+#    #+#             */
/*   Updated: 2022/11/01 14:54:40 by scorreia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Contact.class.hpp"

 Contact::Contact (void) {
	return;
 }

 Contact::~Contact (void) {
 	return;
 }

 std::string Contact::getFirstName ( void ) const {
 	return (this->first_name);
 }

 std::string Contact::getLastName ( void ) const {
 	return (this->last_name);
 }

 std::string Contact::getNickName ( void ) const {
 	return (this->nickname);
 }

 std::string Contact::getSecret ( void ) const {
	return (this->secret);
 }

 std::string Contact::getPhone ( void ) const {
	return (this->phone_nb);
 }

 void Contact::setFirstName ( std::string name ) {
	this->first_name = name;
 }

 void Contact::setLastName ( std::string name ) {
	this->last_name = name;
 }

 void Contact::setNickName ( std::string name ) {
	this->nickname = name;
 }

 void Contact::setSecret ( std::string secret ) {
	this->secret = secret;
 }

 void Contact::setPhone ( std::string nb ) {
	this->phone_nb = nb;
 }
