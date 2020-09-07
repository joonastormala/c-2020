#include <stdio.h>
#include <string.h>

struct Ship{
    const char *name;
    double weight;
    char *cargo[10];
};

void clear_cargo(struct Ship *ship){
    for (size_t i = 0; i < sizeof(ship->cargo)/sizeof(ship->cargo[0]); i++){
        ship->cargo[i] = NULL;
    }   
}

void add_cargo(struct Ship *c, char *item){
    for (size_t i = 0; i < sizeof(c->cargo)/sizeof(c->cargo[0]); i++){
        if(c->cargo[i] == NULL){
            c->cargo[i] = item;
            break;
        }
    }
}

int main(void)
{
    struct Ship vessel_1 = { "Tanker", 100000, { NULL } };

    clear_cargo(&vessel_1);
    add_cargo(&vessel_1, "Gasoline");
    add_cargo(&vessel_1, "Oil");
    add_cargo(&vessel_1, "Diesel");

    struct Ship vessel_2;
    vessel_2.name = "Fun boat";
    vessel_2.weight = 1.25;
    clear_cargo(&vessel_2);
    add_cargo(&vessel_2, "Food basket");
    add_cargo(&vessel_2, "Sunscreen");
    add_cargo(&vessel_2, "Very good lemonade");
    add_cargo(&vessel_2, "Frankfurters");

    struct Ship ships[2];
    ships[0] = vessel_1;
    ships[1] = vessel_2;

    for (int i = 0; i < 2; i++) {
	    printf("Name: %s  / Weight %.2f tonnes\n", ships[i].name, ships[i].weight);
	    printf("Cargo:\n");
	    for (int j = 0; ships[i].cargo[j] != NULL; j++) {
	        printf("* %s\n", ships[i].cargo[j]);
	    }
	    printf("----------\n");
    }
}


