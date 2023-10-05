#include "Funciones.cpp"

int main(int argc, char const *argv[])
{
    ColaPedidos *cola=new ColaPedidos();
    ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    cout<<"---------------------------- CLIENTES ------------------------------------"<<endl;
    ListaClientes *listaClientes=new ListaClientes;
    listaClientes->leerArchivoClientes();
    listaClientes->imprimir();
    cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    ListaDoble * listaArticulos=new ListaDoble();
    listaArticulos->leerArchivoArticulos();
    listaArticulos->imprimir();
    
    threadPedidos threadPed(cola, colaPrioridad, listaClientes,listaArticulos);
    
    this_thread::sleep_for(chrono::seconds(9));
    threadPed.Terminar();

    cout<<"---------------------------- COLAS ------------------------------------"<<endl;
    colaPrioridad->imprimir();
    cout<<"---------------------------- COLAS ------------------------------------"<<endl;
    cola->imprimir();
    return 0;
}
