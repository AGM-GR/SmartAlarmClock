package agm.andruino.arduinoconnect;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Toast;
import android.widget.ToggleButton;


public class Inicio extends AppCompatActivity {

    ToggleButton LEDBtn;
    EditText REDNum, GREENNum, BLUENum;
    SeekBar REDbar, GREENbar, BLUEbar;

    private BluetoothAdapter BTAdapter = null;
    private BluetoothSocket BTSocket = null;
    private StringBuilder recDataString = new StringBuilder();

    Handler bluetoothIn;
    final int handlerState = 0;

    private ConnectedThread mConnectedThread;

    // SPP UUID service - this should work for most devices
    private static final UUID BTMODULEUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    // String for MAC address
    private static String address = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_inicio);

        //Conectar Elementos Gráficos
        LEDBtn = (ToggleButton) findViewById(R.id.LEDButton);

        REDNum = (EditText) findViewById(R.id.REDNumber);
        REDbar = (SeekBar) findViewById(R.id.REDseek);

        GREENNum = (EditText) findViewById(R.id.GREENNumber);
        GREENbar = (SeekBar) findViewById(R.id.GREENseek);

        BLUENum = (EditText) findViewById(R.id.BLUENumber);
        BLUEbar = (SeekBar) findViewById(R.id.BLUEseek);

        //Obtener Adaptador BT
        BTAdapter = BluetoothAdapter.getDefaultAdapter();
        checkBTState();

        //Define el comportamiento de los botones
        LEDBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isCheked) {
                if (isCheked) {
                    //The toggle is enabled
                    mConnectedThread.write("#P$");
                    Toast.makeText(getBaseContext(), "LED Encendido", Toast.LENGTH_SHORT).show();
                } else {
                    //the toggle is disabled
                    mConnectedThread.write("#P$");
                    Toast.makeText(getBaseContext(), "LED Apagado", Toast.LENGTH_SHORT).show();
                }
            }
        });


        //Realiza modificaciones cuando la barra se mueve
        REDbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    REDNum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = generarCodigo('R', String.valueOf(seekBar.getProgress()));
                mConnectedThread.write(codigo);
            }
        });
        GREENbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    GREENNum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = generarCodigo('G', String.valueOf(seekBar.getProgress()));
                mConnectedThread.write(codigo);
            }
        });
        BLUEbar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                //Si la barra se mueve por el usuario, actualiza el valor en el input
                if (fromUser)
                    BLUENum.setText(String.valueOf(progress));
            }
            public void onStartTrackingTouch(SeekBar seekBar){}
            public void onStopTrackingTouch(SeekBar seekBar){

                //Cuando deja de moverse la barra, manda el color al bluetooth
                String codigo = generarCodigo('B', String.valueOf(seekBar.getProgress()));
                mConnectedThread.write(codigo);
            }
        });


        //Realiza modificaciones cuando el texto del input cambia
        REDNum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    REDNum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                REDbar.setProgress(num);
            }
        });
        GREENNum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    GREENNum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                GREENbar.setProgress(num);
            }
        });
        BLUENum.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}
            @Override
            public void afterTextChanged(Editable s) {

                int num = 0;
                //Si hay algun numero escrito lo almacena para procesarlo
                if (s.toString().length() > 0)
                    num = Integer.parseInt(s.toString());
                //Si se introduce un numero negativo se guarda el numero como 0
                if (num < 0) {
                    num = 0;
                    //Si se introduce un numero mayor de 255, el valor cambia automaticamente a 255
                } else if (num > 255) {
                    num = 255;
                    BLUENum.setText(String.valueOf(num));
                }
                //Establece el valor en la barra
                BLUEbar.setProgress(num);
            }
        });

        /*bluetoothIn = new Handler() {
            public void handleMessage(android.os.Message msg) {
                if (msg.what == handlerState) {                         //if message is what we want
                    String readMessage = (String) msg.obj;              // msg.arg1 = bytes from connect thread
                    recDataString.append(readMessage);                  //keep appending to string until ~
                    int endOfLineIndex = recDataString.indexOf("~");    // determine the end-of-line
                    if (endOfLineIndex > 0) {                           // make sure there data before ~
                        String dataInPrint = recDataString.substring(0, endOfLineIndex);    // extract string
                        //txtString.setText("Datos recibidos = " + dataInPrint);
                        int dataLength = dataInPrint.length();          //get length of data received
                        //txtStringLength.setText("Tamaño del String = " + String.valueOf(dataLength));

                        if (recDataString.charAt(0) == '#')                     //if it starts with # we know it is what we are looking for
                        {
                            String sensor0 = recDataString.substring(1, 5);     //get sensor value from string between indices 1-5
                            String sensor1 = recDataString.substring(6, 10);    //same again...
                            String sensor2 = recDataString.substring(11, 15);
                            String sensor3 = recDataString.substring(16, 20);

                            if (sensor0.equals("1.00"))
                                sensorView0.setText("Encendido"); //update the textviews with sensor values
                            else
                                sensorView0.setText("Apagado"); //update the textviews with sensor values
                            sensorView1.setText(sensor1);
                            sensorView2.setText(sensor2);
                            sensorView3.setText(sensor3);
                            //sensorView3.setText(" Sensor 3 Voltage = " + sensor3 + "V");
                        }
                        recDataString.delete(0, recDataString.length());      //clear all string data
                        // strIncom =" ";
                        dataInPrint = " ";
                    }
                }
            }
        };*/

    } //ENDONCREATE


    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {

        return  device.createRfcommSocketToServiceRecord(BTMODULEUUID);
        //creates secure outgoing connecetion with BT device using UUID
    }

    @Override
    public void onResume() {
        super.onResume();

        //Get MAC address from DeviceListActivity via intent
        Intent intent = getIntent();

        //Get the MAC address from the DeviceListActivty via EXTRA
        address = intent.getStringExtra(DeviceList.EXTRA_DEVICE_ADDRESS);

        //create device and set the MAC address
        //Log.i("ramiro", "adress : " + address);
        BluetoothDevice device = BTAdapter.getRemoteDevice(address);

        try {
            BTSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            Toast.makeText(getBaseContext(), "La creacción del Socket fallo", Toast.LENGTH_LONG).show();
        }
        // Establish the Bluetooth socket connection.
        try
        {
            BTSocket.connect();
        } catch (IOException e) {
            try
            {
                BTSocket.close();
            } catch (IOException e2)
            {
                //insert code to deal with this
            }
        }
        mConnectedThread = new ConnectedThread(BTSocket);
        mConnectedThread.start();

        //I send a character when resuming.beginning transmission to check device is connected
        //If it is not an exception will be thrown in the write method and finish() will be called
        mConnectedThread.write("x");
    }

    @Override
    public void onPause()
    {
        super.onPause();
        try
        {
            //Don't leave Bluetooth sockets open when leaving activity
            BTSocket.close();
        } catch (IOException e2) {
            //insert code to deal with this
        }
    }

    //Checks that the Android device Bluetooth is available and prompts to be turned on if off
    private void checkBTState() {

        if(BTAdapter==null) {
            Toast.makeText(getBaseContext(), "El dispositivo no soporta bluetooth", Toast.LENGTH_LONG).show();
        } else {
            if (BTAdapter.isEnabled()) {
            } else {
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, 1);
            }
        }
    }

    //create new class for connect thread
    private class ConnectedThread extends Thread {
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        //creation of the connect thread
        public ConnectedThread(BluetoothSocket socket) {
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                //Create I/O streams for connection
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) { }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
        }


        public void run() {
            byte[] buffer = new byte[256];
            int bytes;

            // Keep looping to listen for received messages
            while (true) {
                try {
                    bytes = mmInStream.read(buffer);    //read bytes from input buffer
                    String readMessage = new String(buffer, 0, bytes);
                    // Send the obtained bytes to the UI Activity via handler
                    bluetoothIn.obtainMessage(handlerState, bytes, -1, readMessage).sendToTarget();
                } catch (IOException e) {
                    break;
                }
            }
        }
        //write method
        public void write(String input) {
            byte[] msgBuffer = input.getBytes();    //converts entered String into bytes
            try {
                mmOutStream.write(msgBuffer);       //write bytes over BT connection via outstream
            } catch (IOException e) {
                //if you cannot write, close the application
                Toast.makeText(getBaseContext(), "La Conexión fallo", Toast.LENGTH_LONG).show();
                finish();

            }
        }
    }

    private String generarCodigo(char clave, String dato) {

        String codigo = dato;

        while (codigo.length()<3)
            codigo = "0" + codigo;

        codigo = "#" + clave + codigo + "$";

        return codigo;
    }
}