#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>
#include <dirent.h>
#include <cstdlib>
#include <cstdio>
using namespace std;

//LISTA BASE


//Lista de Clientes(Ordenar por Prioridad*) ------------------------------------------------------------
struct Cliente{
    string codigoCliente, nombreCliente;
    int prioridad;
    Cliente * siguiente;

    Cliente(string _codigoCliente, string _nombreCliente,int _prioridad){
        codigoCliente=_codigoCliente;
        nombreCliente=_nombreCliente;
        prioridad=_prioridad;
        siguiente=NULL;
    }
    void imprimir();
};

struct ListaClientes{
    Cliente * primerCliente;

    ListaClientes(){
		primerCliente=NULL;
    }
    void imprimir();
    void insertarInicioCliente (string codigoCliente, string nombreCliente,int prioridad);
    void leerArchivoClientes();
    void annadirClienteAlArchivo(string codigoCliente, string nombreCliente,int prioridad);
    int buscarPrioridadCliente(string codigoCliente);
};

//Lista de Productos ----------------------------------------------------------------------------------
struct Producto{
    Producto * siguienteProducto, * productoAnterior;
    string codigoProducto;
    int cantidad;

    Producto(string _codigoProducto, int _cantidad){
        codigoProducto=_codigoProducto;
        cantidad=_cantidad;
        siguienteProducto=productoAnterior=NULL;
    }
};

struct ListaProductos{
    Producto * primerProducto, * ultimoProducto;

    ListaProductos(){
		primerProducto=ultimoProducto=NULL;
    }

    void insertarInicioProducto(string _codigoProducto, int _cantidad);
    void insertarFinalProducto (string _codigoProducto, int _cantidad);
	Producto * borrarAlFinal();
    string revisarProductosFaltantes(ListaDoble *listaArticulos);
};

// Cola de Pedidos ------------------------------------------------------------------------------------
struct NodoPedido{
    NodoPedido * siguiente;
    NodoPedido * anterior;
    int numeroPedido;
    string codigoCliente;
    ListaProductos * productos;

    NodoPedido(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
        numeroPedido=_numeroPedido;
        codigoCliente=_codigoCliente;
        productos=_productos;
    }
};

struct ColaPedidos{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidos(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

struct ColaPedidosPrioridad{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidosPrioridad(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

struct ColaPedidosEspeciales{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaPedidosEspeciales(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// Lista Doble ----------------------------------------------------------------------------------------
struct NodoArticulo{
    string codigo, categoria, ubicacion;
	int cantidad, tiempoFabricacion;
	NodoArticulo * siguiente;
	NodoArticulo * anterior;
    
	NodoArticulo(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
		cantidad=_cantidad;
        categoria=_categoria;
        ubicacion=_ubicacion;
        tiempoFabricacion=_tiempoFabricacion;
        codigo=_codigo;
		siguiente= anterior=NULL;
    }

    void imprimir();
};

struct ListaDoble {
	NodoArticulo * primerArticulo, * ultimoArticulo;
	
    ListaDoble(){
		primerArticulo=ultimoArticulo=NULL;
    }

    void insertarInicio(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion);
    void insertarFinal (int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion);
	NodoArticulo * borrarAlFinal();
    void leerArchivoArticulos();
    void imprimir();
    bool encontrarArticulo(string _codigo);
    void actualizarArchivoArticulos();
    int revisarListaArticulos();
    int largo();
    bool encontrarArticuloRepetido(string _codigo);
};

//------------------------------------------THREADS---------------------------------------------------
struct threadPedidos {
    thread thread; 
    string nombreArchivo, _nombreArchivo;
    string dir=".\\Pedidos-Clientes";
    DIR *direccion;
    dirent *elementos;
    atomic<bool> pausado; 
    atomic<bool> terminar; 
    ColaPedidos* cola;
    ColaPedidosPrioridad *colaPrioridad;
    ListaClientes *listaClientes;
    ListaDoble *listaArticulos;
    mutex mutex;
    // Constructor
    threadPedidos(ColaPedidos *_cola, ColaPedidosPrioridad *_colaPrioridad, ListaClientes *_listaClientes, ListaDoble *_listaArticulos):
    pausado(false), terminar(false), cola(_cola), colaPrioridad(_colaPrioridad), listaClientes(_listaClientes), listaArticulos(_listaArticulos){
        thread = std::thread(threadPedidos::leerArchivosPedidos, this);
    }
    // Función que será ejecutada por el thread
    void leerArchivosPedidos(); 
    void Pausar() {pausado = true;}
    void Reanudar() {pausado = false;}
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }
    //Destructor
    ~threadPedidos() {Terminar();}
};

// {
//                 unique_lock<std::mutex> lock(mutex);
//                 while (pausado) {
//                     // El thread está en pausa, espera
//                     lock.unlock();
//                     this_thread::sleep_for(chrono::milliseconds(100));
//                     lock.lock();
//                 }
//             }

//BALANCEADOR ---------------------------------------------------------------------------------------
struct ThreadBalanceador{
    thread thread; 
    atomic<bool> pausado; 
    atomic<bool> terminar; 
    ColaPedidos* cola;
    ColaPedidosPrioridad *colaPrioridad;
    ColaPedidosEspeciales *colaEspecial;
    ListaDoble *listaArticulos;
    // Constructor
    ThreadBalanceador(ColaPedidos *_cola, ColaPedidosPrioridad *_colaPrioridad, ListaDoble *_listaArticulos, ColaPedidosEspeciales * _colaEspecial):
    pausado(false), terminar(false), cola(_cola), colaPrioridad(_colaPrioridad), listaArticulos(_listaArticulos), colaEspecial(_colaEspecial){
        thread = std::thread(ThreadBalanceador::procesarPedidos, this);
    }
    // Función que será ejecutada por el thread
    void procesarPedidos(); 
    void Pausar() {pausado = true;}
    void Reanudar() {pausado = false;}
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }
    //Destructor
    ~ThreadBalanceador() {Terminar();}
};



