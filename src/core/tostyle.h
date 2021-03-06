
/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * TOra - An Oracle Toolkit for DBA's and developers
 *
 * Shared/mixed copyright is held throughout files in this product
 *
 * Portions Copyright (C) 2000-2001 Underscore AB
 * Portions Copyright (C) 2003-2005 Quest Software, Inc.
 * Portions Copyright (C) 2004-2013 Numerous Other Contributors
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program as the file COPYING.txt; if not, please see
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries.
 *
 * All trademarks belong to their respective owners.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QMetaType>
#include <QtGui/QColor>
#include <QtGui/QFont>

class QsciLexer;

class toStyle : public QObject
{
        Q_OBJECT;
    public:
        toStyle() // make QMap happy
            : QObject(NULL)
            , Size()
            , Weight()
            , Italics()
            , Bold()
        {}

        toStyle(const toStyle &other)
            : QObject(NULL)
            , Name(other.Name)
            , FGColor(other.FGColor)
            , BGColor(other.BGColor)
            , Font(other.Font)
            , Size(other.Size)
            , Weight(other.Weight)
            , Italics(other.Italics)
            , Bold(other.Bold)
        {}

        toStyle& operator =(const toStyle &other)
        {
            Name    = other.Name;
            FGColor = other.FGColor;
            BGColor = other.BGColor;
            Font    = other.Font;
            Size    = other.Size;
            Weight  = other.Weight;
            Italics = other.Italics;
            Bold    = other.Bold;
            return *this;
        }

        toStyle(QString const& name, QColor const& fg, QColor const& bg, QFont const& fo)
            : QObject(NULL)
            , Name(name)
            , FGColor(fg)
            , BGColor(bg)
            , Font(fo)
            , Size(fo.pointSize())
            , Weight(fo.weight())
            , Italics(fo.italic())
            , Bold()
        {}

        QString Name;
        QColor FGColor;
        QColor BGColor;
        QFont Font;
        int Size;
        int Weight;
        bool Italics;
        bool Bold;
};

class toStylesMap: public QMap<int, toStyle>
{
};

Q_DECLARE_METATYPE(toStyle);
Q_DECLARE_METATYPE(toStylesMap);
