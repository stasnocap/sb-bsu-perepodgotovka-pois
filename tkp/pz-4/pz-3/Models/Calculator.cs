namespace pz_3.Models;

public class Calculator
{
    public decimal Value1 { get; set; }
    public decimal Value2 { get; set; }
    public CalculatorAction Action { get; set; }
    public decimal Result { get; private set; }

    public void Calculate()
    {
        Result = Action switch
        {
            CalculatorAction.Add => Value1 + Value2,
            CalculatorAction.Subtract => Value1 - Value2,
            CalculatorAction.Multiply => Value1 * Value2,
            CalculatorAction.Divide => Value1 / Value2,
            CalculatorAction.None => throw new ArgumentOutOfRangeException(),
            _ => throw new NotImplementedException()
        };
    }
}

