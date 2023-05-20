#include <iostream>
#include "../includes/programa.hpp"
#include <time.h>

//lectura del fichero con los datos del problema a resolver

int main(int argc,char *argv[]){

    //tomamos la semilla pasada como parametro, y a partir de la cual se generará un generador 
    unsigned int semilla=0;
    if(argc==1){
        //le hemos pasado una determinada semilla
        cout<<"RECUERDE QUE DEBE PASAR COMO PARÁMETRO LA SEMILLA A UTILIZAR...\n";
        exit(-1);
    }

    semilla=atoi(argv[1]);
    //cout<<"Semilla utilizada ---> "<<semilla<<"\n";

    

    //-------------- LECTURA DE FICHEROS ---------------
    
    vector<string> archivos;
    archivos.push_back("../BIN/chr22a.dat");
    archivos.push_back("../BIN/chr22b.dat");
    archivos.push_back("../BIN/chr25a.dat");
    archivos.push_back("../BIN/esc128.dat"); //repasar
    archivos.push_back("../BIN/had20.dat");
    archivos.push_back("../BIN/lipa60b.dat");
    archivos.push_back("../BIN/lipa80b.dat");
    archivos.push_back("../BIN/nug28.dat");
    archivos.push_back("../BIN/sko81.dat");
    archivos.push_back("../BIN/sko90.dat");
    archivos.push_back("../BIN/sko100a.dat");
    archivos.push_back("../BIN/sko100f.dat");
    archivos.push_back("../BIN/tai100a.dat");
    archivos.push_back("../BIN/tai100b.dat");
    archivos.push_back("../BIN/tai150b.dat");
    archivos.push_back("../BIN/tai256c.dat"); //repasar
    archivos.push_back("../BIN/tho40.dat");
    archivos.push_back("../BIN/tho150.dat");
    archivos.push_back("../BIN/wil50.dat");
    archivos.push_back("../BIN/wil100.dat");
    
    Matrices salida;
    
    //vector<int> solucion;
    clock_t inicio,fin;
    double tiempo_total;
    /*
    for(int i=0;i<archivos.size();i++){
        //para cada archivo...
        //1. LEEMOS LOS DATOS
        salida=lectura_datos(archivos[i]);
        //2. EJECUTAMOS GREEDY
        inicio=clock();
        solucion=algoritmo_greedy(salida.matriz_flujo,salida.matriz_distancia);
        fin=clock();
        tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

        cout<<"\n// Nombre del archivo de datos --> "<<archivos[i]<<" //\n";
        cout<<"\nUSANDO ALGORITMO GREEDY...";
        cout<<"\n-Coste de la solucion obtenida:"<<fitness(solucion,salida.matriz_flujo,salida.matriz_distancia);
        cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total;

        //3. EJECUTAMOS BUSQUEDA LOCAL PRIMERO EL MEJOR
        inicio=clock();
        solucion=busqueda_local(salida.matriz_flujo,salida.matriz_distancia,semilla);
        fin=clock();
        tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

        cout<<"\n\nUSANDO ALGORITMO DE BUSQUEDA LOCAL PRIMERO EL MEJOR...";
        cout<<"\n-Coste de la solucion obtenida:"<<fitness(solucion,salida.matriz_flujo,salida.matriz_distancia);
        cout<<"\n-Tiempo necesario para obtener la solucion (milisegudos):"<<tiempo_total<<"\n";

    }
    */

   srand(semilla);
   
   pair<vector<int>,int> solucion;
   vector<string> operadores_cruce;
   operadores_cruce.push_back("OPERADOR BASADO EN POSICIÓN");
   operadores_cruce.push_back("OPERADOR PMX");
   for(int i=0;i<archivos.size();i++){
        //para cada archivo...
        //1. LEEMOS LOS DATOS
        salida=lectura_datos(archivos[i]);
        cout<<"\n// Nombre del archivo de datos --> "<<archivos[i]<<" //\n";
        
        //2. EJECUTAMOS GENERACIONAL
        for(int j=0;j<2;j++){
            inicio=clock();
            solucion=AGG(salida.matriz_flujo[0].size(),50,j,0.7,0.1,salida.matriz_flujo,salida.matriz_distancia);
            fin=clock();
            tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

            cout<<"\nUSANDO AGG CON "<<operadores_cruce[j]<<"...";
            cout<<"\n-Coste de la solucion obtenida:"<<solucion.second;
            cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total<<"\n";
        }
        //3. EJECUTAMOS ESTACIONARIO
        for(int j=0;j<2;j++){
            inicio=clock();
            solucion=AGE(salida.matriz_flujo[0].size(),50,j,0.1,salida.matriz_flujo,salida.matriz_distancia);
            fin=clock();
            tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

            cout<<"\nUSANDO AGE CON "<<operadores_cruce[j]<<"...";
            cout<<"\n-Coste de la solucion obtenida:"<<solucion.second;
            cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total<<"\n";
        }

        //4. EJECUTAMOS MEMETICOS (tres versiones) usando el operador PMX, ya que nos ofrecio mejores resultados al usar AGG
       
        //PRIMERA VERSION
        inicio=clock();
        solucion=memeticos(salida.matriz_flujo[0].size(),50,1,0.7,0.1,1,salida.matriz_flujo,salida.matriz_distancia);
        fin=clock();
        tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

        cout<<"\nUSANDO AM_All CON "<<operadores_cruce[1]<<"...";
        cout<<"\n-Coste de la solucion obtenida:"<<solucion.second;
        cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total<<"\n";

        //SEGUNDA VERSION
        inicio=clock();
        solucion=memeticos(salida.matriz_flujo[0].size(),50,1,0.7,0.1,2,salida.matriz_flujo,salida.matriz_distancia);
        fin=clock();
        tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

        cout<<"\nUSANDO AM_Rand CON "<<operadores_cruce[1]<<"...";
        cout<<"\n-Coste de la solucion obtenida:"<<solucion.second;
        cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total<<"\n";

        //TERCERA VERSION
        inicio=clock();
        solucion=memeticos(salida.matriz_flujo[0].size(),50,1,0.7,0.1,3,salida.matriz_flujo,salida.matriz_distancia);
        fin=clock();
        tiempo_total=((fin - inicio) / (double) CLOCKS_PER_SEC)* 1000;

        cout<<"\nUSANDO AM_Best CON "<<operadores_cruce[1]<<"...";
        cout<<"\n-Coste de la solucion obtenida:"<<solucion.second;
        cout<<"\n-Tiempo necesario para obtener la solucion (milisegundos):"<<tiempo_total<<"\n";
        


    }

    return 0;
}