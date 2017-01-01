package agm.andruino.arduinoconnect;

import android.app.Dialog;
import android.app.DialogFragment;
import android.app.DatePickerDialog;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.DatePicker;

import java.util.Calendar;


public class DatePickerFragment extends DialogFragment implements DatePickerDialog.OnDateSetListener{

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState){

        //Utiliza la fecha actual como valor por defecto para el selector
        final Calendar c = Calendar.getInstance();
        int day = c.get(Calendar.DAY_OF_MONTH);
        int month = c.get(Calendar.MONTH);
        int year = c.get(Calendar.YEAR);

        //Crea y devuelve una nueva instancia de DatePickerDialog
        return new DatePickerDialog(getActivity(),this, year, month,day);
    }

    //Meotodo llamado al seleccionar la hora
    public void onDateSet(DatePicker view, int year, int month, int dayOfMonth){

        String cdate = "";
        int fixedMonth = month+1;

        if (dayOfMonth < 10)
            cdate = "0";

        cdate = cdate + dayOfMonth + "/";

        if (fixedMonth < 10)
            cdate = cdate + "0";

        cdate = cdate + fixedMonth + "/";

        if (year%100 < 10)
            cdate = cdate + "0";

        cdate = cdate + year%100;

        TextView date = (TextView) getActivity().findViewById(R.id.Date);
        date.setText(cdate);
    }
}