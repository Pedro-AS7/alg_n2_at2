#include <time.h>

#ifndef ALG_N2_AT2_TYPES_H
#define ALG_N2_AT2_TYPES_H

#define MAX_CLIENTS 50
#define MAX_LEN 100
#define MAX_ORDERS 5

#define DIVIDER "==================================================\n"
#define SUB_DIVIDER "--------------------------------------------------\n"

typedef enum
{
  CUSTOMER = 1,
  ADMIN = 2,
  BOTH = 3
} AccountType;

typedef enum
{
  PIX = 1,
  CREDITCARD = 2,
  CASH = 3
} PaymentMethod;

struct Address
{
  char cep[9];
  char neighborhood[MAX_LEN];
  char street[MAX_LEN];
  char number[10];
  char complement[MAX_LEN];
};

struct CreditCard
{
  char number[MAX_LEN];
  char name[MAX_LEN];
  char validity[6];
  char securityCode[4];
};

struct User
{
  int id;
  char username[MAX_LEN];
  AccountType accountType;
  char email[MAX_LEN];
  char password[MAX_LEN];
  struct Address address[5];
  int address_count;
  struct CreditCard creditCard[5];
  int creditcard_count;
};

struct DaySchedule
{
  char open[6];
  char close[6];
};

struct OpeningHours
{
  struct DaySchedule dom;
  struct DaySchedule seg;
  struct DaySchedule ter;
  struct DaySchedule qua;
  struct DaySchedule qui;
  struct DaySchedule sex;
  struct DaySchedule sab;
};

struct DishOptions
{
  int dish_id;
  char name[MAX_LEN];
  char options[5][MAX_LEN];
  int optionsCount;
};

struct Dish
{
  int id;
  int restaurantId;
  char name[MAX_LEN];
  float price;
  char description[MAX_LEN];
  int amount;
  struct DishOptions options[5];
  int optionCount;
};

struct Restaurant
{
  int id;
  int owner_id;
  char name[MAX_LEN];
  struct Dish dishes[20];
  int dishCount;
  struct Address address;
  struct OpeningHours opening_hours;
};

struct DishOrder
{
  struct Dish dish;
  char dishOptions[25][MAX_LEN];
  int dishOptionsCount;
};

struct Bag
{
  int id;
  int userId;
  int restaurantId;
  struct DishOrder dishOrders[5];
  float totalPrice;
  int dishOrdersCount;
};

typedef enum
{
  STATUS_PENDING = 1,
  STATUS_PREPARING = 2,
  STATUS_DELIVERING = 3,
  STATUS_COMPLETED = 4,
  STATUS_CANCELED = 5,
  STATUS_CONFIRMED = 6
} OrderStatus;

struct Order
{
  int id;
  int user_id;
  int restaurant_id;
  struct DishOrder dishOrders[5];
  int dishOrdersCount;
  struct Address address;
  PaymentMethod paymentMethod;
  float price;
  time_t creationDate;
  time_t deliveryDate;
  OrderStatus status;
};

struct Favorite
{
  int userId;
  int restaurantId;
};


#endif
