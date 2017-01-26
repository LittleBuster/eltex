// Threads
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>


static struct {
	unsigned storage[5];
	unsigned clients[3];
	pthread_mutex_t mtx_out;
	pthread_mutex_t mtx_cl;
	pthread_mutex_t mtx_st;
} stock;


void* StartLoader()
{
	for (;;) {
		struct timeval tv = {2, 0};
		unsigned number = rand()%5;
		unsigned i;
		unsigned count;
		bool f = false;

		for (i = 0; i < 3; i++) {
			pthread_mutex_lock(&stock.mtx_cl);
			count = stock.clients[i];
			pthread_mutex_unlock(&stock.mtx_cl);

			if (count < 1500) {
				f = true;
				break;
			}
		}
		if (!f) {
			pthread_mutex_lock(&stock.mtx_out);
			printf("Все клиенты набрали 1500. Завершение работы.\n");
			pthread_mutex_unlock(&stock.mtx_out);
			exit(0);
		}

		pthread_mutex_lock(&stock.mtx_st);
		stock.storage[number] += 100;
		pthread_mutex_unlock(&stock.mtx_st);

		pthread_mutex_lock(&stock.mtx_out);
		printf("Поргрузчик полжил 100 в ячейку %u\n", number);
		pthread_mutex_unlock(&stock.mtx_out);
		
		//Waiting 2 seconds
		if (select(0, NULL, NULL, NULL, &tv) == -1)
			if (EINTR == errno)
				continue;
	}
	return NULL;
}

void* StartClient(void *data)
{
	unsigned* client = (unsigned *)data;

	for (;;) {
		struct timeval tv = {1, 0};
		unsigned num = rand()%5;
		unsigned count;

		//Waiting 1 second
		if (select(0, NULL, NULL, NULL, &tv) == -1)
			if (EINTR == errno)
				continue;

		pthread_mutex_lock(&stock.mtx_st);
		count = stock.storage[num];
		pthread_mutex_unlock(&stock.mtx_st);

		if (count < 300) {
			pthread_mutex_lock(&stock.mtx_out);
			printf("В ячейке %u не хватает предметов.\n", *client);
			pthread_mutex_unlock(&stock.mtx_out);
			continue;
		}

		pthread_mutex_lock(&stock.mtx_st);
		stock.storage[num] -= 300;
		pthread_mutex_unlock(&stock.mtx_st);

		pthread_mutex_lock(&stock.mtx_cl);
		stock.clients[*client] += 300;
		pthread_mutex_unlock(&stock.mtx_cl);

		pthread_mutex_lock(&stock.mtx_out);
		printf("Клиент %u забрал 300 из ячейки %u\n", *client, num);
		pthread_mutex_unlock(&stock.mtx_out);

		pthread_mutex_lock(&stock.mtx_cl);
		count = stock.clients[*client];
		pthread_mutex_unlock(&stock.mtx_cl);

		if (count >= 1500) {
			pthread_mutex_lock(&stock.mtx_out);
			printf("Клиент %u набрал 1500 и завершил работу.\n", *client);
			pthread_mutex_unlock(&stock.mtx_out);
			break;
		}
	}
	return NULL;
}

int main(void)
{
	unsigned i;
	pthread_t loader;
	pthread_t client1, client2, client3;
	unsigned num[3] = {0, 1, 2};

	//Init storage
	for (i = 0; i < 5; i++) {
		stock.storage[i] = rand()%1000;
	}

	pthread_create(&loader, NULL, (void *)StartLoader, 0);
	pthread_create(&client1, NULL, (void *)StartClient, &num[0]);
	pthread_create(&client2, NULL, (void *)StartClient, &num[1]);
	pthread_create(&client3, NULL, (void *)StartClient, &num[2]);
	pthread_join(loader, NULL);
	pthread_join(client1, NULL);
	pthread_join(client2, NULL);
	pthread_join(client3, NULL);

	return 0;
}