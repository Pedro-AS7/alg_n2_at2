#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "utils.h"
#include "globals.h"

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

void manageOrder(struct Restaurant *restaurant, int orderIndex, int mirrorIndex)
{
  struct Order *order = &orders[orderIndex];
  getOrderDetails(order, mirrorIndex);

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
      switch (newStatus)
      {
      case 1:
        order->status = STATUS_PENDING;
        break;
      case 2:
        order->status = STATUS_PREPARING;
        break;
      case 3:
        order->status = STATUS_DELIVERING;
        break;
      case 4:
        order->status = STATUS_COMPLETED;
        order->deliveryDate = time(NULL);
        break;
      case 5:
        order->status = STATUS_CANCELED;
        printf("O pedido foi cancelado.\n");
        break;

      default:
        break;
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

      int mirrorIndex = 0;
      for (int i = 0; i < orders_count; i++)
      {
        if (orders[i].restaurant_id == restaurant->id && orders[i].status != STATUS_CONFIRMED && orders[i].status != STATUS_CANCELED)
        {
          if (mirrorIndex == orderIndex)
          {
            orderIndex = i;
            break;
          }
          mirrorIndex++;
        }
      }
      manageOrder(restaurant, orderIndex, mirrorIndex + 1);
      orderFound = true;
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

void customerReports(struct Restaurant *restaurant)
{
  do
  {
    int option = 0;
    option = optionHandler("1. Diario\n2. Semanal\n3. Mensal\n4. Anual\n5. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      generateCustomersReport(restaurant, 1);
      break;
    case 2:
      generateCustomersReport(restaurant, 2);
      break;
    case 3:
      generateCustomersReport(restaurant, 3);
      break;
    case 4:
      generateCustomersReport(restaurant, 4);
      break;
    case 5:
      return;
    default:
      printf("Opcao invalida.\n");
    }
  } while (true);
}

void sellReports(struct Restaurant *restaurant)
{
  do
  {
    int option = 0;
    option = optionHandler("1. Diario\n2. Semanal\n3. Mensal\n4. Anual\n5. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      generateSellesReport(restaurant, 1);
      break;
    case 2:
      generateSellesReport(restaurant, 2);
      break;
    case 3:
      generateSellesReport(restaurant, 3);
      break;
    case 4:
      generateSellesReport(restaurant, 4);
      break;
    case 5:
      return;
    default:
      printf("Opcao invalida.\n");
    }
  } while (true);
}

void reportSection(struct Restaurant *restaurant)
{

  do
  {
    printf("\n%s   RELATORIOS DO RESTAURANTE   \n%s", DIVIDER, DIVIDER);
    int option = optionHandler("1. Ver relatorios de vendas\n2. Ver relatorios de clientes\n3. Voltar\nOpcao: ");
    switch (option)
    {
    case 1:
      sellReports(restaurant);
      break;
    case 2:
      customerReports(restaurant);
      break;
    case 3:
      return;
    default:
      printf("Opcao invalida.\n");
    }
    printf("%s", DIVIDER);
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
    printf("6. Relatorios\n");
    printf("7. Sair\n");
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
      reportSection(restaurant);
      break;
    case 7:
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