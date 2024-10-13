using System;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;

public class LoginEventArgs
{
    private bool LoginValid;

    public LoginEventArgs (bool IsValid)
    {
        LoginValid = IsValid;
    }

    public bool IsValid
    {
        get { return LoginValid; }
    }
}

public class LoginBase : UserControl
{
    protected HtmlTable MyTable;
    protected TextBox MyUserName;
    protected TextBox MyPassword;

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

    public delegate void LoginEventHandler (Object sender,
        LoginEventArgs e);

    public event LoginEventHandler Login;

    public void OnLoginButtonClicked (Object sender, EventArgs e)
    {
        if (Login != null) {
            bool IsValid = (UserName.ToLower () == "stas" &&
                Password == "123");
            Login (this, new LoginEventArgs (IsValid));
        }
    }
}