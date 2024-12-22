using System;
using System.Web.UI;

namespace Wintellect
{
    public partial class AutoCounterPage : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                Output.Text = "";
            }
        }

        protected void OnDecrement(object sender, EventArgs e)
        {
            UpdateOutput();
        }

        protected void OnIncrement(object sender, EventArgs e)
        {
            UpdateOutput();
        }

        protected void OnCountChanged(object sender, EventArgs e)
        {
            UpdateOutput();
        }

        protected void CalculateAverage(object sender, EventArgs e)
        {
            int total = Subject1Counter.Count + Subject2Counter.Count + Subject3Counter.Count;
            double average = total / 3.0;
            Output.Text = "Средний балл: " + average.ToString("F2");
        }

        private void UpdateOutput()
        {
            Output.Text = $"Баллы: {Subject1Counter.Count}, {Subject2Counter.Count}, {Subject3Counter.Count}";
        }
    }
}

