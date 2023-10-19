import java.io.IOException;
import java.io.Serializable;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Estudiante extends Usuario implements Serializable
{
    private static final long serialVersionUID = 1L; // Indica cual es la versión de la clase

    public Estudiante(String usuario, String contrasena, String nombre) {
        super(usuario, contrasena, nombre);
    }
    
    @Override
    public void menu1()
    {
        int opcion=0;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        System.out.println("Bienvenido al menu de estudiante");
        do 
        {
            System.out.print("\nDigite una opcion (1) Ver Cursos, (2) Incribir o Retirar cursos, (3) Salir: ");
            try 
            {
                try{
                opcion = entrada.nextInt();
                }
                catch(InputMismatchException e){
                    System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                    entrada.nextLine();
                    opcion = -1;
                }
                switch (opcion) {
                    case 1:
                        ver_cursos();
                        break;

                    case 2:
                        ior_cursos();
                        break;

                    case 3:
                        System.out.println("Modulo de estudiante finalizado");
                        break;
                    default:
                        System.out.println("Opcion incorrecta");
                        break;
                }
            } 
            catch (IOException e) 
            {
                //Poner en el log de excepciones
            } 
        } while (opcion!=3);//Se verifica que se haya digitado una de las opciones
        //entrada.close();//Se cierra el Scanner
    }

    public void ver_cursos(){
        int opcion = 0;
        int cursoCodigo, cursoPos = 0;
        boolean noExiste;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        System.out.println("Menu de cursos");
        System.out.println("Tus cursos son:\n");
        System.out.println();
        for (int i = 0; i < Main.cursos.size(); i++) {
            for (int j = 0; j < clases.size(); j++) {
                if (Main.cursos.get(i).getCodigo() == clases.get(j)) {
                    Main.cursos.get(i).imprimir();
                }
            }
        }
        System.out.println();
        do 
        {
            try 
            {
                //verifica que es curso existe asociado al estudiante
                do{
                System.out.print("\nA cual curso quieres acceder, o digita 0 para salir: ");
                cursoCodigo = 0; opcion = 0;
                cursoCodigo = entrada.nextInt();
                noExiste = !Curso.verificarCurso(cursoCodigo,clases);
                if(cursoCodigo == 0)
                    noExiste = false;
                if(noExiste)
                    System.out.println("Opcion invalida, el codigo no esta registrado");
                    entrada.nextLine();
                }while(noExiste);
                //guarda la posicion del curso en el Arraylist
                if(cursoCodigo != 0){
                    cursoPos = Curso.getCursoPos(cursoCodigo);
                    System.out.print("\nQue quieres hacer con el curso: " + Main.cursos.get(cursoPos).getAsignatura() + "\n(1) Enviar proyectos (2) Ver Comunicados (3) Salir: ");
                    opcion = entrada.nextInt();
                }
                switch (opcion) {
                    case 1:
                        //ver_Proyectos(cursoPos);
                        enviar_Proyectos(cursoPos);
                        break;

                    case 2:
                        ver_Comentarios(cursoPos);
                        break;

                    case 3:
                    
                    case 0:
                        System.out.println("Modulo de cursos finalizado");
                        break;
                    default:
                        System.out.println("Opcion invalida");
                        break;
                }
            } 
            catch (InputMismatchException e)
            {
                System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                entrada.nextLine();
                opcion = -1;
            } 
        } while (opcion!=3 && opcion != 0);//Se verifica que se haya digitado una de las opciones
    }

    public void ior_cursos() throws IOException{
        int opcion = 0;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        System.out.println("Inscribir o Retirar cursos");
        System.out.println("Los cursos ofrecidos son:");
        System.out.println();
        for (int i = 0; i < Main.cursos.size(); i++)
        {
            Main.cursos.get(i).imprimir();
        }
        System.out.println();
        do
        {
            try 
            {
                System.out.print("\nQuieres (1) Inscribir Curso (2) Retirar Curso (3) Salir: ");
                opcion = entrada.nextInt();
                switch (opcion) {
                    case 1:
                        ins_Curso();
                        break;
                    case 2:
                        ret_Curso();
                        break;
                    case 3:
                        System.out.println("Modulo de Inscribir o Retirar cursos finalizado");
                        break;
                    default:
                        System.out.println("Opcion incorrecta");
                        break;
                }
            } 
            catch (InputMismatchException e) 
            {
                entrada.nextLine();
                System.out.println("ERROR: POR FAVOR ESCRIBIR UN NUMERO");
                opcion = -1;
            } 
        } while (opcion!=3);//Se verifica que se haya digitado una de las opciones
    }
    
    public void enviar_Proyectos(int cursoPos) {
        // Esta funcion lee los projectos que estan asociados al curso
        String asignacion;
        Scanner scanner = new Scanner(System.in);
        System.out.println("\nDigite el nombre de la asignación que desea entregar: ");
        asignacion = scanner.nextLine();
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");

        Main.cursos.get(cursoPos).proyectos.add("Estudiante: " + getNombre() + "\nAsignación: " + asignacion
                + "\nFecha: " + dtf.format(LocalDateTime.now()));
    }

    public void ver_Comentarios(int cursoPos){
        //Esta funcion lee los comunicados que estan asociados al curso
        System.out.println("\nLos Comunicados del curso: " + Main.cursos.get(cursoPos).getAsignatura());
        Main.cursos.get(cursoPos).imprimirComunicados();
    }

    public void ins_Curso() throws IOException{
        /*
        La idea aqui es recorrer todos los cursos creados que no son iguales a las que ya tienen y presentarlos para inscribirlo
        */ 
        int cursoCodigo;
        boolean existeGeneral, existeLocal;
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        //Imprimir los cursos que actualmente no tiene
        System.out.println("Los cursos que puedes inscribir son:");
        boolean checker = true;
        if(clases.size() != 0){
            for(int x = 0; x < Main.cursos.size(); x++){
                for(int y = 0; y < clases.size(); y++){
                    if(Main.cursos.get(x).getCodigo() == clases.get(y))
                        checker = false;
                }
                if(checker){
                    Main.cursos.get(x).imprimir();
                    checker = false;
                }
            }
        }
        else{
            for(int x = 0; x < Main.cursos.size(); x++){
                Main.cursos.get(x).imprimir();
            }
        }

        try{
            do {
                // Eligir un curso que no tiene y que existe
                System.out.print("\nCual curso quieres inscribir o digite 0 para salir: ");
                cursoCodigo = entrada.nextInt();
                existeGeneral = Curso.verificarCursoGlobal(cursoCodigo);
                existeLocal = Curso.verificarCurso(cursoCodigo, clases);
                if(cursoCodigo != 0){
                    if(!existeGeneral)
                        System.out.println("Opcion invalida, no existe");
                    if(existeLocal)
                        System.out.println("Opcion invalida, curso ya inscrito");
                    if(existeGeneral && !existeLocal){
                        clases.add(cursoCodigo);
                        System.out.println("Curso agregado");
                    }
                }
                if(cursoCodigo == 0){
                    existeGeneral = true;
                    existeLocal = false;
                }
            }while(!(existeGeneral && !existeLocal));
        }
        catch (InputMismatchException e) 
            {
                //Poner en el log de excepciones
            } 
        ArchivoEstudiante.sobreescribir();
    }

    public void ret_Curso() throws IOException{
        /*
         retirar el curso que escoge para eliminarlo
        */ 
        int cursoCodigo;
        boolean existeLocal;
        System.out.print("Cual curso quieres eliminar?: ");
        Scanner entrada = new Scanner(System.in);//Se crea un scanner para el input
        try{
            do{
                cursoCodigo = entrada.nextInt();
                existeLocal = Curso.verificarCurso(cursoCodigo, clases);
                if(!existeLocal)
                    System.out.println("Opcion invalida, el curso no esta inscrito");
                else {
                    Integer codigox = cursoCodigo;
                    clases.remove(codigox);
                    System.out.println("Curso Eliminado");    
                }
            }while(!existeLocal);
        }
        catch (InputMismatchException e) 
            {
                //Poner en el log de excepciones
            } 
        ArchivoEstudiante.sobreescribir();
    }
}
