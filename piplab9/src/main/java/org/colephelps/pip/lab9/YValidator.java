package org.colephelps.pip.lab9;

import javax.faces.application.FacesMessage;
import javax.faces.component.UICommand;
import javax.faces.component.UIComponent;
import javax.faces.context.FacesContext;
import javax.faces.validator.FacesValidator;
import javax.faces.validator.Validator;
import javax.faces.validator.ValidatorException;
import java.util.Objects;

/**
 * Created by colephelps on 3/21/17.
 */
@FacesValidator("yValidator")
public class YValidator implements Validator{

    public void validate(FacesContext facesContext, UIComponent uiComponent, Object value) throws ValidatorException {
            if(new Double(value.toString()) <= -3 || new Double(value.toString())>= 3) {
                FacesMessage msg = new FacesMessage("Validation failed.","Y must be in (-3;3)");
                msg.setSeverity(FacesMessage.SEVERITY_ERROR);
                throw new ValidatorException(msg);
            }
    }
}
