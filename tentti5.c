#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char *name;
    double price;
    int amount;
} Product;

typedef struct{
    Product *products;
    int all;
}Shop;

void add_product(Shop *sp, char *name, int amount, double price){
    int count = sp->all;
    Product *placeholder = calloc(count+1,sizeof(Product));
    if(!placeholder) return;
    Product *p = sp->products;
    memcpy(placeholder, sp->products, sizeof(Product) * count);
    sp->products = placeholder;
    free(p);
    sp->products[count].name = malloc(strlen(name) + 1);
    strcpy(sp->products[count].name, name);
    sp->products[count].amount = amount;
    sp->products[count].price = price;
    count++;
    sp->all = count;
    
}

void print_products(Shop *sp){
    for(int i = 0; i < sp->all; i++){
        printf("name: %s, price: %0.2f, amount: %d\n", 
        sp->products[i].name,
        sp->products[i].price,
        sp->products[i].amount
        );
    }
}

int main(void)
{
    Shop *s = malloc(sizeof(Shop));
    if(!s) return 0;
    memset(s, 0,sizeof(Shop));
    add_product(s,"riisipuuro", 3, 2.6);
    add_product(s,"kauramaito", 8, 5.9);
    add_product(s,"karjala", 24, 0.9);
    print_products(s);
    for(int i = 0; i < s->all; i++){
        free(s->products[i].name);
    }
    free(s->products);
    free(s);
    return 0;
}