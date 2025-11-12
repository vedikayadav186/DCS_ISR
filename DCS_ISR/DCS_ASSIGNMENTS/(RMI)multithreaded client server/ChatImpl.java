import java.rmi.*;
import java.rmi.server.*;

public class ChatImpl extends UnicastRemoteObject implements Chat {
    ChatImpl() throws RemoteException {}

    public String sendMessage(String msg) {
        System.out.println("Client says: " + msg + "  (Handled by: " + Thread.currentThread().getName() + ")");
        return "Server Received: " + msg;
    }
}
