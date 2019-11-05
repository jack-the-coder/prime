#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <cairo.h>

#define X_SIZE 10000
#define Y_SIZE 10000

#define MAX_ITER 300000000


// prime tests whether n is prime
bool prime(long long n) {
  long long i, c = 0;
  for (i = 1; i <= n; i++) {
    if (n % i == 0)
      c++;
  }
  if (c == 2) {
    return true;
  } else {
    return false;
  }
}

bool square(long long n) {
  return (sqrt(n)-floor(sqrt(n)) == 0);
}


// sq draws a square in cr with top-left coordinates x and y
void sq(cairo_t *cr, double x, double y) {
  const double size = 15.0;
  cairo_rectangle(cr, x, y, size, size);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
}

int main(int argc, char **argv) {
  // init
  cairo_surface_t *surface;
  cairo_t *cr;
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, atoi(argv[1]), atoi(argv[1]));
  printf("%d", atoi(argv[1]));
  cr = cairo_create(surface);

  // logic
  cairo_set_source_rgb(cr, 255, 255, 255);
  cairo_paint(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_move_to(cr, 00.0, 00.0);

  bool *values = calloc(MAX_ITER, sizeof(bool));

#pragma omp parallel for
  for (long long n = 0; n < MAX_ITER; n++) {
    if (square(n)) values[n] = true;
  }
  printf("Finished calculating values.\n");

  int y = 0;
  for (long long n = 0; n < MAX_ITER; n++) {
    if (n % atoi(argv[1]) == 0) y++;
    if (values[n]) {
      sq(cr, n % atoi(argv[1]), y);
    }
  }



  // cleanup
  free(values);
  char buf[10];
  snprintf(buf, 10, "%d.png", atoi(argv[1]));
  cairo_surface_write_to_png(surface, buf);
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  printf("Completed.\n");
  return 0;
}
