#include <stdio.h>
#include <structs.h>
#include <string.h>
#include "structs.h"
#include "funciones_utils.h"

void registro_proy()
{
    FILE *reg_proyectos, *cont_proyectos;
    int num_proyectos;

    // Open the files
    reg_proyectos = fopen("registro_proyectos.dat", "ab+");
    cont_proyectos = fopen("contador_proyectos.txt", "r+");

    if (reg_proyectos == NULL || cont_proyectos == NULL)
    {
        printf("\nProblemas para abrir el archivo...");
        return;
    }

    PROYECTO proy;
    printf("\nCaptura de los datos del proyecto:\n");
    printf("\nClave de su proyecto: ");
    scanf("%s", proy.clave_proy);
    printf("\nNombre del proyecto: ");
    scanf("%s", proy.nom);
    printf("\nMonto para proyecto: ");
    scanf("%f", &proy.monto);

    printf("\nFecha de inicio dia/mes/ano: ");
    scanf("%d", &proy.fecha_i);
    printf("\nFecha de inicio dia/mes/ano: ");
    scanf("%d", &proy.fecha_f);

    fwrite(&proy, sizeof(PROYECTO), 1, reg_proyectos);

    num_proyectos = obtener_num(1);
    /*Actualizar el contador*/

    rewind(cont_proyectos);
    fprintf(cont_proyectos, "%d\n", num_proyectos + 1);

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
    printf("Ingrese clave del proyecto (máximo 10 caracteres): ");
    scanf("%9s", empleado.clave_proy);

    printf("Ingrese número de empleado: ");
    scanf("%d", &empleado.num_emp);

    printf("Ingrese nombre (máximo 30 caracteres): ");
    scanf(" %[^\n]%*c", empleado.nombre);

    printf("Ingrese CURP (máximo 18 caracteres): ");
    scanf("%17s", empleado.curp);

    printf("Ingrese fecha de nacimiento (AAAAMMDD): ");
    scanf("%d", &empleado.fecha_nac);

    printf("Ingrese correo electrónico (máximo 20 caracteres): ");
    scanf("%19s", empleado.correo);

    printf("Ingrese teléfono (máximo 10 caracteres): ");
    scanf("%9s", empleado.telefono);

    printf("Seleccione el perfil:\n");
    printf("1.- Líder de proyecto\n");
    printf("2.- Administrador de Base de Datos\n");
    printf("3.- Analista\n");
    printf("4.- Programador\n");
    printf("5.- Tester\n");
    printf("Ingrese el número correspondiente al perfil: ");
    scanf("%d", &empleado.perfil);

    printf("Ingrese tarifa por hora: ");
    scanf("%f", &empleado.tarifa_h);

    printf("Ingrese tarifa mensual: ");
    scanf("%f", &empleado.tarifa_mensual);

    printf("Ingrese dirección:\n");
    printf("Calle (máximo 30 caracteres): ");
    scanf(" %[^\n]%*c", empleado.direccion.calle);

    printf("Colonia (máximo 30 caracteres): ");
    scanf(" %[^\n]%*c", empleado.direccion.colonia);

    printf("Número: ");
    scanf("%d", &empleado.direccion.numero);

    printf("Código Postal: ");
    scanf("%d", &empleado.direccion.CP);

    printf("Municipio (máximo 30 caracteres): ");
    scanf(" %[^\n]%*c", empleado.direccion.municipio);

    /*capturar datos en el archivo de registros*/
    fwrite(&empleado, sizeof(EMPLEADO), 1, reg_empleados);

    /*Actualizar el contador*/
    num_empleados = obtener_num_pacientes(2);
    rewind(cont_empleados);
    fprintf(cont_empleados, "%d\n", num_empleados + 1);

    fclose(reg_empleados);
    fclose(cont_empleados);
}

// Da de baja un proyecto y todos los empleados asociados a este
void baja_proyecto()
{
    // num_empleados_proyecto es el numero de empleados asociados al proyecto seleccionado
    FILE *reg_empleados, *reg_proyectos;
    char clave_proyecto[10];
    int i, num_empleados_proyecto;
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

    fclose(reg_proyectos);
    fclose(reg_empleados);

    // Abrimos los archivos en escritura, borrando todos los datos para sobreescribirlos

    reg_proyectos = fopen("reg_proyectos.dat", "wb+");
    reg_empleados = fopen("reg_empleados.dat", "wb+");
    if (reg_empleados == NULL || reg_proyectos == NULL)
    {
        printf("\nEl proyecto no se pudo dar de baja");
        return;
    }

    printf("Ingrese la clave del proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    // Modifica registros_proyectos.dat, eliminando el proyecto con la clave dada
    for (int i = 0; i < num_proyectos; i++)
    {
        if (strcmp(proyectos[i].clave_proy, clave_proyecto) == 0)
        {
            continue;
        }
        else
        {
            fwrite(&proyectos[i], sizeof(PROYECTO), 1, reg_proyectos);
        }
    }
    // Modifica registros_empleados.dat, eliminando los empleados asociados a
    // El proyecto con la clave dada
    num_empleados_proyecto = 0;
    for (int i = 0; i < num_empleados; i++)
    {
        if (strcmp(empleados[i].clave_proy, clave_proyecto) == 0)
        {
            num_empleados_proyecto++;
            continue;
        }
        else
        {
            fwrite(&empleados[i], sizeof(EMPLEADO), 1, reg_empleados);
        }
    }

    fclose(reg_empleados);
    fclose(reg_proyectos);

    // Modificamos la cantidad de empleados y de proyectos en los archivos de contadores
    FILE *contador_empleados, *contador_proyectos;
    contador_empleados = fopen("contador_proyectos.txt", "w");
    contador_proyectos = fopen("contador_empleados.txt", "w");
    if (contador_empleados == NULL || contador_proyectos == NULL)
    {
        printf("\nNo se pudieron actualizar los archivos de contadores\n\n");
    }
    else
    {
        fprintf(contador_empleados, "%d\n", num_empleados - num_empleados_proyecto);
        fprintf(contador_proyectos, "%d\n", num_proyectos - 1);
    }
    fclose(contador_empleados);
    fclose(contador_proyectos);
}

// Da de baja un empleado
void baja_empleado()
{
    // num_empleados_proyecto es el numero de empleados asociados al proyecto seleccionado
    FILE *reg_empleados;
    char clave_proyecto[10];
    int i, num_emp;
    int num_empleados = obtener_num(2);
    reg_empleados = fopen("reg_empleados.dat", "rb+");
    if (reg_empleados == NULL)
    {
        printf("\nEl empleado no se pudo dar de baja");
        return;
    }

    // Carga los empleados a memoria
    EMPLEADO empleados[num_empleados];
    fread(empleados, sizeof(EMPLEADO), num_empleados, reg_empleados);

    fclose(reg_empleados);

    // Abrimos los archivos en escritura, borrando todos los datos para sobreescribirlos

    reg_empleados = fopen("reg_empleados.dat", "wb+");
    if (reg_empleados == NULL)
    {
        printf("\nEl proyecto no se pudo dar de baja");
        return;
    }

    printf("Ingrese la clave del proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    printf("Ingrese el numero del empleado: ");
    scanf("%d", &num_emp);

    // Modifica registros_empleados.dat, eliminando los empleados asociados a
    // El proyecto con la clave dada
    for (int i = 0; i < num_empleados; i++)
    {
        if ((strcmp(empleados[i].clave_proy, clave_proyecto) == 0) && (empleados[i].num_emp == num_emp))
        {
            continue;
        }
        else
        {
            fwrite(&empleados[i], sizeof(EMPLEADO), 1, reg_empleados);
        }
    }

    fclose(reg_empleados);

    // Modificamos la cantidad de empleados en el archivo de contadores
    FILE *contador_empleados;
    contador_empleados = fopen("contador_proyectos.txt", "w");
    if (contador_empleados)
    {
        printf("\nNo se pudieron actualizar los archivos de contadores\n\n");
        return;
    }
    else
    {
        fprintf(contador_empleados, "%d\n", num_empleados - 1);
    }
    fclose(contador_empleados);
}
// Función para registrar una nómina
void registrar_nomina()
{
    int mes, ano, num_empleados;
    float total_nomina = 0;
    char clave_proyecto[10];
    EMPLEADO *empleados_proyecto;
    num_empleados = obtener_num(2);

    printf("\nMes: ");
    scanf("%d", &mes);
    printf("\nAno: ");
    scanf("%d", &ano);

    printf("\nClave_proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    if ((buscar_proyecto(clave_proyecto).clave_proy == ""))
    {
        printf("\nEl proyecto no existe");
        return;
    }

    empleados_proyecto = leer_empleados_proyecto(clave_proyecto);
    printf("\nIngrese el numero de horas trabajadas para los empleados asociados al proyecto\n\n");

    int horas_trabajadas;
    for (int i = 0; i < MAX_EMPLEADOS; i++)
    {
        printf("No empleado: %d  %s", empleados_proyecto[i].num_emp, empleados_proyecto[i].nombre);
        printf("\nHoras trabajadas: ");
        scanf("%f", &horas_trabajadas);

        total_nomina += horas_trabajadas * empleados_proyecto[i].tarifa_h;
    }

    printf("\nTotal de nomina: %f", total_nomina);
}

void lista_proyectos_act()
{
    char clave_proyecto[10];
    PROYECTO proyecto;
    EMPLEADO *empleados_proyecto;
    printf("Ingrese la clave del proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;
    proyecto = buscar_proyecto(clave_proyecto);
    empleados_proyecto = leer_empleados_proyecto(clave_proyecto);
    printf("PROYECTO\t%s\t%s\n\n", proyecto.clave_proy, proyecto.nom);
    for (size_t i = 0; i < count; i++)
    {
        /* code */
    }
}

// Hay un gran problema en el codigo, no estoy seguro de cuantos empleados hay asociados a cada
// Puedo inicializar los valores en el arreglo 