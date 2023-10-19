import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.StreamCorruptedException;
import java.util.Scanner;

public class ArchivoCurso 
{
    public static void setEscritura() throws IOException
    {
        File file = new File("Cursos.obj");// Se crea un objeto de tipo File con la ruta del archivo
        
        // Si el archivo no existe se utliza la clase estandar de ObjectOutputStream que contiene el metodo para escribir un header
        if (!file.exists()) {
            FileOutputStream fos = new FileOutputStream(file);// Se crea un stream de salida con el archivo
            ObjectOutputStream oos = new ObjectOutputStream(fos);// Se crea un stream de salida con el archivo

            int i, codigo, codigox, opcion;
            String asignatura;
            String profesor;
            boolean repetido;
            Scanner entrada = new Scanner(System.in);

            System.out.print("Digite el nombre de la clase: ");
            asignatura = entrada.nextLine();

            System.out.println("Estos son los profesores que tiene la institución: ");
            for (int j = 0; j < Main.profesores.size(); j++) {
                System.out.print(j + ": ");
                Main.profesores.get(j).imprimir();
            }

            System.out.print("Digite el número del profesor que ofrecera esta materia: ");
            opcion = entrada.nextInt();
            profesor = Main.profesores.get(opcion).getNombre();

            do {
                repetido = false;
                System.out.print("Digite el codigo de la asignatura: ");
                codigo = entrada.nextInt();

                // Se recorren las listas en busca de repetidos
                for (i = 0; i < Main.cursos.size(); i++) {

                    codigox = Main.cursos.get(i).getCodigo();

                    // Se hace la comparacion con el array de Usuarios
                    if (codigo == codigox) {
                        repetido = true;
                        System.out.println("Asignatura repetida, cree otro");
                    }
                }
            } while (repetido == true);

            Curso curso;
            curso = new Curso(codigo, asignatura, profesor);

            //entrada.close();

            // Crear un nuevo usuario en la lista
            Main.cursos.add(curso);
            Main.profesores.get(opcion).clases.add(codigo);

            oos.writeObject(curso);// Se escribe la persona en el archivo

            oos.close();// Se cierra el Stream
        }
        // Si el archivo existe se utliza la clase modificada AppObjectOutputStream que no contiene el metodo para escribir un header
        else {
            
            FileOutputStream fos = new FileOutputStream(file);// Se crea un stream de salida con el archivo
            ObjectOutputStream oos = new ObjectOutputStream(fos);// Se crea un stream de salida con el archivo

            int i, codigo, codigox, opcion;
            String asignatura;
            String profesor;
            boolean repetido;
            Scanner entrada = new Scanner(System.in);

            System.out.print("Digite el nombre de la clase: ");
            asignatura = entrada.nextLine();

            System.out.println("Estos son los profesores que tiene la institución: ");
            for (int j = 0; j < Main.profesores.size(); j++)
            {
                System.out.print(j+": ");
                Main.profesores.get(j).imprimir();
            }

            System.out.print("Digite el número del profesor que ofrecera esta materia: ");
            opcion = entrada.nextInt();
            profesor = Main.profesores.get(opcion).getNombre();
             
            do {
                repetido = false;
                System.out.print("Digite el codigo de la asignatura: ");
                codigo = entrada.nextInt();

                // Se recorren las listas en busca de repetidos
                for (i = 0; i < Main.cursos.size(); i++) {

                    codigox = Main.cursos.get(i).getCodigo();

                    // Se hace la comparacion con el array de Usuarios
                    if (codigo == codigox) {
                        repetido = true;
                        System.out.println("Asignatura repetida, cree otro");
                    }
                }
            } while (repetido == true);

            Curso curso;
            curso = new Curso(codigo, asignatura, profesor);

            //entrada.close();

            // Crear un nuevo usuario en la lista
            Main.cursos.add(curso);
            Main.profesores.get(opcion).clases.add(codigo);

            oos.writeObject(curso);// Se escribe la persona en el archivo

            oos.close();// Se cierra el Stream
        }
        
    }
    
    public static void getLectura() throws IOException, ClassNotFoundException, StreamCorruptedException
    {
        File file = new File("Cursos.obj");// Se crea un objeto de tipo File con la ruta del archivo
        if ((file.exists())&&(file.length()!=0))
        {
            FileInputStream fis = new FileInputStream(file);// Se crea un stream de entrada con el archivo
            ObjectInputStream ois = new ObjectInputStream(fis);// Se crea un stream de entrada para objetos

            // Se lee el archivo y se recuperan los objetos
            Curso curso;
            curso = (Curso) ois.readObject();
            while (curso != null) {
                Main.cursos.add(curso);// Se guardan los objetos en el arraylist
                try {
                    curso = (Curso) ois.readObject();
                } catch (EOFException e) {
                    curso = null;
                }
            }
            ois.close();
        }
    }
    
    public static void eliminar() {
        File file = new File("Cursos.obj"); // Se crea un objeto de tipo archivo
        file.delete();
    }

    public static void sobreescribir() throws IOException
    {
        if(Main.cursos.size()!=0)
        {
            // Se escribe de cero el archivo
            File file = new File("Cursos.obj");// Se crea un objeto de tipo File con la ruta del archivo
            FileOutputStream fos = new FileOutputStream(file);// Se crea un stream de entrada con el archivo
            ObjectOutputStream oos = new ObjectOutputStream(fos);// Se crea un stream de entrada para objetos

            for (int i = 0; i < Main.cursos.size(); i++)// Se recorre el arraylist
            {
                oos.writeObject(Main.cursos.get(i));// Se escribe el objeto en el archivo
            }
            oos.close();// Se cierra el stream
        }
        else
        {
            eliminar();
        }
    }
}
