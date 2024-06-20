#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PACIENTES_ARCH "archivoPacientes.dat"
#define SANOS_ARCH "pacientesSanos.dat"
#define ENFERMOS_ARCH "pacientesEnf.dat"
#define DIM 30

typedef struct{
        int id;
        char nombre[30];
        char apellido[30];
        char dni[12];
        char sexo;
        float temperatura;

    }stPaciente;

stPaciente cargaUnPaciente();
void muestraUnPaciente(stPaciente p);
void cargaArchivoPacientes(char nombre_archi[]);
int buscaPorDni(char nombre_archivo[], int dato);
void muestraArchPorSexo(char nombre_Archivo[], char sexo);
int archivoToArrays(char nombre_archivo[],stPaciente Array[],int validos, char genero);
int cargaArray(stPaciente a[],int v, stPaciente dato);
int devuelvePacientes(char nombre_archivo[]);
void muestraArrayRecursivo(stPaciente a[], int v, int i);
void muestraArchivo(char nombre_archi[]);
void arrayToArchiSanos(char nombre_archivoSano[],char nombre_archivoEnf[], stPaciente a[], int v, float temperatura);

int main()
{
    stPaciente masc[DIM];
    stPaciente fem[DIM];
    int vMasc=0;
    int vFem=0;

   // cargaArchivoPacientes(PACIENTES_ARCH);
    muestraArchivo(PACIENTES_ARCH);
    printf(" \n el de dni se encuentra? %d\n",buscaPorDni(PACIENTES_ARCH,2341231));
    printf(" \n -------------------------------- \n");
    printf(" \n Muestra paciente por sexo \n");
    muestraArchPorSexo(PACIENTES_ARCH,'f');

    vMasc=archivoToArrays(PACIENTES_ARCH,masc,vMasc,'m');
    vFem=archivoToArrays(PACIENTES_ARCH,fem,vFem,'f');
    printf("\nmuestra array recursivo Masc-\n\n");
      //muestraarrayComun(masc,vMasc);
    muestraArrayRecursivo(masc,vMasc,0);

    printf("-------------------------------");
    printf("\nmuestra array recursivo fems-\n\n");
   //muestraarrayComun(fem,vFem);
     muestraArrayRecursivo(fem,vFem,0);
    printf("cantidad de pacientes= %d",devuelvePacientes(PACIENTES_ARCH));

    printf("\n\n---------------ARCHIVO SANOS----------------\n\n");
    arrayToArchiSanos(SANOS_ARCH,ENFERMOS_ARCH,masc,vMasc,37.0);
    muestraArchivo(SANOS_ARCH);

    printf("\n\n---------------ARCHIVO enfermos----------------\n\n");
    muestraArchivo(ENFERMOS_ARCH);

    return 0;
}

stPaciente cargaUnPaciente(){
    system("cls");
    stPaciente paciente;
    printf("ingrese el nombre del paciente: \n");
    fflush(stdin);
    gets(paciente.nombre);
    printf("ingrese el apellido del paciente: \n");
    fflush(stdin);
    gets(paciente.apellido);
    printf("ingrese el dni del paciente: \n");
    fflush(stdin);
    gets(paciente.dni);
    printf("ingrese el sexo del paciente: \n");
    fflush(stdin);
    scanf("%c",&paciente.sexo);
    printf("ingrese temperatura del paciente: \n");
    scanf("%f",&paciente.temperatura);

return paciente;
}

void muestraUnPaciente(stPaciente p){
    printf("--------------------------------------\n");
    printf("Nombre del paciente: %s\n",p.nombre);
    printf("Apellido del paciente: %s \n",p.apellido);
    printf("Dni del paciente: %s \n",p.dni);
    printf("Sexo del paciente: %c \n",p.sexo);
    printf("Temperatura del paciente: %.2f \n",p.temperatura);
    printf("ID del paciente: %d \n",p.id);

}

void cargaArchivoPacientes(char nombre_archi[]){
    char opcion='s';
    int noEsta=0;
    stPaciente p;
    FILE* archi=fopen(nombre_archi,"ab");
    if(archi){
        while(opcion=='s'){
            p=cargaUnPaciente();
            p.id=devuelvePacientes(archi)+1;
            noEsta=buscaPorDni(nombre_archi,p.dni);
            if(noEsta){
                    if(p.temperatura<=40 && p.temperatura>=35){
                        muestraUnPaciente(p);
                        system("pause");
                        fwrite(&p,sizeof(stPaciente),1,archi);
                    }else{
                        printf("Temperatura invalida, intente de nuevo\n");
                    }

            }else{
                printf("dni ya existe actualmente");
                system("pause");
                system("cls");
            }
            printf("Desea seguir cargando? s para continuar o cualquier tecla para salir\n");
            fflush(stdin);
            scanf("%c",&opcion);
        }
        fclose(archi);
    }
}

void muestraArchivo(char nombre_archi[]){
    stPaciente a;
    FILE *archi=fopen(nombre_archi,"rb");
    if(archi){
        while(fread(&a,sizeof(stPaciente),1,archi)>0){
            muestraUnPaciente(a);
        }
      fclose(archi);
    }
}


int buscaPorDni(char nombre_archivo[], int dato){
    stPaciente p;
    int flag=1;
    FILE*archi=fopen(nombre_archivo,"rb");
    if(archi){
        while(fread(&p,sizeof(stPaciente),1,archi)>0 && flag!=1){
            if(p.dni==dato){
                    flag=0;
            }
        }
        fclose(archi);
    }
    return flag;
}

void muestraArchPorSexo(char nombre_Archivo[], char sexo){
    stPaciente p;
    FILE* archi=fopen(nombre_Archivo,"rb");
    if(archi){
        while(fread(&p,sizeof(stPaciente),1,archi)>0){
            if(p.sexo==sexo){
                muestraUnPaciente(p);
            }
        }
        fclose(archi);
    }
}

int archivoToArrays(char nombre_archivo[],stPaciente Array[],int validos, char genero){
    stPaciente p;

    FILE* archi=fopen(nombre_archivo,"rb");
    if(archi){
        while(fread(&p,sizeof(stPaciente),1,archi)>0){
            if(p.sexo==genero){
                Array[validos]=p;
                validos++;
            }
        }
        fclose(archi);
    }
    return validos;
}

int devuelvePacientes(char nombre_archivo[]){
    int cantPacientes;
    FILE* archi=fopen(nombre_archivo,"rb");
    if(archi){
        fseek(archi,0,SEEK_END);
        cantPacientes=ftell(archi)/sizeof(stPaciente);
        fclose(archi);
    }
return cantPacientes;
}

void arrayToArchiSanos(char nombre_archivoSano[],char nombre_archivoEnf[], stPaciente a[], int v, float temperatura){

    FILE *sanosArchi=fopen(nombre_archivoSano,"ab");
    FILE *enfArchi=fopen(nombre_archivoEnf,"ab");
    if(sanosArchi && enfArchi){
        for(int i=0;i<v;i++){
            if(a[i].temperatura>temperatura){
                fwrite(&a[i],sizeof(stPaciente),1,enfArchi);
            }else{
                fwrite(&a[i],sizeof(stPaciente),1,sanosArchi);
            }
        }
        fclose(sanosArchi);
        fclose(enfArchi);
    }
}

void muestraArrayRecursivo(stPaciente a[], int v, int i){
    if(i<v){

        muestraArrayRecursivo(a,v,i+1);
        muestraUnPaciente(a[i]);
    }
}

float muestraPorcentajeSanos(int totalRegistros, int totalSanos){
    float promedioSanos=totalRegistros/totalSanos;
    return promedioSanos;
}

float muestraPorcentajeEnfermos(int totalRegistros, int totalEnf){
    float promedioEnfermo=totalRegistros/totalEnf;
    return promedioEnfermo;
}

void muestraarrayComun(stPaciente a[],int v){
    for(int i=0; i<v; i++){
       muestraUnPaciente(a[i]);
    }
}
