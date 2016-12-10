package agm.andruino.arduinoconnect;

import android.content.Context;
import android.widget.LinearLayout;
import android.widget.TextView;

public class DeviceView extends LinearLayout {

    private TextView name;
    private TextView mac;

    public DeviceView(Context context) {
        super(context);
        inflate(context, R.layout.device_view, this);

        //Guardamos los elementos gráficos que queremos modificar
        name = (TextView) findViewById(R.id.deviceName);
        mac = (TextView) findViewById(R.id.deviceMac);
    }

    //Permite establecer los valores a mostrar
    public void setDevice(Device device) {
        name.setText(""+device.getName());
        mac.setText(""+device.getAdress());
    }
}
