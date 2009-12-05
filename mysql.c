#include <mysql.h>
#include <stdio.h>

int fetch_single_value_from_db(MYSQL *conn, char query[]){
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  int retval;
  
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }

   res = mysql_use_result(conn);
   
   /* convert the first field of the only row to integer */
   row = mysql_fetch_row(res);
   retval = atoi(row[0]);

   /* Release memory used to store results and close connection */
   mysql_free_result(res);
  
   return retval;
  
}
