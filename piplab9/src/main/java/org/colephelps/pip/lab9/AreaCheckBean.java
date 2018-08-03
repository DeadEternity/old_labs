package org.colephelps.pip.lab9;

import org.primefaces.model.DefaultStreamedContent;
import org.primefaces.model.StreamedContent;
import sun.awt.image.ByteArrayImageSource;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;
import javax.faces.bean.ViewScoped;
import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;

@ManagedBean(name="areaCheck")
@SessionScoped
public class AreaCheckBean implements Serializable {
    private Double y;
    private Double r;
    private static ArrayList<Punto> puntoList = new ArrayList<>();
    private StreamedContent image;
    private BufferedImage bimage;
    private Double hiddenX;
    private Boolean x1 = false;
    private Boolean x2 = false;
    private Boolean x3 = false;
    private Boolean x4 = false;
    private Boolean x5 = false;
    private Boolean x6 = false;
    private Boolean x7 = false;

    public Double getHiddenX() {
        return hiddenX;
    }

    public StreamedContent getImage() {
        return image;
    }

    public Double getY() {
        return y;
    }

    public Double getR() {
        return r;
    }

    public Boolean getX1() {
        return x1;
    }

    public Boolean getX2() {
        return x2;
    }

    public Boolean getX3() {
        return x3;
    }

    public Boolean getX4() {
        return x4;
    }

    public Boolean getX5() {
        return x5;
    }

    public Boolean getX6() {
        return x6;
    }

    public Boolean getX7() {
        return x7;
    }


    public ArrayList<Punto> getPuntoList() {
        return puntoList;
    }

    public void setHiddenX(Double hiddenX) {
        this.hiddenX = hiddenX;
    }

    public void setY(Double y) {
        this.y = y;
    }

    public void setR(Double r) {
        this.r = r;
    }

    public void setX1(Boolean x1) {
        this.x1 = x1;
    }

    public void setX2(Boolean x2) {
        this.x2 = x2;
    }

    public void setX3(Boolean x3) {
        this.x3 = x3;
    }

    public void setX4(Boolean x4) {
        this.x4 = x4;
    }

    public void setX5(Boolean x5) {
        this.x5 = x5;
    }

    public void setX6(Boolean x6) {
        this.x6 = x6;
    }

    public void setImage(StreamedContent image) {
        this.image = image;
    }

    public void setX7(Boolean x7) {
        this.x7 = x7;
    }

    public AreaCheckBean() {
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            BufferedImage img = ImageIO.read(new File("/home/colephelps/IdeaProjects/piplab9/src/main/webapp/resources/pictures/areas.png"));
            ImageIO.write(img, "png", baos);
            this.bimage = img;
            this.image = new DefaultStreamedContent(new ByteArrayInputStream(baos.toByteArray()), "image/png");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void clear() {
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            BufferedImage img = ImageIO.read(new File("/home/colephelps/IdeaProjects/piplab9/src/main/webapp/resources/pictures/areas.png"));
            ImageIO.write(img, "png", baos);
            this.bimage = img;
            this.image = new DefaultStreamedContent(new ByteArrayInputStream(baos.toByteArray()), "image/png");
        } catch (Exception e) {
            e.printStackTrace();
        }
        puntoList.clear();
    }

    private String isHit(Double x, Double y, Double r) {
        if(x <= 0 && y >= 0 && y <= r && x >= -r) return "IN";
        if(x >= 0 && y >= 0 && y <= r && x <= r && x + y <= r) return "IN";
        if(x <= 0 && y <= 0 && y >= -r/2 && x >= -r/2 && x*x + y*y <= r*r/4) return "IN";
        return "OUT";
    }

    public void addPunto() {
        if(r == null) return;
        if(!x1 && !x2 && !x3 && !x4 && !x5 && !x6 && !x7 && hiddenX == null)
            return;
        if(y == null) return;

        if(hiddenX != null) {
            Punto p = new Punto(hiddenX, y, r, isHit(hiddenX, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
            hiddenX = null;
            return;
        }
        if(x1) {
            Punto p = new Punto(-3d, y, r, isHit(-3d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x2) {
            Punto p = new Punto(-2d, y, r, isHit(-2d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x3) {
            Punto p = new Punto(-1d, y, r, isHit(-1d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x4) {
            Punto p = new Punto(0d, y, r, isHit(0d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x5) {
            Punto p = new Punto(1d, y, r, isHit(1d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x6) {
            Punto p = new Punto(2d, y, r, isHit(2d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
        if(x7) {
            Punto p = new Punto(3d, y, r, isHit(3d, y, r));
            puntoList.add(p);
            addPuntoToImage(p);
        }
    }

    private void addPuntoToImage(Punto p) {
        Graphics2D g = this.bimage.createGraphics();
        Double a = p.getX() * 80 / p.getR();
        Double b = p.getY() * 80 / p.getR();
        int xCoord = 104 + a.intValue();
        int yCoord = 108 - b.intValue();
        if(p.getIsHit().equals("IN")) g.setColor(Color.green);
        else g.setColor(Color.red);
        g.fillOval(xCoord, yCoord, 5, 5);

        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ImageIO.write(this.bimage, "png", baos);
            this.image = new DefaultStreamedContent(new ByteArrayInputStream(baos.toByteArray()), "image/png");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
