// Copyright (c) 2017 Brian Barto
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the MIT License. See LICENSE for more details.

#include <string.h>
#include "config.h"

/*
 * MODULE DESCRIPTION
 * 
 * The inputpayload module manages a character array that contains the
 * payload string from the last time network_read() was executed.
 */

/*
 * Static Variables
 */
static char payload[MAX_PAYLOAD_SIZE + 1];

/*
 * Set the payload character array to all null characters
 */
void inputpayload_init(void) {
	memset(payload, 0, sizeof(payload));
}

/*
 * Return the payload character array.
 */
char *inputpayload_get(void) {
	return payload;
}

/*
 * Advance the given char pointer (data) by the number of characters equal
 * to the length of the command. Then parse out the next number of
 * characters equal to MAX_PAYLOAD_SIZE and store them in the payload
 * character array.
 */
void inputpayload_parse(char *data) {
	unsigned int cmdlen = 0;
	
	memset(payload, 0, sizeof(payload));
	
	while (*data >= '0' && *data <= '9')
		cmdlen = (cmdlen * 10) + *data++ - '0';
		
	++data;

	if (strlen(data) > cmdlen)
		strncpy(payload, data + cmdlen, MAX_PAYLOAD_SIZE);
}
