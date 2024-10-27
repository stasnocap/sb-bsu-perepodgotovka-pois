<%@ Register TagPrefix="win" Namespace="Wintellect" Assembly="pz_7" %>

<html>
  <body>
    <h1>AutoCounter Demo</h1>
    <hr>
    <form runat="server">
      <win:AutoCounter ID="MyCounter" Count="5"
        OnDecrement="OnDecrement" OnIncrement="OnIncrement"
        OnCountChanged="OnCountChanged" RunAt="server" />
        <br><br>
      <asp:Button Text="Submit" RunAt="server" />
    </form>
    <hr>
    <asp:Label ID="Output" RunAt="server" />
  </body>
</html>

<script language="c#" runat="server">
  void Page_Load (Object sender, EventArgs e)
  {
      Output.Text = "";
  }

  void OnDecrement (Object sender, EventArgs e)
  {
      Output.Text = "Count decremented to " + MyCounter.Count;
  }

  void OnIncrement (Object sender, EventArgs e)
  {
      Output.Text = "Count incremented to " + MyCounter.Count;
  }

  void OnCountChanged (Object sender, EventArgs e)
  {
      Output.Text = "Count changed to " + MyCounter.Count;
  }
</script>