#include "types.h"

struct User *currentUser;

struct User users[MAX_CLIENTS] = {

    {.id = 1,
     .username = "Pedro AS",
     .email = "pedro@email",
     .password = "pedro123",
     .accountType = BOTH,
     .address_count = 1,
     .address = {{.cep = "79152-50", .neighborhood = "Aguas Claras", .street = "Rua 105", .number = "05", .complement = "Apto 1803b"}},
     .creditcard_count = 1,
     .creditCard = {{.number = "1234 5678 9012 3456", .name = "PEDRO A SIMOES", .securityCode = "123", .validity = "12/28"}}},

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

    {.id = 10, .username = "Ze da Pizza", .email = "ze@pizza", .password = "ze123", .accountType = ADMIN, .address_count = 1, .address = {{.cep = "71000-000", .neighborhood = "Taguatinga", .street = "Comercial Norte", .number = "Loja 1", .complement = "Fundos"}}, .creditcard_count = 0},

    {.id = 3, .username = "João Santos", .email = "joao@email", .password = "joao123", .accountType = CUSTOMER, .address_count = 1, .address = {{.cep = "72000-000", .neighborhood = "Ceilandia", .street = "QNM 11", .number = "Lote 5", .complement = "Casa"}}, .creditcard_count = 1, .creditCard = {{.number = "1111 2222 3333 4444", .name = "JOAO SANTOS", .securityCode = "456", .validity = "05/29"}}},

    {.id = 4, .username = "Ana Costa", .email = "ana@email", .password = "ana123", .accountType = CUSTOMER, .address_count = 1, .address = {{.cep = "73000-000", .neighborhood = "Aguas Lindas", .street = "Quadra 10", .number = "Casa 15", .complement = ""}}, .creditcard_count = 2, .creditCard = {{.number = "5555 6666 7777 8888", .name = "ANA COSTA", .securityCode = "789", .validity = "03/27"}, {.number = "9999 8888 7777 6666", .name = "ANA COSTA", .securityCode = "321", .validity = "08/26"}}},

    {.id = 12, .username = "Carlos Aurora", .email = "carlos@padaria", .password = "carlos123", .accountType = ADMIN, .address_count = 1, .address = {{.cep = "74000-000", .neighborhood = "Centro", .street = "Av Principal", .number = "200", .complement = "Loja"}}, .creditcard_count = 0},

    {.id = 13, .username = "Roberto TOP", .email = "roberto@burger", .password = "roberto123", .accountType = ADMIN, .address_count = 1, .address = {{.cep = "75000-000", .neighborhood = "Samambaia", .street = "QR 302", .number = "Loja 8", .complement = ""}}, .creditcard_count = 0},

    {.id = 14, .username = "Fernanda Porto", .email = "fernanda@acai", .password = "fernanda123", .accountType = ADMIN, .address_count = 1, .address = {{.cep = "76000-000", .neighborhood = "Guará", .street = "QE 15", .number = "Loja 3", .complement = "Próximo ao mercado"}}, .creditcard_count = 0}

};

int users_count = 8;

struct Bag bags[MAX_CLIENTS] = {
    {.id = 0, .userId = 1, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0},
    {.id = 1, .userId = 2, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0},
    {.id = 2, .userId = 10, .restaurantId = -1, .totalPrice = 0, .dishOrdersCount = 0}};

int bags_count = 3;

struct Favorite favorites[100] = {

    {.userId = 2, .restaurantId = 1},

    {.userId = 1, .restaurantId = 1},

    {.userId = 1, .restaurantId = 0},

    {.userId = 2, .restaurantId = 2},

    {.userId = 3, .restaurantId = 3},

    {.userId = 4, .restaurantId = 4},

    {.userId = 4, .restaurantId = 1}};

int favorites_count = 7;

struct Order orders[300] = {

    // ============================================================
    // PEDIDOS DO PEDRO (ID 1) - Aguas Claras
    // ============================================================

    // Pedido 1: Pizza Mussarela (com opções) + Pizza Calabresa
    {.id = 1, .user_id = 1, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 87.00, .paymentMethod = CREDITCARD, .creationDate = 1762030000, .deliveryDate = 1762034000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}, {.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    // Pedido 2: Barca
    {.id = 2, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .paymentMethod = PIX, .creationDate = 1762120000, .deliveryDate = 1762125000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    // Pedido 3: Smash Burger (com opções)
    {.id = 3, .user_id = 1, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .paymentMethod = CREDITCARD, .creationDate = 1762210000, .deliveryDate = 1762213000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    // Pedido 4: Misto + Cappuccino (com opção)
    {.id = 4, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 20.50, .paymentMethod = CASH, .creationDate = 1762300000, .deliveryDate = 1762301000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 2, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Medio"}}}},

    // Pedido 5: Copo Açaí (com opção)
    {.id = 5, .user_id = 1, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .paymentMethod = PIX, .creationDate = 1762390000, .deliveryDate = 1762392000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    // Meio de Novembro
    {.id = 6, .user_id = 1, .restaurant_id = 0, .status = STATUS_CANCELED, .price = 45.00, .paymentMethod = CREDITCARD, .creationDate = 1763000000, .deliveryDate = 0, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}}},

    {.id = 7, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 53.80, .paymentMethod = PIX, .creationDate = 1763100000, .deliveryDate = 1763104000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}, {.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cebolinha"}}}},

    {.id = 8, .user_id = 1, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .paymentMethod = CREDITCARD, .creationDate = 1763200000, .deliveryDate = 1763204000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Guarana"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Sem Bebida"}}}},

    // Semana Atual
    {.id = 9, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 18.90, .paymentMethod = CASH, .creationDate = 1763990000, .deliveryDate = 1763991000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .amount = 50, .optionCount = 0}}}},

    {.id = 10, .user_id = 1, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .paymentMethod = PIX, .creationDate = 1764080000, .deliveryDate = 1764084000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    {.id = 11, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 26.90, .creationDate = 1764160000, .deliveryDate = 1764163000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    {.id = 12, .user_id = 1, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764250000, .deliveryDate = 1764254000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 13, .user_id = 1, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764260000, .deliveryDate = 1764263000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 14, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1764270000, .deliveryDate = 1764271000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    // HOJE (28 Nov 2025)
    {.id = 15, .user_id = 1, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 90.00, .creationDate = 1764330000, .deliveryDate = 1764334000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}, {.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}}},

    {.id = 16, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1764335000, .deliveryDate = 1764340000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    {.id = 17, .user_id = 1, .restaurant_id = 3, .status = STATUS_CANCELED, .price = 32.00, .creationDate = 1764340000, .deliveryDate = 0, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Guarana"}}}},

    // ATIVOS
    {.id = 18, .user_id = 1, .restaurant_id = 4, .status = STATUS_DELIVERING, .price = 18.00, .creationDate = 1764345000, .deliveryDate = 0, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Morango"}}}},

    {.id = 19, .user_id = 1, .restaurant_id = 0, .status = STATUS_PREPARING, .price = 45.00, .creationDate = 1764348000, .deliveryDate = 0, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Pan"}}}},

    {.id = 20, .user_id = 1, .restaurant_id = 2, .status = STATUS_PENDING, .price = 30.90, .creationDate = 1764350000, .deliveryDate = 0, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .amount = 50, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    // ============================================================
    // PEDIDOS DA MARIA (ID 2) - Asa Norte
    // ============================================================
    {.id = 21, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 24.00, .paymentMethod = PIX, .creationDate = 1763120000, .deliveryDate = 1763121800, .address = {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 22, .user_id = 2, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 179.80, .paymentMethod = CREDITCARD, .creationDate = 1763220000, .deliveryDate = 1763225000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}, {.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 23, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .paymentMethod = PIX, .creationDate = 1763320000, .deliveryDate = 1763322500, .address = {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 24, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .paymentMethod = CREDITCARD, .creationDate = 1763420000, .deliveryDate = 1763423000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}}},

    {.id = 25, .user_id = 2, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .paymentMethod = CASH, .creationDate = 1763520000, .deliveryDate = 1763524000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte", .street = "SQN 202"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 26, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 8.50, .creationDate = 1763995000, .deliveryDate = 1763996000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 2, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Grande"}}}},

    {.id = 27, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1764085000, .deliveryDate = 1764086000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 28, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764175000, .deliveryDate = 1764177000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Pacoca"}}}},

    {.id = 29, .user_id = 2, .restaurant_id = 1, .status = STATUS_CANCELED, .price = 89.90, .creationDate = 1764265000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 30, .user_id = 2, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 26.90, .creationDate = 1764275000, .deliveryDate = 1764278000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cebolinha"}}}},

    {.id = 31, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .creationDate = 1764300000, .deliveryDate = 1764304000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Guarana"}}}},

    {.id = 32, .user_id = 2, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764310000, .deliveryDate = 1764314000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Fina"}}}},

    {.id = 33, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 18.90, .creationDate = 1764320000, .deliveryDate = 1764321000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2}}}},

    {.id = 34, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 36.00, .creationDate = 1764330000, .deliveryDate = 1764332000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}, {.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Morango"}}}},

    {.id = 35, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764335000, .deliveryDate = 1764338000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Coca-Cola"}}}},

    // ATIVOS
    {.id = 36, .user_id = 2, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 53.80, .creationDate = 1764340000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}, {.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    {.id = 37, .user_id = 2, .restaurant_id = 0, .status = STATUS_PREPARING, .price = 42.00, .creationDate = 1764342000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 38, .user_id = 2, .restaurant_id = 2, .status = STATUS_DELIVERING, .price = 12.00, .creationDate = 1764345000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 39, .user_id = 2, .restaurant_id = 4, .status = STATUS_PENDING, .price = 18.00, .creationDate = 1764350000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    {.id = 40, .user_id = 2, .restaurant_id = 3, .status = STATUS_PENDING, .price = 32.00, .creationDate = 1764352000, .deliveryDate = 0, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Guarana"}}}},

    // ============================================================
    // PEDIDOS DO JOÃO (ID 3) - Ceilândia
    // ============================================================
    {.id = 41, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 90.00, .paymentMethod = CASH, .creationDate = 1763380000, .deliveryDate = 1763384500, .address = {.cep = "72000-000", .neighborhood = "Ceilandia", .street = "QNM 11"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}, {.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}}},

    {.id = 42, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .paymentMethod = PIX, .creationDate = 1763480000, .deliveryDate = 1763484000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia", .street = "QNM 11"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Guarana"}}}},

    {.id = 43, .user_id = 3, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1763580000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Pacoca"}}}},

    {.id = 44, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1763680000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Sem Bebida"}}}},

    {.id = 45, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1763780000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 46, .user_id = 3, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1763880000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 47, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1763980000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 48, .user_id = 3, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764080000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 49, .user_id = 3, .restaurant_id = 0, .status = STATUS_CANCELED, .price = 45.00, .creationDate = 1764180000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}}},

    {.id = 50, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 96.00, .creationDate = 1764270000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 3, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Guarana"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Sem Bebida"}}}},

    {.id = 51, .user_id = 3, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 18.90, .creationDate = 1764280000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2}}}},

    {.id = 52, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1764290000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 53, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764300000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Coca-Cola"}}}},

    {.id = 54, .user_id = 3, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764310000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}}},

    {.id = 55, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .creationDate = 1764320000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 56, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 87.00, .creationDate = 1764330000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}, {.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 57, .user_id = 3, .restaurant_id = 2, .status = STATUS_DELIVERING, .price = 24.00, .creationDate = 1764340000, .deliveryDate = 0, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 58, .user_id = 3, .restaurant_id = 3, .status = STATUS_PENDING, .price = 32.00, .creationDate = 1764345000, .deliveryDate = 0, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Guarana"}}}},

    {.id = 59, .user_id = 3, .restaurant_id = 4, .status = STATUS_PREPARING, .price = 45.00, .creationDate = 1764350000, .deliveryDate = 0, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 60, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1764355000, .deliveryDate = 0, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    // ============================================================
    // PEDIDOS DA ANA (ID 4) - Aguas Lindas
    // ============================================================
    {.id = 61, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 36.00, .paymentMethod = CREDITCARD, .creationDate = 1763990000, .deliveryDate = 1763993000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas", .street = "Quadra 10"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}, {.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}}},

    {.id = 62, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .paymentMethod = CREDITCARD, .creationDate = 1764080000, .deliveryDate = 1764085000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas", .street = "Quadra 10"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 63, .user_id = 4, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764090000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}}},

    {.id = 64, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764170000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Morango"}}}},

    {.id = 65, .user_id = 4, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1764180000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 66, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 53.80, .creationDate = 1764260000, .address = {.cep = "73000-000"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}, {.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    {.id = 67, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764270000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 68, .user_id = 4, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764280000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 69, .user_id = 4, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1764290000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 70, .user_id = 4, .restaurant_id = 4, .status = STATUS_CANCELED, .price = 36.00, .creationDate = 1764300000, .address = {.cep = "73000-000"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Pacoca"}}, {.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    {.id = 71, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1764310000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 72, .user_id = 4, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 24.00, .creationDate = 1764320000, .address = {.cep = "73000-000"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 73, .user_id = 4, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .creationDate = 1764325000, .address = {.cep = "73000-000"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Guarana"}}}},

    {.id = 74, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764330000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}}},

    {.id = 75, .user_id = 4, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764335000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}}},

    {.id = 76, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 26.90, .creationDate = 1764338000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    // ATIVOS
    {.id = 77, .user_id = 4, .restaurant_id = 4, .status = STATUS_PREPARING, .price = 45.00, .creationDate = 1764342000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 78, .user_id = 4, .restaurant_id = 3, .status = STATUS_PREPARING, .price = 32.00, .creationDate = 1764345000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}}},

    {.id = 79, .user_id = 4, .restaurant_id = 1, .status = STATUS_DELIVERING, .price = 89.90, .creationDate = 1764348000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 80, .user_id = 4, .restaurant_id = 4, .status = STATUS_PENDING, .price = 18.00, .creationDate = 1764350000, .address = {.cep = "73000-000"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    {.id = 81, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1762430000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1}}}},

    {.id = 82, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1762510000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Coca-Cola"}}}},

    {.id = 83, .user_id = 3, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 18.90, .creationDate = 1762600000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2}}}},

    {.id = 84, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1762690000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4}}}},

    {.id = 85, .user_id = 1, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1762780000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0}}}},

    {.id = 86, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 24.00, .creationDate = 1762860000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2}}}},

    {.id = 87, .user_id = 3, .restaurant_id = 3, .status = STATUS_CANCELED, .price = 64.00, .creationDate = 1762950000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 88, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 26.90, .creationDate = 1763040000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cebolinha"}}}},

    {.id = 89, .user_id = 1, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1763120000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}}},

    {.id = 90, .user_id = 2, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 90.00, .creationDate = 1763210000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}, {.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}}},

    {.id = 91, .user_id = 3, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1763300000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 92, .user_id = 4, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1763390000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Guarana"}}}},

    {.id = 93, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 20.50, .creationDate = 1763470000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 2, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Medio"}}}},

    {.id = 94, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1763560000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 95, .user_id = 3, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1763650000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    {.id = 96, .user_id = 4, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1763730000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Fina"}}}},

    {.id = 97, .user_id = 1, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .creationDate = 1763820000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}}},

    {.id = 98, .user_id = 2, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 53.80, .creationDate = 1763910000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}, {.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cebolinha"}}}},

    {.id = 99, .user_id = 3, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1763990000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Pacoca"}}}},

    {.id = 100, .user_id = 4, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 36.00, .creationDate = 1764000000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 3, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    // --- Semana Atual: 24 a 27 de Novembro (IDs 101-120) ---

    {.id = 101, .user_id = 1, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1764020000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    {.id = 102, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764035000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Coca-Cola"}}}},

    {.id = 103, .user_id = 3, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 26.90, .creationDate = 1764050000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    {.id = 104, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 90.00, .creationDate = 1764065000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}, {.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 105, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1764100000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 106, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764120000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    {.id = 107, .user_id = 3, .restaurant_id = 0, .status = STATUS_CANCELED, .price = 87.00, .creationDate = 1764140000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}, {.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    {.id = 108, .user_id = 4, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 24.00, .creationDate = 1764160000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 109, .user_id = 1, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 179.80, .creationDate = 1764180000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}, {.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    {.id = 110, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 96.00, .creationDate = 1764200000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 3, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Guarana"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Sem Bebida"}}}},

    {.id = 111, .user_id = 3, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 18.90, .creationDate = 1764210000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .amount = 50, .optionCount = 0}}}},

    {.id = 112, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764220000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 113, .user_id = 1, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 36.00, .creationDate = 1764230000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Morango"}}, {.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}}},

    {.id = 114, .user_id = 2, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1764240000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    {.id = 115, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764250000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Coca-Cola"}}}},

    {.id = 116, .user_id = 4, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 42.00, .creationDate = 1764260000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    {.id = 117, .user_id = 1, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764270000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}}},

    {.id = 118, .user_id = 2, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 12.00, .creationDate = 1764280000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 119, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764290000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}}},

    {.id = 120, .user_id = 4, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 18.00, .creationDate = 1764295000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    // --- HOJE: Sexta-feira, 28 de Novembro de 2025 (IDs 121-140) ---
    // Manhã e Início da Tarde

    {.id = 121, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 30.90, .creationDate = 1764320000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .amount = 50, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 122, .user_id = 2, .restaurant_id = 4, .status = STATUS_CONFIRMED, .price = 36.00, .creationDate = 1764325000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Granola"}}, {.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Pacoca"}}}},

    {.id = 123, .user_id = 3, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 32.00, .creationDate = 1764330000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Guarana"}}}},

    {.id = 124, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 53.80, .creationDate = 1764332000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}, {.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cebolinha"}}}},

    // ATIVOS (Delivering/Preparing/Pending)
    {.id = 125, .user_id = 1, .restaurant_id = 4, .status = STATUS_DELIVERING, .price = 45.00, .creationDate = 1764335000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 126, .user_id = 2, .restaurant_id = 2, .status = STATUS_DELIVERING, .price = 24.00, .creationDate = 1764338000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}, {.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 127, .user_id = 3, .restaurant_id = 0, .status = STATUS_PREPARING, .price = 45.00, .creationDate = 1764340000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}}},

    {.id = 128, .user_id = 4, .restaurant_id = 3, .status = STATUS_PREPARING, .price = 64.00, .creationDate = 1764342000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Sem Bebida"}}}},

    {.id = 129, .user_id = 1, .restaurant_id = 0, .status = STATUS_PREPARING, .price = 90.00, .creationDate = 1764344000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Cheddar", "Massa Pan"}}, {.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Pan"}}}},

    {.id = 130, .user_id = 2, .restaurant_id = 1, .status = STATUS_PREPARING, .price = 89.90, .creationDate = 1764346000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

    {.id = 131, .user_id = 3, .restaurant_id = 4, .status = STATUS_PENDING, .price = 18.00, .creationDate = 1764347000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .amount = 100, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Leite Ninho"}}}},

    {.id = 132, .user_id = 4, .restaurant_id = 2, .status = STATUS_PENDING, .price = 12.00, .creationDate = 1764348000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .amount = 10, .optionCount = 0}}}},

    {.id = 133, .user_id = 1, .restaurant_id = 3, .status = STATUS_PENDING, .price = 32.00, .creationDate = 1764349000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Ao Ponto", "Coca-Cola"}}}},

    {.id = 134, .user_id = 2, .restaurant_id = 0, .status = STATUS_PENDING, .price = 42.00, .creationDate = 1764350000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .amount = 15, .optionCount = 0}}}},

    {.id = 135, .user_id = 3, .restaurant_id = 1, .status = STATUS_PENDING, .price = 26.90, .creationDate = 1764351000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Cream Cheese"}}}},

    {.id = 136, .user_id = 4, .restaurant_id = 4, .status = STATUS_PENDING, .price = 45.00, .creationDate = 1764352000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .amount = 10, .optionCount = 0}}}},

    {.id = 137, .user_id = 1, .restaurant_id = 2, .status = STATUS_CONFIRMED, .price = 8.50, .creationDate = 1764353000, .address = {.cep = "79152-50", .neighborhood = "Aguas Claras"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 2, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .amount = 20, .optionCount = 1}, .dishOptionsCount = 1, .dishOptions = {"Grande"}}}},

    {.id = 138, .user_id = 2, .restaurant_id = 3, .status = STATUS_CONFIRMED, .price = 64.00, .creationDate = 1764354000, .address = {.cep = "70000-000", .neighborhood = "Asa Norte"}, .dishOrdersCount = 2, .dishOrders = {{.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Mal Passado", "Guarana"}}, {.dish = {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .amount = 50, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Bem Passado", "Coca-Cola"}}}},

    {.id = 139, .user_id = 3, .restaurant_id = 0, .status = STATUS_CONFIRMED, .price = 45.00, .creationDate = 1764355000, .address = {.cep = "72000-000", .neighborhood = "Ceilandia"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Pizza Mussarela", .price = 45.00, .restaurantId = 0, .amount = 10, .optionCount = 2}, .dishOptionsCount = 2, .dishOptions = {"Catupiry", "Massa Fina"}}}},

    {.id = 140, .user_id = 4, .restaurant_id = 1, .status = STATUS_CONFIRMED, .price = 89.90, .creationDate = 1764356000, .address = {.cep = "73000-000", .neighborhood = "Aguas Lindas"}, .dishOrdersCount = 1, .dishOrders = {{.dish = {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .amount = 5, .optionCount = 0}}}},

};

int orders_count = 140;

int restaurants_count = 5;

struct Restaurant restaurants[10] = {

    // --- Restaurante 0: Pizzaria do Ze ---
    {.id = 0,
     .owner_id = 10,
     .name = "Pizzaria do Ze",
     .dishCount = 2,
     .opening_hours = {.dom = {"18:00", "23:00"}, .seg = {"Fec", "Fec"}, .ter = {"18:00", "23:00"}, .qua = {"18:00", "23:00"}, .qui = {"18:00", "23:00"}, .sex = {"18:00", "00:00"}, .sab = {"18:00", "00:00"}},
     .dishes = {
         // Prato 0 (era 101)
         {.id = 0,
          .name = "Pizza Mussarela",
          .price = 45.00,
          .description = "Molho, mussarela, oregano e azeitona.",
          .restaurantId = 0,
          .amount = 10,
          .optionCount = 2,
          .options = {
              {.dish_id = 0, .name = "Borda", .optionsCount = 2, .options = {"Catupiry", "Cheddar"}}, // dish_id atualizado
              {.dish_id = 0, .name = "Massa", .optionsCount = 2, .options = {"Fina", "Pan"}}          // dish_id atualizado
          }},
         // Prato 1 (era 102)
         {.id = 1, .name = "Pizza Calabresa", .price = 42.00, .restaurantId = 0, .description = "Mussarela, calabresa e cebola.", .amount = 15, .optionCount = 0}}},

    // --- Restaurante 1: Sushi Mura ---
    {.id = 1, .owner_id = 1, .name = "Sushi Mura", .dishCount = 2, .opening_hours = {.dom = {"19:00", "23:00"}, .seg = {"19:00", "23:00"}, .ter = {"19:00", "23:00"}, .qua = {"19:00", "23:00"}, .qui = {"19:00", "23:00"}, .sex = {"19:00", "00:00"}, .sab = {"19:00", "00:00"}}, .dishes = {// Prato 0 (era 201)
                                                                                                                                                                                                                                                                                              {.id = 0, .name = "Barca 30 Pecas", .price = 89.90, .restaurantId = 1, .description = "Sashimi, Niguiri, Joe e Uramaki.", .amount = 5, .optionCount = 0},
                                                                                                                                                                                                                                                                                              // Prato 1 (era 202)
                                                                                                                                                                                                                                                                                              {.id = 1, .name = "Temaki Salmao", .price = 26.90, .restaurantId = 1, .description = "Cone de alga com arroz e salmao batido.", .amount = 20, .optionCount = 1, .options = {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                  {.dish_id = 1, .name = "Adicionais", .optionsCount = 2, .options = {"Cream Cheese", "Cebolinha"}} // dish_id atualizado
                                                                                                                                                                                                                                                                                                                                                                                                                                                              }}}},
    // --- Restaurante 2: Padaria Aurora ---
    {.id = 2, .owner_id = 12, .name = "Padaria Aurora", .dishCount = 3, .opening_hours = {.dom = {"07:00", "12:00"}, .seg = {"06:00", "20:00"}, .ter = {"06:00", "20:00"}, .qua = {"06:00", "20:00"}, .qui = {"06:00", "20:00"}, .sex = {"06:00", "20:00"}, .sab = {"07:00", "19:00"}}, .dishes = {// Prato 0 (era 301)
                                                                                                                                                                                                                                                                                                   {.id = 0, .name = "Pao Frances (kg)", .price = 18.90, .restaurantId = 2, .description = "Pao fresquinho saindo toda hora.", .amount = 50, .optionCount = 0},
                                                                                                                                                                                                                                                                                                   // Prato 1 (era 302)
                                                                                                                                                                                                                                                                                                   {.id = 1, .name = "Misto Quente", .price = 12.00, .restaurantId = 2, .description = "Pao de forma, presunto e queijo.", .amount = 10, .optionCount = 0},
                                                                                                                                                                                                                                                                                                   // Prato 2 (era 303)
                                                                                                                                                                                                                                                                                                   {.id = 2, .name = "Cappuccino", .price = 8.50, .restaurantId = 2, .description = "Com canela e chocolate.", .amount = 20, .optionCount = 1, .options = {
                                                                                                                                                                                                                                                                                                                                                                                                                                                   {.dish_id = 2, .name = "Tamanho", .optionsCount = 2, .options = {"Medio", "Grande"}} // dish_id atualizado
                                                                                                                                                                                                                                                                                                                                                                                                                                               }}}},

    // --- Restaurante 3: Hamburgueria TOP ---
    {.id = 3, .owner_id = 13, .name = "Hamburgueria TOP", .dishCount = 1, .opening_hours = {.dom = {"18:00", "23:00"}, .seg = {"Fec", "Fec"}, .ter = {"18:00", "23:00"}, .qua = {"18:00", "23:00"}, .qui = {"18:00", "23:00"}, .sex = {"18:00", "02:00"}, .sab = {"18:00", "02:00"}}, .dishes = {// Prato 0 (era 401)
                                                                                                                                                                                                                                                                                                 {.id = 0, .name = "Smash Burger Duplo", .price = 32.00, .restaurantId = 3, .description = "2 Carnes smash, cheddar, bacon e molho.", .amount = 50, .optionCount = 2, .options = {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                          {.dish_id = 0, .name = "Ponto da Carne", .optionsCount = 3, .options = {"Mal Passado", "Ao Ponto", "Bem Passado"}}, // dish_id atualizado
                                                                                                                                                                                                                                                                                                                                                                                                                                                                          {.dish_id = 0, .name = "Bebida", .optionsCount = 3, .options = {"Coca-Cola", "Guarana", "Sem Bebida"}}              // dish_id atualizado
                                                                                                                                                                                                                                                                                                                                                                                                                                                                      }}}},

    // --- Restaurante 4: Acai do Porto ---
    {.id = 4, .owner_id = 14, .name = "Acai do Porto", .dishCount = 2, .opening_hours = {.dom = {"14:00", "20:00"}, .seg = {"12:00", "20:00"}, .ter = {"12:00", "20:00"}, .qua = {"12:00", "20:00"}, .qui = {"12:00", "20:00"}, .sex = {"12:00", "22:00"}, .sab = {"12:00", "22:00"}}, .dishes = {// Prato 0 (era 501)
                                                                                                                                                                                                                                                                                                  {.id = 0, .name = "Copo 500ml", .price = 18.00, .restaurantId = 4, .description = "Acai puro batido com banana.", .amount = 100, .optionCount = 1, .options = {
                                                                                                                                                                                                                                                                                                                                                                                                                                                         {.dish_id = 0, .name = "Complementos", .optionsCount = 4, .options = {"Leite Ninho", "Granola", "Morango", "Pacoca"}} // dish_id atualizado
                                                                                                                                                                                                                                                                                                                                                                                                                                                     }},
                                                                                                                                                                                                                                                                                                  // Prato 1 (era 502)
                                                                                                                                                                                                                                                                                                  {.id = 1, .name = "Barca de Acai", .price = 45.00, .restaurantId = 4, .description = "1kg de Acai com 5 acompanhamentos.", .amount = 10, .optionCount = 0}}},
};