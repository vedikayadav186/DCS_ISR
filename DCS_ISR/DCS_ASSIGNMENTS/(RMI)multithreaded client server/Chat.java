import java.rmi.*;

public interface Chat extends Remote {
    String sendMessage(String msg) throws RemoteException;
}
