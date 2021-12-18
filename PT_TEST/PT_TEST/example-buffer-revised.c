/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the protothreads library.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: example-buffer.c,v 1.5 2005/10/07 05:21:33 adam Exp $
 */

#include <stdio.h>
#include <windows.h>

typedef void * lc_t;
struct pt {
	lc_t lc;
};

struct pt_sem {
	unsigned int count;
};





static int buffer[8];
static int bufptr;

static void
add_to_buffer(int item)
{
	printf("Item %d added to buffer at place %d\n", item, bufptr);
	buffer[bufptr] = item;
	bufptr = (bufptr + 1) % 8;
}
static int
get_from_buffer(void)
{
	int item;
	item = buffer[bufptr];
	printf("Item %d retrieved from buffer at place %d\n",
		item, bufptr);
	bufptr = (bufptr + 1) % 8;
	return item;
}

static int
produce_item(void)
{
	static int item = 0;
	printf("Item %d produced\n", item);
	return item++;
}

static void
consume_item(int item)
{
	printf("Item %d consumed\n", item);
}

static struct pt_sem full, empty;

static
char producer(struct pt *pt)
{
	static int produced;

	{	
		char PT_YIELD_FLAG = 1; 
		
		switch ((int)(pt)->lc) 
		{
			case 0:;

			for (produced = 0; produced < 32; ++produced) 
			{

				do { 
					
					do 
					{ (pt)->lc = 94; 
			
			case 94:; 
						if (!((&full)->count > 0)) { return 0; } 
				
					} while (0); --(&full)->count; 
				
				} while (0);

				
				add_to_buffer(produce_item());

				++(&empty)->count;
			}

		}; 
		PT_YIELD_FLAG = 0; (pt)->lc = 0;; return 3; 
	};
}

static
char consumer(struct pt *pt)
{
	static int consumed;

	{ 
		char PT_YIELD_FLAG = 1; 
	
		switch ((int)(pt)->lc) {
		case 0:;

			for (consumed = 0; consumed < 32; ++consumed) {

				do { 
					do { 
							(pt)->lc = 113; 
		
		
		case 113:; if (!((&empty)->count > 0)) { return 0; } 
					
					} while (0); --(&empty)->count; 
				
				} while (0);

				consume_item(get_from_buffer());

				++(&full)->count;
		}

		}; PT_YIELD_FLAG = 0; (pt)->lc = 0;; return 3; 
	
	};
}

static
char driver_thread(struct pt *pt)
{
	static struct pt pt_producer, pt_consumer;

	{ 
		char PT_YIELD_FLAG = 1; 
	
		switch ((int)(pt)->lc) {
		case 0:;

			(&empty)->count = 0;
			(&full)->count = 8;

			(&pt_producer)->lc = 0;;
			(&pt_consumer)->lc = 0;;

			do {
				(((pt)))->lc =	137; 
		case 137:; 
				if (!  (!  (  ( (producer(&pt_producer) & consumer(&pt_consumer) ) < 2)   )  )  ) 
				{ 
					return 0; 
				}
			} while (0);

	}; PT_YIELD_FLAG = 0; (pt)->lc = 0;; return 3; };
}


int
main(void)
{
	struct pt driver_pt;

	(&driver_pt)->lc = 0;;

	while (((driver_thread(&driver_pt)) < 2)) {
		Sleep(10);

	}
	return 0;
}