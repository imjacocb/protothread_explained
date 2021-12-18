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
 * $Id: example-codelock.c,v 1.5 2005/10/06 07:57:08 adam Exp $
 */

/*
 *
 * This example shows how to implement a simple code lock. The code
 * lock waits for key presses from a numeric keyboard and if the
 * correct code is entered, the lock is unlocked. There is a maximum
 * time of one second between each key press, and after the correct
 * code has been entered, no more keys must be pressed for 0.5 seconds
 * before the lock is opened.
 *
 * This is an example that shows two things:
 * - how to implement a code lock key input mechanism, and
 * - how to implement a sequential timed routine.
 *
 * The program consists of two protothreads, one that implements the
 * code lock reader and one that implements simulated keyboard input.
 *
 *
 */

#include <stdio.h>
#include <time.h>
#include <stdint.h>


#include <Windows.h>
#include <windows.h>

typedef unsigned short lc_t;

struct pt {
	lc_t lc;
};


struct timer { int start, interval; };
static int timer_expired(struct timer *t);
static void timer_set(struct timer *t, int usecs);

static struct timer codelock_timer, input_timer;

static const char code[4] = { '1', '4', '2', '3' };
static struct pt codelock_pt, input_pt;

static char key, key_pressed_flag;

static void
press_key(char k)
{
	printf("--- Key '%c' pressed\n", k);
	key = k;
	key_pressed_flag = 1;
}

static int
key_pressed(void)
{
	if (key_pressed_flag != 0) {
		key_pressed_flag = 0;
		return 1;
	}
	return 0;
}

static
char codelock_thread(struct pt *pt)
{	
	static int keys;
	{ 
		char PT_YIELD_FLAG = 1; switch ((pt)->lc) {
	case 0:;
		while (1) {
			for (keys = 0; keys < sizeof(code); ++keys) {
				if (keys == 0) {
					do { (pt)->lc = 163; 
	
	
	case 163:; 
						if (!(key_pressed())) 
						{ 
							return 0; 
		
						} 
					
					} while (0);
				}
				else {
						
					timer_set(&codelock_timer, 1000);
					do { (pt)->lc = 180; 
	
	case 180:; 
					
						if (!(key_pressed() || timer_expired(&codelock_timer))) { return 0; } 
					} while (0);								   			

					if (timer_expired(&codelock_timer)) {
						printf("Code lock timer expired.\n");
						break;
					}
				}

				if (key != code[keys]) {
					printf("Incorrect key '%c' found\n", key);
					break;
				}
				else {
					printf("Correct key '%c' found\n", key);
				}
			}

			if (keys == sizeof(code)) {
				printf("Correct code entered, waiting for 500 ms before unlocking.\n");
				timer_set(&codelock_timer, 500);
				do { 
					(pt)->lc = 228; 
	case 228:; 
					if (!(key_pressed() || timer_expired(&codelock_timer))) 
					{ 
						return 0; 
					} 
				} while (0);

				if (!timer_expired(&codelock_timer)) {
					printf("Key pressed during final wait, code lock locked again.\n");
				}
				else {
					printf("Code lock unlocked.\n");
					do { (pt)->lc = 0;; return 2; 
					} while (0);
				}
			}
		}
	}; PT_YIELD_FLAG = 0; (pt)->lc = 0;; return 3; };
}


static
char input_thread(struct pt *pt)
{
	{ char PT_YIELD_FLAG = 1; switch ((pt)->lc) {
	case 0:;

		printf("Waiting 1 second before entering first key.\n");

		timer_set(&input_timer, 1000);
	do { (pt)->lc = 268; case 268:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('1');

	timer_set(&input_timer, 100);
	do { (pt)->lc = 273; case 273:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('2');

	timer_set(&input_timer, 100);
	do { (pt)->lc = 278; case 278:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('3');

	timer_set(&input_timer, 2000);
	do { (pt)->lc = 283; case 283:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('1');

	timer_set(&input_timer, 200);
	do { (pt)->lc = 288; case 288:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('4');

	timer_set(&input_timer, 200);
	do { (pt)->lc = 293; case 293:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('2');

	timer_set(&input_timer, 2000);
	do { (pt)->lc = 298; case 298:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('3');

	timer_set(&input_timer, 200);
	do { (pt)->lc = 303; case 303:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('1');

	timer_set(&input_timer, 200);
	do { (pt)->lc = 308; case 308:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('4');

	timer_set(&input_timer, 200);
	do { (pt)->lc = 313; case 313:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('2');

	timer_set(&input_timer, 100);
	do { (pt)->lc = 318; case 318:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('3');

	timer_set(&input_timer, 100);
	do { (pt)->lc = 323; case 323:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('4');

	timer_set(&input_timer, 1500);
	do { (pt)->lc = 328; case 328:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('1');

	timer_set(&input_timer, 300);
	do { (pt)->lc = 333; case 333:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('4');

	timer_set(&input_timer, 400);
	do { (pt)->lc = 338; case 338:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('2');

	timer_set(&input_timer, 500);
	do { (pt)->lc = 343; case 343:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	press_key('3');

	timer_set(&input_timer, 2000);
	do { (pt)->lc = 348; case 348:; if (!(timer_expired(&input_timer))) { return 0; } } while (0);

	}; PT_YIELD_FLAG = 0; (pt)->lc = 0;; return 3; };
}






int main(void)
{

	(&input_pt)->lc = 0;;
	(&codelock_pt)->lc = 0;;

	while (((codelock_thread(&codelock_pt)) < 2)) {
		((input_thread(&input_pt)) < 2);
				Sleep(10);

	}

	return 0;
}




static int clock_time(void)
{ return (int)GetTickCount(); }

static int timer_expired(struct timer *t)
{
	return (int)(clock_time() - t->start) >= (int)t->interval;
}

static void timer_set(struct timer *t, int interval)
{
	t->interval = interval; t->start = clock_time();
}



