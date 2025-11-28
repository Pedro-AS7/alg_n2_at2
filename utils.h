

#ifndef ALG_N2_AT2_UTILS_H
#define ALG_N2_AT2_UTILS_H

// Forward declarations
struct Dish;
struct DishOptions;
struct Restaurant;

int optionHandler(char *optionText);

struct Bag *findBagByUserId(int id);

struct User *findUserByEmail(const char *email);

struct User *findUserById(int id);

struct Order *findOrderByUserId(int id);

struct Restaurant *findRestaurantByUserId(int id);

void showRestaurantOrders(struct Restaurant *restaurant);

char *getStatusText(int status);

struct Address createAddress();

void setOpeningHours(struct Restaurant *restaurant);

void addDishOption(struct Dish *dish);

void deleteDishOption(struct Dish *dish, int optionIndex);

void showDishOptions(struct Dish *dish);

void showDishes(struct Restaurant *restaurant);

void addAddress();

void deleteAddress(int addressIndex);

void addCard();

void deleteCard(int cardIndex);

void addDishOptionOptions(struct DishOptions *dishOption);

void deleteDishOptionOptions(struct DishOptions *dishOptions, int optionIndex);

void showDishOptionOptions(struct DishOptions *dishOptions);

void addDish(struct Restaurant *restaurant);
void deleteDish(struct Restaurant *restaurant, int dishIndex);

void getOrderDetails(struct Order *order, int orderIndex);

void showOpeningHours(struct Restaurant restaurant);

void generateSellesReport(struct Restaurant *restaurant, int reportPeriod);

int checkDate(time_t orderDate, int reportPeriod);

void dishesRanking(struct Restaurant *restaurant, int reportPeriod);

void generateCustomersReport(struct Restaurant *restaurant, int reportPeriod);

#endif // ALG_N2_AT2_UTILS_H