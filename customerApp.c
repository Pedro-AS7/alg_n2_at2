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
  printf("\nAdicionando item à sacola...\n");
  struct DishOrder dishOrder;

  dishOrder.dish = dish;
  dishOrder.dishOptionsCount = optionCount;
  memcpy(dishOrder.dishOptions, dishOptions, sizeof(dishOrder.dishOptions));

  struct Bag *userBag = findBagByUserId(currentUser->id);

  for (int i = 0; i < orders_count; i++)
  {
    if (orders[i].user_id == currentUser->id && orders[i].status != STATUS_CANCELED && orders[i].status != STATUS_COMPLETED)
    {
      printf("(!) Você tem um pedido em andamento. Aguarde a finalização.\n");
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

  printf("[v] Item adicionado à sacola!\n");
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
        printf("(!) Este prato está indisponível!");
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
      printf("Este restaurante não tem pratos cadastrados\n");
      break;
    }
    printf("\n%s        CARDÁPIO: %s        \n%s", DIVIDER, restaurant.name, DIVIDER);
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
    printf("\n%s     RESTAURANTES DISPONÍVEIS     \n%s", DIVIDER, DIVIDER);
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
    printf("\n%s      MEUS ENDEREÇOS      \n%s", DIVIDER, DIVIDER);
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
    printf("\n%s       MEUS CARTÕES       \n%s", DIVIDER, DIVIDER);
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
    printf("\n%s     CONFIGURAÇÕES DA CONTA     \n%s", DIVIDER, DIVIDER);
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
    printf("Selecione o endereço de entrega: \n");
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
  printf("\n%s   HISTÓRICO DE PEDIDOS   \n%s", DIVIDER, DIVIDER);
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
    printf("Nenhum histórico disponível.\n");
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

void customerApp()
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