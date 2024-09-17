/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostRequestHandler.class.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:14:16 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/11 15:21:01 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_REQUEST_HANDLER_CLASS_HPP
# define POST_REQUEST_HANDLER_CLASS_HPP

#include "RequestHandler.class.hpp"

class PostRequestHandler: public RequestHandler
{
	private:

	public:
		PostRequestHandler(void);
		// PostRequestHandler( CONFIG DU SERVER );
		PostRequestHandler(const PostRequestHandler &src);
		PostRequestHandler&	operator=(const PostRequestHandler &src);
		~PostRequestHandler(void);

		HttpRespond	handleRequest(HttpRequest *req, Client *clt, Socket srv);
		void		handlePostFile(HttpRequest *req);

};

#endif
