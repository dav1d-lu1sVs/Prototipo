package ejerauto;

public class Carro {
 double potencia;
 double velocidad;

 public void acelerar(){
     velocidad += potencia;
 }
 public void frenar (){
     velocidad *= 0.5;
 }
}


