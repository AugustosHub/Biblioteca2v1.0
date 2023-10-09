#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

struct libros{
    int ISBN;
    char nombre[50];
    int edicion;
    char tipo[50];
    int cantidad;
    int ISBNeditorial,ISBNeditorial2, ISBNautor;
    int ejemplares_prestados;
    int vacio;
};

struct autor{
    int ISBN;
    int DNI;
    char nombre[20];
    char apellido[20];
    char nacionalidad[20];
    int vacio;
};

struct editorial{
    int ISBN;
    char nombre[50];
    char direccion[50];
    int vacio;
};

struct prestamo{
    int ISBN;
    char nombre[50];
    int dia;
    int mes;
    int anio;
    int libro;
};

void inicializacion(struct libros *libros, struct autor *autor, struct editorial *editorial, struct prestamo *prestamo){
    for(int i=0; i<10; i++){
        libros[i].ISBN=0;
        libros[i].ISBNeditorial=0;
        libros[i].ISBNeditorial2=0;
        libros[i].ISBNautor=0;
        strcpy(libros[i].nombre,"-");
        libros[i].edicion=0;
        strcpy(libros[i].tipo,"-");
        libros[i].cantidad=0;
        libros[i].ejemplares_prestados=0;
        libros[i].vacio = 0;
    }
    for(int i=0; i<10; i++){
        autor[i].ISBN=0;
        autor[i].DNI =0;
        strcpy(autor[i].nombre,"-");
        strcpy(autor[i].apellido,"-");
        strcpy(autor[i].nacionalidad,"-");
        autor[i].vacio=0;
    }

    for(int i=0; i<10; i++){
        editorial[i].ISBN=0;
        strcpy(editorial[i].nombre,"-");
        strcpy(editorial[i].direccion,"-");
        editorial[i].vacio=0;
    }

    for(int i=0; i<10; i++){
        prestamo[i].ISBN=0;
        strcpy(prestamo[i].nombre,"-");
        prestamo[i].dia=0;
        prestamo[i].mes=0;
        prestamo[i].anio=0;
        prestamo[i].libro=0;
    }
}

void cargarEditorial(struct editorial *editorial){
    int c=1,c1=0,c2=0,op;

    //Verifica con un contador de lugares disponibles (vacio) que haya un lugar disponible para añadir una nueva editorial
    for(int i=0;i<10;i++){
        if(editorial[i].vacio==1){
            c1=c1+1; //Si está ocupado el lugar aumento en +1 la cuenta
        }
    }

    //En el caso de que la cuenta llegue a diez se detiene y termina el programa
    if(c1>=10){
        puts("NO HAY MÁS ESPACIO PARA AGREGAR EDITORIALES");
        puts("-------------------------------------------");
        system("pause");
    }else{ //De lo contrario inicia el proceso de agregar una nueva editorial
        for(int i=0;i<10;i++){
            if(editorial[i].vacio==0){
                puts("AGREGUE UNA EDITORIAL: \n");
                fflush(stdin);
                printf("Nombre de la editorial: ");
                gets(editorial[i].nombre);
                fflush(stdin);
                printf("Dirección de la editorial: ");
                gets(editorial[i].direccion);
                puts("-------------------------------------------");
                puts("¡Datos de la editorial cargados con éxito! ");
                puts("-------------------------------------------");

                editorial[i].vacio = 1;

                system("pause");
                system("cls");
                puts("Cargando...");
                sleep(1);

                //Contador que guarda la sumatoria de todos los códigos ISBN
                //Lo utilizo para asignar códigos ISBN seguidos a cada nueva editorial
                for(int j=0; j<10;j++){
                    c2 = c2 + editorial[j].ISBN;
                }
                //Se le asigna el número siguiente a la nueva editorial
                editorial[i].ISBN = c2 + 1;
                //Bucle para verificar que el número no está siendo utilizado por otra editorial
                //Si está siendo utilizado usa el siguiente
                for(int k=0; k<10;k++){
                    if(editorial[k].ISBN==editorial[i].ISBN && k!=i){
                        editorial[i].ISBN = editorial[i].ISBN + 1;
                    }
                }
                system("cls");
                printf("El ISBN de la editorial '%s' será: %d\n",editorial[i].nombre,editorial[i].ISBN);
                puts("----------------------------------------------------");
                system("pause");
                puts("----------------------------------------------------");
                puts("¡Editorial cargada con éxito!");
                sleep(1);
                break;
            }
        }
    }
}

void cargarAutor(struct autor *autor){
        int c=1,c1=0,c2=0,op;
        int dia, mes, anio;
        int error1=0,error2=0; //Almacena errores
        int tyu=0; //Verifica si tiene 31 año
        int bis=0; //Verifica si es bisiesto

    //Verifica con un contador de lugares disponibles (vacio) que haya un lugar disponible para añadir un nuevo autor
    for(int i=0;i<10;i++){
        if(autor[i].vacio==1){
            c1=c1+1; //Si está ocupado el lugar aumento en +1 la cuenta
        }
    }

    //En el caso de que la cuenta llegue a diez se detiene y termina el programa
    if(c1>=10){
        puts("NO HAY MÁS ESPACIO PARA AGREGAR AUTORES");
        puts("---------------------------------------");
        system("pause");
    }else{ //De lo contrario inicia el proceso de agregar una nueva editorial
        for(int i=0;i<10;i++){
            if(autor[i].vacio==0){
                puts("AÑADA UN AUTOR: \n");
                fflush(stdin);
                printf("Nombre del autor: ");
                gets(autor[i].nombre);
                puts("---------------------------------------");
                fflush(stdin);
                printf("Apellido del autor: ");
                gets(autor[i].apellido);
                puts("---------------------------------------");
                fflush(stdin);
                printf("Nacionalidad %s %s: ",autor[i].nombre,autor[i].apellido);
                gets(autor[i].nacionalidad);
                ////////////////////////////////////////////
                //FECHA DE NACIMIENTO
                puts("---------------------------------------");
                printf("Ingrese el natalicio de %s %s\n",autor[i].nombre,autor[i].apellido);
                ////////////////////////////////////////////
                //DIGITACIÓN Y CÁLCULOS
                printf("Dia (XX): ");
                scanf("%d",&dia);
                while(dia>31 || dia<1){
                    puts("----------------------------------");
                    puts("Dia no válido, intente de nuevo...");
                    puts("----------------------------------");
                    puts("Elija otro...");
                    printf("Dia (XX): ");
                    scanf("%d",&dia);
                }
                printf("Mes (XX): ");
                scanf("%d",&mes);
                while(mes>12 || mes<1){
                    puts("----------------------------------");
                    puts("Mes no válido, intente de nuevo...");
                    puts("----------------------------------");
                    puts("Elija otro...");
                    printf("Mes (XX): ");
                    scanf("%d",&mes);
                }
                ///////////////////////////////////////////////
                //Verificaciones de dias que no tienen 31 días
                if((mes==4||mes==6||mes==9||mes==11)&&(dia==31)){
                    tyu=1;
                }
                while(tyu==1){
                    if(mes==4){
                        if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }else{
                            puts("-------------------------------------");
                            puts("Dia no válido, Abril no tiene 31 dias");
                            puts("-------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }

                        if(dia<=30 && dia>0){
                            tyu=0;
                        }
                    }else if(mes==6){
                        if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }else{
                            puts("-------------------------------------");
                            puts("Dia no válido, Junio no tiene 31 dias");
                            puts("-------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }

                        if(dia<=30 && dia>0){
                            tyu=0;
                        }
                    }else if(mes==9){
                        if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }else{
                            puts("------------------------------------------");
                            puts("Dia no válido, Septiembre no tiene 31 dias");
                            puts("------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }

                        if(dia<=30 && dia>0){
                            tyu=0;
                        }
                    }else if(mes==11){
                        if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }else{
                            puts("-----------------------------------------");
                            puts("Dia no válido, Noviembre no tiene 31 dias");
                            puts("-----------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }

                        if(dia<=30 && dia>0){
                            tyu=0;
                        }
                    }
                }
                //////////////////////////////////////////////
                //Verificaciones de Febrero
                if(dia>29 && (mes==2)){
                    error1=1;
                    while(error1==1){
                        if(dia==30){
                        if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                        }else{
                            puts("---------------------------------------");
                            puts("Dia no válido, Febrero no tiene 30 dias");
                            puts("---------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                            if(dia<=29 && (mes==2)){
                                error1=0;
                            }else if(dia==31){
                                    if(dia<=0){
                                        puts("----------------------------------------------");
                                        puts("Dia no válido, no existe mes con dia menor a 1");
                                        puts("----------------------------------------------");
                                        puts("Elija otro...");
                                        printf("Dia (XX): ");
                                        scanf("%d",&dia);
                                    }else{
                                        puts("---------------------------------------");
                                        puts("Dia no válido, Febrero no tiene 31 dias");
                                        puts("---------------------------------------");
                                        puts("Elija otro...");
                                        printf("Dia (XX): ");
                                        scanf("%d",&dia);
                                        if(dia<=29 && (mes==2)){
                                            error1=0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                ///////////////////////////////////////////////
                printf("Año (XXXX): ");
                scanf("%d",&anio);
                //Tomo como parametro de año maximal 1911 segun la fuente CNN Kane Takana es la persona más vieja del mundo nacida en 1904
                //Tomo como parametro de año minimal 2013 considero que 10 años es la edad minima para poder publicar un libro medianamente "decente"
                while(anio>2013 || anio<1904){
                    puts("----------------------------------");
                    printf("Año no válido, ");
                    if(anio>2013){
                        printf("el autor no debería ser tan joven\n");
                    }else if(anio<1904){
                        printf("el autor probablemente esté muerto\n");
                    }
                    puts("----------------------------------");
                    puts("Elija otro...");
                    printf("Año (XXXX): ");
                    scanf("%d",&anio);
                }
                ///////////////////////////////////////////////
                //Verificaciones de Febrero (Bisiesto)
                if(dia==29 && mes==02 && (anio%4!=0)){
                    error2=1;
                }

                while(error2==1){
                    puts("------------------------------------------------------------------------");
                    printf("Dia no válido, el año %d no fue bisiesto, Febrero no tuvo 29 dias",anio);
                    puts("------------------------------------------------------------------------");
                    puts("Elija otro...");
                    printf("Dia (XX): ");
                    scanf("%d",&dia);

                    if(dia<=28 && dia>0){
                        error2=0;
                    }

                    if(dia<=0){
                            puts("----------------------------------------------");
                            puts("Dia no válido, no existe mes con dia menor a 1");
                            puts("----------------------------------------------");
                            puts("Elija otro...");
                            printf("Dia (XX): ");
                            scanf("%d",&dia);
                    }
                }
                //////////////////////////////////////////////
                puts("-------------------------------------");
                puts("¡Datos del autor cargados con éxito! ");
                puts("-------------------------------------");

                autor[i].vacio = 1;

                system("pause");
                system("cls");
                puts("Cargando...");
                sleep(1);

                //Contador que guarda la sumatoria de todos los códigos ISBN
                //Lo utilizo para asignar códigos ISBN seguidos a cada nuevo autor
                for(int j=0; j<10;j++){
                    c2 = c2 + autor[j].ISBN;
                }
                //Se le asigna el número siguiente al nuevo autor
                autor[i].ISBN = c2 + 1;
                //Bucle para verificar que el número no está siendo utilizado por otro autor
                //Si está siendo utilizado usa el siguiente
                for(int k=0; k<10;k++){
                    if(autor[k].ISBN==autor[i].ISBN && k!=i){
                        autor[i].ISBN = autor[i].ISBN + 1;
                    }
                }
                system("cls");
                printf("El ISBN del autor '%s %s' será: %d\n",autor[i].nombre,autor[i].apellido,autor[i].ISBN);
                puts("----------------------------------------------------");
                system("pause");
                puts("----------------------------------------------------");
                puts("¡Autor cargado con éxito!");
                sleep(1);
                break;
            }
        }
    }
}

void cargarLibro(struct libros *libros,struct autor *autor, struct editorial *editorial){
    int op,op2,opAutor,opEditorial,opEditorial2,cantidadLibros;
    int c=1,c1=0,c2=0,c3=1,c4=1;

    //Verifica con un contador de lugares disponibles (vacio) que haya lugar disponible para añadir un nuevo libro
    for(int i=0;i<10;i++){
        if(libros[i].vacio==1){
            c1=c1+1; //Si está ocupado el lugar aumento en +1 la cuenta
        }
    }

    //En el caso de que la cuenta llegue a diez se detiene y termina el programa
    if(c1>=10){
        puts("NO HAY MÁS ESPACIO PARA AGREGAR LIBROS");
        puts("--------------------------------------");
        system("pause");
    }else{ //De lo contrario inicia el proceso de agregar una nueva editorial
        for(int i=0;i<10;i++){
            if(libros[i].vacio==0){
                puts("AÑADA UN LIBRO: \n");
                fflush(stdin);
                printf("Nombre del libro: ");
                gets(libros[i].nombre);
                puts("---------------------------------------");
                fflush(stdin);
                printf("Tipo de libro: ");
                gets(libros[i].tipo);
                puts("---------------------------------------");
                printf("Edición del libro: ");
                scanf("%d",&libros[i].edicion);
                puts("---------------------------------------");
                printf("Cantidad del libro %s: ",libros[i].nombre);
                scanf("%d",&cantidadLibros);
                while(cantidadLibros>10||cantidadLibros<0){
                    puts("---------------------------------------------------------");
                    puts("Cantidad invalida solo se puede agregar entre 0-10 libros");
                    puts("---------------------------------------------------------");
                    printf("Cantidad del libro %s: ",libros[i].nombre);
                    scanf("%d",&cantidadLibros);
                }
                libros[i].cantidad=cantidadLibros;
                puts("---------------------------------------");
                //////////////////////////////////////////////////////////////////////////
                //Elección de autor
                puts("Elija el autor del libro: ");
                for(int j=0;j<10;j++){
                    if(autor[j].vacio==1){
                        printf("%d. %s %s\n",c3,autor[j].nombre,autor[j].apellido);
                        c3= c3 +1;
                    }
                }
                printf("%d. Ninguno\n",c3);
                puts("---------------");
                printf("Elegir opción: ");
                scanf("%d",&opAutor);
                while(opAutor>c3 || opAutor<1){
                    puts("------------------------------------");
                    puts("Opción invalida, intente de nuevo...");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&opAutor);
                }
                if(opAutor==c3){
                    puts("---------------------------------------------------");
                    puts("Es necesario agregar un autor al libro...");
                    puts("Si no lo encontró en la lista, agreguelo en el menú");
                    puts("---------------------------------------------------");
                    system("pause");
                    libros[i].ISBN=0;
                    libros[i].ISBNeditorial=0;
                    libros[i].ISBNautor=0;
                    strcpy(libros[i].nombre,"-");
                    libros[i].edicion=0;
                    strcpy(libros[i].tipo,"-");
                    libros[i].cantidad=0;
                    libros[i].ejemplares_prestados=0;
                    libros[i].vacio = 0;
                    return 0;
                }else{
                    for(int j=0;j<10;j++){
                        if((opAutor-1)==j){
                            libros[i].ISBNautor=autor[j].ISBN;
                            puts("------------------------------------");
                            puts("¡Autor vinculado éxitosamente!");
                            puts("------------------------------------");
                            puts("¿Desea agregar otro autor?");
                            puts("1. Si");
                            puts("2. No");
                            puts("------------");
                            printf("Opción: ");
                            scanf("%d",&op2);
                            while(op>2 || op<1){
                                puts("------------------------------------");
                                puts("Opción invalida, intente de nuevo...");
                                puts("------------------------------------");
                                printf("Opción: ");
                                scanf("%d",&op2);
                            }
                            switch(op2){
                                case 1:
                                    puts("Elija el autor del libro: ");
                                    for(int j=0;j<10;j++){
                                        if(autor[j].vacio==1){
                                            printf("%d. %s %s\n",c3,autor[j].nombre,autor[j].apellido);
                                            c3= c3 +1;
                                        }
                                    }
                                    printf("%d. Ninguno\n",c3);
                                    puts("---------------");
                                    printf("Elegir opción: ");
                                    scanf("%d",&opAutor);
                                    while(opAutor>c3 || opAutor<1){
                                        puts("------------------------------------");
                                        puts("Opción invalida, intente de nuevo...");
                                        puts("------------------------------------");
                                        printf("Elegir opción: ");
                                        scanf("%d",&opAutor);
                                    }
                                    if(opAutor==c){
                                        puts("-------------------------------");
                                        puts("¡El libro tendrá un solo autor!");
                                        puts("-------------------------------");
                                        system("pause");
                                        break;
                                    }else{
                                        for(int j=0;j<10;j++){
                                            if((opAutor-1)==j){
                                                libros[i].ISBNautor=autor[j].ISBN;
                                                puts("------------------------------");
                                                puts("¡Autor vinculado éxitosamente!");
                                                puts("------------------------------");
                                                system("pause");
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    puts("-------------------------------");
                                    puts("¡El libro tendrá un solo autor!");
                                    puts("-------------------------------");
                                    system("pause");
                                    break;
                            }
                        }
                    }
                }
                //////////////////////////////////////////////////////////////////////////
                //Elección de editorial
                puts("---------------------------------------");
                puts("Elija la editorial del libro: ");
                for(int j=0;j<10;j++){
                    if(editorial[j].vacio==1){
                       printf("%d. %s\n",c4,editorial[j].nombre);
                        c4= c4 +1;
                    }
                }
                printf("%d. Ninguno\n",c4);
                puts("---------------");
                printf("Elegir opción: ");
                scanf("%d",&opEditorial);
                while(opEditorial>c4 || opEditorial<1){
                    puts("------------------------------------");
                    puts("Opción invalida, intente de nuevo...");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&opEditorial);
                }
                if(opEditorial==c4){
                    puts("---------------------------------------------------");
                    puts("Es necesario agregar una editorial al libro...");
                    puts("Si no lo encontró en la lista, agreguelo en el menú");
                    puts("---------------------------------------------------");
                    system("pause");
                    libros[i].ISBN=0;
                    libros[i].ISBNeditorial=0;
                    libros[i].ISBNautor=0;
                    strcpy(libros[i].nombre,"-");
                    libros[i].edicion=0;
                    strcpy(libros[i].tipo,"-");
                    libros[i].cantidad=0;
                    libros[i].ejemplares_prestados=0;
                    libros[i].vacio = 0;
                    return 0;
                }else{
                    for(int j=0;j<10;j++){
                        if((opEditorial-1)==j){
                            libros[i].ISBNeditorial=editorial[j].ISBN;
                            puts("------------------------------------");
                            puts("¡Editorial vinculada éxitosamente!");
                        }
                    }
                }
                //////////////////////////////////////////////////////////////////////////
                puts("-------------------------------------");
                puts("¡Datos del libro cargados con éxito! ");
                puts("-------------------------------------");

                libros[i].vacio = 1;

                system("pause");
                system("cls");
                puts("Cargando...");
                sleep(1);

                //Contador que guarda la sumatoria de todos los códigos ISBN
                //Lo utilizo para asignar códigos ISBN seguidos a cada nueva editorial
                for(int j=0; j<10;j++){
                    c2 = c2 + libros[j].ISBN;
                }
                //Se le asigna el número siguiente a la nueva editorial
                libros[i].ISBN = c2 + 1;
                //Bucle para verificar que el número no está siendo utilizado por otra editorial
                //Si está siendo utilizado usa el siguiente
                for(int k=0; k<10;k++){
                    if(libros[k].ISBN==libros[i].ISBN && k!=i){
                        libros[i].ISBN = libros[i].ISBN + 1;
                    }
                }
                system("cls");
                printf("El ISBN del libro '%s' será: %d\n",libros[i].nombre,libros[i].ISBN);
                puts("----------------------------------------------------");
                system("pause");
                puts("----------------------------------------------------");
                puts("¡Libro cargado con éxito!");
                sleep(1);
                break;
            }
        }
    }


    {//CODE VIEJO
        /*for(int i=0; i<10; i++){
        if(op==0&&biblioteca[i].ISBN==0){
            puts("Ingrese el nombre del libro");
            fflush(stdin);
            gets(biblioteca[i].nombre);
            /*puts("Ingrese el o los autores del libro");
            fflush(stdin);
            gets(biblioteca[i].autor);*/
            /*puts("Ingrese la edicion");
            scanf("%d",&biblioteca[i].edicion);
            puts("Ingrese el tipo de libro");
            fflush(stdin);
            gets(biblioteca[i].tipo);
            puts("Ingrese la cantidad de ejemplares por libro");
            scanf("%d",&biblioteca[i].cantidad_de_ejemplares);
            /*puts("Ingrese la editorial");
            fflush(stdin);
            gets(biblioteca[i].editoral);*/
            /*biblioteca[i].ISBN=i+1;*/
        /*}
        puts("Si usted desea dejar de cargar libros presione 1, sino presione 0");
        scanf("%d",&op);
        while(op<0||op>1){
            printf("ingreso un valor erroneo, reingreselo\n");
            scanf("%d",&op);
        }
    }*/}
}

void buscarLibro(struct libros *libros, struct autor *autor, struct editorial *editorial){
    int c=1,buscador;
    puts("BUSCADOR DE LIBROS\n\n");

    puts("Ingrese el ISNB del libro: ");
    scanf("%d",&buscador);
    while(buscador<1){
        puts("-----------------------------------------");
        puts("No éxiste ese código ISBN en ésta versión");
        puts("-----------------------------------------");
        puts("Ingrese el ISNB del libro: ");
        scanf("%d",&buscador);
    }
    system("cls");
    puts("Cargando...");
    sleep(1);
    for(int i=0;i<10;i++){
        if(buscador==libros[i].ISBN){
            system("cls");
            puts("¡Libro encontrado!");
            puts("------------------");
            system("pause");
            system("cls");
            puts("LIBRO: ");
            printf("Nombre del libro: %s\n",libros[i].nombre);
            printf("Tipo de libro: %s\n",libros[i].tipo);
            printf("Edición del libro: %d\n",libros[i].edicion);
            printf("Cantidad de libros: %d\n",libros[i].cantidad);
            puts("-------------------------------");
            for(int j=0;j<10;j++){
                if(libros[i].ISBNautor==autor[j].ISBN){
                    printf("Autor del libro: %s %s\n",autor[j].nombre,autor[j].apellido);
                    break;
                }
            }
            for(int k=0;k<10;k++){
                if(libros[i].ISBNeditorial==editorial[k].ISBN){
                    printf("Editorial del libro: %s\n",editorial[k].nombre);
                }
            }
            printf("Ejemplares prestados: %d\n",libros[i].ejemplares_prestados);
            puts("-------------------------------");
            system("pause");
            break;
        }
        c = c + 1;
    }
    if(c>=10){
        system("-----------------------------------------------------------");
        puts("No éxiste libro con ese código, intente de nuevo más tarde...");
        system("-----------------------------------------------------------");
        system("pause");
    }
}

void modificarLibro(struct libros *libros, struct autor *autor, struct editorial * editorial){
    int op,op2,opAutor,opEditorial,cantidadLibros;
    int c=1,c2=0,c3=1,c4=1,buscador,eleccion;
    puts("MODIFICADOR DE LIBROS\n\n");

    puts("Ingrese el ISNB del libro: ");
    scanf("%d",&buscador);
    while(buscador<1){
        puts("-----------------------------------------");
        puts("No éxiste ese código ISBN en ésta versión");
        puts("-----------------------------------------");
        puts("Ingrese el ISNB del libro: ");
        scanf("%d",&buscador);
    }
    system("cls");
    puts("Cargando...");
    sleep(1);
    for(int i=0;i<10;i++){
        if(buscador==libros[i].ISBN){
            system("cls");
            puts("¡Libro encontrado!");
            puts("------------------");
            system("pause");
            system("cls");
            puts("¿Qué desea hacer?");
            puts("1. Modificar");
            puts("2. Eliminar");
            puts("3. Volver al menú");
            puts("-------------------------");
            printf("Elegir opción: ");
            scanf("%d",&eleccion);
            while(eleccion>3 || eleccion<1){
                puts("------------------------------------");
                puts("Opción invalida, intente de nuevo...");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&eleccion);
            }
            switch(eleccion){
                case 1:
                    system("cls");
                    fflush(stdin);
                    printf("Nombre del libro: ");
                    gets(libros[i].nombre);
                    puts("---------------------------------------");
                    fflush(stdin);
                    printf("Tipo de libro: ");
                    gets(libros[i].tipo);
                    puts("---------------------------------------");
                    printf("Edición del libro: ");
                    scanf("%d",&libros[i].edicion);
                    puts("---------------------------------------");
                    printf("Cantidad del libro %s: ",libros[i].nombre);
                    scanf("%d",&cantidadLibros);
                    while(cantidadLibros>10||cantidadLibros<0){
                        puts("---------------------------------------------------------");
                        puts("Cantidad invalida solo se puede agregar entre 0-10 libros");
                        puts("---------------------------------------------------------");
                        printf("Cantidad del libro %s: ",libros[i].nombre);
                        scanf("%d",&cantidadLibros);
                    }
                    libros[i].cantidad=cantidadLibros;
                    puts("---------------------------------------");
                    //////////////////////////////////////////////////////////////////////////
                    //Elección de autor
                    puts("Elija el autor del libro: ");
                    for(int j=0;j<10;j++){
                        if(autor[j].vacio==1){
                            printf("%d. %s %s\n",c3,autor[j].nombre,autor[j].apellido);
                            c3= c3 +1;
                        }
                    }
                    printf("%d. Ninguno\n",c3);
                    puts("---------------");
                    printf("Elegir opción: ");
                    scanf("%d",&opAutor);
                    while(opAutor>c3 || opAutor<1){
                        puts("------------------------------------");
                        puts("Opción invalida, intente de nuevo...");
                        puts("------------------------------------");
                        printf("Elegir opción: ");
                        scanf("%d",&opAutor);
                    }
                    if(opAutor==c3){
                        puts("---------------------------------------------------");
                        puts("Es necesario agregar un autor al libro...");
                        puts("Si no lo encontró en la lista, agreguelo en el menú");
                        puts("---------------------------------------------------");
                        system("pause");
                        return 0;
                    }else{
                        for(int j=0;j<10;j++){
                            if((opAutor-1)==j){
                            libros[i].ISBNautor=autor[j].ISBN;
                            puts("------------------------------------");
                            puts("¡Autor vinculado éxitosamente!");
                            puts("------------------------------------");
                            puts("¿Desea agregar otro autor?");
                            puts("1. Si");
                            puts("2. No");
                            puts("------------");
                            printf("Opción: ");
                            scanf("%d",&op2);
                            while(op>2 || op<1){
                                puts("------------------------------------");
                                puts("Opción invalida, intente de nuevo...");
                                puts("------------------------------------");
                                printf("Opción: ");
                                scanf("%d",&op2);
                            }
                            switch(op2){
                                case 1:
                                    puts("Elija el autor del libro: ");
                                    for(int j=0;j<10;j++){
                                        if(autor[j].vacio==1){
                                            printf("%d. %s %s\n",c3,autor[j].nombre,autor[j].apellido);
                                            c3= c3 +1;
                                        }
                                    }
                                    printf("%d. Ninguno\n",c3);
                                    puts("---------------");
                                    printf("Elegir opción: ");
                                    scanf("%d",&opAutor);
                                    while(opAutor>c3 || opAutor<1){
                                        puts("------------------------------------");
                                        puts("Opción invalida, intente de nuevo...");
                                        puts("------------------------------------");
                                        printf("Elegir opción: ");
                                        scanf("%d",&opAutor);
                                    }
                                    if(opAutor==c){
                                        puts("-------------------------------");
                                        puts("¡El libro tendrá un solo autor!");
                                        puts("-------------------------------");
                                        system("pause");
                                        break;
                                    }else{
                                        for(int j=0;j<10;j++){
                                            if((opAutor-1)==j){
                                                libros[i].ISBNautor=autor[j].ISBN;
                                                puts("------------------------------");
                                                puts("¡Autor vinculado éxitosamente!");
                                                puts("------------------------------");
                                                system("pause");
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                    puts("-------------------------------");
                                    puts("¡El libro tendrá un solo autor!");
                                    puts("-------------------------------");
                                    system("pause");
                                    break;
                                }
                            }
                        }
                    }
                    //////////////////////////////////////////////////////////////////////////
                    //Elección de editorial
                    puts("---------------------------------------");
                    puts("Elija la editorial del libro: ");
                    for(int j=0;j<10;j++){
                        if(editorial[j].vacio==1){
                           printf("%d. %s\n",c4,editorial[j].nombre);
                            c4= c4 +1;
                        }
                    }
                    printf("%d. Ninguno\n",c4);
                    puts("---------------");
                    printf("Elegir opción: ");
                    scanf("%d",&opEditorial);
                    while(opEditorial>c4 || opEditorial<1){
                        puts("------------------------------------");
                        puts("Opción invalida, intente de nuevo...");
                        puts("------------------------------------");
                        printf("Elegir opción: ");
                        scanf("%d",&opEditorial);
                    }
                    if(opEditorial==c4){
                        puts("---------------------------------------------------");
                        puts("Es necesario agregar una editorial al libro...");
                        puts("Si no lo encontró en la lista, agreguelo en el menú");
                        puts("---------------------------------------------------");
                        return 0;
                    }else{
                        for(int j=0;j<10;j++){
                            if((opEditorial-1)==j){
                                libros[i].ISBNeditorial=editorial[j].ISBN;
                                puts("------------------------------------");
                                puts("¡Editorial vinculada éxitosamente!");
                            }
                        }
                    }
                    //////////////////////////////////////////////////////////////////////////
                    puts("-------------------------------------");
                    puts("¡Datos del libro cargados con éxito! ");
                    puts("-------------------------------------");
                    puts("¡Libro cargado con éxito!");
                    puts("-------------------------------------");
                    system("pause");

                    libros[i].vacio = 1;

                    sleep(1);
                    break;
                case 2:
                    system("cls");
                    puts("Cargando...");
                    sleep(1);
                    system("cls");

                    libros[i].ISBN=0;
                    libros[i].ISBNeditorial=0;
                    libros[i].ISBNautor=0;
                    strcpy(libros[i].nombre,"-");
                    libros[i].edicion=0;
                    strcpy(libros[i].tipo,"-");
                    libros[i].cantidad=0;
                    libros[i].ejemplares_prestados=0;
                    libros[i].vacio = 0;

                    puts("---------------------------------------");
                    puts("¡Datos del libro eliminados con éxito! ");
                    puts("---------------------------------------");
                    system("pause");
                    break;
                case 3:
                    sleep(1);
                    break;
            }
            break;
        }
        c = c + 1;
    }
    if(c>=10){
        system("-----------------------------------------------------------");
        puts("No éxiste libro con ese código, intente de nuevo más tarde...");
        system("-----------------------------------------------------------");
    }
}

void mostrarInformacion(struct libros *libros, struct autor *autor, struct editorial * editorial){
    int op,op2,op3;
    int c=1,c2=1,c3=1,c4=1; //contadores

    puts("PANEL DE INFORMACIÓN: \n");
    puts("Elija una opción:");
    puts("1. Mostar libros por Autor");
    puts("2. Ver autores de un libro");
    puts("3. Libros ordenados por edición");
    puts("4. Salir");
    puts("----------------------------");
    printf("Elegir opción: ");
    scanf("%d",&op);
    while(op>1 || op<4){
        puts("------------------------------------");
        puts("Opción invalida, intente de nuevo...");
        puts("------------------------------------");
        printf("Elegir opción: ");
        scanf("%d",&op);
    }
    switch(op){
        case 1:
            system("cls");
            puts("AUTORES DISPONIBLES: ");
            for(int i=0;i<10;i++){
                if(autor[i].vacio==1){
                    printf("%d. %s %s\n",c,autor[i].nombre,autor[i].apellido);
                    c = c + 1;
                }
            }
            printf("%d. Salir\n",c);
            puts("-----------------");
            printf("Elegir opción: ");
            scanf("%d",&op2);
            while(op2>c || op2<1){
                puts("------------------------------------");
                puts("Opción invalida, intente de nuevo...");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&op2);
            }
            if(op2==c){
                system("cls");
                sleep(1);
                return 0;
            }else{
                for(int j=0;j<10;j++){
                    if((op2-1)==j){
                        system("cls");
                        puts("LIBROS DEL AUTOR");
                        printf("Nombre del autor: %s %s\n",autor[j].nombre,autor[j].apellido);
                        puts("Libros asociados: ");
                        for(int k=0;k<10;k++){
                            if(autor[j].ISBN==libros[k].ISBNautor){
                                printf("- %s\n",libros[k].nombre);
                            }
                            c2 = c2 + 1;
                        }
                        if(c2>=10){
                            puts("--------------------------------------------------");
                            puts("¡El autor seleccionado no tiene libros vinculados!");
                            puts("--------------------------------------------------");
                            system("pause");
                        }else{
                            puts("----------------------------------");
                            puts("¡Información cargada éxitosamente!");
                            puts("----------------------------------");
                            system("pause");
                        }
                    }
                }
            }
            break;
        case 2:
            system("cls");
            puts("LIBROS DISPONIBLES: ");
            for(int i=0;i<10;i++){
                if(libros[i].vacio==1){
                    printf("%d. %s %s\n",c3,libros[i].nombre);
                    c3 = c3 + 1;
                }
            }
            printf("%d. Salir\n",c3);
            puts("-----------------");
            printf("Elegir opción: ");
            scanf("%d",&op3);
            while(op3>c3 || op3<1){
                puts("------------------------------------");
                puts("Opción invalida, intente de nuevo...");
                puts("------------------------------------");
                printf("Elegir opción: ");
                scanf("%d",&op3);
            }
            if(op3==c){
                system("cls");
                sleep(1);
                return 0;
            }else{
                for(int j=0;j<10;j++){
                    if((op3-1)==j){
                        system("cls");
                        puts("AUTORES RELACIONADOS");
                        for(int k=0;k<10;k++){
                            if(libros[j].ISBNautor==autor[k].ISBN){
                                printf("Nombre: %s %s\n",autor[j].nombre,autor[j].apellido);
                            }
                            c2 = c2 + 1;
                        }
                        if(c2>=10){
                            puts("-----------------------------------------------------");
                            puts("¡El libro seleccionado no tiene autores relacionados!");
                            puts("-----------------------------------------------------");
                            system("pause");
                        }else{
                            puts("----------------------------------");
                            puts("¡Información cargada éxitosamente!");
                            puts("----------------------------------");
                            system("pause");
                        }
                    }
                }
            }
            break;
        case 3:
            system("cls");
            puts("Disponible en próximas versiones...");
            puts("-----------------------------------");
            system("pause");
            break;
        case 4:
            system("cls");
            sleep(1);
            return 0;
            break;
    }
}

int main()
{
    int menu,salir;

    ///BANDERAS
    int b1=0;  //Verifica que hayas cargado un libro
    int b2=0; //Verifica que hayas cargado un autor
    int b3=0; //Verifica que hayas cargado una editorial
    int b8=0; //Verifica que hayas leído las restricciones
    ///
    struct libros libros[10];
    struct autor autor[10];
    struct editorial editorial[10];
    struct prestamo prestamo[10];

    setlocale(LC_ALL, "");
    srand(time(NULL));

    inicializacion(libros,autor,editorial,prestamo);

    do{
        system("cls");
        puts("BIBLIOTECA v1.0\n");
        puts("¿Qué desea hacer?\n");
        puts("Menú: ");
        puts("1. Cargar libro");
        puts("2. Cargar autor");
        puts("3. Cargar editorial");
        puts("4. Buscar libro");
        puts("5. Modificar/Eliminar libro");
        puts("6. Ver prestamos y devoluciones");
        puts("7. Ver informacion de los libros");
        puts("8. Restricciones del programa");
        puts("9. Salir del sistema");
        puts("---------------------------------------");
        printf("Opción: ");
        scanf("%d",&menu);

        while(menu<1||menu>9){
            printf("ingreso un valor erroneo, reingreselo\n");
            scanf("%d",&menu);
        }

        switch(menu){
            case 1:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de cargar un libro!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else if(b2!=1){
                    system("cls");
                    puts("¡Debe cargar un autor antes de cargar un libro!");
                    puts("-----------------------------------------------");
                }else{
                    system("cls");
                    cargarLibro(libros,autor,editorial);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                    b1=1;
                }
                break;
            case 2:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de cargar un autor!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else{
                    system("cls");
                    cargarAutor(autor);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                    b2=1;
                }
                break;
            case 3:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else{
                    system("cls");
                    cargarEditorial(editorial);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                    b3=1;
                }
                break;
            case 4:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de buscar un libro!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else if(b2!=1){
                    system("cls");
                    puts("¡Debe cargar un autor antes de buscar un libro!");
                    puts("-----------------------------------------------");
                }else{
                    system("cls");
                    buscarLibro(libros,autor,editorial);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                }
                break;
            case 5:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de modificar un libro!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else if(b2!=1){
                    system("cls");
                    puts("¡Debe cargar un autor antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else if(b1!=1){
                    system("cls");
                    puts("¡Debe cargar un libro antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else{
                    system("cls");
                    modificarLibro(libros,autor,editorial);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                }
                break;
            case 6:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de modificar un libro!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else if(b2!=1){
                    system("cls");
                    puts("¡Debe cargar un autor antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else if(b1!=1){
                    system("cls");
                    puts("¡Debe cargar un libro antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else{
                    system("cls");
                    puts("En proceso...");
                    puts("---------------------------------------");
                    system("pause");
                }
                break;
            case 7:
                if(b8!=1){
                    system("cls");
                    puts("¡Revise las restricciones del programa antes!");
                    puts("---------------------------------------------");
                    system("pause");
                }else if(b3!=1){
                    system("cls");
                    puts("¡Debe cargar una editorial antes de modificar un libro!");
                    puts("----------------------------------------------------");
                    system("pause");
                }else if(b2!=1){
                    system("cls");
                    puts("¡Debe cargar un autor antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else if(b1!=1){
                    system("cls");
                    puts("¡Debe cargar un libro antes de modificar un libro!");
                    puts("-----------------------------------------------");
                }else{
                    system("cls");
                    mostrarInformacion(libros,autor,editorial);
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(1);
                }
                break;
            case 8:
                system("cls");
                    puts("RESTRICCIÓNES: \n");
                    puts("1. En esta versión solo se puede agregar 10 libros");
                    puts("2. En esta versión solo se puede agregar 10 autores");
                    puts("3. En esta versión solo se puede agregar 10 editoriales");
                    puts("4. En esta versión solo se puede agregar 10 prestamos a distintas personas");
                    puts("\nCuando le pidan ingresar el dia de una fecha: ");
                    puts("5. Si el día que va a ingresar es menor a la decena (10) no le agregue un cero adelante de la unidad (1-9)");
                    puts("6. No hay forma de verificar que la nacionalidad del autor sea correcta");
                    puts("7. Como MÁXIMO un libro puede tener dos autores");
                    puts("-------------------------------------------------------------------");
                    b8=1;
                    system("pause");
                break;
            case 9:
                system("cls");
                puts("¿Desea salir del programa?");
                puts("1. Si");
                puts("2. No");
                puts("--------------------------");
                printf("Opción: ");
                scanf("%d",&salir);
                while(salir>2 || salir<1){
                    puts("------------------------------------");
                    puts("Opción invalida, intente de nuevo...");
                    puts("------------------------------------");
                    printf("Opción: ");
                    scanf("%d",&salir);
                }
                switch(salir){
                    case 1:
                        system("cls");
                        puts("¿Nos vemos pronto!");
                        puts("------------------");
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        puts("Toque una tecla para volver al menú");
                        puts("-----------------------------------");
                        system("pause");
                        menu=0;
                        break;
                }
                break;

        }

    }while(menu!=9);

    return 0;
}
