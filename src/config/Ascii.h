// Copyright (c) 2018, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information

#pragma once

#include <string>

const std::string windowsAsciiArt = "  ____  _ _ _       ____             _        \n"
									" |  _ \(_) | |     |  _ \           | |       \n"
									" | |_) |_| | |_   _| |_) |_   _  ___| | _____ \n"
									" |  _ <| | | | | | |  _ <| | | |/ __| |/ / __|\n"
									" | |_) | | | | |_| | |_) | |_| | (__|   <\__ \ \n"
									" |____/|_|_|_|\__, |____/ \__,_|\___|_|\_\___/ \n"
									"			   __/ |                          \n"
									"			  |___/       \n";

const std::string nonWindowsAsciiArt = windowsAsciiArt;

/* Windows has some characters it won't display in a terminal. If your ascii
   art works fine on Windows and Linux terminals, just replace 'asciiArt' with
   the art itself, and remove these two #ifdefs and above ascii arts */
#ifdef _WIN32

const std::string asciiArt = windowsAsciiArt;

#else
const std::string asciiArt = nonWindowsAsciiArt;
#endif
