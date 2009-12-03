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

int main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "localhost";
   char *user = "root";
   char *password = "root";
   char *database = "spacevictory";
   
   int map_width = 930;
   int map_height = 930;
   
   int max_x, max_y, min_x, min_y;
   int galaxy_width, galaxy_height;
   
   conn = mysql_init(NULL);
   
   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return(0);
   }
   
   max_x = fetch_single_value_from_db(conn, "select MAX(x) from planets");
   printf("MAX X: %i\n", max_x);
   max_y = fetch_single_value_from_db(conn, "select MAX(y) from planets");
   printf("MAX Y: %i\n", max_y);
   min_x = fetch_single_value_from_db(conn, "select MIN(x) from planets");
   printf("MIN X: %i\n", min_x);
   min_y = fetch_single_value_from_db(conn, "select MIN(y) from planets");
   printf("MIN Y: %i\n", min_y);

   galaxy_width = max_x - min_x + 1;
   galaxy_height = max_y - min_y + 1;

   printf("GALAXY WIDTH: %i\n", galaxy_width);
   printf("GALAXY HEIGHT: %i\n", galaxy_height);

   /* send SQL query */
   if (mysql_query(conn, "SELECT x,y,z,hue FROM planets LEFT JOIN players on planets.player_id = players.id LIMIT 10")) {
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