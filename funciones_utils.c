#include <stdio.h>
#include <structs.h>

void registro_proy()
{
    FILE *archivo;
    archivo = fopen("registro_proyectos.dat", "ab+");
    if (archivo = NULL)
    {
        printf("\nProblemas para abrir el archivo...");
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
    fwrite(&proy, sizeof(PROYECTO), 1, archivo);

    fclose(archivo);
}

void registro_emp()
{
    FILE *archivo;
    archivo = fopen("registro_empleados.dat", "ab+");
    if (archivo = NULL)
    {
        printf("\nProblemas para abrir el archivo...");
    }

    /*Capturar los datos en la estructura*/
    EMPLEADO empleado;
    printf("Ingrese la clave del proyecto: ");
    scanf("%9s", empleado.clave_proy);

    printf("Ingrese el número de empleado: ");
    scanf("%d", &empleado.num_emp);

    printf("Ingrese el nombre del empleado: ");
    scanf(" %29[^\n]", empleado.nombre);

    printf("Ingrese el CURP: ");
    scanf("%17s", empleado.curp);

    printf("Ingrese la fecha de nacimiento (YYYYMMDD): ");
    scanf("%d", &empleado.fecha_nac);

    printf("Ingrese el correo electrónico: ");
    scanf("%19s", empleado.correo);

    printf("Ingrese el número de teléfono: ");
    scanf("%d", &empleado.telefono);

    /*capturar datos en el archivo */
    fwrite(&archivo, sizeof(PROYECTO), 1, archivo);

    fclose(archivo);
}

void baja_proy() {

};

void baja_emp() {

};