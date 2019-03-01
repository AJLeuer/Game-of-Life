//
//  Util.h
//  Chess
//
//  Created by Adam James Leuer on 2/17/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <codecvt>
#include <locale>



extern std::wstring_convert<std::codecvt_utf8<wchar_t>> stringConverter ;

std::string convertToString(const std::wstring & wide_string) ;