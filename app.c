#include <stdio.h>
#include "globals.h"
#include "customerApp.h"
#include "restaurantApp.h"
#include "utils.h"

void app(const int loggedAs)
{
  if (loggedAs == 1)
  {
    customerApp();
  }
  else if (loggedAs == 2)
  {

    struct Restaurant *restaurant = findRestaurantByUserId(currentUser->id);
    restaurantApp(restaurant);
  }
  else
  {
    printf("Tipo de usuario desconhecido.\n");
  }
}