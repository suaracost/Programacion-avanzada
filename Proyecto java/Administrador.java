import java.io.IOException;
import java.io.Serializable;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Administrador extends Usuario implements Serializable
{
    private static final long serialVersionUID = 1L; // Indica cual es la versión de la clase

    public Administrador(String usuario, String contrasena, String nombre) {
        super(usuario, contrasena, nombre);
    }

    @Override
    public void menu1()
    {
        int opcion = 0;
        int opcionC = 0;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input

        System.out.println("\nBienvenido al menu de administrador");

        do {
            System.out.print(
                    "\nDigite una opcion (1) Gestionar cuentas, (2) Gestionar cursos, (3) Salir: ");

            try {
                try {
                    opcion = entrada.nextInt(); 
                } catch (InputMismatchException e) {
                    System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                    entrada.nextLine();
                    opcion = -1;
                }
                //entrada.nextLine();
                switch (opcion) {
                    case 1:
                    {
                        do {

                            System.out.print(
                                        "\nDigite una opcion (1) Crear cuentas (2) Eliminar cuentas (3) Mostrar usuarios (4) Salir: ");
                            try{
                            opcionC = entrada.nextInt();
                            }
                            catch (InputMismatchException e) {
                                System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                                entrada.nextLine();
                                opcionC = -1;
                            }
                            //entrada.nextLine();

                                switch (opcionC) {
                                    case 1:
                                        try {
                                            crear_cuentas();
                                            System.out.println("Cuenta creada con exito");
                                        } catch (IOException e) {
                                            //TODO: handle exception
                                        } catch (NoSuchElementException r)
                                        {

                                        }

                                        break;

                                    case 2:
                                        borrar_cuentas();
                                        break;

                                    case 3:
                                        mostrar_usuarios();
                                        break;

                                    case 4:
                                        break;

                                    default:
                                        System.out.println("Opcion incorrecta");
                                        break;

                                } 
                            } while (opcionC != 4);
                    }
                    break;

                    case 2:
                        try {
                            gestionar_cursos();
                        } catch (IOException e) {
                            //TODO: handle exception
                        } catch (NoSuchElementException r) {

                        }

                        break;

                    case 3:
                        System.out.println("Modulo de administrador finalizado");
                        break;
                    default:
                        System.out.println("Opcion incorrecta");
                        break;
                }
            } catch (InputMismatchException e) {
                //Poner en el log de excepciones
            }
        } while (opcion != 3);//Se verifica que se haya digitado una de las opciones

        //entrada.close();//Se cierra el Scanner

    }
    
    public void mostrar_usuarios()
    {
        System.out.println("\nAdministradores:");
        for (int i = 0; i<Main.administradores.size(); i++) {
            Main.administradores.get(i).imprimir();
        }
        System.out.println("\nEstudiantes:");
        for(int i=0;i<Main.estudiantes.size();i++)
        {
            Main.estudiantes.get(i).imprimir();
        }
        System.out.println("\nProfesores:");
        for (int i = 0; i<Main.profesores.size(); i++) {
            Main.profesores.get(i).imprimir();
        }
    }
    
    public void crear_cuentas() throws IOException
    {
        String tipo;
        Boolean puede = false;
        Scanner sc = new Scanner(System.in);

        do {

            System.out.print("\n\nQue tipo de cuenta desea crear: ");
            tipo = sc.nextLine();

            switch (tipo) {
                case "estudiante":
                case "Estudiante":

                    ArchivoEstudiante.setEscritura();
                    puede = true;

                    break;

                case "profesor":
                case "Profesor":

                    ArchivoProfesor.setEscritura();
                    puede = true;

                    break;

                case "administrador":
                case "Administrador":

                    ArchivoAdministrador.setEscritura();
                    puede = true;

                    break;

                default:

                    System.out.print("Opcion no valida, intente de nuevo");

                    break;

            }
        } while (puede != true);
    }
    
    public void borrar_cuentas()
    {
        Scanner sc = new Scanner(System.in);
        boolean esta = false;
        String busca, usuariox;

        System.out.print("\nDigite el usuario de la cuenta que desea eliminar: ");
        busca = sc.nextLine();

        for (int i = 0; i < Main.profesores.size(); i++) {
            usuariox = Main.profesores.get(i).getUsuario();
            // Se hace la comparacion con el array de Usuarios
            if (busca.compareTo(usuariox) == 0) {
                Main.profesores.remove(i);
                esta = true;
            }
        }
        // Se hace la verificación de que el usuario y la contraseña esten dentro de la
        // lista
        for (int i = 0; i < Main.estudiantes.size(); i++) {
            // Se hace la comparacion con el array de Usuarios
            usuariox = Main.estudiantes.get(i).getUsuario();
            if (busca.compareTo(usuariox) == 0) {
                esta = true;
                Main.estudiantes.remove(i);
            }
        }
        for (int i = 0; i < Main.administradores.size(); i++) {
            // Se hace la comparacion con el array de Usuarios
            usuariox = Main.administradores.get(i).getUsuario();
            if (busca.compareTo(usuariox) == 0) {
                esta = true;
                Main.administradores.remove(i);
            }
        }
        if (esta == false)
            System.out.println("\nEste usuario no esta en nuestra base de datos, intente de nuevo");
    }

    public void gestionar_cursos() throws IOException
    {
        int opcion = 0, cod;
        Boolean esta = false;
        
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input

        do //Menu iterativo
        {
            System.out.print("\nDigite una opcion (1) Crear (2) Borrar (3) Mostrar (4) Salir: ");

            try 
            {
                try{
                    opcion = entrada.nextInt();
                }
                catch(InputMismatchException e)
                {
                    System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                    entrada.nextLine();
                    opcion = -1;
                }
                switch (opcion) 
                {
                    case 1://Se crea un curso
                        try {
                            ArchivoCurso.setEscritura();
                        } catch (IndexOutOfBoundsException e) {
                            System.out.println("ERROR: NUMERO DE PROFESOR NO EXISTE");
                        }
                        break;

                    case 2://Se elimina un curso

                        System.out.print("\nDigite el codigo del curso que desea eliminar: ");
                        cod = entrada.nextInt();
                        entrada.nextLine();

                        for (int i = 0; i < Main.cursos.size(); i++)//Se verifica que este el curso
                        {
                            if (cod == Main.cursos.get(i).getCodigo()) {
                                Main.cursos.remove(i);
                                esta = true;
                                System.out.println("Se ha eliminado el curso correctamente");

                                //Se elimina el curso de las clases dictadas por el profesor
                                for (int x = 0; x < Main.profesores.size(); x++) {
                                    for (int y = 0; y < Main.profesores.get(x).clases.size(); y++) {
                                        if (Main.profesores.get(x).clases.get(y) == cod) {
                                            Main.profesores.get(x).clases.remove(y);
                                        }
                                    }
                                }
                                // Se elimina el curso de las clases vistas por el estudiante
                                for (int x = 0; x < Main.estudiantes.size(); x++) {
                                    for (int y = 0; y < Main.estudiantes.get(x).clases.size(); y++) {
                                        if (Main.estudiantes.get(x).clases.get(y) == cod) {
                                            Main.estudiantes.get(x).clases.remove(y);
                                        }
                                    }
                                }
                            }
                            // Actualización de archivos
                            ArchivoProfesor.sobreescribir();
                            ArchivoEstudiante.sobreescribir();
                            ArchivoCurso.sobreescribir();
                        }
                        if (esta == false)
                            System.out.println("\nEste curso no esta en nuestra base de datos, intente de nuevo");

                        break;
                    
                    case 3:
                        System.out.println("\nCursos:");
                        for (int i = 0; i < Main.cursos.size(); i++) {//Se imprimen los cursos
                            Main.cursos.get(i).imprimir();
                        }
                        break;

                    case 4:
                        System.out.println("Haz regresado al modulo de administrador");
                        break;

                    default:
                        System.out.println("Opcion incorrecta");
                        break;
                }
            } catch (InputMismatchException e) {
                //Poner en el log de excepciones
            } 
        } while (opcion!=4);//Se verifica que se haya digitado una de las opciones

        //entrada.close();//Se cierra el Scanner
    }
}
