#include <stdio.h>
#include <string.h>
#include "funciones_utils.h"
#include "structs.h"

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

int main()
{
    leer_empleados();
    return 0;
}
