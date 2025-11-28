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

  printf("\n--- Novo Endereço ---\n");
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
    printf("\n(!) Limite de endereços atingido.\n");
    return;
  }

  currentUser->address[currentUser->address_count] = createAddress();
  currentUser->address_count++;
  printf("\n[v] Endereço adicionado com sucesso!\n");
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

  printf("\n%s\nDefina o horário de funcionamento:\n%s", DIVIDER, SUB_DIVIDER);
  inputDaySchedule("Domingo", &dom);
  inputDaySchedule("Segunda-feira", &seg);
  inputDaySchedule("Terça-feira", &ter);
  inputDaySchedule("Quarta-feira", &qua);
  inputDaySchedule("Quinta-feira", &qui);
  inputDaySchedule("Sexta-feira", &sex);
  inputDaySchedule("Sábado", &sab);

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
    printf("Erro: Índice inválido.\n");
    return;
  }

  for (int i = addressIndex; i < currentUser->address_count - 1; i++)
  {
    currentUser->address[i] = currentUser->address[i + 1];
  }

  currentUser->address_count--;

  printf("\n%s Endereço removido com sucesso.\n%s", SUB_DIVIDER, SUB_DIVIDER);
}

void addCard()
{
  char name[MAX_LEN];
  char number[17];
  char validity[6];
  char securityCode[4];

  if (currentUser->creditcard_count >= 5)
  {
    printf("\n(!) Limite de cartões atingido.\n");
    return;
  }

  printf("\n--- Novo Cartão ---\n");
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
    printf("Numero selecionado inválido.\n");
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
    printf("Índice inválido.\n");
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
    printf("Índice de deleção inválido.\n");
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
    printf("Índice inválido.\n");
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
  int counter = 0;
  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].restaurant_id == restaurant->id && orders[i].status != STATUS_CONFIRMED && orders[i].status != STATUS_CANCELED)
    {
      counter++;
      hasOrders = true;
      printf("Pedido #%d | Cliente: %s\nStatus: [%s]\n", counter, findUserById(orders[i].user_id)->username, getStatusText(orders[i].status));
      for (int j = 0; j < orders[i].dishOrdersCount; j++)
      {
        struct DishOrder currentDishOrder = orders[i].dishOrders[j];
        printf("  > %s (Opções: %d)\n", currentDishOrder.dish.name, currentDishOrder.dishOptionsCount);
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
  printf("\n%s DETALHES DO PEDIDO #%d\n%s", DIVIDER, orderIndex, DIVIDER);
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

void dishesRanking(struct Restaurant *restaurant, int reportPeriod)
{

  int dishOrderCounts[20] = {0};

  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].restaurant_id == restaurant->id && (orders[i].status == STATUS_CONFIRMED || orders[i].status == STATUS_CANCELED) && checkDate(orders[i].creationDate, reportPeriod))
    {
      for (int j = 0; j < orders[i].dishOrdersCount; j++)
      {
        int dishId = orders[i].dishOrders[j].dish.id;
        dishOrderCounts[dishId]++;
      }
    }
  }

  // Criar array de índices e ordenar por contagem (descendente)
  int indices[20];
  for (int i = 0; i < restaurant->dishCount; i++)
  {
    indices[i] = i;
  }

  // Bubble sort simples
  for (int i = 0; i < restaurant->dishCount - 1; i++)
  {
    for (int j = 0; j < restaurant->dishCount - i - 1; j++)
    {
      int count_j = dishOrderCounts[restaurant->dishes[indices[j]].id];
      int count_j1 = dishOrderCounts[restaurant->dishes[indices[j + 1]].id];
      if (count_j < count_j1)
      {
        int temp = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < restaurant->dishCount; i++)
  {
    struct Dish currentDish = restaurant->dishes[indices[i]];
    printf("%d. %-30s - Pedidos: %d\n", i + 1, currentDish.name, dishOrderCounts[currentDish.id]);
  }
  printf("%s", DIVIDER);

  for (int i = 0; i < 20; i++)
  {
    dishOrderCounts[i] = 0;
    indices[i] = 0;
  }
}

int checkDate(time_t orderDate, int reportPeriod)
{

  time_t agora;
  time(&agora);

  struct tm *ptr_agora = localtime(&agora);

  struct tm tm_agora = *ptr_agora;

  struct tm *ptr_pedido = localtime(&orderDate);

  if (reportPeriod == 1)
  {
    if (tm_agora.tm_year == ptr_pedido->tm_year &&
        tm_agora.tm_mon == ptr_pedido->tm_mon &&
        tm_agora.tm_mday == ptr_pedido->tm_mday)
    {
      return 1;
    }
  }
  else if (reportPeriod == 2)
  {
    time_t diff = difftime(agora, orderDate);
    int daysDiff = diff / (60 * 60 * 24);
    if (daysDiff >= 0 && daysDiff < 7)
    {
      return 1;
    }
  }
  else if (reportPeriod == 3)
  {
    if (tm_agora.tm_year == ptr_pedido->tm_year &&
        tm_agora.tm_mon == ptr_pedido->tm_mon)
    {
      return 1;
    }
  }
  else if (reportPeriod == 4)
  {
    if (tm_agora.tm_year == ptr_pedido->tm_year)
    {
      return 1;
    }
  }

  return 0;
}

void generateSellesReport(struct Restaurant *restaurant, int reportPeriod)
{
  float totalSales = 0.0;
  int completedOrders = 0;

  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].restaurant_id == restaurant->id && (orders[i].status == STATUS_CONFIRMED || orders[i].status == STATUS_CANCELED) && checkDate(orders[i].creationDate, reportPeriod))
    {
      totalSales += orders[i].price;
      completedOrders++;
    }
  }

  char *periodText;
  switch (reportPeriod)
  {
  case 1:
    periodText = "Hoje";
    break;
  case 2:
    periodText = "Esta semana";
    break;
  case 3:
    periodText = "Este mês";
    break;
  case 4:
    periodText = "Este ano";
    break;
  default:
    periodText = "Período desconhecido";
    break;
  }

  printf("\n%s RELATÓRIO DE VENDAS: %s - %s \n%s", DIVIDER, restaurant->name, periodText, DIVIDER);
  printf("Total de Pedidos Concluídos: %d\n", completedOrders);
  printf("Faturamento Total: R$ %.2f\n", totalSales);
  printf("Pratos mais vendidos no periodo:\n");
  dishesRanking(restaurant, reportPeriod);
  printf("%s", DIVIDER);
}

void generateCustomersReport(struct Restaurant *restaurant, int reportPeriod)
{
  char *periodText;
  switch (reportPeriod)
  {
  case 1:
    periodText = "Hoje";
    break;
  case 2:
    periodText = "Esta semana";
    break;
  case 3:
    periodText = "Este mês";
    break;
  case 4:
    periodText = "Este ano";
    break;
  default:
    periodText = "Período desconhecido";
    break;
  }
  printf("\n%s RELATORIO DE CLIENTES: %s - %s \n%s", DIVIDER, restaurant->name, periodText, DIVIDER);

  int totalClientsWithOrders = 0;

  for (int u = 0; u < users_count; u++)
  {
    struct User *user = &users[u];
    float totalSpent = 0.0;
    int totalOrders = 0;
    int completedOrders = 0;
    int canceledOrders = 0;

    for (int i = 0; i < orders_count; i++)
    {
      if (orders[i].user_id == user->id && orders[i].restaurant_id == restaurant->id && checkDate(orders[i].creationDate, reportPeriod))
      {
        totalOrders++;
        if (orders[i].status == STATUS_CONFIRMED)
        {
          totalSpent += orders[i].price;
          completedOrders++;
        }
        else if (orders[i].status == STATUS_CANCELED)
        {
          canceledOrders++;
        }
      }
    }

    if (totalOrders > 0)
    {
      totalClientsWithOrders++;
      printf("\n--- Cliente: %s ---\n", user->username);
      printf("Total de Pedidos: %d\n", totalOrders);
      printf("Pedidos Concluidos: %d\n", completedOrders);
      printf("Pedidos Cancelados: %d\n", canceledOrders);
      printf("Valor Total Gasto: R$ %.2f\n", totalSpent);
      if (completedOrders > 0)
      {
        printf("Media por Pedido: R$ %.2f\n", totalSpent / completedOrders);
      }
      printf("%s", SUB_DIVIDER);
    }
  }

  if (totalClientsWithOrders == 0)
  {
    printf("\nNenhum cliente realizou pedidos no periodo selecionado.\n");
  }
  else
  {
    printf("\nTotal de clientes com pedidos: %d\n", totalClientsWithOrders);
  }

  printf("%s", DIVIDER);
}
