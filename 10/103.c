#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct {
	char name[31];
	float price;
	int in_stock;
} Product;


int compareAlpha(const void* a, const void* b){
	const Product *na = a;
	const Product *nb = b;
	return strcmp(na->name,nb->name);
}

int compareNum(const void* a, const void* b){
	const Product *na = a;
	const Product *nb = b;
	if(na->in_stock == nb->in_stock) return strcmp(na->name,nb->name);
	else if (na->in_stock > nb->in_stock) return -1; else return 1;
}

const Product* findProduct(const Product* p_array, const char* search_key, int (*cmp)(const void*, const void*)){
	int i=0,size=0;
	while(p_array[i].name[0] != 0){
		size++;
		i++;
	}
	const Product *ret = bsearch(search_key, p_array,size,sizeof(Product),cmp);
	return ret;
}

void printProducts(Product* array){
	int i = 0;
	while(array[i].name[0] != 0){
		printf("product: %s price: %f in stock: %d\n", array[i].name, array[i].price, array[i].in_stock);
		i++;
	}
}

int main()
{
	Product array[6] = {
	{"peanut butter", 1.2, 	5},
	{"cookies", 	 12.3, 23},
	{"cereals", 	  3.2, 12},
	{"bread",	  2.7, 12},
	{"butter", 	  4.2,  5},
	{"\0",		0.0, 0}
	};

	qsort(array, 5, sizeof(Product), compareAlpha);
	printf("sorted lexically:\n");
	printProducts(array);
	
	const Product* search = findProduct(array, "cookies", compareAlpha);
	if(search)
	{
		printf("Found product:\n");
		printf("%s\n", search->name);
	}

	qsort(array, 5, sizeof(Product), compareNum);
	printf("sorted by in stock:\n");
	printProducts(array);

	return 0;
}
