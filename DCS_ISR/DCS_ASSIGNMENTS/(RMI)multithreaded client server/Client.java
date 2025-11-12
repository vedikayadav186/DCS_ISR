import java.rmi.*;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws Exception {
        Chat stub = (Chat) Naming.lookup("rmi://localhost/chat");
        Scanner sc = new Scanner(System.in);

        while(true) {
            System.out.print("Enter message: ");
            String msg = sc.nextLine();
            if(msg.equalsIgnoreCase("exit")) break;

            // This remote call is handled on different thread in server
            String reply = stub.sendMessage(msg);
            System.out.println(reply);
        }
    }
}
