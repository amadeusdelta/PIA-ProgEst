#include <stdio.h>
#include "structs.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // Para mkdir en Unix y Windows
#include <errno.h>

const PROYECTO null_proyecto = {"", "", 0.0, 0, 0};
const EMPLEADO null_empleado = {"", 0, "", "", 0, "", 0};
const USUARIO null_usuario = {"", ""};
const HORAS_EMPLEADO null_horas_empleado = {0, "", 0};
const NOMINA null_nomina = {0, "", 0, 0, {0, "", 0}};

// La opcion 1 obtiene el numero de proyectos, la 2 el numero de empleados y la 3 obtiene el numero de nominas
int obtener_num(int opc)
{
    FILE *archivo_contador;
    int num;
    char nombre_archivo[30];
    switch (opc)
    {
    case 1:
        strcpy(nombre_archivo, "contador_proyectos.txt");
        break;
    case 2:
        strcpy(nombre_archivo, "contador_empleados.txt");
        break;
    case 3:
        strcpy(nombre_archivo, "contador_nominas.txt");
        break;
    default:
        printf("\nOpción invalida ingresada para archivo de contadores.");
    }
    archivo_contador = fopen(nombre_archivo, "r+");
    if (archivo_contador == NULL)
    {
        archivo_contador = fopen(nombre_archivo, "w+");
        if (archivo_contador == NULL)
        {
            printf("Error abriendo %s\n", nombre_archivo);
            return 0;
        }
        fprintf(archivo_contador, "0\n");
        num = 0;
    }
    else if (fgetc(archivo_contador) == EOF)
    {
        fprintf(archivo_contador, "0\n");
        num = 0;
    }
    else
    {
        rewind(archivo_contador);
        fscanf(archivo_contador, "%d\n", &num);
    }
    fclose(archivo_contador);
    return num;
}

void crear_directorio(const char *path)
{
#ifdef _WIN32
    mkdir(path); // Windows: crea el directorio si no existe
#else
    mkdir(path, 0777); // Unix/Linux: crea el directorio con permisos
#endif
}

const char *num_a_mes(int num)
{
    switch (num)
    {
    case 1:
        return "Enero";
    case 2:
        return "Febrero";
    case 3:
        return "Marzo";
    case 4:
        return "Abril";
    case 5:
        return "Mayo";
    case 6:
        return "Junio";
    case 7:
        return "Julio";
    case 8:
        return "Agosto";
    case 9:
        return "Septiembre";
    case 10:
        return "Octubre";
    case 11:
        return "Noviembre";
    case 12:
        return "Diciembre";
    default:
        return "Mes desconocido"; // Maneja el caso de entrada inválida
    }
}

// Dada la clave del proyecto y el numero de empleado, retorna el
//  Empleado asociado a este
EMPLEADO buscar_empleado(char clave_proyecto[10], int num_emp)
{
    int i, num_empleados;
    FILE *reg_empleados;
    num_empleados = obtener_num(2);
    EMPLEADO empleados[num_empleados];

    reg_empleados = fopen("registro_empleados.dat", "rb+");

    if (reg_empleados == NULL)
    {
        printf("No se pudo abrir el archivo correctamente");
        return null_empleado;
    }

    for (i = 0; i < num_empleados; i++)
    {
        // Verifica si el empleado esta asociado con el proyecto y tiene el
        //  Numero de empleado correcto
        if ((strcmp(empleados[i].clave_proy, clave_proyecto) == 0) && (empleados[i].num_emp == num_emp))
        {
            return empleados[i];
        }
    }

    printf("\nNo se pudo encontrar el empleado seleccionado");
    return null_empleado;
}

// Da un array con todos los empleados asociados a un proyecto determinado
EMPLEADO *leer_empleados_proyecto(char clave_proyecto[10])
{
    int i, j = 0, num_empleados;
    FILE *reg_empleados;
    EMPLEADO empleados[MAX_EMPLEADOS];
    EMPLEADO *empleados_proyecto;
    empleados_proyecto = malloc(sizeof(EMPLEADO) * MAX_EMPLEADOS);

    reg_empleados = fopen("registro_empleados.dat", "rb+");
    if (reg_empleados == NULL)
    {
        printf("No se pudo abrir el archivo correctamente\n");
        free(empleados_proyecto);
        return NULL;
    }

    num_empleados = obtener_num(2);
    fread(empleados, sizeof(EMPLEADO), num_empleados, reg_empleados);
    fclose(reg_empleados);

    // Llenar empleados_proyecto solo con los empleados que pertenecen al proyecto
    for (i = 0; i < num_empleados; i++)
    {
        if (strcmp(empleados[i].clave_proy, clave_proyecto) == 0)
        {
            empleados_proyecto[j++] = empleados[i]; // Agrega el empleado al arreglo y aumenta el índice
        }
    }

    // Verificar si no se encontró ningún empleado asociado al proyecto
    if (j == 0)
    {
        free(empleados_proyecto);
        return NULL; // Retorna un puntero al empleado "nulo" si no hay coincidencias
    }

    return empleados_proyecto; // Retorna el arreglo de empleados asociados al proyecto
}

PROYECTO buscar_proyecto(char clave_proyecto[10])
{
    int i, num_proyectos;
    FILE *reg_proyectos;
    num_proyectos = obtener_num(1);

    if (num_proyectos == 0)
    {
        printf("\nNo hay proyectos sobre los cuales realizar una busqueda\n\n");
        return null_proyecto; // Retornar directamente si no hay proyectos
    }

    PROYECTO proyectos[num_proyectos];

    reg_proyectos = fopen("registro_proyectos.dat", "rb");

    if (reg_proyectos == NULL)
    {
        printf("No se pudo abrir el archivo correctamente");
        return null_proyecto;
    }

    // Leer los proyectos desde el archivo
    size_t leidos = fread(proyectos, sizeof(PROYECTO), num_proyectos, reg_proyectos);
    if (leidos != num_proyectos)
    {
        printf("Error al leer los proyectos desde el archivo.\n");
        fclose(reg_proyectos);
        return null_proyecto;
    }

    // Buscar el proyecto con la clave proporcionada
    for (i = 0; i < num_proyectos; i++)
    {
        printf("\nLa clave con la que se esta comparando es: %s\n", proyectos[i].clave_proy);

        if ((strcmp(proyectos[i].clave_proy, clave_proyecto) == 0))
        {
            fclose(reg_proyectos);
            return proyectos[i]; // Retorna el proyecto encontrado
        }
    }

    fclose(reg_proyectos);
    printf("\nNo se pudo encontrar el proyecto seleccionado\n");
    return null_proyecto; // Retorna un proyecto vacío si no se encuentra
}
