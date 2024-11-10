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
    proy.empleados_registrados = 0;
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
// Registra un empleado, aumentando en 1 el numero de empleados asociados con el proyecto
// Al cual este pertenece
void registro_emp()
{
    FILE *reg_empleados, *cont_empleados, *reg_proyectos;
    PROYECTO proyecto;
    int num_empleados, num_proyectos;
    num_proyectos = obtener_num(1);
    PROYECTO proyectos[num_proyectos];
    num_empleados = obtener_num_pacientes(2);
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

    // Modificamos el numero de empleados asociados con el proyecto
    reg_proyectos = fopen("registros_proyectos.txt", "rb+");

    if (reg_proyectos == NULL)
    {
        printf("\nNo se pudo abrir el archivo de proyectos\n");
        fclose(reg_empleados);
        fclose(reg_proyectos);
        fclose(cont_empleados);
        return;
    }

    proyecto = buscar_proyecto(empleado.clave_proy);
    if (strcmp(proyecto.nom, "") == 0)
    {
        printf("Error al encontrar el proyecto con la clave dada, no existe");
        return;
    }

    // Aumenta en 1 el numero de empleados registrados en el proyecto seleccionado
    for (int i = 0; i < num_proyectos; i++)
    {
        if (strcmp(proyectos[i].clave_proy, proyecto.clave_proy))
        {
            proyectos[i].empleados_registrados = proyectos[i].empleados_registrados + 1;
        }
    }

    // Reescribe el proyecto modificado
    reg_proyectos = fopen("registros_proyectos.dat", "wb+");
    if (reg_proyectos == NULL)
    {
        printf("\nNo se pudo abrir el archivo de proyectos\n");
        fclose(reg_empleados);
        fclose(reg_proyectos);
        fclose(cont_empleados);
        return;
    }

    fwrite(&proyectos, sizeof(PROYECTO), num_proyectos, reg_proyectos);

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
    rewind(cont_empleados);
    fprintf(cont_empleados, "%d\n", num_empleados + 1);

    fclose(reg_empleados);
    fclose(reg_proyectos);
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
    int mes, ano, num_empleados, num_nominas;
    float total_nomina = 0;
    char clave_proyecto[10];
    EMPLEADO *empleados_proyecto;
    NOMINA nomina;
    PROYECTO proyecto;
    FILE *reg_nominas, *cont_nominas;

    num_empleados = obtener_num(2);
    num_nominas = obtener_num(3);
    reg_nominas = fopen("registros_nominas.dat", "ab+");
    cont_nominas = fopen("contadores_nominas.dat", "wb+");

    if (reg_nominas == NULL || cont_nominas == NULL)
    {
        printf("\nLos archivos no se pudieron abrir correctamente.");
        return;
    }

    num_empleados = obtener_num(2);

    printf("\nMes: ");
    scanf("%d", &nomina.mes_creacion);
    printf("\nAno: ");
    scanf("%d", &nomina.ano_creacion);

    printf("\nClave_proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    proyecto = buscar_proyecto(clave_proyecto);

    if ((strcmp(proyecto.clave_proy, "") == 0))
    {
        printf("\nEl proyecto no existe");
        return;
    }

    strcpy(nomina.clave_proy, clave_proyecto);

    empleados_proyecto = leer_empleados_proyecto(clave_proyecto);
    printf("\nIngrese el numero de horas trabajadas para los empleados asociados al proyecto\n\n");

    int horas_trabajadas;
    for (int i = 0; i < proyecto.empleados_registrados; i++)
    {
        printf("No empleado: %d  %s", empleados_proyecto[i].num_emp, empleados_proyecto[i].nombre);
        printf("\nHoras trabajadas: ");
        scanf("%f", &horas_trabajadas);
        total_nomina += horas_trabajadas * empleados_proyecto[i].tarifa_h;

        // Llena la subestructura de horas_empleados de la nomina para poder generar el reporte
        // Posteriormente
        nomina.empleados[i].num_emp = empleados_proyecto->num_emp;
        nomina.empleados[i].horas_trabajadas = horas_trabajadas;
        nomina.empleados[i].sueldo_mensual = horas_trabajadas * empleados_proyecto[i].tarifa_h;
        nomina.empleados[i].tarifa_h = empleados_proyecto[i].tarifa_h;
        nomina.empleados[i].perfil = empleados_proyecto[i].perfil;
    }

    printf("\nTotal de nomina: %f", total_nomina);

    // Se escribe la nomina al archivo
    fwrite(&nomina, sizeof(NOMINA), 1, reg_nominas);

    // Se actualiza el numero de nominas registradas
    rewind(cont_nominas);
    fprintf(cont_nominas, "%d\n", num_nominas + 1);

    fclose(reg_nominas);
    fclose(cont_nominas);
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
    printf("NO EMPLEADO\tNOMBRE\tCURP\tFECHA NAC\tPERFIL\tTARIFA");

    for (int i = 0; i < proyecto.empleados_registrados; i++)
    {

        char rol[30];
        // Extrae los componentes de la fecha
        int fecha_nac = empleados_proyecto[i].fecha_nac;
        int dia = fecha_nac / 10000;       // Los dos primeros dígitos representan el día
        int mes = (fecha_nac / 100) % 100; // Los dos siguientes dígitos representan el mes
        int ano = fecha_nac % 100;         // Los dos últimos dígitos representan el año

        switch (empleados_proyecto[i].perfil)
        {
        case 1:
            strcpy(rol, "Líder de proyecto");
            break;
        case 2:
            strcpy(rol, "Administrador de Base de Datos");
            break;
        case 3:
            strcpy(rol, "Analista");
            break;
        case 4:
            strcpy(rol, "Programador");
            break;
        case 5:
            strcpy(rol, "Tester");
            break;
        default:
            strcpy(rol, "Rol desconocido");
            break;
        }

        printf("%d\t%s\t%s\t%d-%d-%d\t%s\t%f", empleados_proyecto[i].num_emp,
               empleados_proyecto[i].nombre, empleados_proyecto[i].curp, rol, empleados_proyecto[i].tarifa_h);
    }
}

void lista_proyectos_act()
{
    char clave_proyecto[10];
    FILE *reg_nominas;
    PROYECTO proyecto;
    NOMINA nomina;
    int num_nominas, i, f = 0;
    num_nominas = obtener_num(3);
    NOMINA nominas[num_nominas];
    reg_nominas = fopen("registros_nominas.txt", "rb+");

    if (reg_nominas == NULL)
    {
        printf("\nHubo un error al abrir los registros de las nominas.");
        return;
    }
    fread(&nominas, sizeof(NOMINA), num_nominas, reg_nominas);

    // Esto no es suficiente para determinar unicamente la nomina que se busca
    // Hay que usar algo como la fecha de registro
    for (i = 0; i < num_nominas; i++)
    {
        if (strcmp(nominas[i].clave_proy, clave_proyecto) == 0)
        {
            nomina = nominas[i];
            f = 1;
            break;
        }
    }

    if (f == 0)
    {
        printf("No se encontro una nomina con la clave del proyecto asociado");
    }

    printf("Ingrese la clave del proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;
    proyecto = buscar_proyecto(clave_proyecto);
    printf("PROYECTO\t%s\t%s\n\n", proyecto.clave_proy, proyecto.nom);
    printf("NO EMPLEADO\tNOMBRE\tPERFIL\tTARIFA\tHORAS\tSUELDO");

    for (int i = 0; i < proyecto.empleados_registrados; i++)
    {

        char rol[30];

        switch (empleados_proyecto[i].perfil)
        {
        case 1:
            strcpy(rol, "Líder de proyecto");
            break;
        case 2:
            strcpy(rol, "Administrador de Base de Datos");
            break;
        case 3:
            strcpy(rol, "Analista");
            break;
        case 4:
            strcpy(rol, "Programador");
            break;
        case 5:
            strcpy(rol, "Tester");
            break;
        default:
            strcpy(rol, "Rol desconocido");
            break;
        }

        printf("%d\t%s\t%s\t%d-%d-%d\t%s\t%f", empleados_proyecto[i].num_emp, empleados_proyecto[i].nombre, rol, empleados_proyecto[i].tarifa_h, empleados_proyecto[i].ho, empl);
    }
}
