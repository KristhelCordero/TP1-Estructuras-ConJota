#include "Estructuras.h"

string leerYEncolarPedidos(ColaPedidos* cola, ColaPedidosPrioridad* colaPrioridad,string _nombreArchivo,
ListaClientes* listaClientes, ListaDoble* listaArticulos);
string obtenerHoraActual();
string obtenerFechaActual();
//hay que configurar todos los mutex porfiii

//COLA PEDIDOS-----------------------------------------------------------------------------------------------
void NodoPedido::annadirMovimiento(Movimiento* nuevoMovimiento){
	movimientos->agregarMovimiento(nuevoMovimiento);
}

bool ColaPedidos::estaVacia(){
	lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaPedidos::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->anterior; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaPedidos::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaPedidos::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaPedidos::largo(){
	lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

///COLA PRIORIDAD -------------------------------------------------------------------------------------------
bool ColaPedidosPrioridad::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaPedidosPrioridad::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaPedidosPrioridad::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaPedidosPrioridad::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl; 
		tmp=tmp->siguiente;
    }
}

int ColaPedidosPrioridad::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//COLA PEDIDOS ESPECIALES -----------------------------------------------------------------------------------
bool ColaPedidosEspeciales::estaVacia(){
	// lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaPedidosEspeciales::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->siguiente; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaPedidosEspeciales::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaPedidosEspeciales::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl; 
		tmp=tmp->siguiente;
    }
}

int ColaPedidosEspeciales::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

//LISTA DOBLE ARTICULOS -------------------------------------------------------------------------------------
void NodoArticulo::imprimir(){
	cout<<codigo<<endl; 
	cout<<cantidad<<endl; 
	cout<<tiempoFabricacion<<endl;
	cout<<categoria<<endl; 
	cout<<ubicacion<<endl; 
	cout<<"------------"<<endl;
}

void ListaDoble::insertarInicio(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
    if (primerArticulo==0)
	    primerArticulo=ultimoArticulo=new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
    else{
	    primerArticulo->anterior= new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
	    primerArticulo->anterior->siguiente=primerArticulo;
	    primerArticulo=primerArticulo->anterior;
    }
}

void ListaDoble::insertarFinal(int _cantidad, string _codigo, string _categoria, string _ubicacion, int _tiempoFabricacion){
    if (primerArticulo==0)
	    primerArticulo=ultimoArticulo=new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
    else{
	    ultimoArticulo->siguiente= new NodoArticulo(_cantidad, _codigo, _categoria, _ubicacion, _tiempoFabricacion);
	    ultimoArticulo->siguiente->anterior=ultimoArticulo;
	    ultimoArticulo=ultimoArticulo->siguiente; 
    }
}

NodoArticulo * ListaDoble::borrarAlFinal(){
	NodoArticulo * borrado=ultimoArticulo;
	if (primerArticulo!=NULL){
		if (primerArticulo==ultimoArticulo){
			primerArticulo=ultimoArticulo=NULL;
    	}else{
        	ultimoArticulo=ultimoArticulo->anterior;
			borrado->anterior=NULL;
			ultimoArticulo->siguiente=NULL;
    	}
	}
    return borrado;
}

void ListaDoble::leerArchivoArticulos(){
	ifstream archivo;
	string texto;
	string codigo, categoria, ubicacion, cantidadS, tiempoS;
	archivo.open("articulos.txt",ios::in);
	
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigo,'\t');
			getline(ss,cantidadS,'\t');
			getline(ss,tiempoS,'\t');
			getline(ss,categoria,'\t');
			getline(ss,ubicacion,'\t');
			insertarFinal(stoi(cantidadS),codigo,categoria,ubicacion,stoi(tiempoS));
		}
		archivo.close();
	}
}

void ListaDoble::imprimir(){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		tmp->imprimir();
		tmp=tmp->siguiente;
    }
}

bool ListaDoble::encontrarArticulo(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return true;
		}
		tmp=tmp->siguiente;
    }
	return false;
}
//Falta probar esta función
int ListaDoble::cantidadArticuloBodega(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			return tmp->cantidad;
		}
		tmp=tmp->siguiente;
    }
	return 0;
}
//Falta probar esta función
void ListaDoble::actualizarArchivoArticulos(){
	ofstream archivo;
	archivo.open("articulos.txt",ios::out); //Al ya existir lo va a sobreescribir
	if (archivo.fail()){
		cout<<"No escribí el archivo"<<endl;
		exit(1);
	}else{
		NodoArticulo * tmp = primerArticulo;
		while(tmp!=NULL){
			archivo<<tmp->codigo<<"\t"<<tmp->cantidad<<"\t"<<tmp->tiempoFabricacion<<"\t"<<tmp->categoria<<"\t"<<tmp->ubicacion<<endl;
			tmp=tmp->siguiente;
    	}
		archivo.close();
	}

}

int ListaDoble::largo(){
    // lock_guard<mutex> lock(mtx);
	NodoArticulo * tmp = primerArticulo;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}
//Falta probar esta función
bool ListaDoble::encontrarArticuloRepetido(string _codigo){
	NodoArticulo * tmp = primerArticulo;
	int contador=0;
	while(tmp!=NULL){
		if(tmp->codigo==_codigo){
			contador++;
		}
		tmp=tmp->siguiente;
    }
	if (contador>1)
		return true;
	else
		return false;
}

//Falta probar esta función
int ListaDoble::revisarListaArticulos(){
	//Si devuelve 0 todo está bien, si devuelve 1 algo está mal
	string articulos[largo()];
	NodoArticulo * tmp = primerArticulo;
	while(tmp!=NULL){
		if(tmp->cantidad<0){
			return 1;
		}else if (tmp->categoria!="A"&& tmp->categoria!="B" && tmp->categoria!="C"){
			return 1;
		}else if(encontrarArticuloRepetido(tmp->codigo)){
			return 1;
		}
		tmp=tmp->siguiente;
    }
	return 0;
}

//LISTA PRODUCTOS ------------------------------------------------------------------------------------------
void ListaProductos::insertarInicioProducto(string _codigoProducto, int _cantidad){
    if (primerProducto==NULL)
	    primerProducto=ultimoProducto=new Producto(_codigoProducto, _cantidad);
    else{
	    primerProducto->productoAnterior= new Producto(_codigoProducto, _cantidad);
	    primerProducto->productoAnterior->siguienteProducto=primerProducto;
	    primerProducto=primerProducto->productoAnterior;
    }
}

void ListaProductos::insertarFinalProducto (string _codigoProducto, int _cantidad){
    if (primerProducto==NULL)
	    primerProducto=ultimoProducto=new Producto(_codigoProducto, _cantidad);
    else{
	    ultimoProducto->siguienteProducto= new Producto(_codigoProducto, _cantidad);
	    ultimoProducto->siguienteProducto->productoAnterior=ultimoProducto;
	    ultimoProducto=ultimoProducto->siguienteProducto; 
    }
}

Producto * ListaProductos::borrarAlFinal(){
	Producto * borrado=ultimoProducto;
	if (primerProducto!=NULL){
		if (primerProducto==ultimoProducto){
			primerProducto=ultimoProducto=NULL;
    	}else{
        ultimoProducto=ultimoProducto->productoAnterior;
		borrado->productoAnterior=NULL;
		ultimoProducto->siguienteProducto=NULL;
    	}
	}
    return borrado;
}
//FALTA PROBAR ESTA FUNCION
Producto * ListaProductos::revisarProductosFaltantes(ListaDoble *listaArticulos){
	Producto *tmp=primerProducto;
	while(tmp!=NULL){
		if (tmp->cantidad>listaArticulos->cantidadArticuloBodega(tmp->codigoProducto)){
			return tmp; // si devuelve un producto, hay que enviar ese producto a fabricar
		}
	}
	return tmp; //si tmp es NULL no hay ningun producto faltante
}
//FALTA PROBAR ESTA FUNCION
bool ListaProductos::exists(string _codigoProducto){
	Producto * tmp = primerProducto;
    while(tmp!=NULL){
	    if (tmp->codigoProducto==_codigoProducto)
			return true;
	    tmp=tmp->siguienteProducto;
    }
	return false;
}
//FALTA PROBAR ESTA FUNCION
int ListaProductos::cantidadArticulosDistintos(){
	Producto * tmp = primerProducto;
	ListaProductos * listaProvisional= new ListaProductos();
    int contador=0;
    while(tmp!=NULL){
	    if (!listaProvisional->exists(tmp->codigoProducto)) //no se si realmente sea necesario
			listaProvisional->insertarFinalProducto(tmp->codigoProducto,0); //porque puede ser que solo se ingresen productos diferentes
			contador++;
	    tmp=tmp->siguienteProducto;
    }
	return contador;
}

//LISTA CLIENTES -------------------------------------------------------------------------------------------
void ListaClientes::insertarInicioCliente (string codigoCliente, string nombreCliente,int prioridad){
    if (primerCliente==NULL)
	    primerCliente=new Cliente (codigoCliente, nombreCliente, prioridad);
    else{
		Cliente * nuevo=new Cliente (codigoCliente, nombreCliente, prioridad);
	    nuevo->siguiente=primerCliente;
	    primerCliente=nuevo;
    }
}

void ListaClientes::imprimir(){
		Cliente * tmp = primerCliente;
		while(tmp!=NULL){
			tmp->imprimir();
			tmp=tmp->siguiente;
        }
    }

void ListaClientes::leerArchivoClientes(){
	ifstream archivo;
	string texto;
	archivo.open("clientes.txt",ios::in);
	string codigo, nombre, sPrioridad;
	int prioridad;
	Cliente * cliente;
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss, codigo, '\t');
    		getline(ss, nombre, '\t');
    		getline(ss, sPrioridad);
			prioridad=stoi(sPrioridad);
			insertarInicioCliente(codigo,nombre,prioridad);
		}
		archivo.close();
	}
}
//Falta probar esta función
void ListaClientes::annadirClienteAlArchivo(string codigoCliente, string nombreCliente,int prioridad){
	ofstream archivo;
	archivo.open("clientes.txt",ios::app);
	if (archivo.fail()){
		cout<<"No abrí el archivo"<<endl;
		exit(1);
	}else{
		archivo <<"\n"<<codigoCliente<<"\t"<<nombreCliente<<"\t"<< prioridad;
		archivo.close();
	}
}

int ListaClientes::buscarPrioridadCliente(string codigoCliente){
	Cliente * tmp=primerCliente;
	while (tmp!=NULL){
		if(tmp->codigoCliente==codigoCliente)
			return tmp->prioridad;
		tmp=tmp->siguiente;
	}
	return 0;
}
//------------------ cliente ----------------------
void Cliente::imprimir(){
	cout<<codigoCliente<<endl; 
	cout<<nombreCliente<<endl; 
	cout<<prioridad<<endl; 
	cout<<"------------"<<endl;
}

// COLA DE ALISTO ------------------------------------------------------------------------------------------
bool ColaAlisto::estaVacia(){
	lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaAlisto::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->anterior; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola de alisto: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaAlisto::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaAlisto::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaAlisto::largo(){
	lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// COLA ALISTADOOS ---------------------------------------------------------------------------------------
bool ColaAlistadoos::estaVacia(){
	lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaAlistadoos::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->anterior; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("En cola de alisto: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaAlistadoos::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaAlistadoos::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaAlistadoos::largo(){
	lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// COLA FACTURACION --------------------------------------------------------------------------------------
bool ColaFacturacion::estaVacia(){
	lock_guard<mutex> lock(mtx);
	return primerPedido==0;
}

void ColaFacturacion::encolar(int _numeroPedido, string _codigoCliente,ListaProductos * _productos){
	// lock_guard<mutex> lock(mtx);
	if(estaVacia())
		primerPedido=ultimoPedido=new NodoPedido(_numeroPedido, _codigoCliente, _productos);
	else{
		ultimoPedido->siguiente= new NodoPedido(_numeroPedido, _codigoCliente, _productos);
		ultimoPedido->siguiente->anterior=ultimoPedido;
		ultimoPedido=ultimoPedido->anterior; 
    }
	//esto último no está probado
	ultimoPedido->annadirMovimiento(new Movimiento("A empaque: ",obtenerFechaActual()+" "+obtenerHoraActual()));
}

NodoPedido * ColaFacturacion::desencolar(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * borrado= primerPedido;
	if(primerPedido==ultimoPedido){
		primerPedido=ultimoPedido=NULL;
	}else{
		primerPedido=primerPedido->siguiente;
		borrado->siguiente=NULL;
		primerPedido->anterior=NULL;
	}
	return borrado;
}

void ColaFacturacion::imprimir(){
	lock_guard<mutex> lock(mtx);
	NodoPedido * tmp = primerPedido;
	while(tmp!=NULL){
		cout<<tmp->numeroPedido<<endl; 
		cout<<tmp->codigoCliente<<endl;
		cout<<"----------------------"<<endl;
		tmp=tmp->siguiente;
    }
}

int ColaFacturacion::largo(){
	lock_guard<mutex> lock(mtx);
    NodoPedido * tmp = primerPedido;
    int contador=0;
    while(tmp!=NULL){
	    contador++;
	    tmp=tmp->siguiente;
    }
	return contador;
}

// LISTA ROBOTS ---------------------------------------------------------------------------------------------
void ListaRobots::insertarFinal(string _codigoRobot, string _articuloFabrica, bool _apagado, bool _esPrioridad){
    if (primerRobot==0)
	    primerRobot=ultimoRobot=new Robot(_codigoRobot, _articuloFabrica, _apagado, _esPrioridad);
    else{
	    ultimoRobot->siguiente= new Robot(_codigoRobot, _articuloFabrica, _apagado, _esPrioridad);
	    ultimoRobot->siguiente->anterior=ultimoRobot;
	    ultimoRobot=ultimoRobot->siguiente; 
    }
}

void Robot::imprimir(){
	cout<<codigoRobot<<endl; 
	cout<<articuloFabrica<<endl; 
	cout<<apagado<<endl;
	cout<<esPrioridad<<endl; 
	cout<<"------------"<<endl;
}

void ListaRobots::imprimir(){
	Robot * tmp = primerRobot;
	while(tmp!=NULL){
		tmp->imprimir();
		tmp=tmp->siguiente;
    }
}

void ListaRobots::leerArchivoRobots(){
	ifstream archivo;
	bool bApagado, bPrioridad;
	string texto,codigoRobot,articulo,apagado,esPrioridad;
	archivo.open("robots.txt",ios::in);
	
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigoRobot,'\t');
			getline(ss,articulo,'\t');
			getline(ss,apagado,'\t');
			if (apagado=="1")
				bApagado=false;
			else
				bApagado=true;
			getline(ss,esPrioridad,'\t');
			if (esPrioridad=="1")
				bPrioridad=true;
			else
				bApagado=false;
			insertarFinal(codigoRobot,articulo,bApagado,bPrioridad);
		}
		archivo.close();
	}
}

Robot * ListaRobots::asignarPedidoRobot(string _CodigoProducto){
	string tipoProducto = string(1,_CodigoProducto.at(0));

	Robot * tmp =primerRobot;
	bool flag=true;
	do
	{
		if((tmp->articuloFabrica==tipoProducto)&&(!tmp->apagado&&tmp->disponible)){
			return tmp;
			flag=false;
		}		
	} while (flag);
	return NULL;
}

//BITACORA DE MOVIMIENTOS -----------------------------------------------------------------------------------

// THREAD PEDIDOS -------------------------------------------------------------------------------------------
void threadPedidos::leerArchivosPedidos() {
    while (!terminar) {
        while(pausado){
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
		cout<<"Entré"<<endl;
        if(direccion=opendir(dir.c_str())){
            while(elementos=readdir(direccion)){
				_nombreArchivo=".\\Pedidos-Clientes\\";
				_nombreArchivo+=elementos->d_name;
				cout<<_nombreArchivo<<endl;
				if(_nombreArchivo!=".\\Pedidos-Clientes\\." && _nombreArchivo!=".\\Pedidos-Clientes\\.."){
                	nombreArchivo=leerYEncolarPedidos(cola, colaPrioridad,_nombreArchivo, listaClientes, listaArticulos);
                	if(nombreArchivo=="Error"){
						cout<<"Llegué1"<<endl;
                	    nombreArchivo=".\\Errores\\"+_nombreArchivo.erase(0,19);;
						cout<<nombreArchivo<<endl;
						_nombreArchivo=".\\Pedidos-Clientes\\"+_nombreArchivo;
						cout<<_nombreArchivo<<endl;
                	    rename(_nombreArchivo.c_str(),nombreArchivo.c_str());
						cout<<"Llegué4"<<endl;
                	}else{
						cout<<"Llegué2"<<endl;
						nombreArchivo.erase(0,19);
                	    nombreArchivo=".\\Pedidos-Procesados\\"+nombreArchivo;
						cout<<nombreArchivo<<endl;
                	    rename(_nombreArchivo.c_str(), nombreArchivo.c_str());
						cout<<"Llegué 3"<<endl;
                	}
				}
            }
        }
		closedir(direccion);
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// THREAD BALANCEADOR ---------------------------------------------------------------------------------------
// No está probado
void ThreadBalanceador::procesarPedidos(){
	NodoPedido * pedidoProcesandose;
	Producto * productoAElaborar;
	while (!terminar){
		while(apagado){
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
		do{
			if (colaEspecial->largo()>=1){
				pedidoProcesandose=colaEspecial->desencolar();
				procesando=true;
			}
			else if (colaPrioridad->largo()>=1){
				pedidoProcesandose=colaPrioridad->desencolar();
				procesando=true;
			}
			else if (cola->largo()>=1){
				pedidoProcesandose=cola->desencolar();
				procesando=true;
			}
			else
				this_thread::sleep_for(chrono::seconds(3));
			pedidoProcesandose->annadirMovimiento(new Movimiento("Balanceador: ",obtenerFechaActual()+" "+obtenerHoraActual()));
		}while (!procesando);
		productoAElaborar=pedidoProcesandose->productos->revisarProductosFaltantes(listaArticulos);
		do{
			if (productoAElaborar==NULL){//No hay ningún producto faltante
				colaDeAlisto->encolar(pedidoProcesandose->numeroPedido,
				pedidoProcesandose->codigoCliente,pedidoProcesandose->productos);
				procesando=false;
			}else{
				//hay que mandar a elaborar un producto
				//hay que hacer los robots por eso no he hecho esta parte XD
				elaborarProducto(productoAElaborar);
			}
		}while (procesando);
	}
}

//THREAD ROBOTS ---------------------------------------------------------------------------------------------
void RobotFabricador::elaborarProducto(Producto* productoAElaborar, int _cantidadProductos, int _cantidadSeg){
	Robot* robotAsignado=asignarPedidoRobot(productoAElaborar->codigoProducto);
	thread hilo;
	
	while(!terminar){
		while(apagado){
			hilo::sleep_for(chrono::milliseconds(2000));
		}while(productoAElaborar->cantidad<_cantidadProductos){
			hilo::sleep_for(chrono::seconds(_cantidadSeg));
			productoAElaborar->cantidad++;
		}
	}
	//Todavía no sé muy bien como va a funcionar esto
}

//--------------------------------------- FUNCIONES SIN ESTRUCTURA ------------------------------------------
string leerYEncolarPedidos(ColaPedidos* cola, ColaPedidosPrioridad* colaPrioridad,string _nombreArchivo,
ListaClientes* listaClientes, ListaDoble* listaArticulos){
	ifstream archivo;
	string texto, numPedido, codigoCliente, codigoProducto, cantidadP, cont;
	ListaProductos * productos= new ListaProductos();
	archivo.open(_nombreArchivo,ios::in);
	cout<<"Estoy en leer y encolar"<<endl;
	if (archivo.fail()){
		cout<<"No lei el archivo"<<endl;
		exit(1);
	}else{
		getline(archivo,numPedido);
		getline(archivo,codigoCliente);
		while(getline(archivo, texto)){
			istringstream ss(texto);
			getline(ss,codigoProducto,'\t');
			if (!listaArticulos->encontrarArticulo(codigoProducto)){
				archivo.close();
				return "Error";
			}
			getline(ss,cantidadP,'\t');
			if (stoi(cantidadP)<1){
				archivo.close();
				return "Error";
			}
			productos->insertarFinalProducto(codigoProducto,stoi(cantidadP));
		}
		cout<<"Llegué hasta aqui wuuu"<<endl;
		if (listaClientes->buscarPrioridadCliente(codigoCliente)!=10 && listaClientes->buscarPrioridadCliente(codigoCliente)!=0){
			cola->encolar(stoi(numPedido),codigoCliente, productos);
		}else if (listaClientes->buscarPrioridadCliente(codigoCliente)!=0){
			colaPrioridad->encolar(stoi(numPedido),codigoCliente, productos);
		}else{
			archivo.close();
			cout<<"Aqui pedido2"<<endl;
			return "Error";
		}
		cout<<"Terminé leer y encolar"<<endl;
		archivo.close();
		return _nombreArchivo;
	}
}

string obtenerHoraActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal = *localtime(&tiempoActual);
    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", tiempoLocal.tm_hour,
	 tiempoLocal.tm_min, tiempoLocal.tm_sec);
    return string(buffer);
}

string obtenerFechaActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempoActual = chrono::system_clock::to_time_t(ahora);
    tm tiempoLocal = *localtime(&tiempoActual);
    char buffer[11];
    sprintf(buffer, "%02d/%02d/%04d", tiempoLocal.tm_mday,
	 tiempoLocal.tm_mon + 1, tiempoLocal.tm_year + 1900);
    return std::string(buffer);
}

string facturarPedido(NodoPedido *pedido, string _nombreArchivo){
	ofstream archivo;
	archivo.open(_nombreArchivo,ios::out); //Al ya existir lo va a sobreescribir
	if (archivo.fail()){
		cout<<"No escribí el archivo"<<endl;
		exit(1);
	}else{
		Movimiento * tmpMov=pedido->movimientos->primerMov;
		archivo<<"Pedido: \t"<<pedido->numeroPedido;
		archivo<<"Cliente: \t"<<pedido->codigoCliente;
		while(!tmpMov->robot && !tmpMov->alistador){
			archivo<<tmpMov->ubicacion<<"\t"<<tmpMov->info<<endl;
			tmpMov=tmpMov->siguiente;
    	}
		archivo<<endl;
		if(tmpMov->robot){ //robot
			archivo<<"Robots Fábrica"<<endl;
			
		}else{ //alistador

		}
		archivo.close();
	}
} 