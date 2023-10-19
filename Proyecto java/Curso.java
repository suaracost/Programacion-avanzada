import java.io.Serializable;
import java.util.ArrayList;

public class Curso implements Serializable
{
    //Atributos
    private static final long serialVersionUID = 1L; // Indica cual es la versión de la clase
    int codigo;
    String asignatura; //nombre
    String profesor; 
    ArrayList<String> comunicados;
    ArrayList<String> proyectos;
    
    public Curso(int codigo, String asignatura, String profesor) {
        this.codigo = codigo;
        this.asignatura = asignatura;
        this.profesor = profesor;
        comunicados = new ArrayList<String>();
        proyectos = new ArrayList<String>();
    }

    public int getCodigo() {
        return codigo;
    }

    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }

    public String getAsignatura() {
        return asignatura;
    }

    public void setAsignatura(String asignatura) {
        this.asignatura = asignatura;
    }

    public String getProfesor() {
        return profesor;
    }

    public void setProfesor(String profesor) {
        this.profesor = profesor;
    }

    public ArrayList<String> getComunicados() {
        return comunicados;
    }

    public void setComunicados(ArrayList<String> comunicados) {
        this.comunicados = comunicados;
    }

    public ArrayList<String> getProyectos() {
        return proyectos;
    }

    public void setProyectos(ArrayList<String> proyectos) {
        this.proyectos = proyectos;
    }

    public void imprimir()
    {
        System.out.println("Codigo: "+codigo+", Asignatura: "+asignatura+" Profesor: "+profesor);
    }
    public void imprimirProyectos(){
        for(int x = 0; x < proyectos.size(); x++)
            System.out.println("Proyecto "+x+": "+proyectos.get(x));
    }
    public void imprimirComunicados(){
        for(int x = 0; x < comunicados.size(); x++){
            System.out.println("Comunicado "+x+": "+comunicados.get(x)); 
        }
    }

    public static boolean verificarCurso(int cursoCodigo, ArrayList<Integer> clases) {
        for (int x = 0; x < clases.size(); x++) {
            if (cursoCodigo == clases.get(x))
                return true;
        }
        return false;
    }
    
    public static boolean verificarCursoGlobal(int cursoCodigo) {
        for (int x = 0; x < Main.cursos.size(); x++) {
            if (cursoCodigo == Main.cursos.get(x).getCodigo())
                return true;
        }
        return false;
    }
    public static int getCursoPos(int cursoCodigo){
        for(int x = 0; x < Main.cursos.size(); x++){
            if(cursoCodigo == Main.cursos.get(x).getCodigo())
                return x;
        }
        return 0;
    }
}
