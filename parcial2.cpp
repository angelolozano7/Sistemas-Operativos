//PARCIAL 2 SISTEMAS OPERATIVOS
//INTEGRANTES:
//JUAN DAVID AYCARDI ARIZA
//ANGELO GIUSEPPE LOZANO BERRUECOS


#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstdlib>
#include <queue>
using namespace std;

//Estructura de los Procesos

struct Proceso{
    int id;
    int arrivalT;
    int burstT;
    int auxBurstT;
    int priority;
    int stop = -1;
    int waitingTime = 0;
    int responseTime = 0;
    double turnArroundTime = 0;
    double contextTime = 0;

    Proceso(){}

    Proceso(int i, int a, int b, int p){
        id = i;
        arrivalT = a;
        burstT = b;
        priority = p;
        auxBurstT = b;
    }
    bool operator<( const Proceso& n) const{
        return arrivalT < n.arrivalT;
    }
};


//Función de comparación para la cola de prioridad

struct Compare{
    bool operator()(Proceso &a, Proceso &b){
        return a.priority < b.priority;
    }
};

//Algoritmo de Scheduling FCFS

int firstCome(vector<Proceso> procesos){
    int n, avwt = 0, avtat = 0, i, j;
    vector<int> wt;
    vector<int> tat;
    n = procesos.size();
    
    wt.push_back(0);    //waiting time para el primer proceso es 0

    cout << endl;
    cout << "FCFS" << endl;
    cout << endl;
    
    //Cálculo de los diferentes Waiting Time

    int t = procesos[0].burstT;
    
    int wait = 0;

    for(i = 1; i < n; i++){
        
        if(t > procesos[i].arrivalT){
            wait =  t - procesos[i].arrivalT;          
        }
        else{
            wait = 0;
        }

        t += procesos[i].burstT;
        wt.push_back(wait);
    }

    //Diagrama de Gantt

    int acumulado = 0;

    cout << "Gantt Chart" << endl;
    cout << endl;

    for(i = 0; i < procesos.size(); ++i){
        for(j = 0; j < procesos[i].burstT; j++){
            cout << " |s:" << acumulado++ << " p" << procesos[i].id << "| ";      
        }
    }

    cout << endl;
    cout << endl;

    cout << "Tabla Cálculos de Tiempos" << endl;
     
    cout << "\nID Process\tBurst Time\tWaiting Time\tTurnaround Time\tResponse time";
 
    //Cálculo de los diferentes Turn Arround Time

    for(i = 0; i < n; i++){
        tat.push_back(procesos[i].burstT + wt[i]);
        avwt += wt[i];
        avtat += tat[i];
        cout << "\nP[" << procesos[i].id << "]" << "\t\t" << procesos[i].burstT << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t" << wt[i];
    }
    
    //Cálculo de tiempos promedios

    avwt /= i;
    avtat /= i;
    cout << "\n\nAverage Waiting Time:" << avwt;
    cout << "\nAverage Turnaround Time:" << avtat;
    cout << "\nAverage Response Time:" << avwt;
    cout << endl;

    return 0;
}

//Comparador por trabajo más corto

bool comp_Job(const Proceso &a, const Proceso &b){
    return a.burstT < b.burstT;
}

//Algoritmo de SJF

int shortestJob(vector<Proceso> procesos){
    int n, avwt = 0, avtat = 0, i, j;
    vector<int> wt;
    vector<int> tat;
    n = procesos.size();
    
    sort(procesos.begin(),procesos.end(),&comp_Job);
    
    wt.push_back(0);    //waiting time para el primer proceso es 0

    cout << endl;
    cout << "SJF" << endl;
    cout << endl;
    
    //Cálculo de los diferentes waiting time

    int t = procesos[0].burstT;
    int wait = 0;

    for(i = 1; i < n; i++){

        if(t > procesos[i].arrivalT){
            wait =  t - procesos[i].arrivalT;          
        }
        else{
            wait = 0;
        }

        t += procesos[i].burstT;
        wt.push_back(wait);
    }

    //Diagrama de Gantt

    cout << "Gantt Chart" << endl;
    cout << endl;

    int acumulado = 0;

    for(i = 0; i < procesos.size(); ++i){
        for(j = 0; j < procesos[i].burstT; j++){
            cout << " |s:" << acumulado++ << " p" << procesos[i].id << "| ";      
        }
    }

    cout << endl;
    cout << endl;

    cout << "Tabla Cálculos de Tiempos" << endl;

 
    cout << "\nID Process\tBurst Time\tWaiting Time\tTurnaround Time\tResponse time";
 
    //Cálculo de los diferentes Turn Arround Time
    for(i = 0; i < n; i++){
        tat.push_back(procesos[i].burstT + wt[i]);
        avwt += wt[i];
        avtat += tat[i];
        cout << "\nP[" << procesos[i].id << "]" << "\t\t" << procesos[i].burstT << "\t\t" << wt[i] << "\t\t" << tat[i] << "\t\t" << wt[i];
    }

    //Cálculo de tiempos promedios
 
    avwt /= i;
    avtat /= i;
    cout << "\n\nAverage Waiting Time:" << avwt;
    cout << "\nAverage Turnaround Time:" << avtat;
    cout << "\nAverage Response Time: " << avwt;
    cout << endl;
 
    return 0;
}

//Algoritmo de Scheduling Priority

int priority(vector<Proceso> procesos, double contextTime){

    int n, i, j, finished = 0;
    double avwt = 0, avtat = 0;

    priority_queue<Proceso, vector<Proceso>, Compare> prioridad;
    vector<Proceso> finalizados;
        
    vector<int> wt;
    vector<int> tat;
    n = procesos.size();
        
    int actualTime = 0; //Simulador de conteo de tiempo real
    Proceso actual;


    //Se ponen en la cola de prioridad todos los procesos que hayan llegado en el segundo 0

    for(i = 0; i < n; i++){
        if(procesos[i].arrivalT == actualTime){
            prioridad.push(procesos[i]);
        }
    }

    actual = prioridad.top();
    prioridad.pop();

    cout << endl;
    cout << "PRIORITY" << endl;
    cout << endl;

    cout << "Gantt Chart" << endl;
    cout << endl;

    //Ciclo que finaliza cuando todos los procesos hayan terminado

    while(finished < n){

        actualTime++;  
        cout << " |s:" << actualTime << " p" << actual.id << "| ";  //Construcción del diagrama de Gantt
        actual.burstT -= 1;
        
        //Se ponen en la cola de prioridad todos los procesos que hayan llegado en el actualTime

        for(i = 0; i < n; i++){
            if(procesos[i].arrivalT == actualTime){
                prioridad.push(procesos[i]);
            }
        }

        //Verificación de finalización de un proceso

        if(actual.burstT == 0){
            finished += 1;
            actual.turnArroundTime = (actualTime - actual.arrivalT) + actual.contextTime;
            finalizados.push_back(actual);
            if(!prioridad.empty()){
                actual = prioridad.top();
                prioridad.pop();

                //Aumento del waiting time en caso de que el próximo proceso que se toma hubiera sido detenido anteriormente

                if(actual.stop != -1){
                    actual.waitingTime += actualTime - actual.stop;
                }
                else{
                    actual.responseTime = actualTime - actual.arrivalT;
                    if(actual.arrivalT < actualTime){
                        actual.waitingTime += actualTime - actual.arrivalT;
                    }  
                }
            }
        }
        else{
            if(!prioridad.empty() && prioridad.top().priority > actual.priority){

                //Suspendión de un proceso que se está ejecutando para dar paso a uno de mayor prioridad

                actual.contextTime += contextTime;
                actual.stop = actualTime;
                prioridad.push(actual);
                actual = prioridad.top();
                prioridad.pop();

                //Aumento del waiting time en caso de que el próximo proceso que se toma hubiera sido detenido anteriormente

                if(actual.stop != -1){
                    actual.waitingTime += actualTime - actual.stop;
                }
                else{
                    actual.responseTime = actualTime - actual.arrivalT;
                    if(actual.arrivalT < actualTime){
                        actual.waitingTime += actualTime - actual.arrivalT;
                    }  
                }
            }
        }
    }

    cout << endl;
    cout << endl;    

    cout << "Tabla Cálculos de Tiempos" << endl;
 
    cout << "\nID Process\tBurst Time\tWaiting Time\tTurnaround Time\tResponse time";
 
    
    int avrt = 0;

    for(i = 0; i < n; i++){

        avwt += finalizados[i].waitingTime + finalizados[i].contextTime;
        avtat += finalizados[i].turnArroundTime;
        avrt += finalizados[i].responseTime;
        cout << "\nP[" << finalizados[i].id << "]" << "\t\t" << finalizados[i].auxBurstT << "\t\t" << finalizados[i].waitingTime + finalizados[i].contextTime << "\t\t" << finalizados[i].turnArroundTime << "\t\t" << finalizados[i].responseTime;
    }

    //Cálculo de tiempos promedios
 
    avwt /= i;
    avtat /= i;
    avrt /= i;
    cout << "\n\nAverage Waiting Time: " << avwt;
    cout << "\nAverage Turnaround Time: " << avtat;
    cout << "\nAverage Response Time: " << avrt;
    cout << endl;
 
    return 0;
}

int main(){
    int flag = 1, id, a, b, pr;
    double contextTime;

    vector<Proceso> procesos; //Almacenamiento de todos los procesos entrantes

    cout << endl;
    cout << "Procesos" << endl;
    
    //cout << "Ingrese el tiempo de cambio de contexto: ";
    cin >> contextTime;

    while(flag){
        
        //cout << "Ingrese nuevo proceso:" << endl;
        //cout << "Ingrese el id: ";
        cin >> id;
        if(id < 0){
            flag = 0;
        }
        else{
            //cout << "Ingrese el tiempo de llegada: ";
            cin >> a;
            //cout << "Ingrese el burst time: ";
            cin >> b;
            //cout << "Ingrese la prioridad: ";
            cin >> pr;
            Proceso p = Proceso(id, a, b, pr); //Creación de un nuevo proceso con sus atributos
            procesos.push_back(p);
            cout << endl;
            cout << "Process ID: " << p.id << endl;
            cout << "Process Arrival Time: "<< p.arrivalT << endl;
            cout << "Process Burst Time: "<< p.burstT << endl;
            cout << "Process Priority: "<< p.priority << endl;
            cout << endl;
        }
    }

    //Ordenamiento inicial de los procesos por tiempo de llegada

    sort(procesos.begin(),procesos.end());

    cout << "Algoritmos de Scheduling" << endl;

    //Creación de hilos para los tres algoritmos de Scheduling

    thread fcfs(firstCome, procesos);
    fcfs.join();
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    thread sjf(shortestJob, procesos);
    sjf.join();
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    thread pri(priority, procesos, contextTime);
    pri.join();

    return 0;
}