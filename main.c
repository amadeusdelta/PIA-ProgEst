#include <stdio.h>
#include <string.h>
#include "funciones_main.h"

void menu_principal();
void menu_proyecto();
void menu_empleados();
void menu_nomina();
void menu_reportes();

int main()
{
    int opcion;

    char usuario[50];
    char contrasena[50];
    printf("\n\t\t-----------------\n\t\tCONTROL DE NOMINA\n\t\t-----------------\n\n");
    printf("\tNota, el usuario default es admin con contrasena 123\n\n");
    do
    {
        printf("\tUsuario: ");
        fgets(usuario, sizeof(usuario), stdin);
        usuario[strcspn(usuario, "\n")] = 0;
        if (strcmp(usuario, "admin") != 0)
        {
            printf("\n\tEl usuario ingresado es incorrecto, intente de nuevo.\n\n");
        }
    } while (strcmp(usuario, "admin") != 0);
    printf("\n\n");
    do
    {
        printf("\tContrasena: ");
        fgets(contrasena, sizeof(contrasena), stdin);
        contrasena[strcspn(contrasena, "\n")] = 0;
        if (strcmp(contrasena, "123") != 0)
        {
            printf("\n\tLa contrasena es erronea, intente de nuevo.\n\n");
        }
    } while (strcmp(contrasena, "123") != 0);

    printf("\nIngresando al control de nominas...\n\n");

    do
    {

        printf("\n--- Menú Principal ---\n");
        printf("1. Proyecto\n");
        printf("2. Empleados\n");
        printf("3. Nómina\n");
        printf("4. Reportes\n");
        printf("5. Salir\n");
        printf("Seleccione la opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menu_proyecto();
            break;
        case 2:
            menu_empleados();
            break;
        case 3:
            menu_nomina();
            break;
        case 4:
            menu_reportes();
            break;
        case 5:
            printf("\nSaliendo del programa...\n");
            break;
        default:
            printf("\nOpción inválida. Intente de nuevo.\n");
        }

    } while (opcion != 5);

    return 0;
}

void menu_proyecto()
{
    int opcion;

    do
    {
        printf("\n--- Menú Proyecto ---\n");
        printf("1. Registro\n");
        printf("2. Baja de proyecto\n");
        printf("3. Regresar al menú principal\n");
        printf("Seleccione la opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nRegistrando proyecto...\n");
            registro_proy();
            break;
        case 2:
            printf("\nDando de baja proyecto...\n");
            baja_proyecto();
            break;
        case 3:
            printf("\nRegresando al menú principal...\n");
            break;
        default:
            printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

void menu_empleados()
{
    int opcion;

    do
    {
        printf("\n--- Menú Empleados ---\n");
        printf("1. Registro\n");
        printf("2. Baja de empleado\n");
        printf("3. Regresar al menú principal\n");
        printf("Seleccione la opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nRegistrando empleado...\n");
            registro_emp();
            break;
        case 2:
            printf("\nDando de baja empleado...\n");
            baja_empleado();
            break;
        case 3:
            printf("\nRegresando al menú principal...\n");
            break;
        default:
            printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

void menu_nomina()
{
    int opcion;

    do
    {
        printf("\n--- Menú Nómina ---\n");
        printf("1. Registrar nómina\n");
        printf("2. Regresar al menú principal\n");
        printf("Seleccione la opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nRegistrando nómina...\n");
            registrar_nomina();
            break;
        case 2:
            printf("\nRegresando al menú principal...\n");
            break;
        default:
            printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 2);
}

void menu_reportes()
{
    int opcion;

    do
    {
        printf("\n--- Menú Reportes ---\n");
        printf("1. Lista Proyectos activos\n");
        printf("2. Lista Nómina\n");
        printf("3. Regresar al menú principal\n");
        printf("Seleccione la opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nMostrando lista de proyectos activos...\n");
            lista_proyectos_act();
            break;
        case 2:
            printf("\nMostrando lista de nómina...\n");
            lista_nomina();
            break;
        case 3:
            printf("\nRegresando al menú principal...\n");
            break;
        default:
            printf("\nOpción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}
