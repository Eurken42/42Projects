/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteRequestHandler.class.hpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:44:20 by vgroux            #+#    #+#             */
/*   Updated: 2023/11/20 19:23:22 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_REQUEST_HANDLER_CLASS_HPP
# define DELETE_REQUEST_HANDLER_CLASS_HPP

#include "RequestHandler.class.hpp"

class DeleteRequestHandler: public RequestHandler
{
	private:

	public:
		DeleteRequestHandler(void);
		// DeleteRequestHandler( CONFIG DU SERVER );
		DeleteRequestHandler(const DeleteRequestHandler &src);
		DeleteRequestHandler&	operator=(const DeleteRequestHandler &src);
		~DeleteRequestHandler(void);

		HttpRespond	handleRequest(HttpRequest *req, Client *clt, Socket srv);		
};

#endif
