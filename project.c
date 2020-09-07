#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// single country's medals and name
typedef struct{
  char country[20];   //country's name
  int gold;           //summ of gold medals
  int silver;         //summ of silver medals
  int bronze;         //summ of bronze medals
} medals;




// data for the list of countries
typedef struct{
  medals *countries;    //list of countries
  unsigned int count;   //counter for how many countries
} data;




// function to add country to the dynamic list of countries
// datap: pointer to dynamically allocated data
// str: name of the country to be added to the list of countries
int add_country( data *datap , char *str ){
  unsigned int length = datap->count;

  // can't use realloc, because of security reasons
  medals *placeh = calloc( ( (length) + 1), sizeof(medals) );
  if (!placeh)
    return 0;
  medals *point=datap->countries;
  memcpy(placeh,datap->countries,sizeof(medals) * length);
  datap->countries=placeh;
  free(point);
  strcpy(datap->countries[length].country, str);
  datap->countries[length].gold = 0;
  datap->countries[length].silver = 0;
  datap->countries[length].bronze = 0;
  length++;
  datap->count = length;
  return 1;

}





// function to change a countrys medals
// datap: pointer to dynamically allocated data
// str: name of the country
// golds,silvers,bronzes: amount of medals to be summed
void update_medals( data *datap , char *str , int golds , int silvers , int bronzes ){
  unsigned char bool = 0;
  int i = 0;
  for(; i<datap->count ; i++){
    if(!strcmp(datap->countries[i].country, str)){
      bool = 1;
      break;
    }
  }
  if(!bool){
    printf("That country was not found!\n");
    return;
  }
  int g = (datap->countries[i].gold) + golds;
  int s = (datap->countries[i].silver) + silvers;
  int b = (datap->countries[i].bronze) + bronzes;
  if( g<0 || s<0 || b<0){
    printf("amount of total medals can't be negative!\n");
    return;
  }
  datap->countries[i].gold = g;
  datap->countries[i].silver = s;
  datap->countries[i].bronze = b;
}





// function sorts the countries based on medals and then prints them in the new order
// datap: pointer to dynamically allocated data
void print_medals(data *datap){
    medals placeh;
    for(int i=0 ; i < datap->count ; i++) for(int j=(i+1) ; j < datap->count ; j++){

      //check for countries with more gold medals
      if( datap->countries[i].gold < datap->countries[j].gold){
        placeh=datap->countries[i];
        datap->countries[i]=(datap->countries[j]);
        datap->countries[j]=placeh;
      }

      //check for countries with the same amount of gold, but more silvers
      else if( (datap->countries[i].gold == datap->countries[j].gold ) &&
               (datap->countries[i].silver < datap->countries[j].silver ) ){

              placeh=datap->countries[i];
              datap->countries[i]=(datap->countries[j]);
              datap->countries[j]=placeh;

            }
      //check for countries with the same amount of gold and silver, but more bronzes
      else if( (datap->countries[i].gold == datap->countries[j].gold ) &&
               (datap->countries[i].silver == datap->countries[j].silver) &&
               (datap->countries[i].bronze < datap->countries[j].bronze) ){

                 placeh=datap->countries[i];
                 datap->countries[i]=(datap->countries[j]);
                 datap->countries[j]=placeh;
               }
    }

    for(int i=0; i < datap->count; i++){
      printf("%-20s:    golds:%3d   silvers:%3d   bronzes:%3d\n",datap->countries[i].country,
            datap->countries[i].gold, datap->countries[i].silver, datap->countries[i].bronze);
    }
}



// save data to a file
// datap: pointer to dynamically allocated data
// str: string containing name to be given to file
int save_data(data *datap, char *str){
  FILE *f= fopen(str, "w");
  if(!f)
    return 0;
  fwrite(&datap->count,sizeof(unsigned int),1,f);
  fwrite(&datap->countries[0], sizeof(medals), (datap->count),f);
  fclose(f);
  return 1;
}



// load data from a file
// datap: pointer to dynamically allocated data
// str: string containig filename
int load_data(data *datap, char *str){
  FILE *f=fopen(str, "r");
  if(!f)
    return 0;
  unsigned int r;
  fread(&r,sizeof(unsigned int),1,f);
  medals *placeh=malloc(sizeof(medals) * r);
  fread(placeh,sizeof(medals),r,f);
  medals *reee=datap->countries;
  datap->countries=placeh;
  free(reee);
  datap->count=r;
  fclose(f);
  return 1;

}



//function to check if user given args are empty
int check_blank(char *str){
  if(!str[2] || !str[3]){
    printf("name must not be blank!\n");
    return 0;
  }
  return 1;
}





//function to check user given args
// datap: pointer to dynamically allocated data
int commands( data *datap , char *str ){
  switch(str[0]){

    case 'A':
      if( !check_blank(str) )
        break;
      str += 2;
      if(strlen(str)>20){
        printf("name is too long\n");
        break;
      }
      int i=0;
      while(1){
        if(str[i]==0 || str[i]==10 || str[i]==32){
          str[i]=0;
          break;
        }
        i++;
      }
      if(!add_country( datap,str))
      printf("memory allocation failed\n");
      break;

    case'M':
      if( !check_blank(str) )
        break;
      int g = 0,s = 0,b = 0;
      char ctry[30];
      str += 2;
      sscanf(str, "%s %d %d %d", ctry, &g, &s, &b);
      update_medals(datap, ctry, g, s, b);
      break;


    case 'L':
      print_medals(datap);
      break;

    case 'W':
      if( !check_blank(str) )
        break;
      str+= 2;
      if(save_data(datap,strtok(str,"\n")))
        printf("saving succeeded\n");
      else
        printf("saving failed\n");
      break;

    case 'O':
      if( !check_blank(str) )
        break;
      str+= 2;
      if(!load_data( datap, strtok(str,"\n") ) )
        printf("loading failed\n");
      else
        printf("loading succeeded\n");
      break;

    case 'Q':
      return 0;
    default:
        printf("what?\n");
  }
  return 1;
}






int main(){
  data *list = malloc( sizeof(data) );
  if(!list){
    printf("malloc failed, closing");
    return 1;
  }
  memset( list, 0, sizeof(data) );
  unsigned char ProgOn = 1;
  char buffer[100];
  printf("This is a program to keep track of countries olympic medals.\n");
  printf("Commands:\n");
  printf("'A countryname'                      -add a new country, name can be max 20 characters\n");
  printf("'M countryname golds silvers bronzes'- add medals to country \n");
  printf("'L'                                  -print countries in order of most goldmedals\n");
  printf("'W filename'                         -save current data to file named filename\n");
  printf("'O filename'                         -load data from a file named filename\n");
  printf("'Q'                                  -quits the program\n");
  while( ProgOn ){
    if(fgets(buffer, sizeof(buffer), stdin)==NULL)
      break;
    ProgOn = commands(list, buffer);
  }
  free(list->countries);
  free(list);
  return 0;
}
