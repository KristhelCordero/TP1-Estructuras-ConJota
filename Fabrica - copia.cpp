#include "Funciones.cpp"

int main(int argc, char const *argv[])
{

    // Movimiento *movimiento= new Movimiento("string1",obtenerFechaYHoraActual());
    // cout<<"hola"<<endl;
    // cout<< movimiento->info<<endl;
    // BitacoraMovimientos *bitacora= new BitacoraMovimientos();
    // bitacora->agregarMovimiento(movimiento);

    // ListaProductos *productos=new ListaProductos();
    // productos->insertarFinalProducto("Hola, soy el codigo",12);
    // NodoPedido *pedido= new NodoPedido(9, "hola soy el otro codigo",productos);
    // string nombre = pedido->numeroPedido +"_"+ pedido->codigoCliente +"_"+ obtenerFechaSYHoraActual();
    // nombre.erase(0, 1);
    // cout<<nombre<<endl;
    // cout<<facturarPedido(pedido, nombre)<<endl;// no me acorde
    ColaPedidos *cola=new ColaPedidos();
    ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    ColaPedidosEspeciales *colaEspecial= new ColaPedidosEspeciales();
    // cout<<"---------------------------- CLIENTES -------------------------------------"<<endl;
    ListaClientes *listaClientes=new ListaClientes();
    listaClientes->leerArchivoClientes();
    // cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    threadPedidos threadPed(cola, colaPrioridad, listaClientes, listaArticulos);
    // this_thread::sleep_for(chrono::seconds(9));
    // threadPed.Terminar();
    ListaRobots *listaRobots= new ListaRobots();
    listaRobots->leerArchivoRobots();
    ColaFacturacion *colaFacturacion=new ColaFacturacion();
    ColaAlistadoos *colaAlistados=new ColaAlistadoos();
    // this_thread::sleep_for(chrono::seconds(12));
    // threadEmpacador.Terminar();
    // colaFacturacion->imprimir();
    ThreadBalanceador balanceador(cola,colaPrioridad,listaArticulos,colaEspecial);
    ThreadEmpacador threadEmpacador(colaFacturacion,colaAlistados);
    ThreadFacturador threadFacturador(colaFacturacion);
    // cout<<"1: Agregar Pedido"<<endl;
	// cout<<"2: Apagar/Encender Balanceador"<<endl;
	// cout<<"3: Agregar Cliente"<<endl;
	// cout<<"4: Modificar Alistadores"<<endl;
	// cout<<"5: Modificar Robots Fabricadores"<<endl;
	// cout<<"6: Apagar/Encender Empacador"<<endl;
	// cout<<"7: Apagar/Encender Facturador"<<endl;
	// cout<<"0: Terminar la simulación"<<endl;
    int opcion=1;
    do{
        opcion=menuPrincipal();
        switch (opcion){
        case 1:
            menuPedidosEspeciales(colaEspecial);
            break;
        case 2:
            if (balanceador.apagado){
                balanceador.Reanudar();
                cout<<"El balanceador ha sido encendido"<<endl;
            }else{
                balanceador.Pausar();
                cout<<"El balanceador ha sido apagado"<<endl;
            }
            break;
        case 3:
            menuNuevoCliente(listaClientes);
            break;
        case 4:
            menuAlistadores(); //Aqui lo que ocupes 
            break;
        case 5:
            menuRobots(listaRobots);
            break;
        case 6:
            if (threadEmpacador.apagado){
                threadEmpacador.Reanudar();
                cout<<"El empacador ha sido encendido"<<endl;
            }else{
                threadEmpacador.Pausar();
                cout<<"El empacador ha sido apagado"<<endl;
            }
            break;
        case 7:
            if (threadFacturador.apagado){
                threadFacturador.Reanudar();
                cout<<"El facturador ha sido encendido"<<endl;
            }else{
                threadFacturador.Pausar();
                cout<<"El facturador ha sido apagado"<<endl;
            }
            break;
        default:
            cout<<"La opción escogida no existe."<<endl;
            break;
        }
    } while (opcion!=0);
    cout<<"Apagando Componentes..."<<endl;
    //Todos los terminar aqui(creo que para que todo termine tiene que estar todo encendido)
    threadPed.Terminar();
    balanceador.Terminar();
    threadEmpacador.Terminar();
    threadFacturador.Terminar();
    this_thread::sleep_for(chrono::seconds(5));
    cout<<"Componentes Apagados..."<<endl;
    cout<<"Simulación terminada..."<<endl;
    return 0;
}
