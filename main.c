/*MAIN y MENU en nuestro arch principal del proyecto*/

/*FUNCION para imprimir el menu principal*/
int menu()
{
    int op;
    printf("\n\t\tMENU\n1) Proyecto\n2) Empleados\n3) Nina\n4) Reportes\n5) Salir\n");
    do
    {
        printf("\nSeleccione la opcion a realizar (1-5): ");
        scanf("%d", &op);
    } while (op > 5 || op < 1);
    return op;
}

int main()
{
    printf("\n\t\tNOMINA\n\n");
    /*-USUARIO Y CONTRASE�A-*/

    int op = menu();
    do
    {
        switch (op)
        {
        case 1:
            printf("\n-OPCION PROYECTO-");
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
        }
    } while (op != 5);

    return 0;
}
