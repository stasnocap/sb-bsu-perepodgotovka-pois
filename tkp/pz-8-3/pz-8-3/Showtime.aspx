<html>
  <body>
    <h1>Showtime</h1>
    <hr>
    <form runat="server">
      Pick a show:<br>
      <asp:DropDownList ID="ShowName" RunAt="Server">
        <asp:ListItem Text="Посещение зоопарка" Selected="true" RunAt="server" />
        <asp:ListItem Text="Всей семьей идем в кукольный театр" RunAt="server" />
        <asp:ListItem Text="Наконец-то посетим ботанический сад" RunAt="server" />
        <asp:ListItem Text="Мама и папа идут в ресторан" RunAt="server" />
        <asp:ListItem Text="Мама и папа at home" RunAt="server" />
      </asp:DropDownList>
      <br><br>
      Pick a date:<br>
      <asp:Calendar
        ID="ShowDate"
        ShowGridLines="true"
        ForeColor="darkblue"
        SelectedDayStyle-BackColor="darkblue"
        SelectedDayStyle-ForeColor="white"
        SelectedDayStyle-Font-Bold="true"
        TitleStyle-BackColor="darkblue"
        TitleStyle-ForeColor="white"
        TitleStyle-Font-Bold="true"
        NextPrevStyle-BackColor="darkblue"
        NextPrevStyle-ForeColor="white"
        DayHeaderStyle-BackColor="beige"
        DayHeaderStyle-ForeColor="darkblue"
        DayHeaderStyle-Font-Bold="true"
        OtherMonthDayStyle-ForeColor="lightgray"
        OnSelectionChanged="OnDateSelected"
        OnDayRender="OnDayRender"
        RunAt="Server" />

        <asp:Calendar ID="Calendar1" runat="server"></asp:Calendar>
      <br />
      <asp:ImageButton ImageUrl="OrderBtn.gif" OnClick="OnOrder"
        RunAt="server" />
      <br><br><hr>
      <h3><asp:Label ID="Output" RunAt="server" /></h3>
    </form>
  </body>
</html>

<script language="C#" runat="server">
  void OnOrder (Object sender, ImageClickEventArgs e)
  {
      if (ShowDate.SelectedDate.Year > 1900)
          Output.Text = "Вы выбрали - " +
              ShowName.SelectedItem.Text + " на " +
              ShowDate.SelectedDate.ToLongDateString ();
      else
          Output.Text = "Пожалуйста, выберите дату!";
  }

  void OnDateSelected (Object sender, EventArgs e)
  {
      Output.Text = "";
  }

  void OnDayRender (Object sender, DayRenderEventArgs e)
  {
      e.Day.IsSelectable =
          (e.Day.Date.DayOfWeek == DayOfWeek.Friday ||
          e.Day.Date.DayOfWeek == DayOfWeek.Saturday) &&
          e.Day.Date >= DateTime.Today &&
          !e.Day.IsOtherMonth;

      if (e.Day.IsSelectable && e.Day.Date != ShowDate.SelectedDate)
          e.Cell.BackColor = System.Drawing.Color.Beige;
  }
</script>