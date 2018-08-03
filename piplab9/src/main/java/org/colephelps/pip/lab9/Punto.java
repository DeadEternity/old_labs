package org.colephelps.pip.lab9;

public class Punto {
    private Double x;
    private Double y;
    private Double r;
    private String isHit;

    public Punto(Double x, Double y, Double r, String isHit) {
        this.x = x;
        this.y = y;
        this.r = r;
        this.isHit = isHit;
    }

    public Double getX() {
        return x;
    }

    public Double getY() {
        return y;
    }

    public Double getR() {
        return r;
    }

    public String getIsHit() {
        return isHit;
    }

    public void setX(Double x) {
        this.x = x;
    }

    public void setY(Double y) {
        this.y = y;
    }

    public void setR(Double r) {
        this.r = r;
    }

    public void setIsHit(String isHit) {
        this.isHit = isHit;
    }
}
