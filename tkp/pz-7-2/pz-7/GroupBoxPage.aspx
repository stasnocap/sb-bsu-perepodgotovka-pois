<html>
  <body>
    <form runat="server">
      <asp:CheckBox ID="Toggle" Text="Show colors" 
        OnCheckedChanged="OnToggle" AutoPostBack="true"
        Checked="true" RunAt="server" /><br>
      <win Text="Colors" ID="MyGroupBox" RunAt="server">
        <asp:RadioButtonList RunAt="server">
          <asp:ListItem Text="Red" Selected="true" RunAt="server" />
          <asp:ListItem Text="Green" RunAt="server" />
          <asp:ListItem Text="Blue" RunAt="server" />
        </asp:RadioButtonList>
      </win>
    </form>
  </body>
</html>

<script language="C#" runat="server">
  void OnToggle (Object sender, EventArgs e)
  {
      MyGroupBox.Visible = Toggle.Checked;
  }
</script>