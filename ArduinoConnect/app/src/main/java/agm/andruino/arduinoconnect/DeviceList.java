package agm.andruino.arduinoconnect;

import java.util.ArrayList;
import java.util.Set;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class DeviceList extends Activity {

    // Declara el AlertDialog para el status
    AlertDialog connectionStatus;

    // Constructores de dialogos
    AlertDialog.Builder notFound;
    AlertDialog.Builder loading;

    // EXTRA string para enviar a la actividad principal la dirección del modulo bt
    public static String EXTRA_DEVICE_ADDRESS = "device_address";

    // Controlador bluetooth y array de dispositivos
    private BTController BTcontroller = BTController.getInstance();
    private ArrayList<Device> PairedDevices = new ArrayList();

    //Al crear la actividad inicializa la lista de dispositivos y los AlertDialog
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_list);

        notFound = new AlertDialog.Builder(this)
                .setTitle("Ningun dispositivo encontrado")
                .setMessage("Empareja el dispositivo desde la configuración del telefono.");

        loading = new AlertDialog.Builder(this)
                .setTitle("Conectando ...")
                .setMessage("Espere unos segundos a que se conecte al dispositivo bluetooth");

        connectionStatus = notFound.create();
    }

    //Función Resume de la actividad
    @Override
    public void onResume() {

        super.onResume();

        // Limpia cualquier mensaje mostrado
        if (connectionStatus.isShowing())
            connectionStatus.dismiss();

        //Limpia la conexión bluetooth anterior
        BTcontroller.close();

        //Comprueba el estado del BT
        BTcontroller.checkBTState(this);

        // Obtiene los dispositivos ya conectados al bluetooth
        Set pairedDevices = BTcontroller.getAdapter().getBondedDevices();

        //Inicializa el array de dispositivos
        PairedDevices = new ArrayList();

        // Añade los dispositivos conectados al array
        if (pairedDevices.size() > 0) {
            for (Object device : pairedDevices) {
                PairedDevices.add(new Device(((BluetoothDevice)device).getName(), ((BluetoothDevice)device).getAddress()));
            }
        } else {
            connectionStatus = notFound.create();
            connectionStatus.show();
        }


        // Establece la vista, el adaptador y la funcion al hacer click de los elementos de la lista
        ListView pairedListView = (ListView) findViewById(R.id.paired_devices);
        pairedListView.setAdapter(new DeviceAdapter(PairedDevices));
        pairedListView.setOnItemClickListener(DeviceClickListener);

    }

    // OnItemClickListener para los dispositivos de la lista
    private OnItemClickListener DeviceClickListener = new OnItemClickListener() {
        public void onItemClick(AdapterView av, View v, int arg2, long arg3) {

            //Muestra alert con el mensaje cargando
            connectionStatus = loading.create();
            connectionStatus.show();

            // Obtiene la dirección MAC de la vista
            String address = ((TextView) v.findViewById(R.id.deviceMac)).getText().toString();

            //Inicia el bluetooth
            boolean iniciado = BTcontroller.initialice(address);

            if (iniciado) {

                // Inicia la siguiente acitividad mandandole un EXTRA que contiene la dirección MAC.
                Intent i = new Intent(DeviceList.this, Inicio.class);
                startActivity(i);
            }

        }
    };

}