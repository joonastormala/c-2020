#include <stdio.h>

enum num_seats{
    BIKE = 1,
    MOTORCYCLE = 2,
    VAN = 3,
    CAR = 5,
    MINIVAN = 7
};

int main(void)
{

    enum num_seats test = BIKE;
    printf("We have a varible test of type enum num_seats\n"
            "and it has an integer value of %d!!\n\n", test);

    for (unsigned int i = 0; i <= 10; i++) {
	switch(i) {
	   case BIKE: // = 1
		printf("Number of seats in a bike is %d\n", BIKE);
		break;
	   case MOTORCYCLE: // = 2
		printf("Number of seats in a motorcycle is %d\n", MOTORCYCLE);
		break;
	   case VAN: // = 3
		printf("Number of seats in a van is %d\n", VAN);
		break;
	   case CAR: // = 5
		printf("Number of seats in a car is %d\n", CAR);
		break;
	   case MINIVAN: // = 7
		printf("Number of seats in a minivan is %d\n", MINIVAN);
		break;
        } // switch
    } // for

    return 0;
}


