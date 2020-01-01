#ifndef TTKGB18030CHECKER
#define TTKGB18030CHECKER

/* =================================================
 * This file is part of the TTK Tiny Tools project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include "checker.h"

class TTK_CORE_EXPORT GB18030Checker : public CheckerBase
{
public:
    GB18030Checker();
    virtual bool detect(const string &str) const override;

};

#endif // TTKGB18030CHECKER

