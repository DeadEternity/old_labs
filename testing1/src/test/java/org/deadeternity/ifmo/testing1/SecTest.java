package org.deadeternity.ifmo.testing1;

import org.junit.Assert;
import org.junit.Test;

import java.math.BigDecimal;

public class SecTest extends Assert {
    @Test
    public void boundaryPointsNull() {
        for(int i = -5; i < 5; i++) {
            BigDecimal result = SecSeries.getValue(Math.PI / 2 + Math.PI * i);
            assertNull(result);
        }
    }

    @Test
    public void boundaryPoints1() {
        for(int i = -5; i < 5; i++) {
            BigDecimal result = SecSeries.getValue( 0 + Math.PI * 2 * i);
            assertEquals(new BigDecimal("1"), result);
        }
    }

    @Test
    public void boundaryPointsMinus1() {
        for(int i = -5; i < 5; i++) {
            BigDecimal result = SecSeries.getValue( Math.PI + Math.PI * 2 * i);
            assertEquals(new BigDecimal("-1"), result);
        }
    }

    @Test
    public void eqClass0toPi4() {
        BigDecimal result1 = SecSeries.getValue(Math.PI/4);
        Double result1real = 1/Math.cos(Math.PI/4);
        BigDecimal result2 = SecSeries.getValue(Math.PI/8);
        Double result2real = 1/Math.cos(Math.PI/8);
        BigDecimal result3 = SecSeries.getValue(Math.PI/16);
        Double result3real = 1/Math.cos(Math.PI/16);
        assertEquals(new BigDecimal(result1real.toString()).setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result1.setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result2real.toString()).setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result2.setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result3real.toString()).setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result3.setScale(8, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
    }

    @Test
    public void eqClassPi4toPi3() {
        BigDecimal result1 = SecSeries.getValue(Math.PI/3);
        Double result1real = 1/Math.cos(Math.PI/3);
        BigDecimal result2 = SecSeries.getValue(Math.PI/3.4);
        Double result2real = 1/Math.cos(Math.PI/3.4);
        BigDecimal result3 = SecSeries.getValue(Math.PI/3.8);
        Double result3real = 1/Math.cos(Math.PI/3.8);
        assertEquals(new BigDecimal(result1real.toString()).setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result1.setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result2real.toString()).setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result2.setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result3real.toString()).setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result3.setScale(5, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
    }

    @Test
    public void eqClassPi3to2Pi5() {
        BigDecimal result1 = SecSeries.getValue(Math.PI/2.5);
        Double result1real = 1/Math.cos(Math.PI/2.5);
        BigDecimal result2 = SecSeries.getValue(Math.PI/2.7);
        Double result2real = 1/Math.cos(Math.PI/2.7);
        BigDecimal result3 = SecSeries.getValue(Math.PI/2.9);
        Double result3real = 1/Math.cos(Math.PI/2.9);
        assertEquals(new BigDecimal(result1real.toString()).setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result1.setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result2real.toString()).setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result2.setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
        assertEquals(new BigDecimal(result3real.toString()).setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros(),
                result3.setScale(1, BigDecimal.ROUND_HALF_UP).stripTrailingZeros());
    }

    @Test
    public void eqClass2Pi5toLessThanPi2() {
        BigDecimal result1 = SecSeries.getValue(Math.PI/2 - 0.1);
        Double result1real = 1/Math.cos(Math.PI/2 - 0.1);
        BigDecimal result2 = SecSeries.getValue(Math.PI/2 - 0.2);
        Double result2real = 1/Math.cos(Math.PI/2 - 0.2);
        BigDecimal result3 = SecSeries.getValue(Math.PI/2 - 0.05);
        Double result3real = 1/Math.cos(Math.PI/2 - 0.05);
        assertTrue(new BigDecimal(result1real.toString()).doubleValue() / result1.doubleValue() > 0.8);
        assertTrue(new BigDecimal(result2real.toString()).doubleValue() / result2.doubleValue() > 0.8);
        assertTrue(new BigDecimal(result3real.toString()).doubleValue() / result3.doubleValue() > 0.8);
    }

}
