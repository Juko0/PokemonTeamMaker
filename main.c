#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "map.h"
#include "list.h"

typedef struct pokemon pokemon;
typedef struct tipo_pkmn tipo_pkmn;

const char *get_csv_field (char * tmp, int i);

pokemon *crear_pokemon (char * nombre, char *tipo, char*tipo2, int hp, int atk, int def, int atkesp, int defesp, int vel);
tipo_pkmn *crear_tipo (char *tipo,char *debilidad1,char *debilidad2,char *debilidad3,char *debilidad4,char *debilidad5,char *inmunidad1,char *inmunidad2,char *efectivo1,char *efectivo2,
                       char *efectivo3,char *efectivo4,char *efectivo5,char *noefectivo1,char *noefectivo2,char *noefectivo3,char *noefectivo4,char *noefectivo5,char *noefectivo6,char *noefectivo7);

void ordenalista(list *lista, pokemon*pkmn ,int stat);

long long stringHash(const void * key) {
    long long hash = 5381;
    const char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }
    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;
    return strcmp(A, B) == 0;
}

struct pokemon{
    char*nombre;
    char *tipo;
    char *tipo2;
    int hp,atk,def,atkesp,defesp,vel;
};

struct tipo_pkmn {
    char *tipo;
    char *debilidad1,*debilidad2,*debilidad3,*debilidad4,*debilidad5;
    char *inmunidad1,*inmunidad2;
    char *efectivo1,*efectivo2,*efectivo3,*efectivo4,*efectivo5;
    char *noefectivo1,*noefectivo2,*noefectivo3,*noefectivo4,*noefectivo5,*noefectivo6,*noefectivo7;

};

int main () {

    system("color 04");  //color rojito uwu

    Map * pkmn = createMap(stringHash, stringEqual);
    list *pkmnn = list_create_empty ();
    Map *tipopkmn = createMap(stringHash, stringEqual);

    int flag=0;
    int menu_opcion;
    do{
        printf("Main Menu\n");
        printf("1. Crear equipo.\n");
        printf("2. Mis Equipos.\n");
        printf("3. Pokedex.\n");
        printf("4. Ayuda.\n");
        printf("5. Salir.\n");
        printf(" Porfavor Seleccione una opcion del menu: ");
        scanf("%d",&menu_opcion);
        printf("\n");



        switch(menu_opcion){

            case 1: {            //Crea un archivo txt con los pokemon del equipo / Carga archivos csv y los une a mapas/lista de tipo y pokemon
                FILE*archivo;
                archivo=fopen("CSV/Pokemon.csv","r");
                if(archivo==NULL){
                    printf("No se pudo cargar el archivo. \n");
                    exit(1);
                }
                else{

                    char linea[1024];

                    while (fgets (linea, 1023, archivo) != NULL){
                        char *nombre = get_csv_field(linea, 1);
                        char *tipo = get_csv_field(linea, 2);
                        char *tipo2 = get_csv_field(linea, 3);
                        int hp = atoi(get_csv_field(linea, 4));
                        int atk = atoi(get_csv_field(linea, 5));
                        int def = atoi(get_csv_field(linea, 6));
                        int atkesp = atoi(get_csv_field(linea, 7));
                        int defesp = atoi(get_csv_field(linea, 8));
                        int vel = atoi(get_csv_field(linea, 9));
                        pokemon *c = crear_pokemon (nombre, tipo, tipo2, hp, atk, def, atkesp, defesp, vel);
                        insertMap(pkmn, c->nombre, c);
                        list_push_back (pkmnn, c);
                    }


                    fclose(archivo);

                    FILE*archivo_tipo;
                    archivo_tipo=fopen("CSV/Tipo.csv","r");
                    if(archivo_tipo==NULL){
                        printf("No se pudo cargar el archivo. \n");
                        exit(1);
                    }
                    else{
                        printf("Los archivos se cargaron correctamente!! \n\n");

                        char linea[1024];

                        while (fgets (linea, 1023, archivo_tipo) != NULL){
                            char *tipo = get_csv_field(linea, 1);
                            char *debilidad1 = get_csv_field(linea, 2);
                            char *debilidad2 = get_csv_field(linea, 3);
                            char *debilidad3 = get_csv_field(linea, 4);
                            char *debilidad4 = get_csv_field(linea, 5);
                            char *debilidad5 = get_csv_field(linea, 6);
                            char *inmunidad1 = get_csv_field(linea, 7);
                            char *inmunidad2 = get_csv_field(linea, 8);
                            char *efectivo1 = get_csv_field(linea, 9);
                            char *efectivo2 = get_csv_field(linea, 10);
                            char *efectivo3 = get_csv_field(linea, 11);
                            char *efectivo4 = get_csv_field(linea, 12);
                            char *efectivo5 = get_csv_field(linea, 13);
                            char *noefectivo1 = get_csv_field(linea, 14);
                            char *noefectivo2 = get_csv_field(linea, 15);
                            char *noefectivo3 = get_csv_field(linea, 16);
                            char *noefectivo4 = get_csv_field(linea, 17);
                            char *noefectivo5 = get_csv_field(linea, 18);
                            char *noefectivo6 = get_csv_field(linea, 19);
                            char *noefectivo7 = get_csv_field(linea, 20);
                            tipo_pkmn * x = crear_tipo (tipo,debilidad1,debilidad2,debilidad3,debilidad4,debilidad5,inmunidad1,inmunidad2,efectivo1,efectivo2,efectivo3,efectivo4,efectivo5,
                                                       noefectivo1,noefectivo2,noefectivo3,noefectivo4,noefectivo5,noefectivo6,noefectivo7);
                            insertMap(tipopkmn, x->tipo, x);
;
                        }
                        fclose(archivo_tipo);
                    }

                    int submenu_opcion;
                    printf("¿Desea ver la lista de Pokemon disponibles?\n");
                    printf("1.-Si.\n");
                    printf("2.-No.\n");
                    scanf("%d",&submenu_opcion);
                    printf("\n");


                    switch(submenu_opcion){

                        case 1:{
                            pokemon *lista = list_first (pkmnn);
                            lista=list_next(pkmnn);
                            while (lista != NULL){
                                printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre, lista->tipo, lista->tipo2, lista->hp, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                lista= list_next (pkmnn);
                            }
                            char nombre_pokemon [20];
                            printf("Escriba el nombre del pokemon que desea:");
                            scanf("%s", nombre_pokemon);
                            int i;
                            nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                            for (i = 1; i < strlen(nombre_pokemon) ; i++){
                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                else toupper (nombre_pokemon[i++]);
                            }


                            pokemon*u = searchMap(pkmn,nombre_pokemon);

                            pokemon *primer = u;

                            int submenu_opcion_equipo;

                            printf("Que funcion desea para su siguiente Pokemon?\n");


                            printf("1.-Defensivo Fisico.\n");
                            printf("2.-Defensivo Especial.\n");
                            printf("3.-Atacante Fisico.\n");
                            printf("4.-Atacante Especial.\n");
                            printf("5.-Defensivo Mixto (Altos stats en HP). \n");
                            scanf("%d",&submenu_opcion_equipo);
                            printf("\n");

                            switch (submenu_opcion_equipo){
                                case 1:{

                                }
                                break;

                                case 2:{
                                }
                                break;

                                case 3:{
                                }
                                break;

                                case 4:{
                                }
                                break;

                                case 5:{
                                }
                                break;

                                default:printf("Seleccion Invalida!!!\n");
                                break;
                            }


                        }
                        break;


                        case 2: {
                            char nombre_pokemon [20];
                            printf("Escriba el nombre del pokemon que desea:");
                            scanf("%s", nombre_pokemon);

                            int i;
                            nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                            for (i = 1; i < strlen(nombre_pokemon) ; i++){
                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                else toupper (nombre_pokemon[i++]);
                            }

                            pokemon*u = searchMap(pkmn,nombre_pokemon);

                            pokemon *primer = u;

                        }
                        break;

                        default:printf("Seleccion Invalida!!!\n");
                        break;

                    }
                }
                flag++;
            }
            break;


            case 2:
            break;


            case 3:{            //Entrega datos de un pokemon especifiado por el usuario
                char nombre[20];
                char pokedex[50];
                char dex[] = "Pokedex/";
                printf("Introduzca el nombre del Pokemon que desea \n");
                scanf("%s", &nombre);
                FILE * archivo;
                strcpy(pokedex,dex);
                strcat(pokedex,nombre);
                strcat(pokedex,".txt");             //Agrega la carpeta y el formato .txt al nombre del pokemon



                archivo=fopen(pokedex,"r");

                if( archivo==NULL ) printf("Error al abrir el fichero\n");

                else
                {
                    printf("\n");
                    while( !feof(archivo)) printf("%c",getc(archivo));    //Imprime
                }
                printf("\n");

                if(flag>0){     //si la opcion 1 fue ingresada anteriormente, el usuario podra ver estadisticas del pokemon
                    pokemon*u = searchMap(pkmn,nombre);
                    printf("\nTipo: %s  Tipo 2: %s \n\nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n", u->tipo, u->tipo2, u->hp, u->atk, u->def, u->atkesp , u->defesp, u->vel);
                }
                printf("\n");
                fclose(archivo);
            }
            break;


            case 4:{   //imprime por panntalla el texto de ayuda

                FILE*archivo;
                archivo=fopen("Ayuda.txt","r");
                if( archivo==NULL )
                    printf("Error al abrir el fichero\n");

                else
                {
                    printf("\n");

                    while( !feof(archivo)) printf("%c",getc(archivo));
                }

                fclose(archivo);
            }
                break;
            case 5:
                break;

            default:printf("Seleccion Invalida!!!");
                break;
        }
        system("pause");
        system("cls");
    }while(menu_opcion != 5);

    return 0;
}



pokemon *crear_pokemon (char * nombre, char *tipo, char*tipo2, int hp, int atk, int def, int atkesp, int defesp, int vel){
    pokemon *c = malloc(sizeof(pokemon));
    c->nombre = nombre;
    c->tipo = tipo;
    c->tipo2 = tipo2;
    c->hp = hp;
    c->atk = atk;
    c->def = def;
    c->atkesp = atkesp;
    c->defesp = defesp;
    c->vel = vel;
    return c;
}

const char *get_csv_field (char * tmp, int i){
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) if (!--i) return tok;
    return NULL;
}

/*void ordenalista(list *lista, pokemon*pkmn ,int stat){

    pokemon * current;

    int insertado=0;

    current = list_first(lista);

    if(current!=NULL){
        do {
            if( current->nivel < j->nivel){
                    list_prev(lista);
                    list_push_current(lista,j);
                    insertado=1;
                    break;
            }


            current = list_next(lista);
        }while( current != NULL);
    }
    if (!insertado){

      list_push_back(lista,j);
    }


}*/

tipo_pkmn *crear_tipo (char *tipo,char *debilidad1,char *debilidad2,char *debilidad3,char *debilidad4,char *debilidad5,char *inmunidad1,char *inmunidad2,char *efectivo1,char *efectivo2,char *efectivo3,char *efectivo4,char *efectivo5,char *noefectivo1,char *noefectivo2,char *noefectivo3,char *noefectivo4,char *noefectivo5,char *noefectivo6,char *noefectivo7){
    tipo_pkmn *x = malloc(sizeof(tipo_pkmn));
    x->tipo = tipo;
    x->debilidad1 = debilidad1;
    x->debilidad2 = debilidad2;
    x->debilidad3 = debilidad3;
    x->debilidad4 = debilidad4;
    x->debilidad5 = debilidad5;
    x->inmunidad1 = inmunidad1;
    x->inmunidad2 = inmunidad2;
    x->efectivo1 = efectivo1;
    x->efectivo2 = efectivo2;
    x->efectivo3 = efectivo3;
    x->efectivo4 = efectivo4;
    x->efectivo5 = efectivo5;
    x->noefectivo1 = noefectivo1;
    x->noefectivo2 = noefectivo2;
    x->noefectivo3 = noefectivo3;
    x->noefectivo4 = noefectivo4;
    x->noefectivo5 = noefectivo5;
    x->noefectivo6 = noefectivo6;
    x->noefectivo7 = noefectivo7;
    return x;
}




