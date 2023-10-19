import java.io.Serializable;
import java.util.ArrayList;

public abstract class Usuario implements Serializable
{
    //Atributos
    private static final long serialVersionUID = 1L; // Indica cual es la versión de la clase
    String usuario;
    String contrasena;
    String nombre;
    ArrayList<Integer> clases;
    
    
    
    public Usuario(String usuario, String contrasena, String nombre) {
        this.usuario = usuario;
        this.contrasena = contrasena;
        this.nombre = nombre;
        this.clases = new ArrayList<Integer>();
    }

    public abstract void menu1();

    public String getUsuario() {
        return usuario;
    }
    public void setUsuario(String usuario) {
        this.usuario = usuario;
    }
    public String getContrasena() {
        return contrasena;
    }
    public void setContrasena(String contrasena) {
        this.contrasena = contrasena;
    }
    public String getNombre() {
        return nombre;
    }
    public void setNombre(String nombre) {
        this.nombre = nombre;
    }
    
    
    public void imprimir()
    {
        System.out.println("Usuario: "+usuario);
    }

    public ArrayList<Integer> getClases() {
        return clases;
    }

    public void setClases(ArrayList<Integer> clases) {
        this.clases = clases;
    }

    //Metodos
    //Metodo constructor


    
}