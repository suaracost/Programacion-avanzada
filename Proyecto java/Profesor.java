import java.io.Serializable;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Profesor extends Usuario implements Serializable
{
    private static final long serialVersionUID = 1L; // Indica cual es la versión de la clase
    public Profesor(String usuario, String contrasena, String nombre) {
        super(usuario, contrasena, nombre);
    }

    @Override
    public void menu1()
    {
        int opcion = 0;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        System.out.println("\nBienvenido al menu de profesor");

        do {
            System.out.print(
                    "\n Digite una opcion (1) Acceder a cursos, (2) Salir: ");

            try {
                try{
                opcion = entrada.nextInt();
                }
                catch (InputMismatchException e) {
                    System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                    entrada.nextLine();
                    opcion = -1;
                }
                switch (opcion) {
                    case 1:
                        ver_cursos();
                        break;

                    case 2:
                        System.out.println("Modulo de profesor finalizado");
                        break;

                    default:
                        System.out.println("Opcion incorrecta");
                        break;
                }
            } catch (Exception e) {
                System.out.println("ERROR GENERAL");
            }
        } while (opcion != 2);//Se verifica que se haya digitado una de las opciones

        //entrada.close();//Se cierra el Scanner

    }
    
    public void ver_cursos() {
        int opcion = 0;
        int cursoCodigo, cursoPos = 0;
        boolean noExiste;
        Scanner entrada = new Scanner(System.in);// Se crea un scanner para el input
        System.out.println("\nMenu de cursos");
        System.out.println("Tus cursos son:\n");
        
        for (int i=0; i<Main.cursos.size();i++)
        {
            for (int j=0; j<clases.size(); j++)
            {
                if(clases.get(j) == Main.cursos.get(i).getCodigo())
                {
                    Main.cursos.get(i).imprimir();
                }
            }
           
        }

        do {
            try {
                // verifica que es curso existe asociado al estudiante
                do {
                    System.out.print("\nA cual curso quieres acceder, o digita 0 para salir: ");
                    cursoCodigo = 0;
                    opcion = 0;
                    try{
                    cursoCodigo = entrada.nextInt();
                    }
                    catch (InputMismatchException e) {
                        System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                        entrada.nextLine();
                        opcion = -1;
                    }
                    noExiste = true;
                    if(opcion != -1)
                        noExiste = !Curso.verificarCurso(cursoCodigo, clases);
                    if (cursoCodigo == 0)
                        noExiste = false;
                    if (noExiste)
                        System.out.println("Opcion invalida, el codigo no esta registrado");
                } while (noExiste);
                // guarda la posicion del curso en el Arraylist
                if (cursoCodigo != 0) {
                    cursoPos = Curso.getCursoPos(cursoCodigo);
                    System.out.print("\nQue quieres hacer con el curso: " + Main.cursos.get(cursoPos).getAsignatura()
                            + "\n(1) Ver proyectos (2) Enviar Comunicados (3) Salir: ");
                    try{
                    opcion = entrada.nextInt();
                    }
                    catch (InputMismatchException e) {
                        System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                        entrada.nextLine();
                        opcion = -1;
                    }
                }
                switch (opcion) {
                    case 1:
                        ver_Proyectos(cursoPos);
                        break;

                    case 2:
                        enviar_Comentarios(cursoPos);
                        break;

                    case 3:

                    case 0:
                        System.out.println("Modulo de cursos finalizado");
                        break;
                    default:
                        System.out.println("Opcion invalida");
                        break;
                }
            } catch (InputMismatchException e) {
                // Poner en el log de excepciones
            }
        } while (opcion != 3 && opcion != 0);// Se verifica que se haya digitado una de las opciones
    }
    
    public void ver_Proyectos(int cursoPos) {
        // Esta funcion lee los projectos que estan asociados al curso
        System.out.println("Los Proyectos del curso: " + Main.cursos.get(cursoPos).getAsignatura()+":");
        Main.cursos.get(cursoPos).imprimirProyectos();
    }

    

    public void enviar_Comentarios(int cursoPos) {
        // Esta funcion envia los comunicados que estan asociados al curso
        String comentario;
        Scanner scanner = new Scanner(System.in);
        System.out.print("\nDigite el mensaje que desea enviar: ");
        comentario = scanner.nextLine();
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

        Main.cursos.get(cursoPos).comunicados.add("\nMensaje: "+comentario
                + "\nFecha: " + dtf.format(LocalDateTime.now()));
    } 
}
