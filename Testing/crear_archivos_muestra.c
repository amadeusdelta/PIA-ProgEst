#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "funciones_utils.h"
void crear_proyectos()
{
    FILE *file = fopen("registro_proyectos.dat", "wb");
    if (!file)
    {
        printf("No se pudo abrir el archivo de proyectos\n");
        return;
    }

    PROYECTO proyectos[5] = {
        {"PROY001", "Proyecto Alpha", 10000.0, 4, 20230101, 20231231},
        {"PROY002", "Proyecto Beta", 20000.0, 4, 20230201, 20231130},
        {"PROY003", "Proyecto Gamma", 15000.0, 4, 20230301, 20230930},
        {"PROY004", "Proyecto Delta", 25000.0, 4, 20230401, 20231215},
        {"PROY005", "Proyecto Epsilon", 30000.0, 4, 20230501, 20231201}};

    fwrite(proyectos, sizeof(PROYECTO), 5, file);
    fclose(file);
}

void crear_empleados()
{
    FILE *file = fopen("registro_empleados.dat", "wb");
    if (!file)
    {
        printf("No se pudo abrir el archivo de empleados\n");
        return;
    }

    EMPLEADO empleados[20];
    const char *proyectos[5] = {"PROY001", "PROY002", "PROY003", "PROY004", "PROY005"};
    const char *nombres[4] = {"Juan Perez", "Maria Lopez", "Carlos Sanchez", "Ana Ramirez"};
    const char *curps[4] = {"CURPJUAN0001", "CURPMARIA0002", "CURPCARLO0003", "CURPANA0004"};
    const char *correos[4] = {"juan@correo.com", "maria@correo.com", "carlos@correo.com", "ana@correo.com"};
    const char *telefonos[4] = {"5551234567", "5552345678", "5553456789", "5554567890"};
    int perfil = 1;

    for (int i = 0; i < 5; i++) // For each project
    {
        for (int j = 0; j < 4; j++) // For each employee in the project
        {
            int index = i * 4 + j;
            strcpy(empleados[index].clave_proy, proyectos[i]);
            empleados[index].num_emp = index + 1;
            strcpy(empleados[index].nombre, nombres[j]);
            strcpy(empleados[index].curp, curps[j]);
            empleados[index].fecha_nac = 19900101 + j;
            strcpy(empleados[index].correo, correos[j]);
            strcpy(empleados[index].telefono, telefonos[j]);
            empleados[index].perfil = perfil++;
            empleados[index].tarifa_h = 50.0 + j * 10;
            empleados[index].tarifa_mensual = empleados[index].tarifa_h * 180; // Assuming 160 hours per month

            // Set address details
            strcpy(empleados[index].direccion.calle, "Calle Falsa");
            strcpy(empleados[index].direccion.colonia, "Colonia Ejemplo");
            empleados[index].direccion.numero = 100 + index; // Unique address number
            empleados[index].direccion.CP = 12345 + i;
            strcpy(empleados[index].direccion.municipio, "Municipio Ejemplo");
        }
    }

    fwrite(empleados, sizeof(EMPLEADO), 20, file);
    fclose(file);
    printf("Empleados escritos correctamente en registro_empleados.dat.\n");
}

void crear_nominas()
{
    FILE *file = fopen("registro_nominas.dat", "wb");
    if (!file)
    {
        printf("No se pudo abrir el archivo de nominas\n");
        return;
    }

    const char *proyectos[5] = {"PROY001", "PROY002", "PROY003", "PROY004", "PROY005"};
    const char *nombres[4] = {"Juan Perez", "Maria Lopez", "Carlos Sanchez", "Ana Ramirez"};
    int perfiles[4] = {1, 2, 3, 4};
    float tarifas_h[4] = {50.0, 60.0, 70.0, 80.0};
    int horas_trabajadas[4] = {160, 150, 140, 130};

    for (int i = 0; i < 5; i++)
    {
        NOMINA nomina;
        strcpy(nomina.clave_proy, proyectos[i]);
        nomina.mes_creacion = 10;   // Example month
        nomina.ano_creacion = 2024; // Example year

        for (int j = 0; j < buscar_proyecto(nomina.clave_proy).empleados_registrados; j++)
        {
            nomina.empleados[j].num_emp = j + 1;
            strcpy(nomina.empleados[j].nom, nombres[j]);
            nomina.empleados[j].perfil = perfiles[j];
            nomina.empleados[j].tarifa_h = tarifas_h[j];
            nomina.empleados[j].horas_trabajadas = horas_trabajadas[j];
            nomina.empleados[j].sueldo_mensual = tarifas_h[j] * horas_trabajadas[j];
        }

        fwrite(&nomina, sizeof(NOMINA), 1, file);
    }

    fclose(file);
    printf("Archivo 'registros_nominas.dat' creado con éxito.\n");
}

int main()
{
    crear_proyectos();
    crear_empleados();
    crear_nominas();
    printf("Archivos de registro creados con éxito.\n");
    return 0;
}
