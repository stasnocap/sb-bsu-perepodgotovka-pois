<%@ Register TagPrefix="user" TagName="LoginControl"
  src="LoginControl4.ascx" %>

<html>
  <body>
    <h1>User Control Demo 4</h1>
    <hr>
    <form runat="server">
      <user:LoginControl ID="MyLogin" BackColor="#ccccff"
        OnLogin="OnLoginUser" RunAt="server" />
    </form>
    <hr>
    <h3><asp:Label ID="Output" RunAt="server" /></h3>
  </body>
</html>

<script language="C#" runat="server">
  void OnLoginUser (Object sender, LoginEventArgs e)
  {
      if (e.IsValid)
          Output.Text = "Hello, " + MyLogin.UserName;
      else {
          Output.Text = "Invalid login";
          MyLogin.UserName = "";
          MyLogin.Password = "";
      }
  }
</script>