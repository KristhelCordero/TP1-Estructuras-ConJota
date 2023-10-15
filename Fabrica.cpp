#include "Funciones.cpp"

int main(int argc, char const *argv[]){
    // ColaPedidos *cola=new ColaPedidos();
    // ColaPedidosPrioridad *colaPrioridad= new ColaPedidosPrioridad();
    // ColaPedidosEspeciales *colaEspecial= new ColaPedidosEspeciales();
    // // cout<<"---------------------------- CLIENTES -------------------------------------"<<endl;
    // ListaClientes *listaClientes=new ListaClientes();
    // listaClientes->leerArchivoClientes();
    // // cout<<"---------------------------- ARTÍCULOS ------------------------------------"<<endl;
    // ListaDoble * listaArticulos=new ListaDoble();
    // listaArticulos->leerArchivoArticulos();
    // threadPedidos threadPed(cola, colaPrioridad, listaClientes, listaArticulos);
    // ListaRobots *listaRobots= new ListaRobots();
    // listaRobots->leerArchivoRobots();
    // ColaFacturacion *colaFacturacion=new ColaFacturacion();
    // ColaAlistadoos *colaAlistados=new ColaAlistadoos();
    // ThreadBalanceador balanceador(cola,colaPrioridad,listaArticulos,colaEspecial);
    // ThreadEmpacador threadEmpacador(colaFacturacion,colaAlistados);
    // ThreadFacturador threadFacturador(colaFacturacion);

    // int opcion=1;
    // do{
    //     opcion=menuPrincipal();
    //     switch (opcion){
    //     case 1:
    //         menuPedidosEspeciales(colaEspecial);
    //         break;
    //     case 2:
    //         if (balanceador.apagado){
    //             balanceador.Reanudar();
    //             cout<<"El balanceador ha sido encendido"<<endl;
    //         }else{
    //             balanceador.Pausar();
    //             cout<<"El balanceador ha sido apagado"<<endl;
    //         }
    //         break;
    //     case 3:
    //         menuNuevoCliente(listaClientes);
    //         break;
    //     case 4:
    //         menuAlistadores(); //Aqui lo que ocupes 
    //         break;
    //     case 5:
    //         menuRobots(listaRobots);
    //         break;
    //     case 6:
    //         if (threadEmpacador.apagado){
    //             threadEmpacador.Reanudar();
    //             cout<<"El empacador ha sido encendido"<<endl;
    //         }else{
    //             threadEmpacador.Pausar();
    //             cout<<"El empacador ha sido apagado"<<endl;
    //         }
    //         break;
    //     case 7:
    //         if (threadFacturador.apagado){
    //             threadFacturador.Reanudar();
    //             cout<<"El facturador ha sido encendido"<<endl;
    //         }else{
    //             threadFacturador.Pausar();
    //             cout<<"El facturador ha sido apagado"<<endl;
    //         }
    //         break;
    //     default:
    //         cout<<"La opción escogida no existe."<<endl;
    //         break;
    //     }
    // } while (opcion!=0);
    // cout<<"Apagando Componentes..."<<endl;
    // //Todos los terminar aqui(creo que para que todo termine tiene que estar todo encendido)
    // threadPed.Terminar();
    // balanceador.Terminar();
    // threadEmpacador.Terminar();
    // threadFacturador.Terminar();
    // this_thread::sleep_for(chrono::seconds(5));
    // cout<<"Componentes Apagados..."<<endl;
    // cout<<"Simulación terminada..."<<endl;

    Movimiento *prueba = new Movimiento("SAJAD ", "fecha + hora ");
    return 0;

}
