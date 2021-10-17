/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File3b;

/**
 *
 * @author anive
 */
public class Automobile {
   private int id;
   private String year;
   private String model, brand;
   
   public Automobile(){}
   
   public Automobile(String model, String brand, String year){
       this.model = model;
       this.brand = brand;
       this.year = year;
   }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getYear() {
        return year;
    }

    public void setYear(String year) {
        this.year = year;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }
   
   public String toString(){
       return "ID: "+this.id+"\nModelo: "+this.model+"\nMarca: "+this.brand+"\nAno: "+this.year+"\n";
   }
   
}
