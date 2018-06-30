/***************************************************************************
 *   Copyright (C) 2009 by Christian Borss                                 *
 *   christian.borss@rub.de                                                *
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


#ifndef __TEXTLIST_H__
#define __TEXTLIST_H__


#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>


class TextList
{
public:
    void clear()
        { list.clear(); }
    size_t findOrCreate(const String &entry);
    const String &getEntry(size_t pos) const
        { return list.at(pos); }
    const std::vector<String> &getList() const
        { return list; }

private:
    std::vector<String> list;
};


#endif   // __TEXTLIST_H__