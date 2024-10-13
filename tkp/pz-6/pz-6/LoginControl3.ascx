<table id="MyTable" cellpadding="4" runat="server">
  <tr>
    <td>User Name:</td>
    <td><asp:TextBox ID="MyUserName" RunAt="server" /></td>
  </tr>
  <tr>	
    <td>Password:</td>
    <td><asp:TextBox ID="MyPassword" TextMode="password"
      RunAt="server" /></td>
  </tr>
  <tr>
    <td></td>
    <td><asp:LinkButton Text="Log In" OnClick="OnLoginButtonClicked"
      RunAt="server" /></td>
  </tr>
</table>

<script language="C#" runat="server">
  public string BackColor
  {
      get { return MyTable.BgColor; }
      set { MyTable.BgColor = value; }
  }
 
  public string UserName
  {
      get { return MyUserName.Text; }
      set { MyUserName.Text = value; }
  }
 
  public string Password
  {
      get { return MyPassword.Text; }
      set { MyPassword.Text = value; }
  }

  public event EventHandler Login;

  void OnLoginButtonClicked (Object sender, EventArgs e)
  {
      if (Login != null && UserName.Length > 0 && Password.Length > 0)
          Login (this, new EventArgs ()); // Fire Login event
  }
</script>