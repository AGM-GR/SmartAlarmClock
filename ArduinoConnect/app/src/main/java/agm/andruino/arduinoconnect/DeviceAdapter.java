package agm.andruino.arduinoconnect;

import android.widget.BaseAdapter;
import java.util.ArrayList;
import android.view.View;
import android.view.ViewGroup;

public class DeviceAdapter extends BaseAdapter {

    //ArrayList con todos los Devices a mostrar
    private ArrayList<Device> devices;

    public DeviceAdapter(ArrayList<Device> devices) {
        this.devices = devices;

        //Cada vez que cambiamos los elementos debemos noficarlo
        notifyDataSetChanged();
    }

    //Devuelve el numero de elementos
    public int getCount() {
        return devices.size();
    }

    //Devuelve el elemento de una posición
    public Object getItem(int position) {
        return devices.get(position);
    }

    //Devulve el ID del elemento (Generalmente no se usa)
    public long getItemId(int position) {
        return 0;
    }

    //Devuelve la vista de un elemento
    public View getView(int position, View convertView, ViewGroup parent) {

        //Si el contentView ya tiene un device, lo reutilizaremos con los nuevos datos
        // Si no crearemos uno nuevo
        DeviceView view;
        if (convertView == null)
            view = new DeviceView(parent.getContext());
        else
            view = (DeviceView) convertView;

        //Asignamos los valores del Device a mostrar
        view.setDevice(devices.get(position));

        return view;
    }
}
