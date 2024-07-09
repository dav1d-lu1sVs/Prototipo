#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LONGITUD 10
#define LON 20

int leerEnteroPositivo(char* mensaje);
int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior);
float leerFlotantePositivo(char*);

void menuIn();
void controlInventario(char[][50], int[], float[], int, int, int, char[], long);
void agregarLibro(char[][50], int[], float[], int, int, int);

void menuUsu();
void controlUsuario(char[][50] ,char[][50], int[],char[],long);
void ingresarUsuario();
void buscarPosicion(const char* buscado, long* pos);
void Infolibros(long pos);
void buscarUsu(const char* buscado, long* pos);
void mostrarInfoUsu(long pos);

int main(int argc, char const *argv[]) {
    int tamano, opcion, grade;
    int noma;
    int menu; 
    int i=0;
    long posicion;
    printf("--> * Bienvenido a la Libreria Andina* <--\n");
    char usuarioAp[50][50];
    char usuarioN[50][50];
    int cedula[LONGITUD];
    char libros[50][50];  
    int cantidades[50];
    float precios[50];  
   
    char buscar[LON];
    
    do {
        printf("=====================================\n");
        printf("[1] Control de inventario\n");
        printf("[2] Control de usuarios\n");
        printf("[3] Factura \n");
        printf("[4] Cerrar Programa \n");
        printf("=====================================\n");
        scanf("%d", &menu);
        
        switch (menu) {
            case 1:
                printf("------------------------------------\n");
                controlInventario(libros, cantidades, precios, i, noma, tamano, buscar,posicion);
                printf("------------------------------------\n");
                break;
            case 2:
                printf("------------------------------------\n");
                controlUsuario(usuarioN,usuarioAp,cedula,buscar,posicion);
                printf("------------------------------------\n");
                break;
            case 3:
                printf("------------------------------------\n"); 
                printf("[3] Factura \n");
                printf("------------------------------------\n");
                break;
            case 4:
                printf("------------------------------------\n");
                sleep(1);
                printf("Cerrando ");
                sleep(1);
                printf("el ");
                sleep(1);
                printf("programa...\n");
                printf("------------------------------------\n");
                break;
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcion incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (menu != 4);
    
    return 0;
}


void menuIn(){
    printf("\n");
    printf("Inventario:\n");
    printf("[1] Agregar Producto\n");
    printf("[2] Consultar Producto\n");
    printf("[3] Eliminar Producto\n");
    printf("[4] Modificar Producto\n");
    printf("[5] Regresar a Menu Principal\n");
}

void controlInventario(char libros[][50], int cantidades[], float precios[], int i, int tamano, int noma,char buscar[], long posicion ) {
    int ivent;
    do {
        printf("//===================================//\n");
        menuIn();
        printf("//===================================//\n");
        scanf("%d", &ivent);
        
        switch (ivent) {
            case 1:
                printf("//-----------------/-----------------//\n");
                agregarLibro(libros, cantidades, precios, i, noma, tamano);
                printf("\n Inventario modificado:\n");
                break;
                printf("//-----------------/-----------------//\n");
                break;
                
            case 2:
                printf("//-----------------/-----------------//\n");
                printf ("Ingrese producto que busca: ");
                scanf("%s",buscar);
                buscarPosicion(buscar,&posicion);
                 if(posicion != -1){
                    printf("\nEncontrado\n");
                    Infolibros(posicion);
                }else
                    printf("No se encontro\n");
                printf("//-----------------/-----------------//\n");
                break;
            case 3:
                printf("//-----------------/-----------------//\n");
                
                printf("//-----------------/-----------------//\n");
                break;
            case 4:
                printf("//-----------------/-----------------//\n");
               
                printf("//-----------------/-----------------//\n");
                break;
            case 5:
                printf("------------------------------------\n");
                printf("Regresando a menu principal...\n");
                
                break;
                
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcion incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (ivent != 5);
}


void agregarLibro(char libros[][50], int cantidades[], float precios[], int i, int tamano, int noma){
    printf("-------------------------------------------------------------------\n");
    noma = leerEnteroPositivo("\nIngrese la nueva cantidad de libros a almacenar: ");
    FILE *archivo;
    archivo = fopen("libros.txt","a");
    
    if(archivo == NULL){
        printf("No se abrio el archivo");
        return;
    }
    for (int i = 0; i < noma; i++) {
        printf(" -----------------------------------------\n"); 
        printf("Ingrese el nombre del libro %d: ", i + 1);
        scanf("%s", libros[i]);
        cantidades[i]=leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresdo: ");
        precios[i]=leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
   
    tamano=noma;
    printf("-------------------------------------------------------------------\n");
     fprintf(archivo,"%s %d  %.2f$\n", libros[i],cantidades[i], precios[i]);
    }
    fclose(archivo);
    }

void buscarPosicion(const char* buscado, long* pos) {
    FILE *archivo;
    archivo = fopen("libros.txt", "r");
    char libro[50];
    int cantidades;
    float precios;
    *pos = -1;
    if (archivo == NULL) {
        printf("No se abrio el archivo");
        return;
    }
    while (!feof(archivo)) {
        fscanf(archivo, "%s %d %f", libro, &cantidades, &precios);
        if (strcmp(libro, buscado) == 0) {
            *pos = ftell(archivo) - (strlen(libro) + sizeof(cantidades) + sizeof(precios));
            fclose(archivo);
            return;
        }
    }
    fclose(archivo);
}

void Infolibros(long pos) {
    FILE *archivo;
    archivo = fopen("libros.txt", "r");
    char libro[50];
    int cantidades;
    float precios;
    if (archivo == NULL) {
        printf("No se abrio el archivo");
        return;
    }
    
    fseek(archivo, pos, SEEK_SET);
    fscanf(archivo, "%s %d %f", libro, &cantidades, &precios);
    printf("\n%s %d %.2f\n", libro, cantidades, precios);
    fclose(archivo);
}

/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** *//******** */

void menuUsu(){
    printf("\n");
    printf("Usuarios:\n");
    printf("[1] Ingresar Usuario\n");
    printf("[2] Modificar Usuario\n");
    printf("[3] Consultar Usuario\n");
    printf("[4] Regresar a Menu Principal\n");
}

void controlUsuario(char usuarioN[][50], char usuarioAp[][50], int cedula[], char buscar[], long posicion) {
    int usuent;
    do {
        printf("//===================================//\n");
        menuUsu();
        printf("//===================================//\n");
        scanf("%d", &usuent);
        
        switch (usuent) {
            case 1:
                printf("//-----------------//-----------------//\n");
                ingresarUsuario();
                printf("//-----------------//-----------------//\n");
                break;
            case 2:
                printf("//-----------------//-----------------//\n");
                
                printf("//-----------------//-----------------//\n");
                break;    
            case 3:
                printf("//-----------------//-----------------//\n");
                 printf ("Ingrese el nombre de la persona que busca: ");
                scanf("%s",buscar);
                buscarPosicion(buscar,&posicion);
                 if(posicion != -1){
                    printf("\nEncontrado\n");
                   mostrarInfoUsu(posicion);
                }else
                    printf("\n Usuasio no encontrado\n");
                printf("//-----------------//-----------------//\n");
                break;
            case 4:
                printf("------------------------------------\n");
                printf("Regresando a menu principal...\n");
                break;
                
            default:
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                printf("Opcion incorrecta.\n");
                printf("!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
        }
    } while (usuent != 4);
}

void ingresarUsuario(){
    char usuarioAp[20][15];
    char usuarioN[20][15];
    int cedula[20];
    int cant;
    printf("Ingrese cuantos Usuarios va a registrar: ");
    scanf("%d",&cant);
    FILE *archivo;
    archivo = fopen("Usuarios.txt","a");
    if(archivo == NULL){
        printf("No se abrio el archivo");
        return;
    }
    for (int i = 0; i < cant; i++)
    {
         printf("-------------------------------------------------------------------\n");
        printf("Ingrese el nombre: ");
        scanf("%s",usuarioN[i]);
         printf("Ingrese el apellido: ");
        scanf("%s",usuarioAp[i]);
        printf("Ingrese la cedula: ");
        scanf("%d",&cedula[i]);
        fprintf(archivo,"%s %s %d\n",usuarioN[i],usuarioAp[i],cedula[i]);
         printf("-------------------------------------------------------------------\n");
    }
    fclose(archivo);
 }
void buscarUsu(const char* buscado, long* pos){
     FILE *archivo;
    archivo = fopen("Usuarios.txt","r");
    char usuarioAp[20];
    int cedula;
    *pos = 0;
    if(archivo == NULL){
        printf("No se abrio el archivo\n");
        return;
    }
    fprintf(archivo, "Ingrese el nombre que desea buscar: ");
    while(!feof(archivo)){
        fscanf(archivo,"%s %d",usuarioAp,&cedula);
        if(strcmp(usuarioAp,buscado)==0){
            *pos = ftell(archivo) - 1;
            fclose(archivo);
            return;
        }
        *pos = ftell(archivo);
    }
    fclose(archivo);
    *pos = -1;
}

void mostrarInfoUsu(long pos){
  FILE *archivo;
    archivo = fopen("Usuarios.txt","r");
    char usu[20];
    int cedula;
    if(archivo == NULL){
        printf("No se abrio el archivo");
        return;
    }
    
    fseek(archivo,pos,SEEK_SET);
    fscanf(archivo,"%s %d",usu,&cedula);
    printf("\n%s %d\n",usu,cedula);
    fclose(archivo);
}

int leerEnteroEntre(char*mensaje, int limInferior,int limSuperior){
  int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if((valor < limInferior)||(valor > limSuperior)){
          printf("-------------------------------------------------------------------\n");
           printf("Error: El numero debe estar entre %d y %d.\n", limInferior, limSuperior);
          printf("-------------------------------------------------------------------\n");
    }
    }while((valor < limInferior)||(valor > limSuperior));
  return valor;
      
}

int leerEnteroPositivo(char* mensaje){
    int valor;
    do{
        printf("%s", mensaje);
        scanf("%d",&valor);
         if(valor <=0){
          printf("-------------------------------------------------------------------\n");
            printf("Error");
          printf("-------------------------------------------------------------------\n");
        }
    }while(valor <= 0);
    return valor;
}

float leerFlotantePositivo(char* mensaje){
    float valor;
    do{
        printf("%s",mensaje);
        scanf("%f",&valor);
         if(valor <= 0){
            printf("-------------------------------------------------------------------\n");
            printf("Error");
            printf("-------------------------------------------------------------------\n");
        }
    }while(valor <= 0);
   return valor;
}
