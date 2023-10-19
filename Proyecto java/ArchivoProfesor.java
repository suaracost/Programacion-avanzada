import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.StreamCorruptedException;
import java.util.Scanner;

public class ArchivoProfesor 
{
    public static void setEscritura() throws IOException
    {
        File file = new File("Profesores.obj");// Se crea un objeto de tipo File con la ruta del archivo
        
        // Si el archivo no existe se utliza la clase estandar de ObjectOutputStream que contiene el metodo para escribir un header
        if (!file.exists()) {
            FileOutputStream fos = new FileOutputStream(file);// Se crea un stream de salida con el archivo
            ObjectOutputStream oos = new ObjectOutputStream(fos);// Se crea un stream de salida con el archivo

            int i;
            String usuario, usuariox;
            String contrasena;
            String nombre;
            boolean repetido;
            Scanner entrada = new Scanner(System.in);

            do {
                repetido = false;
                System.out.print("\nDigite el usuario: ");
                usuario = entrada.nextLine();

                // Se recorren las listas en busca de repetidos
                for (i = 0; i < Main.profesores.size(); i++) {

                    usuariox = Main.profesores.get(i).getUsuario();

                    // Se hace la comparacion con el array de Usuarios
                    if (usuario.compareTo(usuariox) == 0) {

                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }
                for (i = 0; i < Main.estudiantes.size(); i++) {
                    // Se hace la comparacion con el array de Usuarios
                    usuariox = Main.estudiantes.get(i).getUsuario();
                    if ((usuario.compareTo(usuariox) == 0)) {
                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }
                for (i = 0; i < Main.administradores.size(); i++) {
                    // Se hace la comparacion con el array de Usuarios
                    usuariox = Main.administradores.get(i).getUsuario();
                    if ((usuario.compareTo(usuariox) == 0)) {
                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }
            } while (repetido == true);

            System.out.print("Digite la contraseña: ");
            contrasena = entrada.nextLine();

            System.out.print("Digite el nombre: ");
            nombre = entrada.nextLine();

            Profesor profesor;
            profesor = new Profesor(usuario, contrasena, nombre);

            //entrada.close();

            // Crear un nuevo usuario en la lista
            Main.profesores.add(profesor);

            oos.writeObject(profesor);// Se escribe la persona en el archivo

            oos.close();// Se cierra el Stream
        }
        // Si el archivo existe se utliza la clase modificada AppObjectOutputStream que no contiene el metodo para escribir un header
        else {
            
            FileOutputStream fos = new FileOutputStream(file, true);// Se crea un stream de salida con el archivo, se crea este stream con un append
            AppObjectOutputStream oos = new AppObjectOutputStream(fos);
            
            int i;
            String usuario, usuariox;
            String contrasena;
            String nombre;
            boolean repetido;
            Scanner entrada = new Scanner(System.in);

            do {
                repetido = false;
                System.out.print("\nDigite el usuario: ");
                usuario = entrada.nextLine();

                // Se recorren las listas en busca de repetidos
                for (i = 0; i < Main.profesores.size(); i++) {

                    usuariox = Main.profesores.get(i).getUsuario();

                    // Se hace la comparacion con el array de Usuarios
                    if (usuario.compareTo(usuariox) == 0) {

                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }
                for (i = 0; i < Main.estudiantes.size(); i++) {
                    // Se hace la comparacion con el array de Usuarios
                    usuariox = Main.estudiantes.get(i).getUsuario();
                    if ((usuario.compareTo(usuariox) == 0)) {
                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }
                for (i = 0; i < Main.administradores.size(); i++) {
                    // Se hace la comparacion con el array de Usuarios
                    usuariox = Main.administradores.get(i).getUsuario();
                    if ((usuario.compareTo(usuariox) == 0)) {
                        repetido = true;
                        System.out.println("Usuario repetido, cree otro");
                    }
                }

            } while (repetido == true);

            System.out.print("Digite la contraseña: ");
            contrasena = entrada.nextLine();

            System.out.print("Digite el nombre: ");
            nombre = entrada.nextLine();

            Profesor profesor;
            profesor = new Profesor(usuario, contrasena, nombre);

            //entrada.close();

            // Crear un nuevo usuario en la lista
            Main.profesores.add(profesor);

            oos.writeObject(profesor);// Se escribe la persona en el archivo

            oos.close();// Se cierra el Stream

        }
        
    }
    
    public static void getLectura() throws IOException, ClassNotFoundException, StreamCorruptedException
    {
        File file = new File("Profesores.obj");// Se crea un objeto de tipo File con la ruta del archivo
        if ((file.exists())&&(file.length()!=0))
        {
            FileInputStream fis = new FileInputStream(file);// Se crea un stream de entrada con el archivo
            ObjectInputStream ois = new ObjectInputStream(fis);// Se crea un stream de entrada para objetos

            // Se lee el archivo y se recuperan los objetos
            Profesor profesor;
            profesor = (Profesor) ois.readObject();
            while (profesor != null) {
                Main.profesores.add(profesor);// Se guardan los objetos en el arraylist
                try {
                    profesor = (Profesor) ois.readObject();
                } catch (EOFException e) {
                    profesor = null;
                }
            }
            ois.close();
        }
    }
    
    public static void eliminar() {
        File file = new File("Profesores.obj"); // Se crea un objeto de tipo archivo
        file.delete();
    }

    public static void sobreescribir() throws IOException
    {
        if (Main.profesores.size()!=0)
        {
            // Se escribe de cero el archivo
            File file = new File("Profesores.obj");// Se crea un objeto de tipo File con la ruta del archivo
            FileOutputStream fos = new FileOutputStream(file);// Se crea un stream de entrada con el archivo
            ObjectOutputStream oos = new ObjectOutputStream(fos);// Se crea un stream de entrada para objetos

            for (int i = 0; i < Main.profesores.size(); i++)// Se recorre el arraylist
            {
                oos.writeObject(Main.profesores.get(i));// Se escribe el objeto en el archivo
            }
            oos.close();// Se cierra el stream
        }
       else
       {
           eliminar();
       }
    }
}
