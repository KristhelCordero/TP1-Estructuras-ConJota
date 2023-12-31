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
#include <ctime>

using namespace std;

//LISTA BASE
//NOTA PARA KRIS DE KRIS DEL PASADO: REVISAR LOS NEW DE LAS LISTAS QUE ESTÁN DENTRO DE NODOS
// hay que agregar los destructores a las structs que les faltan, los que están añadidos no están probados
// puede que generen errores sin sentido 
struct ListaDoble;
struct BitacoraMovimientos;

//Lista de Clientes(Ordenar por Prioridad*) -----------------------------------------------------------
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
    bool elaborando;

    Producto(string _codigoProducto, int _cantidad){
        codigoProducto=_codigoProducto;
        cantidad=_cantidad;
        elaborando=false;
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
	Producto* borrarAlFinal();
    Producto* revisarProductosFaltantes(ListaDoble* listaArticulos);
    bool exists(string _codigoProducto);
    int cantidadArticulosDistintos();

    ~ListaProductos(){
        while(primerProducto != NULL){
            Producto* temp = primerProducto;
            primerProducto = primerProducto->siguienteProducto;
            delete temp;
        }
    }
};

// Cola de Pedidos ------------------------------------------------------------------------------------
struct NodoPedido{
    NodoPedido * siguiente;
    NodoPedido * anterior;
    int numeroPedido;
    string codigoCliente;
    ListaProductos * productos;
    BitacoraMovimientos * movimientos;

    NodoPedido(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
        numeroPedido=_numeroPedido;
        codigoCliente=_codigoCliente;
        productos=_productos;
        movimientos= new BitacoraMovimientos();
    }
    void annadirMovimiento(Movimiento* nuevoMovimiento);
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
    int cantidadArticuloBodega(string _codigo);
};

// COLA DE ALISTO -------------------------------------------------------------------------------------
struct ColaAlisto{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaAlisto(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// COLA ALISTADOS -------------------------------------------------------------------------------------
struct ColaAlistadoos{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaAlistadoos(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// COLA FACTURACIÓN -----------------------------------------------------------------------------------
struct ColaFacturacion{
    NodoPedido * primerPedido, * ultimoPedido;
    mutex mtx;

    ColaFacturacion(){
        primerPedido=ultimoPedido=NULL;
    }

    bool estaVacia();
    void encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos);
    void imprimir();
    int largo();
    NodoPedido * desencolar();
};

// ROBOTS ---------------------------------------------------------------------------------------------
struct Robot{
    string codigoRobot;
    string articuloFabrica;
    bool apagado;
    bool esPrioridad;
    bool disponible;
    Robot *siguiente;
    Robot *anterior;

    Robot(string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad){
        codigoRobot=_codigoRobot;
        articuloFabrica=_articuloFabrica;
        apagado=_apagado;
        esPrioridad=_esPrioridad;
        disponible=true;
    }

    void imprimir();
};

struct ListaRobots{
    Robot * primerRobot;
    Robot * ultimoRobot;

    ListaRobots(){
		primerRobot=ultimoRobot=NULL;
    }

    void insertarFinal (string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad);
    void leerArchivoRobots();
    Robot * asignarPedidoRobot(string _Codigo);
    void imprimir();

};

// BITÁCORA DE MOVIMIENTOS ----------------------------------------------------------------------------
struct Movimiento{
    string ubicacion, info;//info= fecha, hora, faltantes en caso de haber
    bool robot; 
    string articulo, fabricadoEn, cantidad, fechaInicio, fechaFinal;
    bool alistador;
    string numAlistador, tiempo; //ubi y articulo aqui 2
    Movimiento * siguiente, *anterior;

    //robot
    Movimiento(string _articulo, string _fabricadoEn, string _cantidad, string _fechaFinal,string _fechaInicio){
        articulo=_articulo;
        fabricadoEn=_fabricadoEn;
        cantidad=_cantidad;
        fechaFinal=_fechaFinal;
        fechaInicio=_fechaInicio;
        robot=true;
        alistador=false;
    }
    //alistador
    Movimiento(string _numAlistador, string _articulo, string _ubicacion, string _tiempo){
        articulo=_articulo;
        numAlistador=_numAlistador;
        ubicacion=_ubicacion;
        tiempo=_tiempo;
        robot=false;
        alistador=true;
    }
    //otros
    Movimiento(string _ubicacion, string _info){
        ubicacion=_ubicacion;
        info=_info;
    }

};

struct BitacoraMovimientos{
    Movimiento * primerMov, *ultimoMov;
    
    BitacoraMovimientos(){
        primerMov=ultimoMov=NULL;
    }

    void agregarMovimiento(Movimiento* nuevoMovimiento) {
        if (!primerMov) {
            primerMov = nuevoMovimiento;
            ultimoMov = nuevoMovimiento;
        } else {
            ultimoMov->siguiente = nuevoMovimiento;
            nuevoMovimiento->anterior = ultimoMov;
            ultimoMov = nuevoMovimiento;
        }
    }
    //Destructor
    ~BitacoraMovimientos() {
        Movimiento* tmp = primerMov;
        while (tmp) {
            Movimiento* siguiente = tmp->siguiente;
            delete tmp;
            tmp = siguiente;
        }
    }
};

//------------------------------------------THREADS----------------------------------------------------
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

//BALANCEADOR -----------------------------------------------------------------------------------------
struct ThreadBalanceador{
    thread thread; 
    atomic<bool> apagado; 
    atomic<bool> terminar; 
    ColaPedidos* cola;
    ColaPedidosPrioridad *colaPrioridad;
    ColaPedidosEspeciales *colaEspecial;
    ColaAlisto *colaDeAlisto;
    ListaDoble *listaArticulos;
    bool procesando=false;
    // Constructor
    ThreadBalanceador(ColaPedidos *_cola, ColaPedidosPrioridad *_colaPrioridad, ListaDoble *_listaArticulos, ColaPedidosEspeciales * _colaEspecial):
    apagado(false), terminar(false), cola(_cola), colaPrioridad(_colaPrioridad), listaArticulos(_listaArticulos), colaEspecial(_colaEspecial){
        thread = std::thread(ThreadBalanceador::procesarPedidos, this);
    }
    // Función que será ejecutada por el thread
    void procesarPedidos(); 
    void Pausar() {apagado = true;}
    void Reanudar() {apagado = false;}
    void Terminar() {
        terminar = true;
        if (thread.joinable()) {
            thread.join();
        }
    }
    //Destructor
    ~ThreadBalanceador() {Terminar();}
};

//ROBOTS ----------------------------------------------------------------------------------------------
struct RobotFabricador{
// operar desde el thread la lista de robots
// hacer una función que opere al robot correspondiente
// Necesito: ver donde putas meto las validaciones :)
    thread thread;
    atomic<bool> apagado; 
    atomic<bool> terminar;
    bool procesado=false;
    void elaborarProducto(Producto * productoAElaborar, int _cantidadProductos, int _cantidadSeg);
};

// EMPACADOR ------------------------------------------------------------------------------------------
struct ThreadEmpacador{
    
};

//FACTURADOR ------------------------------------------------------------------------------------------
struct ThreadFacturador{
    
};


