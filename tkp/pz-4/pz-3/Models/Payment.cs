namespace pz_3.Models;

public class Payment
{
    public double Principal { get; set; }
    public double Rate { get; set; }
    public double Term { get; set; }
    public double Result { get; private set; }

    public void Calculate()
    {
        var rate = Rate / 100;
        var tmp = Math.Pow(1 + rate / 12, Term);
        Result = Principal * (rate / 12 * tmp / (tmp - 1));
    }
}