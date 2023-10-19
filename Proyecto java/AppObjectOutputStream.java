import java.io.*;

//Esta clase es utilizada para hacer un cambio en el metodo writeStreamheader que daña la escritura al final del fichero
public class AppObjectOutputStream extends ObjectOutputStream
{
    public AppObjectOutputStream(OutputStream out) throws IOException {
        super(out);
    }
    protected void writeStreamHeader() throws IOException {
        //Do not write a header
    }
}
