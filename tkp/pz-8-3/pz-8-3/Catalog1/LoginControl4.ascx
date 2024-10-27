<%@ Control Inherits="LoginBase" %>

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