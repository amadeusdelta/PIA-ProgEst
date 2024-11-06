#include <stdio.h>
#include <structs.h>

void registro_proy()
{
    FILE *reg_proyectos, *cont_proyectos;
    int num_proyectos;
    reg_proyectos = fopen("registro_proyectos.dat", "ab+");
    cont_proyectos = fopen("contador_proyectos.txt", "r+");

    if (reg_proyectos == NULL || cont_proyectos == NULL)
    {
        printf("\nProblemas para abrir el archivo...");
        return;
    }

    /*Capturar los datos en la estructura*/
    PROYECTO proy; /*proy=proyecto */
    printf("\nCaptura de los datos del proyecto:\n");
    printf("\nClave de su proyecto: ");
    scanf("%s", proy.clave_proy);
    printf("\nNombre del proyecto: ");
    scanf("%s", proy.nom);
    printf("\nMonto para proyecto: ");
    scanf("%f", proy.monto);
    printf("\nFecha de inicio dia/mes/ano: ");
    scanf("%d", proy.fecha_i); // check
    printf("\nFecha de inicio dia/mes/ano: ");
    scanf("%d", proy.fecha_f);

    /*capturar datos en el archivo */
    fwrite(&proy, sizeof(PROYECTO), 1, reg_proyectos);
    /*Actualizar el contador*/
    num_proyectos = obtener_num_pacientes(2);
    fprintf(cont_proyectos, "%d\n", num_proyectos);

    fclose(reg_proyectos);
    fclose(cont_proyectos);
}

void registro_emp()
{
    FILE *reg_empleados, *cont_empleados;
    int num_empleados;
    reg_empleados = fopen("registro_empleados.dat", "ab+");
    cont_empleados = fopen("contador_empleados.txt", "r+");
    if (reg_empleados == NULL || cont_empleados == NULL)
    {
        printf("\nProblemas para abrir el archivo...");
        return;
    }

    /*Capturar los datos en la estructura*/
    EMPLEADO empleado;
    printf("Ingrese la clave del proyecto: ");
    scanf("%9s", empleado.clave_proy);

    printf("Ingrese el número de empleado: ");
    scanf("%d", &empleado.num_emp);

    printf("Ingrese el nombre del empleado: ");
    scanf("%29[^\n]", empleado.nombre);

    printf("Ingrese el CURP: ");
    scanf("%17s", empleado.curp);

    printf("Ingrese la fecha de nacimiento (YYYYMMDD): ");
    scanf("%d", &empleado.fecha_nac);

    printf("Ingrese el correo electrónico: ");
    scanf("%19s", empleado.correo);

    printf("Ingrese el número de teléfono: ");
    scanf("%d", &empleado.telefono);

    /*capturar datos en el archivo de registros*/
    fwrite(&reg_empleados, sizeof(PROYECTO), 1, reg_empleados);
    /*Actualizar el contador*/
    num_empleados = obtener_num_pacientes(2);
    fprintf(cont_empleados, "%d\n", num_empleados);

    fclose(reg_empleados);
    fclose(cont_empleados);
}

// La opcion 1 obtiene el numero de proyectos, la 2 el numero de empleados
int obtener_num(int opc)
{
    FILE *archivo_contador;
    int num_pacientes;
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
        num_pacientes = 0;
    }
    else if (fgetc(archivo_contador) == EOF)
    {
        fprintf(archivo_contador, "0\n");
        num_pacientes = 0;
    }
    else
    {
        rewind(archivo_contador);
        fscanf(archivo_contador, "%d\n", &num_pacientes);
    }
    fclose(archivo_contador);
    return num_pacientes;
}

void baja_proy()
{
    FILE *reg_empleados, *reg_proyectos;
    char clave_proyecto[10];
    int i;
    int num_proyectos = obtener_num(1);
    int num_empleados = obtener_num(2);
    reg_proyectos = fopen("reg_proyectos.dat", "rb+");
    reg_empleados = fopen("reg_empleados.dat", "rb+");
    if (reg_empleados == NULL || reg_proyectos == NULL)
    {
        printf("\nEl proyecto no se pudo dar de baja");
        return;
    }

    // Carga los proyectos y los empleados a memoria
    PROYECTO proyectos[num_proyectos];
    EMPLEADO empleados[num_empleados];
    fread(proyectos, sizeof(PROYECTO), num_proyectos, reg_proyectos);
    fread(empleados, sizeof(EMPLEADO), num_empleados, reg_empleados);

    // Abrimos los archivos en escritura, borrando todos los datos para sobreescribirlos
    reg_proyectos = fopen("reg_proyectos.dat", "wb+");
    reg_empleados = fopen("reg_empleados.dat", "wb+");
    if (reg_empleados == NULL || reg_proyectos == NULL)
    {
        printf("\nEl proyecto no se pudo dar de baja");
        return;
    }

    printf("Ingrese el nombre del proyecto: ");
    fgets(clave_proyecto, 10, stdin);

    i = 0;

    // Modifica registros_proyectos.dat, eliminando el proyecto con la clave dada
    for (int i = 0; i < num_proyectos; i++)
    {
        if (!(strcmp(proyectos[i].clave_proy, clave_proyecto)))
        {
            continue;
        }
        else
        {
            fwrite(proyectos + i, sizeof(PROYECTO), 1, reg_proyectos);
        }
    }
    // Modifica registros_proyectos.dat, eliminando los empleados asociados a
    // El proyecto con la clave dada
    for (int i = 0; i < num_empleados; i++)
    {
        if (!(strcmp(empleados[i].clave_proy, clave_proyecto)))
        {
            continue;
        }
        else
        {
            fwrite(empleados + i, sizeof(EMPLEADO), 1, reg_empleados);
        }
    }

    fclose(reg_empleados);
    fclose(reg_proyectos);
};

void baja_emp() {

};