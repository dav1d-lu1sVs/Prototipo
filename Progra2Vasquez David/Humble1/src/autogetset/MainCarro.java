package autogetset;

import java.util.Scanner;

public class MainCarro {
    public static void main(String[] args) {
        Scanner sc =new Scanner(System.in);
        Carro c1= new Carro();
        double potencia;
        System.out.println("|•La potencia del carro es "+c1. getPotencia());
        System.out.println("|•La velocidad del carro es "+c1. getVelocidad());
        System.out.println("Ingrese la potencia del vehiculo: ");
        potencia =sc.nextDouble();
        c1.setPotencia(potencia);
        System.out.println("Ingrese la velocidad del vehiculo: ");
        c1.setVelocidad(sc.nextDouble());
        System.out.println("------------------------------------");
        System.out.println("|•La potencia del carro es "+c1. getPotencia()+"\n");
        System.out.println("|•La velocidad del carro es "+c1. getVelocidad());
    }


}