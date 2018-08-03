package org.colephelps.pip.lab9;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.bean.ViewScoped;
import java.io.Serializable;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

@ManagedBean
@ViewScoped

public class WelcomePageBean implements Serializable {

    private DateFormat dateFormat = new SimpleDateFormat("dd/MM/YYYY HH:mm:ss");
    private Date date = new Date();
    private String dateString = dateFormat.format(this.date);

    public String getDateString() {
        return dateString;
    }

    public void refreshDate() {
        date = new Date();
        dateString = dateFormat.format(date);
    }
}
