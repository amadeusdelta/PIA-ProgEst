#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "funciones_utils.h"
void leer_proyectos(const char *nombre_archivo)
{
    FILE *archivo = fopen(nombre_archivo, "rb"); // Abrir archivo en modo lectura binaria
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    PROYECTO proyecto;
    while (fread(&proyecto, sizeof(PROYECTO), 1, archivo) == 1)
    {
        // Imprime los datos del proyecto leído
        printf("\n\n\nClave del Proyecto: %s\n", proyecto.clave_proy);
        printf("Nombre del Proyecto: %s\n", proyecto.nom);
        printf("Empleados Registrados: %d\n", proyecto.empleados_registrados);
        printf("\n");
    }

    fclose(archivo); // Cerrar el archivo
}

void leer_empleados()
{
    FILE *file = fopen("registro_empleados.dat", "rb");
    if (!file)
    {
        printf("No se pudo abrir el archivo de empleados\n");
        return;
    }

    int num_empleados = obtener_num(2); // Usamos la función obtener_num para obtener la cantidad de empleados
    EMPLEADO empleados[num_empleados];  // Creamos un arreglo de EMPLEADO según la cantidad

    fread(empleados, sizeof(EMPLEADO), num_empleados, file);

    // Imprimimos la información de los empleados leídos
    for (int i = 0; i < num_empleados; i++)
    {
        printf("\nEmpleado %d\n", empleados[i].num_emp);
        printf("Nombre: %s\n", empleados[i].nombre);
        printf("CURP: %s\n", empleados[i].curp);
        printf("Fecha de Nacimiento: %d\n", empleados[i].fecha_nac);
        printf("Correo: %s\n", empleados[i].correo);
        printf("Telefono: %s\n", empleados[i].telefono);
        printf("Perfil: %d\n", empleados[i].perfil);
        printf("Tarifa por Hora: %.2f\n", empleados[i].tarifa_h);
        printf("Tarifa Mensual: %.2f\n", empleados[i].tarifa_mensual);

        // Detalles de la dirección
        printf("Direccion:\n");
        printf("  Calle: %s\n", empleados[i].direccion.calle);
        printf("  Colonia: %s\n", empleados[i].direccion.colonia);
        printf("  Numero: %d\n", empleados[i].direccion.numero);
        printf("  CP: %d\n", empleados[i].direccion.CP);
        printf("  Municipio: %s\n", empleados[i].direccion.municipio);
        printf("\n----------------------------\n");
    }

    fclose(file);
}

void leer_nominas()
{
    FILE *file = fopen("registro_nominas.dat", "rb");
    if (!file)
    {
        printf("No se pudo abrir el archivo de nominas\n");
        return;
    }

    int num_nominas = obtener_num(3);
    NOMINA nominas[num_nominas];

    printf("Nominas registradas:\n\n");

    // Read each NOMINA record from the file

    fread(nominas, sizeof(NOMINA), num_nominas, file);

    for (int i = 0; i < num_nominas; i++)
    {
        printf("Nomina #%d\n", i + 1);
        printf("Clave del Proyecto: %s\n", nominas[i].clave_proy);
        printf("Fecha de Creacion: %d/%d\n", nominas[i].mes_creacion, nominas[i].ano_creacion);

        for (int j = 0; j < buscar_proyecto(nominas[i].clave_proy).empleados_registrados; j++)
        {
            printf("\nEmpleado #%d\n", nominas[i].empleados[j].num_emp);
            printf("Nombre: %s\n", nominas[i].empleados[j].nom);
            printf("Perfil: %d\n", nominas[i].empleados[j].perfil);
            printf("Tarifa por Hora: %.2f\n", nominas[i].empleados[j].tarifa_h);
            printf("Horas Trabajadas: %d\n", nominas[i].empleados[j].horas_trabajadas);
            printf("Sueldo Mensual: %.2f\n", nominas[i].empleados[j].sueldo_mensual);
        }

        printf("\n-----------------------------\n");
    }

    fclose(file);
    printf("Fin de la lectura de nominas.\n");
}
int main()
{
    leer_proyectos("registro_proyectos.dat");
    leer_empleados();
    leer_nominas();

    return 0;
}
