#include <stdio.h>
#include <string.h>
#define LONGITUD 50
#define LON 20

int leerEnteroEntre(char*, int, int);
int leerEnteroPositivo(char*);
float leerFlotantePositivo(char*);

void agregarLibro(char[][50], int[], float[], int*);
void mostrarmenu();
void ingresarUsuario();
void buscarPosicion(const char*, long*);
void mostrarInformacionPosicion(long);
void eliminarUsuario();
void eliminarLibro();

int main(int argc, char const *argv[]) {
    int tamano = 0, opcion;
    char nombres[LONGITUD][50];  
    int cantidades[LONGITUD];
    float precios[LONGITUD];  

    printf("--> * Bienvenido a la Libreria Andina* <--\n");

    do {
        mostrarmenu();
        opcion = leerEnteroEntre("Ingrese su opcion: ", 1, 6);

        switch (opcion) {
            case 1:
                agregarLibro(nombres, cantidades, precios, &tamano);
                printf("\nInventario modificado:\n");
                break;
            case 2:
                ingresarUsuario();
                break;
            case 3:
                eliminarUsuario();
                break;
            case 4:
                eliminarLibro();
                break;
            case 5: {
                printf("Ingrese el nombre de la persona que busca: ");
                char buscar[LON];
                long posicion;
                scanf("%s", buscar);
                buscarPosicion(buscar, &posicion);
                if (posicion != -1) {
                    printf("\nEncontrado:\n");
                    mostrarInformacionPosicion(posicion);
                } else {
                    printf("\nNo encontrado.\n");
                }
                break;
            }
            case 6:
                printf("Cerrando el programa...\n");
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }

    } while (opcion != 6);
    printf("Programa finalizado\n");
    return 0;
}

int leerEnteroEntre(char* mensaje, int limInferior, int limSuperior) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor < limInferior || valor > limSuperior) {
            printf("-------------------------------------------------------------------\n");
            printf("Error: El numero debe estar entre %d y %d.\n", limInferior, limSuperior);
            printf("-------------------------------------------------------------------\n");
        }
    } while (valor < limInferior || valor > limSuperior);
    return valor;
}

int leerEnteroPositivo(char* mensaje) {
    int valor;
    do {
        printf("%s", mensaje);
        scanf("%d", &valor);
        if (valor <= 0) {
            printf("-------------------------------------------------------------------\n");
            printf("Error: El número debe ser positivo.\n");
            printf("-------------------------------------------------------------------\n");
        }
    } while (valor <= 0);
    return valor;
}

void mostrarmenu() {
    printf("\n");
    printf("********************\n");
    printf("Menu de opciones:\n");
    printf("1. Agregar al Inventario\n");
    printf("2. Agregar Usuario\n");
    printf("3. Eliminar Usuario\n");
    printf("4. Eliminar Libro\n");
    printf("5. Buscar Usuario\n");
    printf("6. Cerrar\n");
    printf("********************\n");
}

void agregarLibro(char nombres[][50], int cantidades[], float precios[], int* tamano) {
    int noma = leerEnteroPositivo("\nIngrese la cantidad de libros a almacenar: ");
    FILE *archivo = fopen("libros.txt", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    for (int i = 0; i < noma; i++) {
        printf(" -----------------------------------------\n"); 
        printf("Ingrese el nombre del libro %d: ", i + 1);
        scanf("%s", nombres[*tamano]);
        cantidades[*tamano] = leerEnteroPositivo("Ingrese la cantidad de libros del ejemplar ingresado: ");
        precios[*tamano] = leerFlotantePositivo("Ingrese el precio del libro por unidad en dolares: ");
        fprintf(archivo, "%s %d  %.2f\n", nombres[*tamano], cantidades[*tamano], precios[*tamano]);
        (*tamano)++;
    }

    fclose(archivo);
}

float leerFlotantePositivo(char* mensaje) {
    float valor;
    do {
        printf("%s", mensaje);
        scanf("%f", &valor);
        if (valor <= 0) {
            printf("-------------------------------------------------------------------\n");
            printf("Error: El número debe ser positivo.\n");
            printf("-------------------------------------------------------------------\n");
        }
    } while (valor <= 0);
    return valor;
}

void ingresarUsuario() {
    char usuarioAp[20][15];
    char usuarioN[20][15];
    int cedula[20];
    int cant = leerEnteroPositivo("Ingrese cuantos Usuarios va a registrar: ");
    FILE *archivo = fopen("Usuarios.txt", "a");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    for (int i = 0; i < cant; i++) {
        printf("-------------------------------------------------------------------\n");
        printf("Ingrese el nombre: ");
        scanf("%s", usuarioN[i]);
        printf("Ingrese el apellido: ");
        scanf("%s", usuarioAp[i]);
        printf("Ingrese la cedula: ");
        scanf("%d", &cedula[i]);
        fprintf(archivo, "%s %s %d\n", usuarioN[i], usuarioAp[i], cedula[i]);
        printf("-------------------------------------------------------------------\n");
    }

    fclose(archivo);
}

void buscarPosicion(const char* buscado, long* pos) {
    FILE *archivo = fopen("Usuarios.txt", "r");
    char usuarioN[20], usuarioAp[20];
    int cedula;
    *pos = -1;

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    while (fscanf(archivo, "%s %s %d", usuarioN, usuarioAp, &cedula) != EOF) {
        if (strcmp(usuarioN, buscado) == 0) {
            *pos = ftell(archivo) - (strlen(usuarioN) + strlen(usuarioAp) + sizeof(cedula) + 2); // ajustar posición
            fclose(archivo);
            return;
        }
    }

    fclose(archivo);
}

void mostrarInformacionPosicion(long pos) {
    FILE *archivo = fopen("Usuarios.txt", "r");
    char usuarioN[20], usuarioAp[20];
    int cedula;

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    fseek(archivo, pos, SEEK_SET);
    fscanf(archivo, "%s %s %d", usuarioN, usuarioAp, &cedula);
    printf("\n%s %s %d\n", usuarioN, usuarioAp, cedula);

    fclose(archivo);
}

void eliminarUsuario() {
    char nombre[50], apellido[50];
    printf("Ingrese el nombre del usuario que desea eliminar: ");
    scanf("%s", nombre);
    printf("Ingrese el apellido del usuario que desea eliminar: ");
    scanf("%s", apellido);

    FILE *archivo = fopen("Usuarios.txt", "r");
    FILE *tempArchivo = fopen("tempUsuarios.txt", "w");

    if (archivo == NULL || tempArchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char usuarioN[50], usuarioAp[50];
    int cedula;
    int encontrado = 0;

    while (fscanf(archivo, "%s %s %d", usuarioN, usuarioAp, &cedula) != EOF) { //El bucle se repite hasta que llegue al final del archivo por EOF(End Of File)
        if (strcmp(usuarioN, nombre) == 0 && strcmp(usuarioAp, apellido) == 0) {
            encontrado = 1;
            continue; // Omitir la escritura de este usuario al archivo temporal
        }
        fprintf(tempArchivo, "%s %s %d\n", usuarioN, usuarioAp, cedula);
    }

    fclose(archivo);
    fclose(tempArchivo);

    // Eliminar el archivo original y renombrar el temporal
    remove("Usuarios.txt");
    rename("tempUsuarios.txt", "Usuarios.txt");

    if (encontrado)
        printf("Usuario eliminado correctamente.\n");
    else
        printf("Usuario no encontrado.\n");
}

void eliminarLibro() {
    char nombreLibro[50];
    printf("Ingrese el nombre del libro que desea eliminar: ");
    scanf("%s", nombreLibro);

    FILE *archivo = fopen("libros.txt", "r");
    FILE *tempArchivo = fopen("tempLibros.txt", "w");

    if (archivo == NULL || tempArchivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char nombre[50];
    int cantidad;
    float precio;
    int econtrado = 0;

    while (fscanf(archivo, "%s %d %f", nombre, &cantidad, &precio) == 3) {
        if (strcmp(nombre, nombreLibro) == 0) {
            econtrado = ftell(archivo) - (strlen(nombre) + sizeof(cantidad) + sizeof(precio) + 2);
            continue; // Omitir la escritura de este libro al archivo temporal
        }
        fprintf(tempArchivo, "%s %d %.2f\n", nombre, cantidad, precio);
    }

    fclose(archivo);
    fclose(tempArchivo);

    // Eliminar el archivo original y renombrar el temporal
    remove("libros.txt");
    rename("tempLibros.txt", "libros.txt");

    if (econtrado=2)
        printf("Libro eliminado correctamente.\n");
    else
        printf("Libro no encontrado.\n");
}

