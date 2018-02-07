//
//  Util.cpp
//  Chess
//
//  Created by Adam James Leuer on 2/17/15.
//  Copyright (c) 2015 Adam James Leuer. All rights reserved.
//

#include "Util.h"

std::wstring_convert<std::codecvt_utf8<wchar_t>> stringConverter ;

std::string convertToString(const std::wstring & wide_string) {
	return stringConverter.to_bytes(wide_string) ;
}
