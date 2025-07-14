# Sistemas-Operativos

# 🧠 Simulador de Algoritmos de Planificación de Procesos

Proyecto desarrollado como parte del **Parcial 2 de Sistemas Operativos**, que simula la ejecución de algoritmos de planificación de procesos: **FCFS (First Come First Served)**, **SJF (Shortest Job First)** y **Prioridad con Desalojo**. Implementado en C++ con soporte multihilo.

---

## 👥 Integrantes

- Juan David Aycardi Ariza  
- Angelo Giuseppe Lozano Berruecos

---

## 🎯 Objetivo

Este programa permite simular y comparar distintos algoritmos de planificación de procesos (scheduling) en sistemas operativos. Los algoritmos muestran sus respectivos diagramas de Gantt, cálculos de tiempos promedio (waiting, turnaround y response) y gestión de prioridades.

---

## ⚙️ Algoritmos implementados

### 🔹 FCFS (First Come, First Served)
- Ordena los procesos por orden de llegada.
- No considera prioridades.
- No hay desalojo.

### 🔹 SJF (Shortest Job First)
- Planifica según el menor tiempo de ráfaga.
- No considera prioridades.
- No hay desalojo.

### 🔹 Prioridad con desalojo
- Usa una cola de prioridad para gestionar la planificación.
- Si un proceso con mayor prioridad llega, interrumpe al actual.
- Considera tiempos de cambio de contexto.

---

## 🛠️ Tecnologías y herramientas

- **Lenguaje:** C++
- **Librerías:** `<iostream>`, `<vector>`, `<queue>`, `<thread>`, `<algorithm>`
- **Paradigmas:** Programación estructurada y concurrente

---

## 📌 Cómo usar el programa

1. Compila el programa:
   g++ -std=c++11 -pthread simulador.cpp -o simulador
2. Ejecuta el programa:
   ./simulador
3. Luego ingresa la data en este formato, termina el bloque de procesos con un -1:
   ID ArrivalTime BurstTime Priority
4. Ejemplo:
   1 0 5 2
   2 2 3 1
   3 4 2 3
   -1
5.) El programa ejecutará automáticamente los tres algoritmos, cada uno en un hilo separado, y mostrará:

  - Gantt Chart

  - Tabla de tiempos por proceso

  - Tiempos promedio
6.) Ejemplo salida:
    FCFS

    Gantt Chart
     |s:0 p1| |s:1 p1| ... |s:5 p1|
    
    Tabla Cálculos de Tiempos
    
    ID Process	Burst Time	Waiting Time	Turnaround Time	Response time
    P[1]		5		0		5		0
    ...
    
    Average Waiting Time: X
    Average Turnaround Time: Y
    Average Response Time: Z

## Notas:
- Cada algoritmo es ejecutado usando std::thread para mostrar independencia de ejecución.

- El código incluye estructuras de datos como struct Proceso y priority_queue.

- La prioridad más alta se representa con un valor mayor (priority = 3 es mayor prioridad que priority = 1).

## Aprendizajes:
Este proyecto fue una oportunidad para profundizar en conceptos clave de los sistemas operativos como:

- Algoritmos de planificación

- Gestión del tiempo de CPU

- Simulación de comportamiento concurrente

- Análisis de métricas de desempeño (waiting, turnaround y response time)
