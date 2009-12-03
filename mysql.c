#include <mysql.h>
#include <stdio.h>

int fetch_single_value_from_db(MYSQL *conn, char query[]){
  MYSQL_RES *res;
  MYSQL_ROW row;
  
   /* send SQL query */
   if (mysql_query(conn, query)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }

   res = mysql_use_result(conn);
   
   /* output fields 1 and 2 of each row */
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s %s %s (%s)\n", row[0], row[1], row[2], row[3]);

   /* Release memory used to store results and close connection */
   mysql_free_result(res);
  
  
}

int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "localhost";
   char *user = "root";
   char *password = "root";
   char *database = "spacevictory";
   
   conn = mysql_init(NULL);
   
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   
   fetch_single_value_from_db(conn, "select MAX(x) from planets");

   /* send SQL query */
   if (mysql_query(conn, "SELECT x,y,z,hue FROM planets LEFT JOIN players on planets.player_id = players.id")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }

   res = mysql_use_result(conn);
   
   /* output fields 1 and 2 of each row */
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s %s %s (%s)\n", row[0], row[1], row[2], row[3]);

   /* Release memory used to store results and close connection */
   mysql_free_result(res);
   mysql_close(conn);
   }