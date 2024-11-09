#include <stdio.h>
#include <structs.h>
#include <string.h>

// La opcion 1 obtiene el numero de proyectos, la 2 el numero de empleados
int obtener_num(int opc)
{
    FILE *archivo_contador;
    int num;
    char nombre_archivo[20];
    switch (opc)
    {
    case 1:
        strcpy(nombre_archivo, "contador_proyectos.txt");
        break;
    case 2:
        strcpy(nombre_archivo, "contador_empleados.txt");
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

// Dada la clave del proyecto y el numero de empleado, retorna el
//  Empleado asociado a este
EMPLEADO buscar_empleado(char clave_proyecto[10], int num_emp)
{
    int i, num_empleados;
    FILE *reg_empleados;
    EMPLEADO empleados[num_empleados];

    reg_empleados = fopen("registros_empleados.dat", "rb+");
    num_empleados = obtener_num(2);

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

    printf("\nNo se pudo encontrar al empleado seleccionado");
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

    reg_empleados = fopen("registros_empleados.dat", "rb+");
    if (reg_empleados == NULL)
    {
        printf("No se pudo abrir el archivo correctamente\n");
        free(empleados_proyecto);
        return &null_empleado; // Retorna un puntero al empleado nulo
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
        return &null_empleado; // Retorna un puntero al empleado "nulo" si no hay coincidencias
    }

    return empleados_proyecto; // Retorna el arreglo de empleados asociados al proyecto
}

PROYECTO buscar_proyecto(char clave_proyecto[10])
{
    int i, num_proyectos;
    FILE *reg_proyectos;
    PROYECTO proyectos[num_proyectos];

    reg_proyectos = fopen("registros_proyectos.dat", "rb+");
    num_proyectos = obtener_num(1);

    if (reg_proyectos == NULL)
    {
        printf("No se pudo abrir el archivo correctamente");
        return null_proyecto;
    }

    for (i = 0; i < num_proyectos; i++)
    {
        // Verifica si el empleado esta asociado con el proyecto y tiene el
        //  Numero de empleado correcto
        if ((strcmp(proyectos[i].clave_proy, clave_proyecto) == 0))
        {
            return proyectos[i];
        }
    }

    printf("\nNo se pudo encontrar al empleado seleccionado");
    return null_proyecto;
}
