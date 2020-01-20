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

struct pokemon{            //Estructura Pokemon
    char*nombre;
    char *tipo;
    char *tipo2;
    int health,atk,def,atkesp,defesp,vel;
};

struct tipo_pkmn {      //Estructura Tipo
    char *tipo;
    char *debilidad1,*debilidad2,*debilidad3,*debilidad4,*debilidad5;
    char *inmunidad1,*inmunidad2;
    char *efectivo1,*efectivo2,*efectivo3,*efectivo4,*efectivo5;
    char *noefectivo1,*noefectivo2,*noefectivo3,*noefectivo4,*noefectivo5,*noefectivo6,*noefectivo7;

};

int main () {

    system("color 04");  //color rojito uwu


	//Crea los mapas y listas a trabajar
	Map * pkmn = createMap(stringHash, stringEqual);
    list *pkmnn = list_create_empty ();
    Map *tipopkmn = createMap(stringHash, stringEqual);
    list *HP = list_create_empty();
    list *ATK = list_create_empty();
    list *DEF = list_create_empty();
    list *ATKESP = list_create_empty();
    list *DEFESP = list_create_empty();
    list *VEL = list_create_empty();


    FILE*archivo;
    archivo=fopen("CSV/Pokemon.csv","r");
    if(archivo==NULL){
        printf("No se pudo cargar el archivo. \n");
        exit(1);
    }
    else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

        char linea[1024];

        while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade al mapa pokemon y a la lista pokemon
                char *nombre = get_csv_field(linea, 1);
                char *tipo = get_csv_field(linea, 2);
                char *tipo2 = get_csv_field(linea, 3);
                int health = atoi(get_csv_field(linea, 4));
                int atk = atoi(get_csv_field(linea, 5));
                int def = atoi(get_csv_field(linea, 6));
                int atkesp = atoi(get_csv_field(linea, 7));
                int defesp = atoi(get_csv_field(linea, 8));
                int vel = atoi(get_csv_field(linea, 9));
                pokemon *c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
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

            while (fgets (linea, 1023, archivo_tipo) != NULL){  //crea los tipos desde el archivo .csv y los añade al mapa tipo
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
            }
            fclose(archivo_tipo);
        }
    }


    int menu_opcion;
    do{
        printf("Main Menu\n");
        printf("1. Ver lista de Pokemon Disponibles.\n");
        printf("2. Crear equipo.\n");
        printf("3. Mis Equipos.\n");
        printf("4. Pokedex.\n");
        printf("5. Ayuda.\n");
        printf("6. Salir.\n");
        printf(" Porfavor Seleccione una opcion del menu: ");
        scanf("%d",&menu_opcion);
        printf("\n");



        switch(menu_opcion){

            case 1: {            //Imprime la lista de pokemon
                pokemon *lista = list_first (pkmnn);
                lista=list_next(pkmnn);
                while (lista != NULL){     //imprime lista de pokemon
                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre, lista->tipo, lista->tipo2,
                                                lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                        lista= list_next (pkmnn);
                }
            }
            break;

            case 2: {      //Crea un archivo txt con los pokemon del equipo


                char nombre_pokemon [20];           //Consulta a usuario nombre de pokemon y lo guarda
                printf("\n");
                printf("Escriba el nombre del pokemon que desea:  ");
                scanf("%s", nombre_pokemon);
                printf("\n");

                int i;
                nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                        if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                        else toupper (nombre_pokemon[i++]);
                }

                pokemon*u = searchMap(pkmn,nombre_pokemon);   // busca el pokemon deseado

                list *equipo = list_create_empty();     //crea lista de equipo
                list_push_back(equipo,u);         //inserta el primer pokemon en la lista

                int tam_equipo=1;

                while(tam_equipo<7){

                        int submenu_opcion_equipo;


						//Menu que segun eleccion muestra los pokemon ordenados de mayor a menor por el stat deseado
                        printf("Que funcion desea para su siguiente Pokemon?\n");
                        printf("1.-Defensivo Mixto (Altos stats en HP).\n");
                        printf("2.-Atacante Fisico.\n");
                        printf("3.-Defensivo Fisico.\n");
                        printf("4.-Atacante Especial.\n");
                        printf("5.-Defensivo Especial.\n");
                        printf("6.-Velocidad (Ataca primero que el rival). \n");
                        printf(" Porfavor Seleccione una opcion del menu:  ");
                        scanf("%d",&submenu_opcion_equipo);
                        printf("\n");

                        switch (submenu_opcion_equipo){

                                case 1:{  // Opcion defensivo mixto
                                        FILE*archivo;
                                        archivo=fopen("CSV/HP.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a lista de tipo y pokemon HP

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade a la lista
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (HP, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (HP);
                                        lista=list_next(HP);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (HP);
                                        }

                                        char nombre_pokemon [20];        //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);     //inserta en el equipo
                                        tam_equipo++;

                                }
                                break;

                                case 2:{  //opcion Atacante Fisico

                                        FILE*archivo;
                                        archivo=fopen("CSV/ATK.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){     //crea los pokemon desde el archivo .csv y los añade a la lista
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (ATK, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (ATK);
                                        lista=list_next(ATK);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (ATK);
                                        }

                                        char nombre_pokemon [20];            //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);    //inserta en el equipo
                                        tam_equipo++;

                                }
                                break;

                                case 3:{  //opcion Defensa Fisica

                                        FILE*archivo;
                                        archivo=fopen("CSV/DEF.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade a la lista
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (DEF, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (DEF);
                                        lista=list_next(DEF);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (DEF);
                                        }

                                        char nombre_pokemon [20];                    //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);    //inserta en el equipo
                                        tam_equipo++;

                                }
                                break;

                                case 4:{  //opcion Ataque Especial
                                        FILE*archivo;
                                        archivo=fopen("CSV/ATKESP.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade a la lista
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (ATKESP, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (ATKESP);
                                        lista=list_next(ATKESP);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (ATKESP);
                                        }

                                        char nombre_pokemon [20];                                      //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);    //inserta en el equipo
                                        tam_equipo++;
                                }
                                break;

                                case 5: {   //opcion defensivo especial
                                        FILE*archivo;
                                        archivo=fopen("CSV/DEFESP.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade a la lista
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (DEFESP, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (DEFESP);
                                        lista=list_next(DEFESP);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (DEFESP);
                                        }

                                        char nombre_pokemon [20];                               //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);     //inserta en el equipo
                                        tam_equipo++;
                                }
                                break;

                                case 6: {   //Opcion Velocidad
                                        FILE*archivo;
                                        archivo=fopen("CSV/VEL.csv","r");
                                        if(archivo==NULL){
                                            printf("No se pudo cargar el archivo. \n");
                                            exit(1);
                                        }
                                        else{                       //Carga archivos csv y los une a mapas/lista de tipo y pokemon

                                                char linea[1024];

                                                while (fgets (linea, 1023, archivo) != NULL){      //crea los pokemon desde el archivo .csv y los añade al mapa pokemon y a la lista pokemon
                                                        char *nombre = get_csv_field(linea, 1);
                                                        char *tipo = get_csv_field(linea, 2);
                                                        char *tipo2 = get_csv_field(linea, 3);
                                                        int health = atoi(get_csv_field(linea, 4));
                                                        int atk = atoi(get_csv_field(linea, 5));
                                                        int def = atoi(get_csv_field(linea, 6));
                                                        int atkesp = atoi(get_csv_field(linea, 7));
                                                        int defesp = atoi(get_csv_field(linea, 8));
                                                        int vel = atoi(get_csv_field(linea, 9));
                                                        pokemon*c = crear_pokemon (nombre, tipo, tipo2, health, atk, def, atkesp, defesp, vel);
                                                        list_push_back (VEL, c);
                                                }


                                                fclose(archivo);
                                        }


                                        tipo_pkmn * busca_tipo= searchMap(tipopkmn,(u->tipo));  //obtiene el tipo del pokemon
                                        tipo_pkmn * busca_debilidad = searchMap(tipopkmn, (busca_tipo->debilidad1));  //obtiene la debilidad del pokemon
                                        tipo_pkmn * busca_efectividad = searchMap(tipopkmn,(busca_debilidad->debilidad1)); //obtiene efectividad

                                        pokemon *lista = list_first (VEL);
                                        lista=list_next(VEL);
                                        while (lista != NULL){     //imprime lista de pokemon recomendados
                                                if (strcmp((busca_efectividad->tipo),(lista->tipo))==0 || strcmp((busca_efectividad->tipo),(lista->tipo2))==0 )
                                                        printf("Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", lista->nombre,
                                                                                    lista->tipo, lista->tipo2, lista->health, lista->atk, lista->def, lista->atkesp , lista->defesp, lista->vel);
                                                lista= list_next (VEL);
                                        }

                                        char nombre_pokemon [20];                            //Pregunta al usuario el pokemon que desea (no necesariamente de la lista impresa)
                                        printf("\n");
                                        printf("Escriba el nombre del pokemon que desea:  ");
                                        scanf("%s", nombre_pokemon);
                                        printf("\n");

                                        int i;
                                        nombre_pokemon[0]= toupper(nombre_pokemon[0]);
                                        for (i = 1; i < strlen(nombre_pokemon) ; i++){     //cambia el char escrito por el usuario en caso de ser necesario para que el programa pueda leerlo
                                                if (nombre_pokemon[i]!=' ') nombre_pokemon[i]= tolower (nombre_pokemon[i]);

                                                else toupper (nombre_pokemon[i++]);
                                        }

                                        pokemon*u = searchMap(pkmn,nombre_pokemon);

                                        list_push_back(equipo,u);   //inserta en el equipo
                                        tam_equipo++;
                                }
                                break;


                                default:printf("Seleccion Invalida!!!");
                                break;
                        }
                }

                char nombre[20];
                char Equipo_Archivo[50];
                char Carpeta[] = "Equipos/";
                printf("Introduzca el nombre que desea darle al equipo: ");
                scanf("%s", &nombre);
                printf("\n");
                strcpy(Equipo_Archivo,Carpeta);
                strcat(Equipo_Archivo,nombre);
                strcat(Equipo_Archivo,".txt");

                FILE*f;                                     //ingresa el equipo a un .txt especificado por el usuario
                f=fopen(Equipo_Archivo, "w");

                pokemon *team = list_first (equipo);
                while (team != NULL){
                        fprintf(f,"Nombre: %s\nTipo: %s  Tipo 2: %s \nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n\n", team->nombre,
                                                            team->tipo, team->tipo2, team->health, team->atk, team->def, team->atkesp , team->defesp, team->vel);
                        team= list_next (equipo);
                }

                fclose(f);

            }
            break;

            case 3:{     //Imprime por pantalla los archivos de equipo creados

                char nombre[20];
                char Equipo_Archivo[50];
                char Carpeta[] = "Equipos/";
                printf("Introduzca el nombre del equipo que desea ver: ");
                scanf("%s", &nombre);
                printf("\n");
                strcpy(Equipo_Archivo,Carpeta);
                strcat(Equipo_Archivo,nombre);
                strcat(Equipo_Archivo,".txt");

                FILE*archivo;
                archivo=fopen(Equipo_Archivo,"r");

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


            case 4:{    //Entrega datos de un pokemon especifiado por el usuario
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

                pokemon*u = searchMap(pkmn,nombre);
                printf("\nTipo: %s  Tipo 2: %s \n\nStats:  \nHP: %d    ATK: %d    DEF: %d   ATKSP: %d  DEFSP: %d  VEL: %d \n", u->tipo, u->tipo2, u->health, u->atk, u->def, u->atkesp ,
                                u->defesp, u->vel);

                printf("\n");
                fclose(archivo);
            }
            break;


            case 5:{   //imprime por panntalla el texto de ayuda

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
            case 6:
                break;

            default:printf("Seleccion Invalida!!!");
                break;
        }
        system("pause");
        system("cls");
    }while(menu_opcion != 5);

    return 0;
}


pokemon *crear_pokemon (char * nombre, char *tipo, char*tipo2, int health, int atk, int def, int atkesp, int defesp, int vel){
    pokemon *c = malloc(sizeof(pokemon));
    c->nombre = nombre;
    c->tipo = tipo;
    c->tipo2 = tipo2;
    c->health = health;
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




