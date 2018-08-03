package org.deadeternity.ifmo.testing1;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;

public class SecSeries {
    private static BigDecimal euler[] = {
            new BigDecimal("1"),
            new BigDecimal("0"),
            new BigDecimal("-1"),
            new BigDecimal("0"),
            new BigDecimal("5"),
            new BigDecimal("0"),
            new BigDecimal("-61"),
            new BigDecimal("0"),
            new BigDecimal("1385"),
            new BigDecimal("0"),
            new BigDecimal("-50521"),
            new BigDecimal("0"),
            new BigDecimal("2702765"),
            new BigDecimal("0"),
            new BigDecimal("-199360981"),
            new BigDecimal("0"),
            new BigDecimal("19391512145"),
            new BigDecimal("0"),
            new BigDecimal("-2404879675441"),
            new BigDecimal("0"),
            new BigDecimal("370371188237525"),
            new BigDecimal("0"),
            new BigDecimal("-69348874393137901"),
            new BigDecimal("0"),
            new BigDecimal("15514534163557086905"),
            new BigDecimal("0"),
            new BigDecimal("-4087072509293123892361"),
            new BigDecimal("0"),
            new BigDecimal("1252259641403629865468285"),
            new BigDecimal("0"),
            new BigDecimal("-441543893249023104553682821"),
            new BigDecimal("0"),
            new BigDecimal("177519391579539289436664789665"),
            new BigDecimal("0")
            // 	1, -1, 5, -61, 1385, -50521, 2702765, -199360981, 19391512145, -2404879675441, 370371188237525,
            // -69348874393137901, 15514534163557086905, -4087072509293123892361, 1252259641403629865468285,
            // -441543893249023104553682821, 177519391579539289436664789665
    };

    // -p/2 <= x <= p/2
    private static BigDecimal getCenterValue(double x) {
        BigDecimal value = new BigDecimal(0);
        if(x == Math.PI/2 || x == Math.PI/(-2)) return null;
        for(int i = 0; i <= 16; i++) {
            BigDecimal x2n = new BigDecimal(x).pow(i*2);
            BigDecimal f2n = new BigDecimal(factorial(new BigInteger(new Integer(2*i).toString())));
            BigDecimal e2n = euler[i*2];
            BigDecimal np = new BigDecimal("-1").pow(i);
            value = value.add(x2n.multiply(e2n).multiply(np).divide(f2n, 10, RoundingMode.HALF_UP));
        }
        return value.stripTrailingZeros();
    }

    //-p/2 <= x <= 3p/2
    private static BigDecimal getPeriodicValue(double x) {
        if(x > Math.PI/2) return getCenterValue(x-Math.PI).multiply(new BigDecimal("-1"));
        else return getCenterValue(x);
    }

    public static BigDecimal getValue(double x) {
        x = Math.abs(x) + Math.PI/2;
        x = x%(Math.PI*2);
        return getPeriodicValue(x-Math.PI/2);
    }

    private static BigInteger factorial(BigInteger value) {
        if(value.intValue() == 0) return new BigInteger("1");
        return value.multiply(factorial(value.add(new BigInteger("-1"))));
    }

    public static void main(String[] args) {
        double x = Math.PI/2 - 0.01;
        System.out.println(getValue(x));
        System.out.println(1/Math.cos(x));
        FibonacchiHeap heap = new FibonacchiHeap();
        heap.addNode(new FibonacchiHeapNode(5));
        System.out.println(heap.toString());
        heap.addNode(new FibonacchiHeapNode(15));
        System.out.println(heap.toString());
        heap.addNode(new FibonacchiHeapNode(25));
        System.out.println(heap.toString());
        heap.addNode(new FibonacchiHeapNode(45));
        heap.addNode(new FibonacchiHeapNode(35));
        System.out.println(heap.toString());
        heap.removeMin();
        System.out.println(heap.toString());
    }
}
