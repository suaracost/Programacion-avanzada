#include <iostream>//librerias
#include <fstream>//librerias
#include <ctime>//librerias

using namespace std;//librerias

struct cosa//creamos estructura de los productos
{
    int codigo;
    string nombre;
    int precio;
};

struct compra//creamos estructura de la informacion de la compra
{
    string usuario;
    int fecha;
    int cuantoS;
    string productosComprados[5];
    int cantiCompra[5];
    string tipoPago;
    int valor;
    int factura;
    int estado;
    int estadoAdmin;
    compra *sig;

};

struct nodo //creamos estructura del login
{
    string rol;
    string usuario;
    string contra;
    int intentos;
    int aprobacion; //0 no aprobado, 1 si
    nodo *sig;
};

void regis(nodo *&lista, int rol, string adminU, string adminloginu, string adminC, string adminloginc);//funcion para el registro del usuario
bool login(nodo *lista, int rol, bool acceso,string *ua, string adminU, string adminloginu, string adminC, string adminloginc);//funcion para el login del usuario
void admin(string adminU, string adminloginu, string adminC, string adminloginc, int *ptr, cosa productos[]);   //funcion para el ingreso del admin
void cliente(cosa productos[],int *ptr, string usuarioActual, string adminU, string adminloginu, string adminC, string adminloginc, string procom[100], int cantiprocom[100]);//funcion para opciones del cliente
void consulta(int cantiPro, cosa productos[100], string procom[100], int cantiprocom[100], int *ptr);//funcion para las consultas

nodo *lista = NULL; //cuentas del sistema
compra *comprados = NULL;//se crean las listas para las compras
int factu=1;//variable global para contar el numero de facturas

int main() 
{
cout<<endl;    

    int rol, cantiPro = 0, op, i,*ptr;//creacion de variable y punteros
    bool acceso;//creacion de variable que permite o deniega el acceso
    string adminU = "admin", adminloginu; //Usuario
    string adminC = "contra", adminloginc;//contraseña
    cosa productos[100];//La cantidad de elementos de un mismo producto
    string usuarioActual;//para saber si cuenta con el mismo usiario
    string *ua;//puntero

    ua = &usuarioActual;// asigna al puntero el valor de la ubicacion de la variable

    fstream mandapro ("productos.txt");//Abre canal entre el codigo y el archivo que contiene los productos
    ifstream arpro ("productos.txt");//Abre canal para leer el archivo

    if (!mandapro || !arpro)//en caso de que no se pueda leer
        cout<<"no se pudieron leer los datos\n";

    else//en caso de que si se pueda leer
    {
        cout<<"los datos se leyeron correctamente\n";

        while (!arpro.eof())//hasta el archivo se acabe
        {
            arpro>>productos[cantiPro].codigo;//lee el codigo
            arpro>>productos[cantiPro].nombre;//lee el nombre
            arpro>>productos[cantiPro].precio;//lee el precio

            cantiPro++; //aunenta el numero del indice
        }

        ptr = &cantiPro;//se asigna valor al puntero
        
        string procom[cantiPro];//string del producto que se compro
        int cantiprocom[cantiPro];// Variable con el cantidad de elementos de un mismo producto que se compro

        for (int d=0; d<cantiPro; d++)// for para ir aumentado la poscion en el arreglo
        {
            procom[d] = productos[d].nombre;// se asugna el valor de procom[d] en el del arreglo de la estructura
            cantiprocom[d] = 0;
        }

        do // Para hacer un menu
        {
            acceso = false;
            
            cout<<endl<<"Roles del sistema:\n";
            cout<<endl<<"1. Administrador";
            cout<<endl<<"2. Cliente";
            cout<<endl<<"3. Consulta";
            cout<<endl<<"0. Salir";

            cout<<endl<<endl<<"Digite su opcion: ";
            cin>>rol;// elegir la opcion

            switch(rol)
            {
                case 0:// para salir
                    cout<<endl<<"Gracias por usar nuestros servicios!"<<endl<<endl;

                    break;
                
                case 1: // para ingresar al administrador
                    
                    admin(adminU, adminloginu, adminC, adminloginc, ptr, productos);//lamma la funcion

                    break;

                case 2:// para ingresar como cliente
                    do//sub menu opciones del cliente
                    {
                        cout<<endl<<"Acciones cliente:\n";
                        cout<<endl<<"1. Iniciar sesion";
                        cout<<endl<<"2. Registrarse";
                        cout<<endl<<"0. Regresar";

                        cout<<endl<<endl<<"Digite su opcion: ";
                        cin>>op;//elejir la opcion

                        switch (op)
                        {
                        case 0://regrsar al menu principal

                            cout<<endl<<"Haz regresado al menu principal\n";

                            break;

                        case 1://iniciar sesion

                            acceso = login(lista, rol, acceso,ua, adminU, adminloginu, adminC, adminloginc);
                            if (acceso == true)// si el acceso es correcto
                                cliente(productos, ptr, usuarioActual, adminU, adminloginu, adminC, adminloginc, procom, cantiprocom);//lama la funcion

                            break;

                        case 2://para registrarse

                            regis(lista, rol, adminU, adminloginu, adminC, adminloginc);

                            break;
                        
                        default:

                            cout<<endl<<"Opcion no valida, seleccione otra \n";

                            break;
                        }
                    } while (op != 0);

                    break;

                case 3://Para consulta

                    do//sub menu de consulta
                    {
                        cout<<endl<<"Acciones consulta:\n";
                        cout<<endl<<"1. Iniciar sesion";
                        cout<<endl<<"2. Registrarse";
                        cout<<endl<<"0. Regresar";

                        cout<<endl<<endl<<"Digite su opcion: ";
                        cin>>op;//elije la opcion

                        switch (op)
                        {
                        case 0://regresar menu principal

                            cout<<endl<<"Haz regresado al menu principal\n\n";

                            break;

                        case 1://iniciar sesion

                            acceso = login(lista, rol, acceso,ua, adminU, adminloginu, adminC, adminloginc);
                            
                            if (acceso == true)//si el acceso es correcto
                                consulta(cantiPro, productos, procom, cantiprocom, ptr);//lamar funcion

                            break;

                        case 2://registrarse

                            regis(lista, rol, adminU, adminloginu, adminC, adminloginc);//lama la funcion

                            break;
                        
                        default:

                            cout<<endl<<"Opcion no valida, seleccione otra \n";

                            break;
                        }
                    } while (op != 0);

                    break;

                default:  
                    cout<<endl<<"Opcion no valida, seleccione otra \n";

                    break;
            }
        
        } while (rol != 0);

    }

    for (i=0; i<*ptr; i++)//for
    {
        mandapro<<productos[i].codigo<<" "<<productos[i].nombre<<" "<<productos[i].precio;//guarda los productos en los archivos
        
        if(i<(cantiPro-1))
            mandapro<<endl;

    }

mandapro.close();//cierra mandapro
arpro.close();//cierra arpro

return 0;

}

void regis(nodo *&lista, int rol, string adminU, string adminloginu, string adminC, string adminloginc)//asigna la funcion regis
{
    string usuarioL; //crea un string para el usuario
    string contraL;   //crea un string para la contrase�a 

    cout<<"\nUsuario: "; 
    cin>>usuarioL;//se asigna el usuario

    cout<<"\nContrasena: ";
    cin>>contraL;//se asigna el contrase�a

    nodo *nuevo_nodo = new nodo(); //reservamos espacio en la memoria
    nuevo_nodo->usuario = usuarioL;//al nuevo nodo se le asigna el usuario que la persona elijio
    nuevo_nodo->contra = contraL;//al nuevo nodo se le asigna la contrase�a que la persona elijio
    nuevo_nodo->intentos = 0;//cada usuario comienza con 0 intentos 
    nuevo_nodo->aprobacion = 0; //el usuario no a sido aprovado entonces se pone 0

    if (rol == 2)//para saber si es cliente o consulta
    {
        nuevo_nodo->rol = "cliente";
    }
    else if (rol == 3)
    {
        nuevo_nodo->rol = "consulta";
    }

    cout<<endl<<"Esperando aprobacion del admin\n";

    bool acceso = false;

    do
    {
        cout<<"\nBienvenido administrador!\n";//este es el inicio de sesion del administrador
        cout<<"Ingrese su usuario: ";
        cin>>adminloginu;

        cout<<"Ingrese su contrasena: ";
        cin>>adminloginc;

        if (adminloginu == adminU && adminloginc == adminC)//si metio ambas cosas bien lo va a dejar elejir si quiere o cancelar el usuario
        {
            cout<<endl<<"Acceso correcto\n";
            cout<<endl<<"Para aceptar la creacion del usuario "<<usuarioL<<" presione 1 de lo contrario presione 0: ";
            cin>>nuevo_nodo->aprobacion;

                if (nuevo_nodo->aprobacion == 1)
                {
                    if (rol == 2)
                    {
                        cout<<endl<<"Usuario de cliente creado correctamente\n";
                    }
                    else if (rol == 3)
                    {
                        cout<<endl<<"Usuario de consulta creado correctamente\n";
                    }
                }

                else 
                    cout<<endl<<"Usuario no aceptado";
            
            acceso = true; 
        }
        else
        {
            cout<<"Usuario o contrasena incorecta, intente de nuevo\n\n";
        }
    } while (acceso != true);
    
    nodo *aux1 = lista; //creamos auxiliares para la lista
    nodo *aux2;

    while (aux1 != NULL)
    {
        aux2 = aux1;
        aux1 = aux1->sig; //recorre la lista hasta que apunte a null
    }

    if (lista == aux1)
    {
        lista = nuevo_nodo; //insertar el dato al inicio
    }
    else
    {
        aux2->sig = nuevo_nodo; //insertarlo una posicion mas
    }

    nuevo_nodo->sig = aux1; //avanza un paso

}

bool login(nodo *lista, int rol, bool acceso,string *ua, string adminU, string adminloginu, string adminC, string adminloginc)// asigna la funcion
{
    bool esta = false, entra = false;//se c
    string usuarioL;
    string contraL;

    nodo *actual = new nodo();// se crea nuevo espacio de memoria
    actual = lista;

    cout<<"\nUsuario: ";//la persona mete su usuario
    cin>>usuarioL;

    *ua = usuarioL;

    while (actual != NULL && esta != true) //recorre la lista
    {                                      
        if (rol == 2)//si es un cliente 
        {
            if (actual->usuario == usuarioL && actual->rol == "cliente" && actual->aprobacion == 0)//si tiene cuenta pero no ha sido aprovado
            {
                cout<<endl<<"Este usuario no ha sido aprobado o esta bloqueado\n";

                bool acceso = false;
    
    do
    {
        cout<<"\nBienvenido administrador!\n";//este es el inicio de sesion del administrador
        cout<<"Ingrese su usuario: ";
        cin>>adminloginu;

        cout<<"Ingrese su contrasena: ";
        cin>>adminloginc;

        if (adminloginu == adminU && adminloginc == adminC)//si mete el usuario y contrase�a bien puede elejir seguir o dejar bloqueado el usuario
        {
            cout<<endl<<"Acceso correcto\n";
            cout<<endl<<"Para desbloquear al usuario "<<usuarioL<<" presione 1 de lo contrario presione 0: ";
            cin>>actual->aprobacion;

                if (actual->aprobacion == 1)
                    cout<<endl<<"Usuario desbloqueado correctamente\n";

                else 
                    cout<<endl<<"Usuario no desbloqueado";
            
            acceso = true; 
        }
        else
        {
            cout<<"Usuario o contrasena incorecta, intente de nuevo\n\n";
        }
    } while (acceso != true);

            }

            else if (actual->usuario == usuarioL && actual->rol == "cliente" && actual->aprobacion == 1)//si el usuario se encontro y eta aprovado se pide su contrase�a
            {
                while (entra != true)
                {
                    cout<<"\nContrasena: ";
                    cin>>contraL;
                    
                    if (actual->contra == contraL)//si la contrase�a concuerda retorna un valor booleano al main
                    {
                        cout<<endl<<"Acceso exitoso, bienvenido\n";
                        actual->intentos = 0;
                        entra = true;
                        acceso = true;
                    }
                    else //si falla se suma un intento
                    {
                        cout<<endl<<"Contrasena incorrecta\n";
                        actual->intentos = actual->intentos + 1;

                        if (actual->intentos >= 3)//si llega a tres intentos se bloquea
                        {
                            cout<<endl<<"Este usuario ha sido bloqueado, hable con un administrador para que lo desbloquee\n";
                            actual->aprobacion = 0;

                            break;
                        }
                    }
                }

                if (entra == true)
                    esta = true;

            }
        }
        else if (rol == 3)// si rol es =3 entonces es para un usuario de consulta entonces se repite todo lo de arriba
        {
            if (actual->usuario == usuarioL && actual->rol == "consulta" && actual->aprobacion == 0)
            {
                cout<<endl<<"Este usuario no ha sido aprobado o esta bloqueado\n";
            }

            else if (actual->usuario == usuarioL && actual->rol == "consulta" && actual->aprobacion == 1)
            {
                while (entra != true)
                {
                    cout<<"\nContrasena: ";
                    cin>>contraL;
                    
                    if (actual->contra == contraL)
                    {
                        cout<<endl<<"Acceso exitoso, bienvenido\n";
                        actual->intentos = 0;
                        entra = true;
                        acceso = true;
                    }
                    else 
                    {
                        cout<<endl<<"Contrasena incorrecta\n";
                        actual->intentos = actual->intentos + 1;

                        if (actual->intentos >= 3)
                        {
                            cout<<endl<<"Este usuario ha sido bloqueado, hable con un administrador para que lo desbloquee\n";
                            actual->aprobacion = 0;

                            break;
                        }
                    }
                }

                if (entra == true)
                    esta = true;

            }
    
        }
        actual = actual->sig;
    }

    if (entra == false)
    {
        cout<<endl<<"Vuelve a intentarlo\n";
    }

    return acceso;

cout<<endl;
}  

void admin(string adminU, string adminloginu, string adminC, string adminloginc, int *ptr, cosa productos[])  //se asigna la funcion admin 
{
    bool acceso = false;
    int opciones;

    do
    {
        cout<<"\nBienvenido administrador!\n";
        cout<<"Ingrese su usuario: ";
        cin>>adminloginu;

        cout<<"Ingrese su contrasena: ";
        cin>>adminloginc;

        if (adminloginu == adminU && adminloginc == adminC)
        {
            do // se utiliza un sub menu para la opcion administrador
            {
                cout<<endl<<"Acciones administrador:\n";
                cout<<endl<<"1. Administrar cuentas sin aprobacion";
                cout<<endl<<"2. Administrar productos";
                cout<<endl<<"3. Despachar ordenes";
                cout<<endl<<"0. Regresar";

                cout<<endl<<endl<<"Digite su opcion: ";
                cin>>opciones;

                switch (opciones)// se elije que caso quiere hacer
                {
                    case 0://regresa al menu principal

                        cout<<endl<<"Haz regresado al menu principal\n";

                        break;

                    case 1://es para administrar cuentas sin aprovacion el admin sera llamado cuando una cuenta bloqueada solicite entrar

                        cout<<endl<<"Debes esperar que una cuenta sea bloqueada o solicite un acceso nuevo";
                        cout<<endl<<"Cuando esto suceda el administrador sera solicitado";

                        break;

                    case 2://Administra productos
                    {
                        int opAdmin;

                        cout<<endl<<"Ha seleccionado 'Administrar productos'";
                        cout<<endl<<"1. Cambiar precio";
                        cout<<endl<<"2. Agregar producto";
                        cout<<endl<<"3. Quitar producto";
                        cout<<endl<<"0. Regresar";

                        cout<<endl<<endl<<"Digite su opcion: ";
                        cin>>opAdmin;

                        switch (opAdmin)
                        {
                        case 0://regresar al menu de administrador

                            cout<<endl<<"Haz regresado al menu de administrador\n";

                            break;

                        case 1://Actualiza la estructura de los productos
                        {
                            string procambio;
                            int nuevoPrecio;
                            int i;
                            
                            cout<<endl<<"Estos son nuestros productos: ";
                            for(i=0;i<*ptr;i++)
                            {
                                cout<<endl<< "Codigo: "<<productos[i].codigo<<"\tNombre: "<<productos[i].nombre<< "\tPrecio: "<<productos[i].precio;
                            }
                            
                            cout<<endl<<endl<<"De que producto quieres cambiar el precio? ";
                            cin>>procambio;

                            for (i=0; i<*ptr; i++)
                            {
                                if (procambio == productos[i].nombre)
                                {
                                    cout<<endl<<"Cual es el nuevo precio? ";
                                    cin>>nuevoPrecio;

                                    productos[i].precio = nuevoPrecio;
                                }
                            }
                            
                            break;
                        }

                        case 2://Crea un nuevo producto
                        {
                            string nombre;
                            int precioN, codigoN;
                            int auxArreglo = *ptr;
                            
                            cout<<endl<<"Escriba el nombre del nuevo producto: ";
                            cin>>nombre;

                            cout<<endl<<"Escriba el codigo del nuevo producto: ";
                            cin>>codigoN;

                            cout<<endl<<"Escriba el precio del nuevo producto: ";
                            cin>>precioN;

                            auxArreglo = auxArreglo + 1;

                            *ptr = auxArreglo;

                            productos[auxArreglo-1].nombre = nombre;
                            productos[auxArreglo-1].codigo = codigoN;
                            productos[auxArreglo-1].precio = precioN;

                            break;
                        }
                        case 3://elimina un producto
                        {
                            string elimi;
                            int i, auxArreglo = *ptr, x = 0;
                            cosa nuevoArreglo[auxArreglo];
                            
                            cout<<endl<<"Estos son nuestros productos: ";
                            for(i=0;i<*ptr;i++)
                            {
                                cout<<endl<< "Codigo: "<<productos[i].codigo<<"\tNombre: "<<productos[i].nombre<< "\tPrecio: "<<productos[i].precio;
                            }
                            
                            cout<<endl<<endl<<"Que producto desea eliminar? ";
                            cin>>elimi;

                            for (i=0; i<*ptr; i++)
                            {
                                if (productos[i].nombre == elimi)
                                {
                                    auxArreglo--;
                                }

                                else 
                                {
                                    nuevoArreglo[x].nombre = productos[i].nombre;
                                    nuevoArreglo[x].codigo = productos[i].codigo;
                                    nuevoArreglo[x].precio = productos[i].precio;
                                    x++;
                                }
                            }
                            
                            for (i=0; i<auxArreglo; i++)
                            {
                                productos[i].nombre = nuevoArreglo[i].nombre;
                                productos[i].codigo = nuevoArreglo[i].codigo;
                                productos[i].precio = nuevoArreglo[i].precio;
                            }

                            *ptr = auxArreglo;

                            cout<<endl<<"Producto borrado exitosamente";

                            cout<<endl<<"Este es el catalogo nuevo: ";
                            
                            for(i=0;i<*ptr;i++)
                            {
                                cout<<endl<< "Codigo: "<<productos[i].codigo<<"\tNombre: "<<productos[i].nombre<< "\tPrecio: "<<productos[i].precio;
                            }

                            cout<<endl;

                            break;
                        }
                        
                        default:

                            cout<<endl<<"Opcion no valida selecione otra\n";
                            
                            break;
                        }

                        break;
                    }
                    
                    case 3://Para despachar compras el admin sera llamdo para confirmar

                        cout<<endl<<"Debes esperar que un usuario haga un compra";
                        cout<<endl<<"Cuando esto suceda el administrador sera solicitado";

                        break;
                    
                    default:

                        cout<<endl<<"Opcion no valida, seleccione otra \n";

                        break;

                }

            } while (opciones != 0); 

            acceso = true; 
        }
        else
        {
            cout<<"Usuario o contrasena incorecta, intente de nuevo\n\n";
        }
    } while (acceso != true);

}

void cliente(cosa productos[], int *ptr, string usuarioActual, string adminU, string adminloginu, string adminC, string adminloginc, string procom[100], int cantiprocom[100])//se asigna la funcio n cliente
{
    int opciones,i,cuanto,j;
    int valor,auxPago;

    do //se crea un sub menu para cliente
    {
        cout<<endl<<"Menu:\n"; 
        cout<<endl<<"1. Hacer compra";
        cout<<endl<<"2. Valor total compras";
        cout<<endl<<"3. Cantidad productos comprados";
        cout<<endl<<"0. Salir";

        cout<<endl<<endl<<"Digite su opcion: "; 
        cin>>opciones;

        time_t now = time(0); //unas cosas que se deben hacer para traer el tiempo local al archivo

        tm * time = localtime(&now); // las pongo dentro del ciclo para que se actualice la hora

        switch(opciones)
        {
            case 1://para realizar una compra
            {
                cout<<endl<<"Estos son nuestros productos: ";
                for(i=0;i<*ptr;i++)
                {
                    cout<<endl<< "Codigo: "<<productos[i].codigo<<"\tNombre: "<<productos[i].nombre<< "\tPrecio: "<<productos[i].precio;
                }

                compra *nuevo_nodo = new compra();// se guarda un espacio en la memoria para un nuevo nodo
                nuevo_nodo -> usuario = usuarioActual;
                nuevo_nodo -> fecha = time->tm_mday*1000000 + (1 + time->tm_mon)*10000 + 1900 + time->tm_year;// se usa una libreria para traer la fecha actual, se multiplica por esos valores para que quede como fecha es igual a dia/mes/a�o
                
                cuanto=6;
                valor=0;
                while(cuanto>5)
                {
                    cout<<endl<<endl<< "Cuantos productos va a querer?(maximo 5 productos) ";
                    cin>>cuanto;
                    nuevo_nodo->cuantoS = cuanto;
                }
                
               
                for(i = 0;i<cuanto;i++)
                {
                   cout<<endl<<"Nombre del producto "<<i+1<<" : ";
                   cin>>nuevo_nodo -> productosComprados[i];  
                   nuevo_nodo->cantiCompra[i] = 101; 
                   while(nuevo_nodo->cantiCompra[i]>100)
                   {
                        cout<<endl<<"Cuantos va a llevar?(maximo 100 unidades) ";
                        cin>>nuevo_nodo->cantiCompra[i]; 
                   } 

                   for(int d = 0; d<*ptr; d++)
                   {
                        if (nuevo_nodo->productosComprados[i] == procom[d])
                        {
                            cantiprocom[d] = cantiprocom[d] + nuevo_nodo->cantiCompra[i];
                        }
                   }
                   
                }

                for(i = 0;i < cuanto; i++)
                {
                    for(j=0; j < *ptr; j++)
                    {
                        if(nuevo_nodo->productosComprados[i] == productos[j].nombre)
                        {
                            valor = valor + nuevo_nodo->cantiCompra[i]*productos[j].precio;
                        }
                    }
                    
                }
                nuevo_nodo ->valor = valor;
                cout<<endl<<"EL valor de su compra es "<<valor<<". \nPara confirmar su compra pulse '1', para cancelar pulse '2':  ";//confirmar el pedido
                cin>>nuevo_nodo->estado;

                if(nuevo_nodo->estado == 2)
                {
                    cout<<endl<<"Has cancelado tu compra :( ";
                }
                else 
                {
                    cout<<endl<<"Selecciona el metodo de pago ";//elejir el metodo de pago
                    cout<<endl<<"1. Tarjeta de credito";
                    cout<<endl<<"2. Efectivo";
                    cout<<endl<<endl<<"Dijite su opcion: ";
                    cin>>auxPago;

                    if(auxPago == 1)
                    {
                        nuevo_nodo->tipoPago = "Tarjeta de credito";
                    }
                    else if(auxPago == 2)
                    {
                        nuevo_nodo->tipoPago = "Efectivo";
                    }
                    nuevo_nodo->factura = factu;

                    factu = factu + 1;

                    cout<<endl<<"Compra exitosa, esperando a ser despachada \n";

                    cout<<endl<<"Espere que el administrador despache su compra\n";

                    bool acceso = false;
    
                    do//aca se llama el admin para confirmar la compra
                    {
                        cout<<"\nBienvenido administrador!\n";
                        cout<<"Ingrese su usuario: ";
                        cin>>adminloginu;

                        cout<<"Ingrese su contrasena: ";
                        cin>>adminloginc;

                        if (adminloginu == adminU && adminloginc == adminC)
                        {
                            cout<<endl<<"Acceso correcto\n";
                            cout<<endl<<"Para despachar la compra del usuario "<<usuarioActual<<" presione 1 de lo contrario presione 2: ";
                            cin>>nuevo_nodo->estadoAdmin;

                                if (nuevo_nodo->estadoAdmin == 1)
                                    cout<<endl<<"Compra despachada\n";

                                else 
                                    cout<<endl<<"Compra no despachada\n";
                            
                            acceso = true; 
                        }
                        else
                        {
                            cout<<"Usuario o contrasena incorecta, intente de nuevo\n\n";
                        }
                    } while (acceso != true);

                }
                
                compra *aux1 = comprados; //creamos auxiliares para la lista
                
                compra *aux2;

                while (aux1 != NULL)
                {
                    aux2 = aux1;
                    aux1 = aux1->sig; //recorre la lista hasta que apunte a null
                }

                if (comprados == aux1)
                {
                    comprados = nuevo_nodo; //insertar el dato al inicio
                }
                else
                {
                    aux2->sig = nuevo_nodo; //insertarlo una posicion mas
                }

                    nuevo_nodo->sig = aux1; //avanza un paso
                
                break;
            }
            case 2:// saber el valor total de la compra
            {
                int sumaValores=0;

                compra *actual = new compra();

                actual = comprados;

                while (actual != NULL) //recorre la lista y cuando encuentre el valor
                {                                      // muestra sus datos y sale del ciclo
                    if (actual->usuario == usuarioActual)
                    {
                        sumaValores = sumaValores + actual->valor;
                    }
                    actual = actual->sig;
                }

                    cout<<endl<<"El usuario "<<usuarioActual<<" ha gastado $"<<sumaValores<<" pesos"<<endl;

                break;
            }
            case 3://saber la cantidad de productos comprados
            {
                int sumaCosas=0,cosas=0;

                compra *actual = new compra();

                actual = comprados;
                
                
                while (actual != NULL) //recorre la lista y cuando encuentre el valor
                {   
                    for(i=0;i<cuanto;i++)
                    {
                        cosas = cosas + actual->cantiCompra[i];
                    }                                 

                    if (actual->usuario == usuarioActual)
                    {
                        sumaCosas = sumaCosas + cosas;
                    }
                    actual = actual->sig;
                }

                    cout<<endl<<"El usuario "<<usuarioActual<<" ha comprado "<<sumaCosas<<" productos"<<endl;

                break;
            }

            case 0:// regresar al menu principal
                        
                cout<<endl<<"Regresaste al menu principal"<<endl;

                break;
                    
            default:  
                
                cout<<endl<<"Opcion no valida, seleccione otra \n";
 
        }

    } while (opciones != 0);

    cout<<"\n"; //cada elemento de la lista esta separado por un salto de linea
    
}

void consulta(int cantiPro, cosa productos[100], string procom[100], int cantiprocom[100], int *ptr)// se asigna la funcion consulta 
{
    int consul;
    char orden;
    bool cierre1 = false, cierre2 = false, cierre3 = false;
    int j, k, aux, code[cantiPro];

    for(j=0;j<cantiPro;j++)
    {
        code[j] = productos[j].codigo;
    }

    do 
    {
        cout<<endl<<"Que desea hacer?\n";
        cout<<endl<<"1. Listar productos";
        cout<<endl<<"2. Listar clientes";
        cout<<endl<<"3. Total de ventas";
        cout<<endl<<"4. Producto mas comprado";
        cout<<endl<<"5. Listar compras";
        cout<<endl<<"0. Regresar";

        cout<<endl<<endl<<"Digite su opcion: ";
        cin>>consul;

        switch(consul)
        {
            case 0:
                cout<<endl<<"Regresaste al menu principal"<<endl;

                break;
            
            case 1: 
                //Listar productos usando metodo burbuja

                do
                {

                    cout<<endl<<"como desea ordenar los productos?\n";
                    cout<<endl<<"a. Orden ascendente (dependiendo del codigo)";
                    cout<<endl<<"d. Orden descendente (dependiendo del codigo)";
                    cout<<endl<<"r. Regresar";

                    cout<<endl<<endl<<"Digite su opcion (minusculas) : ";
                    cin>>orden;

                    switch(orden)
                    {
                        case 'r'://regresa al menu de consulta

                            cout<<endl<<"Regresaste al menu de consultas"<<endl;
                            cierre1 = true;

                            break;
                        
                        case 'a'://ordenar acendente

                            for (k=0; k<cantiPro; k++)
                            {
                                for(j=0;j<cantiPro;j++)
                                {
                                    if(code[k] < code[j])
                                    {
                                        aux = code[k];
                                        code[k] = code[j];
                                        code[j] = aux;
                                    }
                                }
                            }   
                            
                            cout<<"Estos son los productos: ";
                            
                            for (k=0; k<cantiPro; k++)
                            {
                                for(j=0;j<cantiPro;j++)
                                {
                                    if (code[k] == productos[j].codigo)
                                    {
                                        cout<<endl<<"Codigo: "<<productos[j].codigo;
                                        cout<<"\tNombre: "<<productos[j].nombre;
                                        cout<<"\tPrecio: "<<productos[j].precio;
                                    }
                                }
                            }

                            cout<<endl;

                            cierre1 = true;

                            break;

                        case 'd':// ordenar decente

                            for (k=0; k<cantiPro; k++)
                            {
                                for(j=0;j<cantiPro;j++)
                                {
                                    if(code[k] > code[j])
                                    {
                                        aux = code[k];
                                        code[k] = code[j];
                                        code[j] = aux;
                                    }
                                }
                            }                            
                            
                            cout<<"Estos son los productos: ";
                            
                            for (k=0; k<cantiPro; k++)
                            {
                                for(j=0;j<cantiPro;j++)
                                {
                                    if (code[k] == productos[j].codigo)
                                    {
                                        cout<<endl<<"Codigo: "<<productos[j].codigo;
                                        cout<<"\tNombre: "<<productos[j].nombre;
                                        cout<<"\tPrecio: "<<productos[j].precio;
                                    }
                                }
                            }

                            cout<<endl;

                            cierre1 = true;
                        
                            break;

                        default:

                            cout<<endl<<"Opcion no valida, seleccione otra \n";
                        
                            break;
                    }

                } while (cierre1 != true);

                break;

            case 2:
            {   //Listar clientes usando metodo quicksort
                do
                {

                    cout<<endl<<"como desea ordenar los clientes?\n";
                    cout<<endl<<"a. Orden ascendente (alfabeticamente)";
                    cout<<endl<<"d. Orden descendente (alfabeticamente)";
                    cout<<endl<<"r. Regresar";

                    cout<<endl<<endl<<"Digite su opcion (minusculas) : ";
                    cin>>orden;

                    switch(orden)
                    {
                        case 'r'://regresar

                            cout<<endl<<"Regresaste al menu de consultas"<<endl;

                            break;
                        
                        case 'a'://ordenar acendente
                        {
                            nodo *actual;
                            actual = lista;

                            string aux1, aux2, aux3;
                            int aux4, aux5;
                            
                            while (actual != NULL)
                            {
                                nodo *ordena = actual->sig;

                                while (ordena != NULL)
                                {
                                    if (actual->usuario > ordena->usuario) //esto es un metodo basico de ordenacion
                                    {                                    
                                        aux1 = ordena->usuario;
                                        ordena->usuario = actual->usuario;
                                        actual->usuario = aux1;

                                        aux2 = ordena->rol;
                                        ordena->rol = actual->rol;
                                        actual->rol = aux2;

                                        aux3 = ordena->contra;
                                        ordena->contra = actual->contra;
                                        actual->contra = aux3;

                                        aux4 = ordena->intentos;
                                        ordena->intentos = actual->intentos;
                                        actual->intentos = aux4;

                                        aux5 = ordena->aprobacion;
                                        ordena->aprobacion = actual->aprobacion;
                                        actual->aprobacion = aux5;
                                        
                                    }
                                    
                                    ordena = ordena->sig;
                                }

                                actual = actual->sig;
                            }

                            nodo *mostrar;
                            mostrar = lista;

                            cout<<endl<<endl<<"Estas son todas las cuentas en nuestra base de datos: \n";
                            while (mostrar != NULL) //recorre la lista y va imprimiendo lo que contiene
                            {
                                cout<<"Usuario: "<<mostrar->usuario<<"\t";
                                cout<<" \tRol: "<<mostrar->rol<<"\t";
                                cout<<" \tIntentos: "<<mostrar->intentos<<"\t";
                                cout<<" \tAprobacion: "<<mostrar->aprobacion<<"\t\n";
                                mostrar = mostrar->sig;
                            }

                            cierre2 = true;

                            break;
                        } 

                        case 'd':// ordenar decente
                        {
                        nodo *actual;
                        actual = lista;

                        string aux1, aux2, aux3;
                        int aux4, aux5;
                        
                        while (actual != NULL)
                        {
                            nodo *ordena = actual->sig;

                            while (ordena != NULL)
                            {
                                if (actual->usuario < ordena->usuario) //esto es un metodo basico de ordenacion
                                {                                    
                                    aux1 = ordena->usuario;
                                    ordena->usuario = actual->usuario;
                                    actual->usuario = aux1;

                                    aux2 = ordena->rol;
                                    ordena->rol = actual->rol;
                                    actual->rol = aux2;

                                    aux3 = ordena->contra;
                                    ordena->contra = actual->contra;
                                    actual->contra = aux3;

                                    aux4 = ordena->intentos;
                                    ordena->intentos = actual->intentos;
                                    actual->intentos = aux4;

                                    aux5 = ordena->aprobacion;
                                    ordena->aprobacion = actual->aprobacion;
                                    actual->aprobacion = aux5;
                                    
                                }
                                
                                ordena = ordena->sig;
                            }

                            actual = actual->sig;
                        }

                        nodo *mostrar;
                        mostrar = lista;

                        cout<<endl<<endl<<"Estas son todas las cuentas en nuestra base de datos: \n";
                        while (mostrar != NULL) //recorre la lista y va imprimiendo lo que contiene
                        {
                            cout<<"Usuario: "<<mostrar->usuario<<"\t";
                            cout<<" \tRol: "<<mostrar->rol<<"\t";
                            cout<<" \tIntentos: "<<mostrar->intentos<<"\t";
                            cout<<" \tAprobacion: "<<mostrar->aprobacion<<"\t\n";
                            mostrar = mostrar->sig;
                        }

                        cierre2 = true;

                        break;
                    } 

                        default:

                            cout<<endl<<"Opcion no valida, seleccione otra \n";
                        
                            break;
                    }

                } while (cierre2 != true);

                break;
            }

            case 3:
            { 
                //Total de ventas

                cout<<endl<<"Han habido "<<factu-1<<" ventas en nuestra tienda\n";

                break;
            }

            case 4:
            {
                //Producto mas comprado
                int caux;
                string paux;

                for (k=0; k<*ptr; k++)
                {
                    for(j=0;j<*ptr;j++)
                    {
                        if(cantiprocom[k] > cantiprocom[j])
                        {
                            caux= cantiprocom[k];
                            cantiprocom[k] = cantiprocom[j];
                            cantiprocom[j] = caux;

                            paux= procom[k];
                            procom[k] = procom[j];
                            procom[j] = paux;
                        }
                    }
                }

                cout<<endl<<"El producto mas comprado fue "<<procom[0]<<", fue comprado "<<cantiprocom[0]<<" veces\n";

                break;
            }

            case 5:
                //Listar compras en metodo burbuja

                do
                {

                    cout<<endl<<"como desea ordenar las compras?\n";
                    cout<<endl<<"a. Orden ascendente (dependiendo de la factura)";
                    cout<<endl<<"d. Orden descendente (dependiendo de la factura)";
                    cout<<endl<<"r. Regresar";

                    cout<<endl<<endl<<"Digite su opcion (minusculas) : ";
                    cin>>orden;

                    switch(orden)
                    {
                        case 'r':// regresar al menu

                            cout<<endl<<"Regresaste al menu de consultas"<<endl;

                            break;
                        
                        case 'a'://ordenar acendente
                        {
                            compra *actual;
                            actual = comprados;

                            string aux1a, aux4a[5], aux6a;
                            int aux2a, aux3a, aux5a[5], aux7a, aux8a, aux9a, aux0a;

                            
                            while (actual != NULL)
                            {
                                compra *ordena = actual->sig;

                                while (ordena != NULL)
                                {
                                    if (actual->factura > ordena->factura) //esto es un metodo basico de ordenacion
                                    {                                    
                                        aux1a = ordena->usuario;
                                        ordena->usuario = actual->usuario;
                                        actual->usuario = aux1a;

                                        aux2a = ordena->fecha;
                                        ordena->fecha = actual->fecha;
                                        actual->fecha = aux2a;

                                        aux3a = ordena->cuantoS;
                                        ordena->cuantoS = actual->cuantoS;
                                        actual->cuantoS = aux3a;

                                        for (int y=0; y<aux3a; y++)
                                        {
                                        aux4a[y] = ordena->productosComprados[y];
                                        ordena->productosComprados[y] = actual->productosComprados[y];
                                        actual->productosComprados[y] = aux4a[y];

                                        aux5a[y] = ordena->cantiCompra[y];
                                        ordena->cantiCompra[y] = actual->cantiCompra[y];
                                        actual->cantiCompra[y] = aux5a[y];
                                        }

                                        aux6a = ordena->tipoPago;
                                        ordena->tipoPago = actual->tipoPago;
                                        actual->tipoPago = aux6a;

                                        aux7a = ordena->valor;
                                        ordena->valor = actual->valor;
                                        actual->valor = aux7a;

                                        aux8a = ordena->factura;
                                        ordena->factura = actual->factura;
                                        actual->factura = aux8a;

                                        aux9a = ordena->estado;
                                        ordena->estado = actual->estado;
                                        actual->estado = aux9a;

                                        aux0a = ordena->estadoAdmin;
                                        ordena->estadoAdmin = actual->estadoAdmin;
                                        actual->estadoAdmin = aux0a;
                                        
                                    }
                                    
                                    ordena = ordena->sig;
                                }

                                actual = actual->sig;
                            }

                            compra *mostrar;
                            mostrar = comprados;

                            cout<<endl<<endl<<"Estas son todas las ventas hechas en nuestra tienda: \n";
                            while (mostrar != NULL) //recorre la lista y va imprimiendo lo que contiene
                            {
                                cout<<"Usuario: "<<mostrar->usuario<<"\t";
                                cout<<" Fecha: "<<mostrar->fecha<<"\t";
                                cout<<" #Productos: "<<mostrar->cuantoS<<"\t";
                                for (int z=0; z<mostrar->cuantoS; z++)
                                {   
                                    cout<<" Producto: "<<mostrar->productosComprados[z]<<": ";
                                    cout<<mostrar->cantiCompra[z]<<"\t";
                                }
                                cout<<" Tipo de pago: "<<mostrar->tipoPago<<"\t";
                                cout<<" Valor: "<<mostrar->valor<<"\t";
                                cout<<" #Factura: "<<mostrar->factura<<"\t";
                                cout<<" Estado cliente: "<<mostrar->estado<<"\t";
                                cout<<" Estado administrador: "<<mostrar->estadoAdmin<<"\n";
                                mostrar = mostrar->sig;
                            }

                            cierre3 = true;

                            break;
                        }

                        case 'd'://ordenar decendente
                        {
                            compra *actual;
                            actual = comprados;

                            string aux1a, aux4a[5], aux6a;
                            int aux2a, aux3a, aux5a[5], aux7a, aux8a, aux9a, aux0a;

                            
                            while (actual != NULL)
                            {
                                compra *ordena = actual->sig;

                                while (ordena != NULL)
                                {
                                    if (actual->factura < ordena->factura) //esto es un metodo basico de ordenacion
                                    {                                    
                                        aux1a = ordena->usuario;
                                        ordena->usuario = actual->usuario;
                                        actual->usuario = aux1a;

                                        aux2a = ordena->fecha;
                                        ordena->fecha = actual->fecha;
                                        actual->fecha = aux2a;

                                        aux3a = ordena->cuantoS;
                                        ordena->cuantoS = actual->cuantoS;
                                        actual->cuantoS = aux3a;

                                        for (int y=0; y<aux3a; y++)
                                        {
                                        aux4a[y] = ordena->productosComprados[y];
                                        ordena->productosComprados[y] = actual->productosComprados[y];
                                        actual->productosComprados[y] = aux4a[y];

                                        aux5a[y] = ordena->cantiCompra[y];
                                        ordena->cantiCompra[y] = actual->cantiCompra[y];
                                        actual->cantiCompra[y] = aux5a[y];
                                        }

                                        aux6a = ordena->tipoPago;
                                        ordena->tipoPago = actual->tipoPago;
                                        actual->tipoPago = aux6a;

                                        aux7a = ordena->valor;
                                        ordena->valor = actual->valor;
                                        actual->valor = aux7a;

                                        aux8a = ordena->factura;
                                        ordena->factura = actual->factura;
                                        actual->factura = aux8a;

                                        aux9a = ordena->estado;
                                        ordena->estado = actual->estado;
                                        actual->estado = aux9a;

                                        aux0a = ordena->estadoAdmin;
                                        ordena->estadoAdmin = actual->estadoAdmin;
                                        actual->estadoAdmin = aux0a;
                                        
                                    }
                                    
                                    ordena = ordena->sig;
                                }

                                actual = actual->sig;
                            }

                            compra *mostrar;
                            mostrar = comprados;

                            cout<<endl<<endl<<"Estas son todas las ventas hechas en nuestra tienda: \n";
                            while (mostrar != NULL) //recorre la lista y va imprimiendo lo que contiene
                            {
                                cout<<"Usuario: "<<mostrar->usuario<<"\t";
                                cout<<" Fecha: "<<mostrar->fecha<<"\t";
                                cout<<" #Productos: "<<mostrar->cuantoS<<"\t";
                                for (int z=0; z<mostrar->cuantoS; z++)
                                {   
                                    cout<<" Producto: "<<mostrar->productosComprados[z]<<": ";
                                    cout<<mostrar->cantiCompra[z]<<"\t";
                                }
                                cout<<" Tipo de pago: "<<mostrar->tipoPago<<"\t";
                                cout<<" Valor: "<<mostrar->valor<<"\t";
                                cout<<" #Factura: "<<mostrar->factura<<"\t";
                                cout<<" Estado cliente: "<<mostrar->estado<<"\t";
                                cout<<" Estado administrador: "<<mostrar->estadoAdmin<<"\n";
                                mostrar = mostrar->sig;
                            }

                            cierre3 = true;

                            break;
                        }

                        default:

                            cout<<endl<<"Opcion no valida, seleccione otra \n";
                        
                            break;
                    }

                } while (cierre3 != true);

                break;

            default:  
                cout<<endl<<"Opcion no valida, seleccione otra \n";

                break;
        } 

    } while (consul != 0);

}
//fin