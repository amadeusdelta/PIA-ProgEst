#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "structs.h"
#include "funciones_utils.h"

void registro_proy()
{
    FILE *reg_proyectos, *cont_proyectos;
    int num_proyectos;

    num_proyectos = obtener_num(1);

    // Abrir los archivos
    reg_proyectos = fopen("registro_proyectos.dat", "ab");
    if (reg_proyectos == NULL)
    {
        perror("Error al abrir archivo registro_proyectos.dat");
        return;
    }

    cont_proyectos = fopen("contador_proyectos.txt", "r+");
    if (cont_proyectos == NULL)
    {
        cont_proyectos = fopen("contador_proyectos.txt", "w+");
        if (cont_proyectos == NULL)
        {
            printf("El archivo contador_proyectos.txt no pudo ser abierto correctamente");
            fclose(reg_proyectos);
            fclose(cont_proyectos);

            return;
        }
    }

    PROYECTO proy;
    proy.empleados_registrados = 0;
    printf("\nCaptura de los datos del proyecto:\n");
    getchar();

    printf("\nClave de su proyecto (maximo 10 caracteres): ");
    fgets(proy.clave_proy, sizeof(proy.clave_proy), stdin);
    proy.clave_proy[strcspn(proy.clave_proy, "\n")] = 0;

    printf("\nNombre del proyecto (maximo 30 caracteres): ");
    fgets(proy.nom, sizeof(proy.nom), stdin);
    proy.nom[strcspn(proy.nom, "\n")] = 0;

    printf("\nMonto para proyecto: ");
    scanf("%f", &proy.monto);
    getchar();

    printf("\nFecha de inicio dia/mes/ano: ");
    scanf("%d", &proy.fecha_i);
    getchar();
    printf("\nFecha de final dia/mes/ano: ");
    scanf("%d", &proy.fecha_f);
    getchar();

    fwrite(&proy, sizeof(PROYECTO), 1, reg_proyectos);

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
    num_empleados = obtener_num(2);

    if (num_proyectos == 0)
    {
        printf("\nNo hay ningun proyecto al cual registrar un empleado\n\n");
        return;
    }

    reg_empleados = fopen("registro_empleados.dat", "ab+");
    cont_empleados = fopen("contador_empleados.txt", "r+");
    if (reg_empleados == NULL || cont_empleados == NULL)
    {
        printf("\nProblemas para abrir el archivo...");
        return;
    }

    printf("\nIngresando a registro_emp\n");

    /*Capturar los datos en la estructura*/
    EMPLEADO empleado;
    getchar();
    printf("Ingrese clave del proyecto (máximo 10 caracteres): ");
    fgets(empleado.clave_proy, sizeof(empleado.clave_proy), stdin);
    empleado.clave_proy[strcspn(empleado.clave_proy, "\n")] = 0;

    printf("\nIngresando a registro_emp\n");

    if (num_proyectos == 0)
    {
        printf("\nNo hay proyectos en los cuales buscar");
        return;
    }
    printf("\nIngresando a registro_emp\n");

    proyecto = buscar_proyecto(empleado.clave_proy);
    if (strcmp(proyecto.nom, "") == 0)
    {
        printf("Error al encontrar el proyecto con la clave dada, no existe");
        return;
    }

    reg_proyectos = fopen("registro_proyectos.dat", "rb");

    if (reg_proyectos == NULL)
    {
        printf("\nNo se pudo registrar el empleado, error al abrir el archivo\n\n");
        return;
    }

    fread(proyectos, sizeof(PROYECTO), num_proyectos, reg_proyectos);

    // Aumenta en 1 el numero de empleados registrados en el proyecto seleccionado
    for (int i = 0; i < num_proyectos; i++)
    {
        if (strcmp(proyectos[i].clave_proy, empleado.clave_proy) == 0)
        {
            proyectos[i].empleados_registrados = proyectos[i].empleados_registrados + 1;
        }
    }

    fclose(reg_proyectos);

    // Reescribe el proyecto modificado
    reg_proyectos = fopen("registro_proyectos.dat", "wb+");
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
    getchar();
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

    printf("\n\nSe guardo correctamente el empleado\n");
}

// Da de baja un proyecto y todos los empleados asociados a este
void baja_proyecto()
{

    printf("Entrando a la función baja_proyecto...\n");

    FILE *reg_empleados, *reg_proyectos;
    char clave_proyecto[10];
    int i, num_empleados_proyecto;
    int num_proyectos = obtener_num(1);
    int num_empleados = obtener_num(2);

    printf("El numero de empleados actualmente es: %d\n", num_empleados);
    if (num_empleados == 0)
    {
        printf("\nNo hay ningun empleado registrado, asegurese de registrar primero al menos uno\n\n");
        return;
    }

    printf("Intentando abrir archivos...\n");

    reg_proyectos = fopen("registro_proyectos.dat", "rb");
    reg_empleados = fopen("registro_empleados.dat", "rb");

    if (reg_proyectos == NULL || reg_empleados == NULL)
    {
        perror("Error al abrir los archivos");
        return;
    }

    printf("Archivos abiertos correctamente. Cargando datos...\n");

    PROYECTO proyectos[num_proyectos];

    EMPLEADO empleados[num_empleados];

    size_t proyectos_leidos = fread(proyectos, sizeof(PROYECTO), num_proyectos, reg_proyectos);
    if (proyectos_leidos != num_proyectos)
    {
        perror("Error al leer registro_proyectos.dat");
        fclose(reg_proyectos);
        fclose(reg_empleados);
        return;
    }

    size_t empleados_leidos = fread(empleados, sizeof(EMPLEADO), num_empleados, reg_empleados);
    if (empleados_leidos != num_empleados)
    {
        perror("Error al leer registro_empleados.dat");
        fclose(reg_proyectos);
        fclose(reg_empleados);
        return;
    }

    printf("Datos cargados correctamente.\n");

    reg_proyectos = fopen("registro_proyectos.dat", "wb");
    reg_empleados = fopen("registro_empleados.dat", "wb");

    if (reg_proyectos == NULL || reg_empleados == NULL)
    {
        perror("Error al abrir los archivos para escritura");
        return; // Si no se pueden abrir para escritura, la función termina
    }

    printf("Ingrese la clave del proyecto: ");
    getchar();
    if (fgets(clave_proyecto, sizeof(clave_proyecto), stdin) == NULL)
    {
        perror("Error al leer la clave del proyecto");
        fclose(reg_proyectos);
        fclose(reg_empleados);
        return;
    }
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    for (int i = 0; i < num_proyectos; i++)
    {

        printf("\nLa clave del proyecto es %s: \n", clave_proyecto);
        printf("\nLa clave del proyecto siendo comparada es %s: \n", proyectos[i].clave_proy);
        printf("\nEl nombre del proyecto siendo comparado es %s: \n", proyectos[i].nom);
        if (strcmp(proyectos[i].clave_proy, clave_proyecto) != 0)
        {

            fwrite(&proyectos[i], sizeof(PROYECTO), 1, reg_proyectos);
        }
        else
        {
            continue;
        }
    }

    num_empleados_proyecto = 0;
    for (int i = 0; i < num_empleados; i++)
    {
        if (strcmp(empleados[i].clave_proy, clave_proyecto) != 0)
        {
            fwrite(&empleados[i], sizeof(EMPLEADO), 1, reg_empleados);
        }
        else
        {
            num_empleados_proyecto++;
        }
    }

    fclose(reg_empleados);
    fclose(reg_proyectos);

    FILE *contador_empleados, *contador_proyectos;
    contador_empleados = fopen("contador_proyectos.txt", "w");
    contador_proyectos = fopen("contador_empleados.txt", "w");
    if (contador_empleados == NULL || contador_proyectos == NULL)
    {
        perror("No se pudieron abrir los archivos de contadores");
    }
    else
    {
        fprintf(contador_empleados, "%d\n", num_empleados - num_empleados_proyecto);
        fprintf(contador_proyectos, "%d\n", num_proyectos - 1);
    }

    printf("\nSe dio de baja al proyecto existosamente\n");

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
    reg_empleados = fopen("registro_empleados.dat", "rb+");
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

    reg_empleados = fopen("registro_empleados.dat", "wb+");
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
    contador_empleados = fopen("contador_empleados.txt", "w");
    if (contador_empleados == NULL)
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
    char clave_proyecto[11];
    EMPLEADO *empleados_proyecto;
    NOMINA nomina;
    PROYECTO proyecto;
    FILE *reg_nominas, *cont_nominas;

    num_nominas = obtener_num(3);
    reg_nominas = fopen("registro_nominas.dat", "ab+");
    cont_nominas = fopen("contador_nominas.dat", "wb+");

    if (reg_nominas == NULL || cont_nominas == NULL)
    {
        printf("\nLos archivos no se pudieron abrir correctamente.");
        return;
    }

    if (num_empleados == 0)
    {
        printf("\nNo hay empleados registrados\n\n");
        return;
    }

    printf("\nMes: ");
    scanf("%d", &nomina.mes_creacion);
    printf("\nAno: ");
    scanf("%d", &nomina.ano_creacion);

    printf("\nClave_proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;

    proyecto = buscar_proyecto(clave_proyecto);

    // Verifica si el proyecto existe o no
    if ((strcmp(proyecto.clave_proy, "") == 0))
    {
        printf("\nEl proyecto no existe");
        return;
    }

    strcpy(nomina.clave_proy, clave_proyecto);

    empleados_proyecto = leer_empleados_proyecto(clave_proyecto);
    printf("\nIngrese el numero de horas trabajadas para los empleados asociados al proyecto\n\n");

    int horas_trabajadas;
    int i;
    for (i = 0; i < proyecto.empleados_registrados; i++)
    {
        printf("\nNo empleado: %d  %s", empleados_proyecto[i].num_emp, empleados_proyecto[i].nombre);
        printf("\nHoras trabajadas: ");
        scanf("%f", &horas_trabajadas);
        total_nomina += (horas_trabajadas * empleados_proyecto[i].tarifa_h);

        // Llena la subestructura de horas_empleados de la nomina para poder generar el reporte
        // Posteriormente
        nomina.empleados[i].num_emp = empleados_proyecto[i].num_emp;
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

        char rol[40];
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

void lista_nomina()
{
    char clave_proyecto[10];
    // Archivo es el archivo al cual se guardara el reporte en caso de que el
    //  usuario seleccione la opcion para hacerlo
    FILE *reg_nominas, *archivo;
    char nom_archivo[30];
    PROYECTO proyecto;
    NOMINA nomina;
    int num_nominas, mes_creacion, ano_creacion, i, f = 0;
    num_nominas = obtener_num(3);
    NOMINA nominas[num_nominas];

    reg_nominas = fopen("registro_nominas.dat", "rb+");

    const char *directorio = "Nominas";
    // Crea el directorio si no existe
    crear_directorio(directorio);

    if (reg_nominas == NULL)
    {
        printf("\nHubo un error al abrir los registros de las nominas.");
        return;
    }
    fread(&nominas, sizeof(NOMINA), num_nominas, reg_nominas);

    printf("Ingrese la clave del proyecto: ");
    fgets(clave_proyecto, sizeof(clave_proyecto), stdin);
    clave_proyecto[strcspn(clave_proyecto, "\n")] = 0;
    proyecto = buscar_proyecto(clave_proyecto);

    printf("\nIngrese el ano de creacion del proyecto: ");
    scanf("%d", &ano_creacion);
    printf("\nIngrese el mes de creacion del proyecto: ");
    scanf("%d", &mes_creacion);

    // Esto no es suficiente para determinar unicamente la nomina que se busca
    // Hay que usar algo como la fecha de registro
    for (i = 0; i < num_nominas; i++)
    {
        if (strcmp(nominas[i].clave_proy, clave_proyecto) == 0)
        {
            if ((nominas[i].mes_creacion == mes_creacion) && (nominas[i].ano_creacion == ano_creacion))
            {
                nomina = nominas[i];
                f = 1;
                break;
            }
        }
    }

    if (f == 0)
    {
        printf("\nNo se encontro una nomina con la clave del proyecto asociado");
        return;
    }

    // Le da el formato correcto a el nombre del archivo en el cual se guardara el reporte
    snprintf(nom_archivo, sizeof(nom_archivo), "Nominas/%s_%d_%02d.txt", proyecto.clave_proy, nomina.ano_creacion, nomina.mes_creacion);
    archivo = fopen(nom_archivo, "w+");
    if (archivo == NULL)
    {
        printf("\nEl archivo para generar el reporte no se pudo abrir correctamente");
    }

    printf("PROYECTO\t%s\t%s\n\n", proyecto.clave_proy, proyecto.nom);
    printf("NOMINA DE: \t%s\t%d\n\n", num_a_mes(nomina.mes_creacion), nomina.ano_creacion);

    printf("NO EMPLEADO\tNOMBRE\tPERFIL\tTARIFA\tHORAS\tSUELDO");

    for (int i = 0; i < proyecto.empleados_registrados; i++)
    {

        char rol[40];

        switch (nomina.empleados[i].perfil)
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
        // Imprime a pantalla
        printf("%d\t%s\t%s\t%d-%d-%d\t%s\t%f", nomina.empleados[i].num_emp, nomina.empleados[i].nom, rol, nomina.empleados[i].tarifa_h, nomina.empleados[i].horas_trabajadas, nomina.empleados->sueldo_mensual);

        // Imprime al archivo

        fprintf(archivo, "%d\t%s\t%s\t%.2f\t%d\t%.2f\n",
                nomina.empleados[i].num_emp,
                nomina.empleados[i].nom,
                rol,
                nomina.empleados[i].tarifa_h,
                nomina.empleados[i].horas_trabajadas,
                nomina.empleados[i].sueldo_mensual);
    }

    // Se guarda el archivo o no dependiendo de la eleccion del usuario
    // Notese que el archivo ya esta creado
    int opc;
    printf("\nQuiere guardar el reporte?\n1)Guardar\n2)No guardar\nOpcion: ");
    scanf("%d", &opc);

    if (opc == 1)
    {
        printf("\nEl archivo se guardó exitosamente\n\n");
        return;
    }
    else if (opc == 2)
    {
        if (remove(nom_archivo) == 0)
        {
            printf("\nEl archivo %s se eliminó exitosamente\n", nom_archivo);
        }
        else
        {
            perror("\nError al intentar eliminar el archivo");
        }
        printf("\nRetornando al menú principal...\n\n");
        return;
    }
    else
    {
        printf("\nOpción inválida, retornando al menú principal...\n\n");
    }
}
