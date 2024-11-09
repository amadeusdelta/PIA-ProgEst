#include <stdio.h>
#include <structs.h>

void imprimir_empleado(EMPLEADO empleado);

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
    printf("\nIngrese la clave del proyecto: ");
    scanf("%9s", empleado.clave_proy);

    printf("\nIngrese el número de empleado: ");
    scanf("%d", &empleado.num_emp);

    printf("\nIngrese el nombre del empleado: ");
    scanf(" %29[^\n]", empleado.nombre);

    printf("\nIngrese el CURP: ");
    scanf("%17s", empleado.curp);

    printf("\nIngrese la fecha de nacimiento (YYYYMMDD): ");
    scanf("%d", &empleado.fecha_nac);

    printf("\nIngrese el correo electrónico: ");
    scanf("%19s", empleado.correo);

    printf("\nIngrese el número de teléfono: ");
    scanf("%d", &empleado.telefono);

    printf("\nIngrese el número de teléfono: ");
    scanf("%d", &empleado.telefono);

    printf("\nIngrese la tarifa por hora del empleado: ");
    scanf("%f", &empleado.tarifa_h);

    /*capturar datos en el archivo de registros*/
    fwrite(&empleado, sizeof(EMPLEADO), 1, reg_empleados);

    /*Actualizar el contador*/
    num_empleados = obtener_num_pacientes(2);
    rewind(cont_empleados);
    fprintf(cont_empleados, "%d\n", num_empleados);

    fclose(reg_empleados);
    fclose(cont_empleados);
}

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

// Da de baja un proyecto y todos los empleados asociados a este
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
    for (int i = 0; i < num_empleados; i++)
    {
        if (strcmp(empleados[i].clave_proy, clave_proyecto) == 0)
        {
            continue;
        }
        else
        {
            fwrite(&empleados[i], sizeof(EMPLEADO), 1, reg_empleados);
        }
    }

    fclose(reg_empleados);
    fclose(reg_proyectos);
}

void baja_emp() {

};

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
    for (int i = 0; i < num_empleados; i++)
    {
        printf("No empleado: %d  %s", empleados_proyecto[i].num_emp, empleados_proyecto[i].nombre);
        printf("\nHoras trabajadas: ");
        scanf("%f", &horas_trabajadas);

        total_nomina += horas_trabajadas * empleados_proyecto[i].tarifa_h;
    }

    printf("\nTotal de nomina: %f", total_nomina);
}
