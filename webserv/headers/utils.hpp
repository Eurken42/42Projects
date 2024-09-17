/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrigger <afrigger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:59 by vgroux            #+#    #+#             */
/*   Updated: 2024/01/10 14:02:04 by afrigger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <sstream>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <dirent.h>
# include <vector>
# include <sys/stat.h>

# define CRLN "\r\n"

std::string	getStatusStr(int statusCode);
std::string	toString(int i);
std::string	openReadFile(std::string relative_path);
std::string	openReadCloseDir(std::string path, std::string uri);
std::string openWriteFile(std::string relative_path);
std::string	openReadCloseUpload(std::string path, std::string uri);

#endif
