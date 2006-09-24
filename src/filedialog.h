/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef FILEDIALOG_H_
#define FILEDIALOG_H_

#include <string>
#include "gmenu2x.h"

using std::string;
using std::vector;

class FileDialog {
private:
	int selRow;
	string text;
	GMenu2X *gmenu2x;
	vector<string> filter;

	void browsePath(string path, vector<string>* directories, vector<string>* files);
	
public:
	string path, file;
	FileDialog(GMenu2X *gmenu2x, string text, string filter="");
	
	bool exec();
};

#endif /*INPUTDIALOG_H_*/