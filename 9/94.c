#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[31];
	float price;
	int in_stock;
} Product;

int write_binary(const char* filename, Product* shop){
    int i = 0;
    FILE *f = fopen(filename, "w");
    if(!f) return 1;
    while(1){
        if(shop[i].name[0] == 0) break;
        i++;
    }
    fwrite(shop, sizeof(Product),(i+1), f);
    fclose(f);
    return 0;
}

Product* read_binary(const char* filename){
    int i = 0;
    FILE *f = fopen(filename, "r");
    if(!f) return NULL;
    Product *list = calloc(1,sizeof(Product));
    fread(list, sizeof(Product),1,f);
    while(!feof(f)){
        list = realloc(list, (sizeof(Product) * (i + 2)));
        i++;
        fread((list + i), sizeof(Product),1,f);
    }
    fclose(f);
    list[i].name[0] = 0;
    list[i].price = 0;
    list[i].in_stock = 0;
    return list;
}

int write_plaintext(const char* filename, Product* shop){
    int i=0;
    if(!shop) return 1;
    FILE *f= fopen(filename, "w");
    if(!f) return 1;
    while(shop[i].name[0] != 0){
        fprintf(f, "%s %f %d\n", shop[i].name, shop[i].price, shop[i].in_stock);
        if(feof(f)) return 0;
        i++;
    }
    fclose(f);
    return 0;
}

Product* read_plaintext(const char* filename){
    int i=0,a;
    FILE *f = fopen(filename, "r");
    if(!f) return NULL;
    Product *list = calloc(1, sizeof(Product));
    while(1){
        a = fscanf(f, "%s %f %d\n", list[i].name, &list[i].price, &list[i].in_stock);
        if(a == -1) break;
        i++;
        list = realloc(list,sizeof(Product)*(i+1));
    }
    list[i].name[0]='\0';
    list[i].price=0;
    list[i].in_stock=0;
    fclose(f);
    return list;
}

int main()
{
	Product* arr = calloc(3,  sizeof(Product));
	strcpy(arr[0].name, "peanut_butter");
	arr[0].price = 5.2;
	arr[0].in_stock = 4;
	strcpy(arr[1].name, "milk");
	arr[1].price = 1.1;
	arr[1].in_stock = 42;
	arr[2].name[0] = 0;
	
	write_binary("test", arr);
	
	Product* arr2 = read_binary("test");
	for(int i = 0; i < 3; i++)
	{
		printf("%s %f %d\n", arr2[i].name, arr2[i].price, arr2[i].in_stock);
	}

	write_plaintext("test.txt", arr2);

	Product* arr3 = read_plaintext("test.txt");
	for(int i = 0; i < 3; i++)
	{
		printf("%s %f %d\n", arr3[i].name, arr3[i].price, arr3[i].in_stock);
	}

	free(arr);
	free(arr2);
	free(arr3);
	
	return 0;
}