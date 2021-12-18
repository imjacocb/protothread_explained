#include "stdio.h"

static int protothread1_flag, protothread2_flag;


int protothread1( int value)
{

	char PT_YIELD_FLAG = 1; 
	
	switch (value) {
	case 0:;


		while (1) {

			do {
				value = 33;
	
			case 33:; 
				if (!(protothread2_flag != 0)) 
				{ 
					return 0; 
				} 
			
			} while (0);
			printf("Protothread 1 running\n");



			protothread2_flag = 0;
			protothread1_flag = 1;

		}
	}; PT_YIELD_FLAG = 0; value= 0;; return 3;
};

int protothread2(int value)
{

	{ 
		char PT_YIELD_FLAG = 1; 
		switch (value) {
		case 0:;

			while (1) {

				protothread2_flag = 1;


				do { 
					value = 63; 
					case 63:; 
						if (!(protothread1_flag != 0)) 
						{ 
							return 0; 
						} 
				} while (0);
				printf("Protothread 2 running\n");

				protothread1_flag = 0;
			}
		}; 
		PT_YIELD_FLAG = 0; value = 0;; return 3; 
	};
};


int main()
{
	while (1) {
		protothread1(0);
		protothread2(0);
	}
}

