#include "galaxc.h"

int main() {
  
  MYSQL *conn;
  MYSQL_RES *res;
  MYSQL_ROW row;

  MagickWand *magick_wand;   
  DrawingWand *drawing_wand;
  PixelWand *bgcolor;
  MagickBooleanType status;

  char *server = "localhost";
  char *user = "root";
  char *password = "root";
  char *database = "spacevictory";

  int map_width = 930;
  int map_height = 930;

  int max_x, max_y, min_x, min_y;
  int galaxy_width, galaxy_height, no_of_planets, galaxy_measure;
  int planet_x, planet_y, planet_height, planet_width, planet_radius;

  conn = mysql_init(NULL);

  /* Connect to database */
  if (!mysql_real_connect(conn, server,
       user, password, database, 0, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return(0);
  }

  /*
    Get ballpark galaxy data required for drawing initializations.
  */

  no_of_planets = fetch_single_value_from_db(conn, "select COUNT(*) from planets");
  printf("NO OF PLANETS: %i\n", no_of_planets);
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
  if (galaxy_width > galaxy_height) {
    galaxy_measure = galaxy_width;
  } else {
    galaxy_measure = galaxy_width;
  }
  printf("GALAXY WIDTH: %i\n", galaxy_width);
  printf("GALAXY HEIGHT: %i\n", galaxy_height);
  printf("GALAXY MEASUER: %i\n", galaxy_measure);


  planet_width = map_width / galaxy_measure;
  planet_height = map_height / galaxy_measure;
  printf("PLANET WIDTH: %i\n", planet_width);
  printf("PLANET HEIGHT: %i\n", planet_height);

  /*
    Initialize an image for us to draw on.
  */
  MagickWandGenesis();

  magick_wand=NewMagickWand();
  bgcolor=NewPixelWand();
  PixelSetColor(bgcolor, "#0000ff");

  MagickSetBackgroundColor(magick_wand, bgcolor);
  MagickSetSize(magick_wand, map_width, map_height);
  MagickNewImage(magick_wand, map_width, map_height, bgcolor);

  drawing_wand = NewDrawingWand();

   /* send SQL query for the actual planet info */
  if (mysql_query(conn, "SELECT x,y,z,hue FROM planets LEFT JOIN players on planets.player_id = players.id")) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    return(0);
  }

  res = mysql_use_result(conn);

  /* output fields 1 and 2 of each row */
  while ((row = mysql_fetch_row(res)) != NULL) {
    printf("%s %s %s (%s)\n", row[0], row[1], row[2], row[3]);
    planet_x = atoi(row[0]) * planet_width + (map_width/2);
    planet_y = atoi(row[1]) * planet_width + (map_height/2);
    planet_radius = planet_width/2;
    DrawCircle(drawing_wand, planet_x, planet_y, planet_x + planet_radius, planet_y + planet_radius);
  };
  /* Release memory used to store results and close connection */
  mysql_free_result(res);
  mysql_close(conn);

  /* draw to wand image */
  MagickDrawImage(magick_wand, drawing_wand);

  /*
    Write the image then destroy it.
  */
  status=MagickWriteImages(magick_wand,"galaxy.png", MagickTrue);
  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  return(0);
}