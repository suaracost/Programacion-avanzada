import java.io.EOFException;
import java.io.IOException;
import java.io.StreamCorruptedException;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main
{
    //Atributos 
    public static ArrayList<Profesor> profesores;
    public static ArrayList<Estudiante> estudiantes;
    public static ArrayList<Administrador> administradores;
    public static ArrayList<Curso> cursos;


    public static void main (String [] args) throws StreamCorruptedException, ClassNotFoundException, IOException, EOFException
    {
        //Se inicalizan las listas
        profesores = new ArrayList<Profesor>();
        administradores = new ArrayList<Administrador>();
        estudiantes = new ArrayList<Estudiante>();
        cursos = new ArrayList<Curso>();
        int opcion = 0;
        menu1();
        Scanner scanner = new Scanner(System.in);
        //Menu iterativo para login
        do 
        {
            // Se llean las listas con lo que esta en los archivos
            estudiantes.clear();
            ArchivoEstudiante.getLectura();
            administradores.clear();
            ArchivoAdministrador.getLectura();
            profesores.clear();
            ArchivoProfesor.getLectura();
            cursos.clear();
            ArchivoCurso.getLectura();

            System.out.print("\nDigite 1 una para iniciar sesión o 2 para cerrar el programa: ");
            try {
                opcion = scanner.nextInt(); 
            } catch (InputMismatchException e) {
                System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                scanner.nextLine();
                opcion = -1;
            }      
            //scanner.nextLine();
            
            switch (opcion) {
                case 1:
                    login();
                    break;

                case 2:
                    System.out.println("Programa finalizado.");
                    break;

                default:
                    System.out.println("Opción incorrecta");
                    break;
            }
            // Actualización de archivos
            ArchivoAdministrador.sobreescribir();
            ArchivoProfesor.sobreescribir();
            ArchivoEstudiante.sobreescribir();
            ArchivoCurso.sobreescribir();
        } while (opcion != 2);
    }

    public static void menu1()
    {
        System.out.println("\nBienvenido al Aula virtual Chandke space");
        System.out.println("Esta es el aula virtual donde profesores y estudiantes pueden comunicarse");

    }
    
    public static void login() throws StreamCorruptedException, ClassNotFoundException, IOException 
    {
        int i;
        boolean login = false;
        String usuario, usuariox;
        String contrasena, contrasenax;

        System.out.println("\nBienvenido al login");

        Scanner entrada = new Scanner(System.in);//Se crea el Scanner para ingresar datos
        do {
            login = false;

            System.out.print("Digite el usuario: ");
            usuario = entrada.nextLine();
            
            System.out.print("Digite la contraseña: ");
            contrasena = entrada.nextLine();

            //Se hace la verificación de que el usuario y la contraseña esten dentro de la lista
            for (i=0; i<profesores.size();i++)
            {

                usuariox = profesores.get(i).getUsuario();
                contrasenax = profesores.get(i).getContrasena();

                //Se hace la comparacion con el array de Usuarios
                if ((usuario.compareTo(usuariox)==0) && (contrasena.compareTo(contrasenax)==0)) {
                    System.out.println("Login exitoso");
                    login = true;
                    profesores.get(i).menu1();
                }
            }
            // Se hace la verificación de que el usuario y la contraseña esten dentro de la
            // lista
            for (i = 0; i < estudiantes.size(); i++) {
                // Se hace la comparacion con el array de Usuarios
 
                usuariox = estudiantes.get(i).getUsuario();
                contrasenax = estudiantes.get(i).getContrasena();

                if ((usuario.compareTo(usuariox)==0) && (contrasena.compareTo(contrasenax)==0)) {
                    System.out.println("Login exitoso");
                    login = true;
                    estudiantes.get(i).menu1();
                }
            }
            for (i = 0; i < administradores.size(); i++) {
                // Se hace la comparacion con el array de Usuarios
                
                usuariox = administradores.get(i).getUsuario();
                contrasenax = administradores.get(i).getContrasena();

                if ((usuario.compareTo(usuariox)==0) && (contrasena.compareTo(contrasenax)==0)) {
                    System.out.println("Login exitoso");
                    login = true;
                    administradores.get(i).menu1();
                }
            }
            //Si el login es falso y se recorrio toda la lista se imprime un mensaje
            if (login==false)
            {
                System.out.println("Usuario o contraseña incorrecto, vuelva a digitar sus datos");
            }

        } while (login == false);//Se repite hasta que se haga un login exitoso
    } 
}
