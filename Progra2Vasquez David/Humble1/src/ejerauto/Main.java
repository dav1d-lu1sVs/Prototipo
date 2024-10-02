package ejerauto;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        Carro c1= new Carro();
        Carro c2= new Carro();

        c1.potencia = 2.5;
        c1.velocidad = 100;
        c2.potencia = 2.5;
        c2.velocidad = 100;
        System.out.println("|•La potencia de carro es "+c1.potencia);
        System.out.println("|•La velocidad del carro es "+c1.velocidad);
        c1.acelerar();
        c1.acelerar();
        System.out.println("|•La velocidad del carro es "+c1.velocidad);
        c1.frenar();
        System.out.println("|•La velocidad del carro es "+c1.velocidad);
        System.out.println("|•La potencia de carro es "+c1.potencia);
        System.out.println("------------------------------------");
        System.out.println("|•La potencia de carro es "+c2.potencia);
        System.out.println("|•La velocidad del carro es "+c2.velocidad);
    }
}