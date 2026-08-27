#include "Physics.h"

/*The commadore 64 has two display modes, 4 color and 2 color. Respectively these have the dimensions,
 160x200 & 320x200. Again respectively, mode 0 & 1. */
void set_display(int mode, Display* display){
  if(mode == 0){
    display->height = 200;
    display->width = 160;
  }else{
    display->height = 200;
    display->width = 320;
  }
}
void invert_mass_values(Body** bodies, int num_bodies){
  for(int body = 0; body < num_bodies; body++){
    bodies[body]->mass = 1/bodies[body]->mass;
  }
}
/* Steps the simulation forward one step, calculating and applying the changes and effects of gravity
    in a 2-D space to all the of bodies in the given list hence the reference to the list of bodies.
*/
void update_vel_newtonian(Body* body1, Body* body2, double delta_time){
  double x_b1 = body1->x;
  double y_b1 = body1->y;
  double x_b2 = body2->x;
  double y_b2 = body2->y;
  double dist = sqrt(pow(x_b2 - x_b1, 2) + pow(y_b2 - y_b1, 2));
  
  double force = -(GRAV_CONST * body1->mass * body2->mass)/pow(dist,2);
  
  double angle = atan2(y_b2-y_b1, x_b2-x_b1);
  /*printf("dist - %f\n", dist); // DEBUG
  printf("grav const - %lf\n", GRAV_CONST); // DEBUG
  printf("force - %f\n", force); // DEBUG
  printf("angle - %f\n", angle); // DEBUG*/

  double x_b1_acc = (force*cos(angle))/body1->mass;
  double x_b2_acc = (force*cos(angle))/body2->mass;
  double y_b1_acc =(force*sin(angle))/body1->mass;
  double y_b2_acc = (force*sin(angle))/body2->mass;
  body1->x_vel += x_b1_acc * delta_time;
  body1->y_vel += y_b1_acc * delta_time;
  body2->x_vel += x_b2_acc * delta_time;
  body2->y_vel += y_b2_acc * delta_time;
}
void update(Body*** bodies, int num_bodies, double delta_time){
  for(int body = 0; body < num_bodies/2; body++){
    Body* curr_body = (*bodies)[body];
    for(int other_body = body+1; other_body < num_bodies; other_body++){
      update_vel_newtonian(curr_body, (*bodies)[other_body], delta_time);
      
    }
  }
  for(int body = 0; body < num_bodies; body++){
    (*bodies)[body]->x += (*bodies)[body]->x_vel * delta_time;
    (*bodies)[body]->y += (*bodies)[body]->y_vel * delta_time;
  }
}
int main(){
  Display display;
  set_display(0, &display);
  Body b1 = {.x = display.width/2, .y = display.height/2, .x_vel = 0, .y_vel = 0, .mass = 7.34767309e22 , .radius = 50000};
  Body b2 = {.x = display.width/2 , .y = -2000, .x_vel = 55000, .y_vel = 0, .mass = 50, .radius = 2};
  //printf("%f", b1.x_vel); // DEBUG
  Body** bodies = malloc(sizeof(Body*) * 2);
  bodies[0] = &b1;
  bodies[1] = &b2;
  double delta_time = 0.00001;
 // return 0; // DEBUG
  int index = 0;
  while(1){
    update(&bodies, 2, delta_time);
    if(index > 10){
      //printf("body 1 (%f, %f) | body 2 (%f, %f)\n", b1.x, b1.y, b2.x, b2.y);
      printf("%f,%f|%f,%f\n", b1.x, b1.y, b2.x, b2.y);
      index = 0;
    }else{
      index++;
    }
    
  }
  free(bodies[0]);
  free(bodies[1]);
  free(bodies);
  return 0;
}
