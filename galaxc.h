#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <wand/MagickWand.h>
#include "mysql.c"
#include "wand.c"

int fetch_single_value_from_db(MYSQL*,char[]);