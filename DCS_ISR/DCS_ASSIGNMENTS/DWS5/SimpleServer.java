import java.io.*;
import java.net.*;

public class SimpleServer {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server started. Waiting for client...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected.");

        BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

        String clientMessage;
        while ((clientMessage = input.readLine()) != null) {
            System.out.println("Received: " + clientMessage);

            // Expecting format: "number1 number2"
            String[] parts = clientMessage.trim().split("\\s+");
            if (parts.length == 2) {
                try {
                    int a = Integer.parseInt(parts[0]);
                    int b = Integer.parseInt(parts[1]);
                    int sum = a + b;
                    output.println("Sum is: " + sum);
                } catch (NumberFormatException e) {
                    output.println("Invalid input. Please send two integers.");
                }
            } else {
                output.println("Please send exactly two numbers separated by space.");
            }
        }

        socket.close();
        serverSocket.close();
    }
}