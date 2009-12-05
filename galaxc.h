#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <wand/MagickWand.h>
#include "mysql.c"

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


//int fetch_single_value_from_db(MYSQL*,char[]);
