<%@ WebService Language="C#" Class="CalcService" %>

using System.Web.Services;

[WebService(Name = "Calculator Web Service",
    Description = "Простые вычисления через ВЭБ")]
class CalcService
{
    [WebMethod(Description = "Вычисление суммы двух целых чисел")]
    public int Add(int a, int b)
    {
        return a + b;
    }

    [WebMethod(Description = "Вычисление разности между двумя целыми числами")]
    public int Subtract(int a, int b)
    {
        return a - b;
    }
}