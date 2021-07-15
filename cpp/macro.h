#pragma once

#ifndef CONNECTION
#define CONNECTION(text1, text2) text1##text2
#endif

#ifndef CONNECT_STR
#define CONNECT_STR(text1, text2) CONNECTION(text1, text2)
#endif

#ifndef CONNECT_STR3
#define CONNECT_STR3(text1, text2, text3) CONNECTION(CONNECTION(text1, text2), text3)
#endif