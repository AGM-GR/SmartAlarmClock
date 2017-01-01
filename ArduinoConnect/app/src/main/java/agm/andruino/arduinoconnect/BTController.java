package agm.andruino.arduinoconnect;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class BTController {

    //Instancia de la clase
    private static BTController ourInstance = new BTController();

    // SPP UUID service
    private static final UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    //Variables de la clase
    private String address = "";
    private InputStream mmInStream = null;
    private OutputStream mmOutStream = null;
    private BluetoothAdapter BTAdapter = null;
    private BluetoothSocket BTSocket = null;

    //Devuelve la instancia
    public static BTController getInstance() {
        return ourInstance;
    }

    //Constructor vacío
    private BTController() { BTAdapter = BluetoothAdapter.getDefaultAdapter(); }

    //Inicializa el socket bluetooth
    public boolean initialice(String adress) {

        //Guarda la dirección
        this.address = adress;

        //Crea el dispositivo bluetooth con el MAC address
        BluetoothDevice device = BTAdapter.getRemoteDevice(address);

        //Crea el socket
        try {
            BTSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            return false;
        }

        // Establece el socket Bluetooth
        try {

            BTSocket.connect();

        } catch (IOException e) {
            try {
                close();
                return false;
            }
            catch (IOException e2) { return false; }
        }

        //Establece los Stream de comunicación
        InputStream tmpIn = null;
        OutputStream tmpOut = null;

        try {
            //Crea los I/O streams para la conexión
            tmpIn = BTSocket.getInputStream();
            tmpOut = BTSocket.getOutputStream();
        } catch (IOException e) { return false; }

        mmInStream = tmpIn;
        mmOutStream = tmpOut;

        return true;
    }


    //Cierra el socket
    public void close() throws IOException {

        if (BTSocket != null) {

            //Cierra el socket

            BTSocket.close();

            //Limpia todas las variables
            address = "";
            mmInStream = null;
            mmOutStream = null;
            BTSocket = null;
        }
    }

    //Metodo de lectura
    public String read() {
        byte[] buffer = new byte[250];
        int bytes = 0;
        String message = "";
        String received = "";
        boolean messageReceived = false;

        while (!messageReceived) {

            try {
                //Lee los bytes del stream de entrada
                bytes = mmInStream.read(buffer);
                received = new String(buffer, 0, bytes);

            } catch (IOException e) { continue; }

            message = message + received;

            //Si contiene la cadena entera
            if (message.contains("#") && message.contains("$")) {
                message = message.substring(message.indexOf("#")+1, message.indexOf("$"));
                messageReceived = true;
            }
            else if (!message.contains("#"))
                message = "";
        }

        //Devuelve un OK
        write("OK");

        return message;
    }

    //Metodo de escritura
    public boolean write(String input) {
        //Convierte los String en bytes
        byte[] msgBuffer = input.getBytes();
        try {
            //Escribe los bytes en la conexión BT por el outstream
            mmOutStream.write(msgBuffer);
        } catch (IOException e) {
            return false;
        }

        return true;
    }


    public void checkBTConnection (Activity activity_caller) {

        boolean conexion = write("OK");

        if (!conexion)
            activity_caller.finish();
    }

    //Función para consultar el adaptador
    public BluetoothAdapter getAdapter() {

        return BTAdapter;
    }


    //Función para clear una conexión segura saliente con el BT usando UUID
    static final public BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {

        return  device.createRfcommSocketToServiceRecord(BTMODULEUUID);
    }


    // Comprueba le estado del Bluetooth y si está encendido
    static final public void checkBTState(Activity activity_caller) {

        if(ourInstance.getAdapter()==null) {
            Toast.makeText(activity_caller.getBaseContext(), "El dispositivo no soporta Bluetooth", Toast.LENGTH_SHORT).show();
        } else {
            if (!ourInstance.getAdapter().isEnabled()) {

                //Pide al usuario encender el Bluetooth
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                activity_caller.startActivityForResult(enableBtIntent, 1);
            }
        }
    }


    //Metodo para generar un código para que Arduino pueda entenderlo dado una clave un dato
    static final public String generarCodigo(String clave, String dato) {

        String codigo = dato;

        while (codigo.length()<3)
            codigo = "0" + codigo;

        codigo = "#" + clave + codigo + "$";

        return codigo;
    }
}
