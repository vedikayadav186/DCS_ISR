import java.rmi.*;

public class Server {
    public static void main(String[] args) throws Exception {
        ChatImpl obj = new ChatImpl();
        Naming.rebind("rmi://localhost/chat", obj);
        System.out.println("Server Ready...");
    }
}
//javac *.java
//rmiregistry
//java Server java client