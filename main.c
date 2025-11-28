#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"
#include "restaurantApp.h"
#include "globals.h"
#include "app.h"
// Dados para teste
// Conta de usuario + restaurante
// Email: pedro@email
// Senha: pedro123

// Conta de usuario:
// Email: maria@email
// Senha: maria123

// Conta de restaurante:
// Email: ze@pizza
// Senha: ze123

//-------------------------------------------------------------------------------------------------------------------
// types.h

/* #define MAX_CLIENTS 50
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

//-------------------------------------------------------------------------------------------------------------------
// globals.c

struct User *currentUser;

struct User users[MAX_CLIENTS] = {
    // Usuario 1: Pedro (Cliente e Dono - Super User)
    {.id = 1,
     .username = "Pedro AS",
     .email = "pedro@email",
     .password = "pedro123",
     .accountType = BOTH,
     .address_count = 1,
     .address = {{.cep = "79152-50", .neighborhood = "Aguas Claras", .street = "Rua 105", .number = "05", .complement = "Apto 1803b"}},
     .creditcard_count = 1,
     .creditCard = {{.number = "1234 5678 9012 3456", .name = "PEDRO A SIMOES", .securityCode = "123", .validity = "12/28"}}},

    // Usuario 2: Maria (Apenas Cliente)
    {.id = 2,
     .username = "Maria Silva",
     .email = "maria@email",
     .password = "maria123",
     .accountType = CUSTOMER,
     .address_count = 2,
     .address = {
         {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202", .number = "Bl A", .complement = "Ap 101"},
         {.cep = "70000-001", .neighborhood = "Lago Sul", .street = "QI 05", .number = "Casa 10", .complement = "Portao Verde"}},
     .creditcard_count = 1,
     .creditCard = {{.number = "9876 5432 1098 7654", .name = "MARIA SILVA", .securityCode = "999", .validity = "10/30"}}},

    // Usuario 3: Zé (Dono da Pizzaria - ID 10 para bater com o owner_id do restaurante 0)
    {.id = 10, .username = "Ze da Pizza", .email = "ze@pizza", .password = "ze123",
     .accountType = ADMIN, // Apenas restaurante
     .address_count = 1,
     .address = {{.cep = "71000-000", .neighborhood = "Taguatinga", .street = "Comercial Norte", .number = "Loja 1", .complement = "Fundos"}},
     .creditcard_count = 0} // Dono de restaurante nao precisa de cartao no mock inicial
};

int users_count = 3; // Atualizado para 3

// Inicializando sacolas para os 3 usuarios criados
struct Bag bags[MAX_CLIENTS] = {
    {.id = 0, .userId = 1, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0},
    {.id = 1, .userId = 2, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0},
    {.id = 2, .userId = 10, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0}};

int bags_count = 3; // Uma sacola para cada usuario inicial

struct Favorite favorites[100] = {
    {.userId = 2,
     .restaurantId = 1},
    {.userId = 1,
     .restaurantId = 1}};

int favorites_count = 2;

struct Order orders[MAX_CLIENTS];
int orders_count = 0;

int restaurants_count = 5;

struct Restaurant restaurants[10] = {
    // Restaurante 1: Pizzaria
    {.id = 0,
     .owner_id = 10, // Pertence ao usuario Zé (ID 10)
     .name = "Pizzaria do Ze",
     .dishCount = 2,
     .opening_hours = {.dom = {"18:00", "23:00"}, .seg = {"Fec", "Fec"}, .ter = {"18:00", "23:00"}, .qua = {"18:00", "23:00"}, .qui = {"18:00", "23:00"}, .sex = {"18:00", "00:00"}, .sab = {"18:00", "00:00"}},
     .dishes = {
         {.id = 101, .name = "Pizza Mussarela", .price = 45.00, .description = "Molho, mussarela, oregano e azeitona.", .restaurantId = 0, .amount = 10, .optionCount = 2, .options = {{.dish_id = 101, .name = "Borda", .optionsCount = 2, .options = {"Catupiry", "Cheddar"}}, {.dish_id = 101, .name = "Massa", .optionsCount = 2, .options = {"Fina", "Pan"}}}},
         {.id = 102, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .description = "Mussarela, calabresa e cebola.", .amount = 15, .optionCount = 0}}},

    // Restaurante 2: Japones
    {.id = 1, .owner_id = 1, .name = "Sushi Mura", .dishCount = 2, .opening_hours = {.dom = {"19:00", "23:00"}, .seg = {"19:00", "23:00"}, .ter = {"19:00", "23:00"}, .qua = {"19:00", "23:00"}, .qui = {"19:00", "23:00"}, .sex = {"19:00", "00:00"}, .sab = {"19:00", "00:00"}}, .dishes = {{.id = 201, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .description = "Sashimi, Niguiri, Joe e Uramaki.", .amount = 5, .optionCount = 0}, {.id = 202, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .description = "Cone de alga com arroz e salmao batido.", .amount = 20, .optionCount = 1, .options = {{.dish_id = 202, .name = "Adicionais", .optionsCount = 2, .options = {"Cream Cheese", "Cebolinha"}}}}}},

    // Restaurante 3: Padaria
    {.id = 2, .owner_id = 12, .name = "Padaria Aurora", .dishCount = 3, .opening_hours = {.dom = {"07:00", "12:00"}, .seg = {"06:00", "20:00"}, .ter = {"06:00", "20:00"}, .qua = {"06:00", "20:00"}, .qui = {"06:00", "20:00"}, .sex = {"06:00", "20:00"}, .sab = {"07:00", "19:00"}}, .dishes = {{.id = 301, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .description = "Pao fresquinho saindo toda hora.", .amount = 50, .optionCount = 0}, {.id = 302, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .description = "Pao de forma, presunto e queijo.", .amount = 10, .optionCount = 0}, {.id = 303, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .description = "Com canela e chocolate.", .amount = 20, .optionCount = 1, .options = {{.dish_id = 303, .name = "Tamanho", .optionsCount = 2, .options = {"Medio", "Grande"}}}}}},

    // Restaurante 4: Hamburgueria
    {.id = 3, .owner_id = 13, .name = "Hamburgueria TOP", .dishCount = 1, .opening_hours = {.dom = {"18:00", "23:00"}, .seg = {"Fec", "Fec"}, .ter = {"18:00", "23:00"}, .qua = {"18:00", "23:00"}, .qui = {"18:00", "23:00"}, .sex = {"18:00", "02:00"}, .sab = {"18:00", "02:00"}}, .dishes = {{.id = 401, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .description = "2 Carnes smash, cheddar, bacon e molho.", .amount = 50, .optionCount = 2, .options = {{.dish_id = 401, .name = "Ponto da Carne", .optionsCount = 3, .options = {"Mal Passado", "Ao Ponto", "Bem Passado"}}, {.dish_id = 401, .name = "Bebida", .optionsCount = 3, .options = {"Coca-Cola", "Guarana", "Sem Bebida"}}}}}},

    // Restaurante 5: Acai (Novo)
    {.id = 4, .owner_id = 14, .name = "Acai do Porto", .dishCount = 2, .opening_hours = {.dom = {"14:00", "20:00"}, .seg = {"12:00", "20:00"}, .ter = {"12:00", "20:00"}, .qua = {"12:00", "20:00"}, .qui = {"12:00", "20:00"}, .sex = {"12:00", "22:00"}, .sab = {"12:00", "22:00"}}, .dishes = {{.id = 501, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .description = "Acai puro batido com banana.", .amount = 100, .optionCount = 1, .options = {{.dish_id = 501, .name = "Complementos", .optionsCount = 4, .options = {"Leite Ninho", "Granola", "Morango", "Pacoca"}}}}, {.id = 502, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .description = "1kg de Acai com 5 acompanhamentos.", .amount = 10, .optionCount = 0}}},
};

//-------------------------------------------------------------------------------------------------------------------
// utils.c

int optionHandler(char *optionText)
{
  do
  {
    int option = 0;
    printf("%s", optionText);
    scanf("%d", &option);

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
    return option;
  } while (true);
}

char *getStatusText(int status)
{
  switch (status)
  {
  case STATUS_PENDING:
    return "Pendente";
  case STATUS_PREPARING:
    return "Em Preparo";
  case STATUS_DELIVERING:
    return "A Caminho";
  case STATUS_COMPLETED:
    return "Entregue";
  case STATUS_CANCELED:
    return "Cancelado";
  default:
    return "Desconhecido";
  }
}

struct User *findUserByEmail(const char *email)
{
  for (int i = 0; i < users_count; i++)
  {
    if (strcmp(users[i].email, email) == 0)
    {
      return &users[i];
    }
  }
  return NULL;
}

struct Bag *findBagByUserId(const int id)
{
  for (int i = 0; i < bags_count; i++)
  {
    if (bags[i].userId == id)
    {
      return &bags[i];
    }
  }
  return NULL;
}

struct User *findUserById(int id)
{
  for (int i = 0; i < users_count; i++)
  {
    if (users[i].id == id)
    {
      return &users[i];
    }
  }
  return NULL;
}

struct Restaurant *findRestaurantByUserId(int id)
{
  for (int i = 0; i < restaurants_count; i++)
  {
    if (restaurants[i].owner_id == id)
    {
      return &restaurants[i];
    }
  }
  return NULL;
}

struct Order *findOrderByUserId(int id)
{
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == id)
    {
      return &orders[i];
    }
  }

  return NULL;
}

struct Address createAddress()
{
  char cep[10];
  char street[MAX_LEN];
  char number[10];
  char complement[MAX_LEN];
  char neighborhood[MAX_LEN];
  struct Address newAddr = {0};

  printf("\n--- Novo Endereco ---\n");
  printf("CEP: ");
  if (fgets(cep, 10, stdin) == NULL)
    return newAddr;
  cep[strcspn(cep, "\n")] = 0;

  printf("Bairro: ");
  if (fgets(neighborhood, MAX_LEN, stdin) == NULL)
    return newAddr;
  neighborhood[strcspn(neighborhood, "\n")] = 0;

  printf("Rua/Quadra: ");
  if (fgets(street, MAX_LEN, stdin) == NULL)
    return newAddr;
  street[strcspn(street, "\n")] = 0;
  printf("Numero: ");
  if (fgets(number, 10, stdin) == NULL)
    return newAddr;
  number[strcspn(number, "\n")] = 0;

  printf("Complemento: ");
  if (fgets(complement, MAX_LEN, stdin) == NULL)
    return newAddr;
  complement[strcspn(complement, "\n")] = 0;

  strcpy(newAddr.cep, cep);
  strcpy(newAddr.street, street);
  strcpy(newAddr.number, number);
  strcpy(newAddr.complement, complement);
  strcpy(newAddr.neighborhood, neighborhood);

  return newAddr;
}

void addAddress()
{
  if (currentUser->address_count >= 5)
  {
    printf("\n(!) Limite de enderecos atingido.\n");
    return;
  }

  currentUser->address[currentUser->address_count] = createAddress();
  currentUser->address_count++;
  printf("\n[v] Endereco adicionado com sucesso!\n");
}

void inputDaySchedule(const char *dayName, struct DaySchedule *schedule)
{
  printf("%-15s\n", dayName);
  printf("  Abertura (HH:MM): ");
  if (fgets(schedule->open, 6, stdin) == NULL)
    return;
  schedule->open[strcspn(schedule->open, "\n")] = 0;
  printf("  Fechamento (HH:MM): ");
  if (fgets(schedule->close, 6, stdin) == NULL)
    return;
  schedule->close[strcspn(schedule->close, "\n")] = 0;
}

void setOpeningHours(struct Restaurant *restaurant)
{
  struct DaySchedule dom, seg, ter, qua, qui, sex, sab;

  printf("\n%s\nDefina o horario de funcionamento:\n%s", DIVIDER, SUB_DIVIDER);
  inputDaySchedule("Domingo", &dom);
  inputDaySchedule("Segunda-feira", &seg);
  inputDaySchedule("Terca-feira", &ter);
  inputDaySchedule("Quarta-feira", &qua);
  inputDaySchedule("Quinta-feira", &qui);
  inputDaySchedule("Sexta-feira", &sex);
  inputDaySchedule("Sabado", &sab);

  restaurant->opening_hours.dom = dom;
  restaurant->opening_hours.seg = seg;
  restaurant->opening_hours.ter = ter;
  restaurant->opening_hours.qua = qua;
  restaurant->opening_hours.qui = qui;
  restaurant->opening_hours.sex = sex;
  restaurant->opening_hours.sab = sab;
}

void deleteAddress(int addressIndex)
{
  if (currentUser->address_count == 0 || addressIndex < 0 || addressIndex >= currentUser->address_count)
  {
    printf("Erro: indice invalido.\n");
    return;
  }

  for (int i = addressIndex; i < currentUser->address_count - 1; i++)
  {
    currentUser->address[i] = currentUser->address[i + 1];
  }

  currentUser->address_count--;

  printf("\n%s Endereco removido com sucesso.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void addCard()
{
  char name[MAX_LEN];
  char number[17];
  char validity[6];
  char securityCode[4];

  if (currentUser->creditcard_count >= 5)
  {
    printf("\n(!) Limite de cartoes atingido.\n");
    return;
  }

  printf("\n--- Novo Cartao ---\n");
  printf("Nome no cartao: ");
  if (fgets(name, MAX_LEN, stdin) == NULL)
    return;
  name[strcspn(name, "\n")] = 0;

  printf("Numero do cartao: ");
  if (fgets(number, MAX_LEN, stdin) == NULL)
    return;
  number[strcspn(number, "\n")] = 0;

  printf("Validade: ");
  if (fgets(validity, MAX_LEN, stdin) == NULL)
    return;
  validity[strcspn(validity, "\n")] = 0;
  printf("Codigo de seguranca: ");
  if (fgets(securityCode, 10, stdin) == NULL)
    return;
  securityCode[strcspn(securityCode, "\n")] = 0;

  struct CreditCard *newCard = &currentUser->creditCard[currentUser->creditcard_count];

  strcpy(newCard->name, name);
  strcpy(newCard->number, number);
  strcpy(newCard->validity, validity);
  strcpy(newCard->securityCode, securityCode);

  currentUser->creditcard_count++;

  printf("\n[v] Cartao adicionado!\n");
}

void deleteCard(int cardIndex)
{
  if (currentUser->creditcard_count == 0 || cardIndex < 0 || cardIndex >= currentUser->creditcard_count)
  {
    printf("Numero selecionado invalido.\n");
    return;
  }

  for (int i = cardIndex; i < currentUser->creditcard_count - 1; i++)
  {
    currentUser->creditCard[i] = currentUser->creditCard[i + 1];
  }

  currentUser->creditcard_count--;

  printf("\n%s Cartao removido com sucesso.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void showDishOptions(struct Dish *dish)
{
  if (dish->optionCount == 0)
  {
    printf("Nenhuma opcao cadastrada para este prato.\n");
    return;
  }

  printf("\nOpcoes do prato '%s':\n", dish->name);
  for (int i = 0; i < dish->optionCount; i++)
  {
    struct DishOptions currentOption = dish->options[i];
    printf(" %d. %s\n", i + 1, currentOption.name);
    for (int j = 0; j < currentOption.optionsCount; j++)
    {
      printf("    - %s\n", currentOption.options[j]);
    }
  }
}

void addDishOption(struct Dish *dish)
{
  if (dish->optionCount >= 5)
  {
    printf("Limite de opcoes atingido.\n");
    return;
  }
  char optionName[MAX_LEN];

  printf("Nome da categoria de opcao (ex: Tamanho): ");
  if (fgets(optionName, MAX_LEN, stdin) == NULL)
    return;
  optionName[strcspn(optionName, "\n")] = 0;

  strcpy(dish->options[dish->optionCount].name, optionName);

  dish->options[dish->optionCount].dish_id = dish->id;
  dish->options[dish->optionCount].optionsCount = 0;
  dish->optionCount++;

  printf("Adicione as escolhas para '%s':\n", optionName);
  for (int i = 0; i < 5; i++)
  {
    char optionValue[MAX_LEN];
    printf("Escolha %d (ou digite 'sair'): ", i + 1);
    if (fgets(optionValue, MAX_LEN, stdin) == NULL)
      return;
    optionValue[strcspn(optionValue, "\n")] = 0;
    if (strcmp(optionValue, "sair") == 0)
    {
      break;
    }
    strcpy(dish->options[dish->optionCount - 1].options[i], optionValue);
    dish->options[dish->optionCount - 1].optionsCount++;
  }

  printf("Opcao adicionada!\n");
}

void deleteDishOption(struct Dish *dish, int optionIndex)
{
  if (dish->optionCount == 0 || optionIndex < 0 || optionIndex >= dish->optionCount)
  {
    printf("indice invalido.\n");
    return;
  }

  for (int i = optionIndex; i < dish->optionCount - 1; i++)
  {
    dish->options[i] = dish->options[i + 1];
  }

  dish->optionCount--;

  printf("\n%s Opcao deletada.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void addDishOptionOptions(struct DishOptions *dishOptions)
{
  if (dishOptions->optionsCount >= 5)
  {
    printf("Limite de opcoes atingido.\n");
    return;
  }
  char optionValue[MAX_LEN];

  printf("Valor da opcao: ");
  if (fgets(optionValue, MAX_LEN, stdin) == NULL)
    return;
  optionValue[strcspn(optionValue, "\n")] = 0;

  strcpy(dishOptions->options[dishOptions->optionsCount], optionValue);
  dishOptions->optionsCount++;

  printf("Opcao adicionada!\n");
}

void deleteDishOptionOptions(struct DishOptions *dishOptions, int optionIndex)
{
  if (dishOptions->optionsCount == 0 || optionIndex < 0 || optionIndex >= dishOptions->optionsCount)
  {
    printf("indice de delecao invalido.\n");
    return;
  }

  for (int i = optionIndex; i < dishOptions->optionsCount - 1; i++)
  {
    strcpy(dishOptions->options[i], dishOptions->options[i + 1]);
  }

  dishOptions->optionsCount--;

  printf("\n%s Opcao deletada.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void showDishOptionOptions(struct DishOptions *dishOptions)
{
  if (dishOptions->optionsCount == 0)
  {
    printf("Nenhuma opcao cadastrada.\n");
    return;
  }

  printf("Opcoes para %s:\n", dishOptions->name);
  for (int i = 0; i < dishOptions->optionsCount; i++)
  {
    printf("  - %s\n", dishOptions->options[i]);
  }
}

void showDishes(struct Restaurant *restaurant)
{
  if (restaurant->dishCount == 0)
  {
    printf("Nenhum prato cadastrado.\n");
    return;
  }

  printf("\n=== Pratos de %s ===\n", restaurant->name);
  for (int i = 0; i < restaurant->dishCount; i++)
  {
    struct Dish currentDish = restaurant->dishes[i];
    printf("%d. %-30s R$ %.2f\n", i + 1, currentDish.name, currentDish.price);
    printf("    Descricao: %s\n", currentDish.description);
    printf("    Estoque: %d\n", currentDish.amount);
    if (currentDish.optionCount > 0)
    {
      printf("    Opcoes configuraveis:\n");
      for (int j = 0; j < currentDish.optionCount; j++)
      {
        struct DishOptions currentOption = currentDish.options[j];
        printf("      * %s\n", currentOption.name);
      }
    }
    printf("%s", SUB_DIVIDER);
  }
}

void addDish(struct Restaurant *restaurant)
{
  if (restaurant->dishCount >= 20)
  {
    printf("Limite de pratos atingido.\n");
    return;
  }

  char dishName[MAX_LEN];
  float dishPrice;
  int dishAmount;
  char dishDescription[MAX_LEN];

  printf("\n--- Novo Prato ---\n");
  printf("Nome do prato: ");
  if (fgets(dishName, MAX_LEN, stdin) == NULL)
    return;
  dishName[strcspn(dishName, "\n")] = 0;

  printf("Preco (ex: 25.50): ");
  scanf("%f", &dishPrice);

  printf("Quantidade disponivel: ");
  scanf("%d", &dishAmount);

  getchar();

  printf("Descricao do prato: ");
  if (fgets(dishDescription, MAX_LEN, stdin) == NULL)
    return;
  dishDescription[strcspn(dishDescription, "\n")] = 0;

  struct Dish *newDish = &restaurant->dishes[restaurant->dishCount];

  newDish->id = restaurant->dishCount;
  newDish->restaurantId = restaurant->id;
  strcpy(newDish->name, dishName);
  newDish->price = dishPrice;
  newDish->amount = dishAmount;
  strcpy(newDish->description, dishDescription);
  newDish->optionCount = 0;
  restaurant->dishCount++;

  printf("Adicionar opcoes personalizaveis? (s/n): ");
  char addOptions;
  scanf(" %c", &addOptions);
  getchar();

  if (addOptions == 's' || addOptions == 'S')
  {
    do
    {
      if (newDish->optionCount >= 5)
      {
        printf("Limite de opcoes atingido.\n");
        break;
      }
      addDishOption(newDish);
      printf("Adicionar outra categoria de opcao? (s/n): ");
      char anotherOption;
      scanf(" %c", &anotherOption);
      getchar();
      if (anotherOption != 's' && anotherOption != 'S')
      {
        break;
      }
    } while (true);
  }
  else
  {
    printf("Prato adicionado (sem opcoes extras).\n");
  }
}

void deleteDish(struct Restaurant *restaurant, int dishIndex)
{
  if (restaurant->dishCount == 0 || dishIndex < 0 || dishIndex >= restaurant->dishCount)
  {
    printf("indice invalido.\n");
    return;
  }

  for (int i = dishIndex; i < restaurant->dishCount - 1; i++)
  {
    restaurant->dishes[i] = restaurant->dishes[i + 1];
  }

  restaurant->dishCount--;

  printf("\n%s Prato deletado com sucesso.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void showRestaurantOrders(struct Restaurant *restaurant)
{
  printf("\n=== Pedidos Recebidos: %s ===\n", restaurant->name);
  bool hasOrders = false;
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].restaurant_id == restaurant->id && orders[i].status != STATUS_CONFIRMED && orders[i].status != STATUS_CANCELED)
    {
      hasOrders = true;
      printf("Pedido #%d | Cliente: %s\nStatus: [%s]\n", i + 1, findUserById(orders[i].user_id)->username, getStatusText(orders[i].status));
      for (int j = 0; j < orders[i].dishOrdersCount; j++)
      {
        struct DishOrder currentDishOrder = orders[i].dishOrders[j];
        printf("  > %s (Opcoes: %d)\n", currentDishOrder.dish.name, currentDishOrder.dishOptionsCount);
      }
      printf("%s", SUB_DIVIDER);
    }
  }
  if (!hasOrders)
  {
    printf("Nenhum pedido ativo no momento.\n");
  }
}

void getOrderDetails(struct Order *order, int orderIndex)
{
  printf("\n%s DETALHES DO PEDIDO #%d\n%s", DIVIDER, orderIndex + 1, DIVIDER);
  printf("Cliente....: %s\n", findUserById(order->user_id)->username);
  printf("Status.....: %s\n", getStatusText(order->status));
  printf("Itens:\n");
  for (int j = 0; j < order->dishOrdersCount; j++)
  {
    struct DishOrder currentDishOrder = order->dishOrders[j];
    printf("  %d. %s\n", j + 1, currentDishOrder.dish.name);
    if (currentDishOrder.dishOptionsCount > 0)
    {
      for (int k = 0; k < currentDishOrder.dishOptionsCount; k++)
      {
        printf("     * %s\n", currentDishOrder.dishOptions[k]);
      }
    }
  }
  printf("%s", DIVIDER);
}

//-------------------------------------------------------------------------------------------------------------------
// customerApp.c

void cleanBag(struct Bag *bag)
{
  bag->totalPrice = 0;
  bag->dishOrdersCount = 0;
  bag->restaurantId = -1;
}

void showAddress()
{
  for (int i = 0; i < currentUser->address_count; i++)
  {
    struct Address currentAddress = currentUser->address[i];
    printf("%s", SUB_DIVIDER);
    printf("Endereco [%d]: \n", i + 1);
    printf("   CEP........: %s\n", currentAddress.cep);
    printf("   Bairro.....: %s\n", currentAddress.neighborhood);
    printf("   Rua........: %s, %s\n", currentAddress.street, currentAddress.number);
    printf("   Complemento: %s\n", currentAddress.complement);
  }
  printf("%s", SUB_DIVIDER);
}

void createDishOrder(struct Restaurant restaurant, struct Dish dish, char dishOptions[25][MAX_LEN], int optionCount)
{
  printf("\nAdicionando item a sacola...\n");
  struct DishOrder dishOrder;

  dishOrder.dish = dish;
  dishOrder.dishOptionsCount = optionCount;
  memcpy(dishOrder.dishOptions, dishOptions, sizeof(dishOrder.dishOptions));

  struct Bag *userBag = findBagByUserId(currentUser->id);

  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == currentUser->id && orders[i].status != STATUS_CANCELED && orders[i].status != STATUS_COMPLETED)
    {
      printf("(!) Voce tem um pedido em andamento. Aguarde a finalizacao.\n");
      return;
    }
  }

  if (dishOrder.dish.restaurantId != userBag->restaurantId && userBag->restaurantId != -1)
  {
    int option = 0;
    bool whileLoop = true;

    do
    {
      printf("(!) A sacola contem itens de outro restaurante.\n");
      printf("Deseja esvaziar a sacola atual e iniciar uma nova? (1-Sim / 0-Nao)\n");
      option = optionHandler("Opcao: ");
      switch (option)
      {
      case 0:
        return;
      case 1:
        cleanBag(userBag);
        whileLoop = false;
        break;
      default:
        printf("Opcao invalida!\n");
      }

    } while (whileLoop);
  }

  if (userBag->dishOrdersCount == 5)
  {
    printf("\n(!) Limite de itens na sacola atingido!\n");
    return;
  }

  bags[userBag->id].userId = currentUser->id;
  bags[userBag->id].dishOrders[bags[userBag->id].dishOrdersCount] = dishOrder;
  bags[userBag->id].dishOrdersCount++;
  bags[userBag->id].totalPrice = bags[userBag->id].totalPrice + dish.price;
  bags[userBag->id].restaurantId = restaurant.id;

  printf("[v] Item adicionado a sacola!\n");
}

void dishOptions(const struct Restaurant restaurant, struct Dish dish)
{
  int dishOption = 0;
  char options[25][MAX_LEN];
  int optionsCount = 0;

  if (dish.optionCount != 0)
  {
    do
    {
      if (dish.amount == 0)
      {
        printf("(!) Este prato esta indisponivel!");
        return;
      }
      printf("\n--- Personalize seu Pedido ---\n");

      for (int j = 0; j < dish.optionCount; j++)
      {
        printf(" %s: \n", dish.options[j].name);
        for (int k = 0; k < dish.options[j].optionsCount; k++)
        {
          printf("    %d. %s\n", k + 1, dish.options[j].options[k]);
        }
        dishOption = optionHandler("Selecione a opcao: ");
        strcpy(options[j], dish.options[j].options[dishOption - 1]);
        optionsCount++;
      }
      printf("%s", SUB_DIVIDER);
      break;
    } while (true);
  }

  createDishOrder(restaurant, dish, options, optionsCount);
}

void restaurantMenu(const struct Restaurant restaurant)
{
  int option = 0;
  do
  {
    if (restaurant.dishCount == 0)
    {
      printf("Este restaurante nao tem pratos cadastrados\n");
      break;
    }
    printf("\n%s        CARDaPIO: %s        \n%s", DIVIDER, restaurant.name, DIVIDER);
    for (int i = 0; i < restaurant.dishCount; i++)
    {
      struct Dish currentDish = restaurant.dishes[i];

      printf("%d. %-30s (R$ %.2f)\n    Descricao: %s\n%s",
             i + 1,
             currentDish.name,
             currentDish.price,
             currentDish.description,
             SUB_DIVIDER);
    }
    option = optionHandler("Digite o numero do prato para adicionar (0 para voltar): ");

    if (option == 0)
    {
      break;
    }
    dishOptions(restaurant, restaurant.dishes[option - 1]);
  } while (true);
}

void showOpeningHours(struct Restaurant restaurant)
{
  struct OpeningHours openingHours = restaurant.opening_hours;
  printf("\n%s Horarios de: %s\n%s", DIVIDER, restaurant.name, DIVIDER);
  printf("Domingo....: %s - %s\n", openingHours.dom.open, openingHours.dom.close);
  printf("Segunda....: %s - %s\n", openingHours.seg.open, openingHours.seg.close);
  printf("Terca......: %s - %s\n", openingHours.ter.open, openingHours.ter.close);
  printf("Quarta.....: %s - %s\n", openingHours.qua.open, openingHours.qua.close);
  printf("Quinta.....: %s - %s\n", openingHours.qui.open, openingHours.qui.close);
  printf("Sexta......: %s - %s\n", openingHours.sex.open, openingHours.sex.close);
  printf("Sabado.....: %s - %s\n", openingHours.sab.open, openingHours.sab.close);
  printf("%s", DIVIDER);
}

void intoRestaurant(const struct Restaurant restaurant)
{
  int option = 0;
  do
  {
    printf("\n%s Restaurante: %s\n%s", DIVIDER, restaurant.name, DIVIDER);
    option = optionHandler("1. Cardapio\n2. Horarios de funcionamento\n3. Marcar como favorito\n4. Voltar\nOpcao: ");

    switch (option)
    {
    case 1:
      restaurantMenu(restaurant);
      break;
    case 2:
      showOpeningHours(restaurant);
      break;
    case 3:
      for (int i = 0; i < favorites_count; i++)
      {
        if (favorites[i].userId == currentUser->id && favorites[favorites_count].restaurantId == restaurant.id)
        {
          printf("Voce ja marcou este restaurante como favorito!\n");
          break;
        }
      }
      favorites[favorites_count].userId = currentUser->id;
      favorites[favorites_count].restaurantId = restaurant.id;
      favorites_count++;
      printf("O restaurante %s foi marcado como favorito!\n", restaurant.name);

    case 4:
      return;
    default:
      printf("Opcao invalida\n");
    }
  } while (true);
}

void restaurantsSection()
{
  int option = 0;
  do
  {
    printf("\n%s     RESTAURANTES DISPONiVEIS     \n%s", DIVIDER, DIVIDER);
    for (int i = 0; i < restaurants_count; i++)
    {
      printf("%d. %s\n", i + 1, restaurants[i].name);
    }
    printf("%s", SUB_DIVIDER);
    option = optionHandler("Selecione um restaurante (0 para voltar): ");

    if (option == 0)
    {
      break;
    }

    intoRestaurant(restaurants[option - 1]);
  } while (true);
}

void addressSection()
{
  int option = 0;
  do
  {
    printf("\n%s      MEUS ENDEREcOS      \n%s", DIVIDER, DIVIDER);
    showAddress();
    option = optionHandler("1. Adicionar endereco\n2. Remover endereco\n3. Voltar\nOpcao: ");

    switch (option)
    {
    case 1:
      addAddress();
      break;
    case 2:
      do
      {
        if (currentUser->address_count < 1)
        {
          printf("Nao ha enderecos para remover");
        }
        int deleteOption = optionHandler("Numero do endereco para deletar (0 cancelar): ");
        if (deleteOption == 0)
        {
          break;
        }
        if (deleteOption > currentUser->address_count || deleteOption < 1)
        {
          continue;
        }
        deleteOption = deleteOption - 1;
        deleteAddress(deleteOption);
        break;
      } while (true);
      break;
    case 3:
      return;
    default:
      printf("Opcao invalida\n");
    }
  } while (true);
}

void showCards()
{
  for (int i = 0; i < currentUser->creditcard_count; i++)
  {
    struct CreditCard currentCard = currentUser->creditCard[i];
    printf("%s", SUB_DIVIDER);
    printf("Cartao [%d]: \n", i + 1);
    printf("   Titular....: %s\n", currentCard.name);
    printf("   Numero.....: %s\n", currentCard.number);
    printf("   Validade...: %s\n", currentCard.validity);
  }
  printf("%s", SUB_DIVIDER);
}

void cardSection()
{
  int option = 0;
  do
  {
    printf("\n%s       MEUS CARToES       \n%s", DIVIDER, DIVIDER);
    showCards();
    option = optionHandler("1. Adicionar cartao\n2. Remover cartao\n3. Voltar\nOpcao: ");

    switch (option)
    {
    case 1:
      addCard();
      break;
    case 2:
      do
      {
        if (currentUser->creditcard_count < 1)
        {
          printf("Nao ha cartoes para remover");
        }
        int deleteOption = optionHandler("Numero do cartao para deletar (0 cancelar): ");
        if (deleteOption == 0)
        {
          break;
        }
        if (deleteOption > currentUser->creditcard_count || deleteOption < 1)
        {
          continue;
        }
        deleteOption = deleteOption - 1;
        deleteCard(deleteOption);
        break;
      } while (true);
    case 3:
      return;
    }
  } while (true);
}

void profile()
{
  int option = 0;
  do
  {
    printf("\n%s     CONFIGURAcoES DA CONTA     \n%s", DIVIDER, DIVIDER);
    option = optionHandler("1. Enderecos\n2. Cartoes\n3. Dados da conta\n4. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      addressSection();
      break;
    case 2:
      cardSection();
      break;
    case 3:
      printf("\n%s DADOS DO PERFIL\n", SUB_DIVIDER);
      printf(" Username: %s\n", currentUser->username);
      printf(" Email...: %s\n", currentUser->email);
      printf(" Senha...: ********\n");
      printf("%s", SUB_DIVIDER);
      break;
    case 4:
      return;
    default:
      printf("Opcao invalida\n");
    }
  } while (true);
}

void finalizeBag(struct Bag *bag)
{
  if (currentUser->address_count < 1)
  {
    printf("(!) Voce nao tem um endereco cadastrado. Cadastre um para finalizar o pedido.\n");
    return;
  }
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == currentUser->id)
    {
      printf("(!) Voce ja tem um pedido em andamento.\n");
      return;
    }
  }
  int addressOption = 0;
  int paymentMethodOption = 0;
  PaymentMethod paymentMethod;
  int cardOption = 0;
  struct Restaurant *restaurant = findRestaurantByUserId(bag->restaurantId);

  printf("\n%s   FINALIZANDO PEDIDO   \n%s", DIVIDER, DIVIDER);
  do
  {
    printf("Selecione o endereco de entrega: \n");
    showAddress();
    addressOption = optionHandler("Opcao: ");
    if (addressOption < 1 || addressOption > currentUser->address_count)
    {
      printf("Endereco invalido\n");
      continue;
    }
    addressOption--;
    break;
  } while (true);

  do
  {
    printf("\nForma de pagamento: \n");
    printf("1. Pix\n2. Cartao de credito\n3. Dinheiro\n");
    paymentMethodOption = optionHandler("Opcao: ");
    switch (paymentMethodOption)
    {
    case 1:
      printf("Pix selecionado.\n");
      paymentMethod = PIX;
      break;
    case 2:
      paymentMethod = CREDITCARD;
      if (currentUser->creditcard_count < 1)
      {
        printf("(!) Voce nao tem um cartao cadastrado.\n");
        return;
      }
      do
      {
        showCards();
        cardOption = optionHandler("Selecione o cartao: ");
        if (cardOption < 1 || cardOption > currentUser->creditcard_count)
        {
          printf("Cartao invalido\n");
          continue;
        }
        cardOption--;
        printf("Cartao final %s selecionado\n", currentUser->creditCard[cardOption].number);

        break;
      } while (true);
      break;
    case 3:
      paymentMethod = CASH;
      printf("Dinheiro selecionado.\n");
      break;
    }
    break;
  } while (true);

  printf("\n%s   RESUMO DO PEDIDO   \n%s", DIVIDER, SUB_DIVIDER);
  printf("Entrega: %s, %s - %s\n", currentUser->address[addressOption].street,
         currentUser->address[addressOption].number,
         currentUser->address[addressOption].complement);
  switch (paymentMethodOption)
  {
  case 1:
    printf("Pagamento: Pix.\n");
    break;
  case 2:
    printf("Pagamento: Cartao de credito\n");
    break;
  case 3:
    printf("Pagamento: Dinheiro.\n");
    break;
  }

  printf("\nTOTAL A PAGAR: R$ %.2f\n", bag->totalPrice);
  printf("%s", DIVIDER);

  int option = 0;
  do
  {
    option = optionHandler("1. Confirmar Pedido\n2. Cancelar\nOpcao: ");
    switch (option)
    {
    case 1:
      if (paymentMethod == PIX)
      {
        int pixOption = 0;
        bool whileValid = true;
        do
        {
          printf("\n(i) Efetue o Pix para a chave: 9999999999 (Valido por 10 min).\n");
          pixOption = optionHandler("1. Pagamento efetuado\n2. Cancelar\nOpcao: ");
          switch (pixOption)
          {
          case 1:
            whileValid = false;
            break;
          case 2:
            printf("Pedido Cancelado!\n");
            return;
          default:
            printf("Opcao invalida!\n");
          }
        } while (whileValid);
      }
      orders[orders_count].id = orders_count;
      orders[orders_count].restaurant_id = bag->restaurantId;
      orders[orders_count].user_id = bag->userId;
      orders[orders_count].paymentMethod = paymentMethod;
      orders[orders_count].address = currentUser->address[addressOption];
      orders[orders_count].price = bag->totalPrice;
      for (int i = 0; i < bag->dishOrdersCount; i++)
      {
        orders[orders_count].dishOrders[i] = bag->dishOrders[i];
        orders[orders_count].dishOrdersCount++;
      }
      const time_t current_time = time(NULL);
      orders[orders_count].creationDate = current_time;
      orders[orders_count].status = STATUS_PENDING;
      orders_count++;
      cleanBag(bag);
      printf("\n[v] Pedido realizado com sucesso!\n");
      return;
    case 2:
      printf("Pedido Cancelado!\n");
      return;
    }
  } while (true);
}

void showBag(const struct Bag *bag)
{
  printf("\n%s      MINHA SACOLA      \n%s", DIVIDER, DIVIDER);
  if (bag->dishOrdersCount == 0)
  {
    printf("A sacola esta vazia.\n");
    printf("%s", DIVIDER);
    return;
  }
  for (int i = 0; i < bag->dishOrdersCount; i++)
  {
    struct DishOrder currentDish = bag->dishOrders[i];
    printf("%d. %-25s R$ %.2f\n", i + 1, currentDish.dish.name, currentDish.dish.price);

    if (currentDish.dishOptionsCount != 0)
    {
      for (int j = 0; j < currentDish.dishOptionsCount; j++)
      {
        printf("    + %s\n", currentDish.dishOptions[j]);
      }
    }
  }
  printf("%s", SUB_DIVIDER);
  printf(" TOTAL: R$ %6.2f", bag->totalPrice);
  printf("\n%s", DIVIDER);
}

void bagSection()
{
  int option = 0;
  struct Bag *currentBag = findBagByUserId(currentUser->id);
  do
  {
    showBag(currentBag);
    option = optionHandler("1. Finalizar Sacola\n2. Limpar sacola\n3. Remover item da sacola\n4. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      if (currentBag->dishOrdersCount == 0)
      {
        printf("Sua sacola esta vazia.\n");
      }
      else
      {
        finalizeBag(currentBag);
      }
      break;
    case 2:
      cleanBag(currentBag);
      printf("Sacola limpa.\n");
      break;
    case 3:
      do
      {
        if (currentBag->dishOrdersCount < 1)
        {
          printf("Nao ha itens para remover");
          break;
        }
        int deleteOption = optionHandler("Numero do item para deletar (0 cancelar): ");
        if (deleteOption == 0)
        {
          break;
        }
        if (deleteOption > currentBag->dishOrdersCount || deleteOption < 1)
        {
          continue;
        }
        deleteOption = deleteOption - 1;
        struct Dish dishToRemove = currentBag->dishOrders[deleteOption].dish;
        for (int i = deleteOption; i < currentBag->dishOrdersCount - 1; i++)
        {
          currentBag->dishOrders[i] = currentBag->dishOrders[i + 1];
        }
        currentBag->dishOrdersCount--;
        currentBag->totalPrice -= dishToRemove.price;
        printf("\n%s Item removido da sacola.\n%s", SUB_DIVIDER, SUB_DIVIDER);
        break;
      } while (true);
      break;
    case 4:
      return;
    default:
      printf("Opcao invalida\n");
    }
  } while (true);
}

void orderStatus()
{
  int option = 0;
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == currentUser->id && orders[i].status != STATUS_CANCELED && orders[i].status != STATUS_CONFIRMED)
    {
      char *date = ctime(&orders[i].creationDate);
      printf("\n%s   ACOMPANHAMENTO DO PEDIDO   \n%s", DIVIDER, DIVIDER);
      printf("Pedido #%d | Data: %s", orders[i].id, date);
      printf("Status Atual: [%s]\n", getStatusText(orders[i].status));
      printf("%s", SUB_DIVIDER);

      switch (orders[i].status)
      {
      case STATUS_PENDING:
      case STATUS_PREPARING:
      case STATUS_DELIVERING:
        break;
      case STATUS_COMPLETED:
        printf("O pedido foi marcado como entregue.\n");
        printf("Confirme o recebimento:\n");
        option = optionHandler("1. Recebi o pedido\n0. Ainda nao recebi\nOpcao: ");
        if (option == 1)
        {
          orders[i].status = STATUS_CONFIRMED;
          printf("Recebimento confirmado. Bom apetite!\n");
        }
        else
        {
          printf("Aguardando confirmacao.\n");
        }
        break;
      case STATUS_CONFIRMED:
      case STATUS_CANCELED:
        break;
      }

      if (orders[i].status != STATUS_CONFIRMED)
      {
        do
        {
          int option = 0;
          option = optionHandler("1. Cancelar pedido\n2. Voltar\nOpcao: ");
          switch (option)
          {
          case 1:
            orders[i].status = STATUS_CANCELED;
            printf("Pedido Cancelado!\n");
            return;
          case 2:
            return;
          default:
            printf("Opcao invalida\n");
            break;
          }
        } while (true);
      }
    }
  }
  printf("\nNenhum pedido em andamento no momento.\n");
}

void orderHistory()
{
  printf("\n%s   HISToRICO DE PEDIDOS   \n%s", DIVIDER, DIVIDER);
  bool hasHistory = false;
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == currentUser->id && (orders[i].status == STATUS_CANCELED || orders[i].status == STATUS_CONFIRMED))
    {
      hasHistory = true;
      char *date = ctime(&orders[i].creationDate);
      printf("Pedido #%d | Data: %s", orders[i].id, date);
      printf("Status Final: %s\n", getStatusText(orders[i].status));
      printf("%s", SUB_DIVIDER);
    }
  }
  if (!hasHistory)
  {
    printf("Nenhum historico disponivel.\n");
  }
  printf("%s", DIVIDER);
}

void orderSection()
{
  int option = 0;
  do
  {
    printf("\n%s        MEUS PEDIDOS        \n%s", DIVIDER, DIVIDER);
    option = optionHandler("1. Pedido em andamento (Status)\n2. Historico de pedidos\n3. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      orderStatus();
      break;
    case 2:
      orderHistory();
      break;
    case 3:
      return;
    }
  } while (true);
}

void costumerApp()
{
  int option = 0;
  do
  {
    printf("\n%s      MENU DO CLIENTE      \n%s", DIVIDER, DIVIDER);
    printf("Bem vindo, %s!\n", currentUser->username);
    printf("%s", SUB_DIVIDER);
    option = optionHandler(
        "1. Restaurantes\n2. Sacola\n3. Meu Perfil\n4. Pedidos\n5. Sair (Logout)\nOpcao: ");
    switch (option)
    {
    case 1:
      restaurantsSection();
      break;
    case 2:
      bagSection();
      break;
    case 3:
      profile();
      break;
    case 4:
      orderSection();
      break;
    case 5:
      return;
    default:
      printf("Opcao invalida");
    }
  } while (true);
}

//-------------------------------------------------------------------------------------------------------------------
// restaurantApp.c

void dishOptionsOptionSection(struct DishOptions *dishOption)
{
  printf("\nEditando opcoes para: %s\n", dishOption->name);
  int option = 0;
  do
  {
    printf("%s", SUB_DIVIDER);
    for (int i = 0; i < dishOption->optionsCount; i++)
    {
      printf("%d. %s\n", i + 1, dishOption->options[i]);
    }
    printf("%s", SUB_DIVIDER);
    option = optionHandler("1. Adicionar item\n2. Remover item\n3. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      addDishOptionOptions(dishOption);
      break;
    case 2:

      do
      {
        int itemIndex = 0;
        itemIndex = optionHandler("Numero do item para remover (0 cancelar): ") - 1;
        if (itemIndex == -1)
        {
          break;
        }
        if (itemIndex < 0 || itemIndex >= dishOption->optionsCount)
        {
          printf("Indice invalido.\n");
          continue;
        }
        deleteDishOptionOptions(dishOption, itemIndex);
        break;
      } while (true);

      break;
    case 3:
      return;
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } while (true);
}

void dishOptionsSection(struct Dish *dish)
{
  int option = 0;
  do
  {
    printf("\n--- Gerenciar Opcoes do Prato: %s ---\n", dish->name);
    showDishOptions(dish);
    printf("%s", SUB_DIVIDER);
    option = optionHandler("1. Adicionar categoria de opcao\n2. Remover categoria\n3. Editar itens da categoria\n4. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      addDishOption(dish);
      break;
    case 2:

      do
      {
        int optionIndex = 0;
        optionIndex = optionHandler("Numero da opcao para remover (0 cancelar): ") - 1;
        if (optionIndex == -1)
        {
          break;
        }
        if (optionIndex < 0 || optionIndex >= dish->optionCount)
        {
          printf("Indice invalido.\n");
          continue;
        }
        deleteDishOption(dish, optionIndex);
        break;
      } while (true);

      break;
    case 3:
      do
      {
        int optionIndex = 0;
        optionIndex = optionHandler("Numero da opcao para editar (0 cancelar): ") - 1;
        if (optionIndex == -1)
        {
          break;
        }
        if (optionIndex < 0 || optionIndex >= dish->optionCount)
        {
          printf("Indice invalido.\n");
          continue;
        }
        dishOptionsOptionSection(&dish->options[optionIndex]);
        break;
      } while (true);
    case 4:
      return;
    default:
      printf("Opcao invalida.\n");
      break;
    }
  } while (true);
}

void dishesSection(struct Restaurant *restaurant)
{
  int option = 0;
  do
  {
    printf("\n--- Gerenciar Pratos: %s ---\n", restaurant->name);
    showDishes(restaurant);
    option = optionHandler("1. Adicionar prato\n2. Remover prato\n3. Configurar opcoes do prato\n4. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      addDish(restaurant);
      break;
    case 2:
      do
      {
        int optionIndex = 0;
        optionIndex = optionHandler("Numero do prato para remover (0 cancelar): ") - 1;
        if (optionIndex == -1)
        {
          break;
        }
        if (optionIndex < 0 || optionIndex >= restaurant->dishCount)
        {
          printf("Indice invalido.\n");
          continue;
        }
        deleteDish(restaurant, optionIndex);
        break;
      } while (true);

      break;
    case 3:
      do
      {
        int optionIndex = 0;
        optionIndex = optionHandler("Numero do prato para configurar (0 cancelar): ") - 1;
        if (optionIndex == -1)
        {
          break;
        }
        if (optionIndex < 0 || optionIndex >= restaurant->dishCount)
        {
          printf("Indice invalido.\n");
          continue;
        }
        dishOptionsSection(&restaurant->dishes[optionIndex]);
        break;
      } while (true);
      break;
    case 4:
      return;

    default:
      break;
    }
  } while (true);
}

void manageOrder(struct Restaurant *restaurant, int orderIndex)
{
  struct Order *order = &orders[orderIndex];
  getOrderDetails(order, orderIndex);

  int option = optionHandler("1. Atualizar status\n2. Voltar\nOpcao: ");
  switch (option)
  {
  case 1:
    printf("--- Atualizar Status ---\n");
    printf("Atual: %s\n", getStatusText(order->status));
    printf("Novo status:\n");
    printf("1. Pendente\n2. Em Preparo\n3. A Caminho\n4. Entregue\n5. Cancelado\n");
    int newStatus = optionHandler("Opcao: ");
    if (newStatus >= STATUS_PENDING && newStatus <= STATUS_CANCELED)
    {
      order->status = newStatus;
      printf("Status atualizado para: %s\n", getStatusText(order->status));
      if (order->status == STATUS_CANCELED)
      {
        printf("O pedido foi cancelado.\n");
      }
      if (order->status == STATUS_COMPLETED)
      {
        order->deliveryDate = time(NULL);
      }
    }
    else
    {
      printf("Status invalido.\n");
    }
    break;
  case 2:
    return;
  default:
    printf("Opcao invalida.\n");
    break;
  }
}

void ordersHistory(struct Restaurant *restaurant)
{
  printf("\n--- Historico de Pedidos: %s ---\n", restaurant->name);
  bool hasOrders = false;
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].restaurant_id == restaurant->id && (orders[i].status == STATUS_COMPLETED || orders[i].status == STATUS_CANCELED))
    {
      hasOrders = true;
      getOrderDetails(&orders[i], i);
    }
  }
  if (!hasOrders)
  {
    printf("Nenhum pedido finalizado.\n");
  }
}

void ordersSection(struct Restaurant *restaurant)
{
  printf("\n%s   GERENCIAMENTO DE PEDIDOS   \n%s", DIVIDER, DIVIDER);
  do
  {
    int option = 0;
    showRestaurantOrders(restaurant);
    printf("1. Gerenciar/Detalhes de pedido ativo\n2. Historico de Pedidos\n3. Voltar\n");
    option = optionHandler("Opcao: ");
    switch (option)
    {
    case 1:
    {
      int orderIndex = optionHandler("Numero do pedido para gerenciar (0 cancelar): ") - 1;
      if (orderIndex == -1)
      {
        break;
      }
      bool orderFound = false;
      for (int i = 0; i < orders_count; i++)
      {
        if (orders[i].restaurant_id == restaurant->id && i == orderIndex)
        {
          manageOrder(restaurant, i);
          orderFound = true;
          break;
        }
      }
      if (!orderFound)
      {
        printf("Pedido nao encontrado.\n");
      }
      break;
    }
    case 2:
      ordersHistory(restaurant);
      break;
    case 3:
      return;
    default:
      printf("Opcao invalida.\n");
      break;
    }

  } while (true);
}

void restaurantApp(struct Restaurant *restaurant)
{
  int option;
  int modifyOpeningHours;
  do
  {
    printf("\n%s      PAINEL DO RESTAURANTE      \n%s", DIVIDER, DIVIDER);
    printf("Logado como: %s\n", restaurant->name);
    printf("%s", SUB_DIVIDER);
    printf("1. Ver perfil\n");
    printf("2. Gerenciar cardapio (Pratos)\n");
    printf("3. Gerenciar pedidos\n");
    printf("4. Horarios de funcionamento\n");
    printf("5. Mostrar favoritos\n");
    printf("6. Sair\n");
    option = optionHandler("Opcao: ");

    switch (option)
    {
    case 1:
      printf("\n%s DADOS DO RESTAURANTE\n", SUB_DIVIDER);
      printf("Nome: %s\n", restaurant->name);
      printf("%s", SUB_DIVIDER);
      break;
    case 2:
      dishesSection(restaurant);
      break;
    case 3:
      ordersSection(restaurant);
      break;
    case 4:
      showOpeningHours(*restaurant);
      modifyOpeningHours = optionHandler("1. Modificar horarios de funcionamento\n2. Voltar\nOpcao: ");
      if (modifyOpeningHours == 1)
      {
        setOpeningHours(restaurant);
      }
      break;

    case 5:
      printf("\n%s      Clientes que marcaram seu restaurante como favorito      \n%s", DIVIDER, DIVIDER);
      for (int i = 0; i < favorites_count; i++)
      {
        if (favorites[i].restaurantId == restaurant->id)
        {
          struct User *userFavorite = findUserById(favorites[i].userId);
          printf("Cliente: %s\n", userFavorite->username);
        }
      }
      break;

    case 6:
      return;
    default:
      printf("Opcao invalida.\n");
    }
  } while (true);
}

void createRestaurantProfile(struct User *user)
{
  char name[MAX_LEN];

  printf("Nome do novo restaurante: ");

  if (fgets(name, MAX_LEN, stdin) == NULL)
    return;
  name[strcspn(name, "\n")] = 0;

  strcpy(restaurants[restaurants_count].name, name);
  printf("Restaurante '%s' criado!\n", restaurants[restaurants_count].name);
  setOpeningHours(&restaurants[restaurants_count]);

  restaurants[restaurants_count].id = restaurants_count;

  restaurants[restaurants_count].owner_id = user->id;

  restaurants[restaurants_count].dishCount = 0;

  restaurants_count++;

  printf("Perfil configurado com sucesso!\n");
}

//-------------------------------------------------------------------------------------------------------------------
// app.c

void app(const int loggedAs)
{
  if (loggedAs == 1)
  {
    costumerApp();
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
 */
//-------------------------------------------------------------------------------------------------------------------
// main.c

void createAccount()
{
  int id = users_count;
  AccountType accountType = CUSTOMER;
  char username[20];
  char email[100];
  bool successEmail = false;
  char password[100];

  printf("\n--- Nova Conta ---\n");
  printf("Username: ");
  fgets(username, 20, stdin);
  username[strcspn(username, "\n")] = 0;
  do
  {
    successEmail = true;

    printf("Email: ");
    scanf("%s", email);

    for (int i = 0; i < users_count; i++)
    {
      if (strcmp(users[i].email, email) == 0)
      {
        printf("Este email ja esta em uso! Tente novamente.\n");
        successEmail = false;

        break;
      }
    }
  } while (successEmail == false);

  printf("Senha: ");
  scanf("%s", password);
  do
  {
    accountType = optionHandler("Tipo de conta:\n1. Consumidor\n2. Restaurante\n3. Ambos\nOpcao: ");
  } while (accountType != 1 && accountType != 2 && accountType != 3);

  users[id].id = id;
  users[id].accountType = accountType;
  strcpy(users[id].email, email);
  strcpy(users[id].password, password);
  strcpy(users[id].username, username);

  bags[bags_count].id = bags_count;
  bags[bags_count].userId = id;
  bags[bags_count].dishOrdersCount = 0;

  bags_count++;
  users_count++;

  printf("\n[v] Usuario criado com sucesso!\n");
  if (accountType == 2 || accountType == 3)
  {
    printf("--- Configurar Restaurante ---\n");
    createRestaurantProfile(&users[users_count - 1]);
  }
}

void login()
{
  AccountType loginAs = 1;
  char email[MAX_LEN] = "";
  bool loggedIn = false;

  do
  {
    char password[MAX_LEN] = "";
    printf("\n--- Login (Digite 'exit' para voltar) ---\n");
    printf("Email: ");

    if (fgets(email, MAX_LEN, stdin) == NULL)
    {
      break;
    }
    email[strcspn(email, "\n")] = 0;

    if (strcmp(email, "exit") == 0)
    {
      return;
    }

    printf("Senha: ");
    if (fgets(password, MAX_LEN, stdin) == NULL)
    {
      break;
    }

    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < users_count; i++)
    {
      if (strcmp(users[i].email, email) == 0 && strcmp(users[i].password, password) == 0)
      {
        if (users[i].accountType == BOTH)
        {
          int op = 0;
          op = optionHandler("Entrar como:\n1. Consumidor\n2. Restaurante\nOpcao: ");
          loginAs = op;
        }
        else
        {
          loginAs = users[i].accountType;
        }

        loggedIn = true;
        break;
      }
    }
    if (!loggedIn)
      printf("(!) Email ou senha incorretos.\n");
  } while (loggedIn == false);

  currentUser = findUserByEmail(email);

  app(loginAs);
}

void homePage()
{
  int option = 0;
  do
  {
    option = 0;
    printf("\n%s\n        BEM-VINDO AO IFOOD (CLI)        \n%s", DIVIDER, DIVIDER);
    option = optionHandler(
        "1. Criar conta \n2. Fazer Login \n3. Sair\nOpcao: ");
    switch (option)
    {
    case 1:
      createAccount();
      break;
    case 2:
      login();
      break;
    case 3:
      return;
    default:
      printf("Opcao invalida");
    }
  } while (option != 5);
}

int main(void)
{
  homePage();
  return 0;
}